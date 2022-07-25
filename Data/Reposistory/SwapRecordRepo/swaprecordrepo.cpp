#include "swaprecordrepo.h"

SwapRecordRepo::SwapRecordRepo( QObject *parent)  : QObject(parent)
{
    currentCheckingPosition =0;
    QObject::connect(&timeoutCheckingDb, &QTimer::timeout, this, &SwapRecordRepo::checkDataSending);
    timeoutCheckingDb.start(1000);
}
SwapRecordRepo* SwapRecordRepo:: getNewSwapRecordRepo()
{
    static SwapRecordRepo* self;
    if(self==nullptr){
        self=new SwapRecordRepo();
    }
    return self;
}

void SwapRecordRepo::createDb(LocalSQLiteDb *db)
{
    Database = QSqlDatabase::addDatabase("QSQLITE");
    Database.setDatabaseName("/home/hoanpx/"+ db->getNameDatabase());
    if(!Database.open())
    {
        qDebug() << "cannot create new:" <<db->getNameDatabase();
    }
    else qDebug() << "created new:" << db->getNameDatabase();
}
void SwapRecordRepo::createTable(LocalSQLiteDb *db)
{
    QSqlQuery qry;
    SqLiteDb=db;
    QString swapRecordColum =CREATE_TABLE;
    swapRecordColum.append(SPACE);
    swapRecordColum.append(db->getNameTable());
    swapRecordColum.append(SPACE);
    swapRecordColum.append(FIRST_COL);
    swapRecordColum.append(DELIMITER);
    for(int i =0; i< db->getLishColCreate().count();i++)
    {
        swapRecordColum.append(SPACE);
        swapRecordColum.append(db->getLishColCreate().at(i));
        if(i != ( db->getLishColCreate().count() - 1 ))swapRecordColum.append(DELIMITER);
    }
    swapRecordColum.append(LAST_COL);
    qDebug()<< swapRecordColum;
    if(!qry.exec(swapRecordColum)) qDebug()<< "cannot create new table"<< db->getNameTable();
    else qDebug()<< "created new table " << db->getNameTable();
}
void SwapRecordRepo::updateToMqttServer() const
{
}
void SwapRecordRepo::insertData(const SwapRecord* swaprecord)
{
    QSqlQuery qry;
    uint32_t countList = SqLiteDb->getListColInsert().count();
    QString commandInsert = "INSERT INTO " + SqLiteDb->getNameTable()+ " (";
    for(uint32_t i=0; i< countList; i++)
    {
        commandInsert.append(SqLiteDb->getListColInsert().at(i));
        (i ==( countList - 1))? commandInsert.append(")"): commandInsert.append(DELIMITER);
    }
    commandInsert.append("VALUES (");
    for(uint32_t i=0;i<countList;i++)
    {
        (i==(countList-1))? commandInsert.append("?);"):commandInsert.append("?,");
    }
    qry.prepare(commandInsert);
    QString dateTime = QDate::currentDate().toString("yyyy:MM:dd") + " " + QTime::currentTime().toString();
    qry.addBindValue(dateTime);
    if(swaprecord->getBss() == nullptr) qry.addBindValue("NONE");
    else qry.addBindValue(swaprecord->getBss());
    if(swaprecord->getUser() == nullptr) qry.addBindValue("NONE");
    else qry.addBindValue(swaprecord->getUser());
    if(swaprecord->getOldCab() == nullptr)
        {
            qry.addBindValue("NONE");
            qry.addBindValue("NONE");
        }
    else
    {
        qry.addBindValue(swaprecord->getOldCab()->getId()+1);
        qry.addBindValue(swaprecord->getOldCab()->getBp()->getSerialNumber());
    }

    if(swaprecord->getNewCab() == nullptr)
    {
        qry.addBindValue("NONE");
        qry.addBindValue("NONE");
    }
    else
    {
        qry.addBindValue(swaprecord->getNewCab()->getId()+1);
        qry.addBindValue(swaprecord->getNewCab()->getBp()->getSerialNumber());
    }
    qry.addBindValue(swaprecord->getState());
    qry.addBindValue(0);
    qry.addBindValue(0);
    qDebug() << qry.executedQuery();
   if(!qry.exec()) qDebug() << "cannot insert into table"<<SqLiteDb->getNameTable() ;
   else qDebug() << "added to table "<<SqLiteDb->getNameTable();
   qry.clear();
}
void SwapRecordRepo::updateData(const SwapRecord *swaprecord)
{
    QSqlQuery qry;
    QString command="UPDATE swaprecord SET ";
    qry.prepare("SELECT * from 'swaprecord' order by id desc;");
    qry.exec();
    qry.next();
    QString index = qry.value("id").toString();
    qry.clear();
    if(swaprecord->getBss() != nullptr) command += "bss='"+ swaprecord->getBss()+"',";
    if(swaprecord->getUser() != nullptr) command +="username='"+swaprecord->getUser()+"',";
    if(swaprecord->getOldCab() != nullptr){
        command += "old_cab='" + QString::number(swaprecord->getOldCab()->getId()+1) +"',";
        if(swaprecord->getOldCab()->getBp()->getSerialNumber()!="0")command += "old_pin='" + swaprecord->getOldCab()->getBp()->getSerialNumber() +"',";
    }
    if(swaprecord->getNewCab() != nullptr)
    {
        command += "new_cab='"+ QString::number(swaprecord->getNewCab()->getId()+1)+"',";
        if(swaprecord->getNewCab()->getBp()->getSerialNumber()!="0") command += "new_pin='" + swaprecord->getNewCab()->getBp()->getSerialNumber() + "',";
    }
    command += "state='" + QString::number(int(swaprecord->getState()))+"'";
    if(swaprecord->getState() == SWAP_RECORD_ST_FINISH) command +=",isDone=1";
    command += " WHERE id =" + index +";";
    qry.prepare(command);
    qDebug() << qry.executedQuery();
   if(!qry.exec()) qDebug() << "cannot update";
}
void SwapRecordRepo::debug()
{

}
void SwapRecordRepo::updatetoDb(const SwapRecord *swapRecord)
{
    switch (swapRecord->getStatusWriteRecord()) {
    case INSERT:
        insertData(swapRecord);
        break;
    case UPDATE:
        updateData(swapRecord);
        break;
    default:
        break;
    }
}
void SwapRecordRepo::checkDataSending()
{

    QSqlQuery qry;
    qry.prepare("SELECT MAX(id) from 'swaprecord';");
    qry.exec();
    qry.next();
    int index = qry.value("MAX(id)").toInt();
    index = index - currentCheckingPosition;
    if(index <= 0)
    {
        currentCheckingPosition = 0;
        return;
    }
    qry.clear();
    qry.prepare("SELECT * from 'swaprecord' WHERE id='"+ QString::number(index) +"';" );
    qry.exec();
    qry.next();
    if(!qry.value("isDone").toBool())
    {
        currentCheckingPosition>=TOTAL_CHECKING_DATABASE?currentCheckingPosition=1:currentCheckingPosition++;
        return;
    }
        if(!qry.value("isSync").toBool())
    {
        SqLiteDb->setId(qry.value("id").toUInt());
        SqLiteDb->setTime(qry.value("time").toString());
        SqLiteDb->setBss(qry.value("bss").toString());
        SqLiteDb->setuserName(qry.value("username").toString());
        SqLiteDb->setoldCab(qry.value("old_cab").toString());
        SqLiteDb->setoldPin(qry.value("old_pin").toString());
        SqLiteDb->setnewCab(qry.value("new_cab").toString());
        SqLiteDb->setnewPin(qry.value("new_pin").toString());
        SqLiteDb->setState(qry.value("state").toString());
        emit onUpdateMqttServer(SqLiteDb);
    }
    currentCheckingPosition>=TOTAL_CHECKING_DATABASE?currentCheckingPosition=1:currentCheckingPosition++;
}
void SwapRecordRepo::okSend(const uint32_t &id)
{
    QSqlQuery qry;
    QString command="UPDATE 'swaprecord' SET isSync=1 WHERE id="+QString::number(id)+";";
    qry.prepare(command);
    qry.exec();
}
