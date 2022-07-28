#include "localdatabase.h"
LocalDatabase::LocalDatabase(QObject *parent)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("/home/tuan/"+nameDatabase+".db");
    if(!database.open()) qDebug() << "cannot careate new database";
    QObject::connect(&timeoutDatabase, &QTimer::timeout, this,&LocalDatabase::debug);
    timeoutDatabase.start(1000);
}
LocalDatabase* LocalDatabase::getLocalDatabase()
{
    static LocalDatabase* self;
    if(self==nullptr){
        self=new LocalDatabase();
    }
    return self;
}
void LocalDatabase::debug()
{


}
void LocalDatabase::setNameDatabase(QString value)
{
    nameDatabase = value;
}
QString LocalDatabase::getNameDatabase()
{
    return nameDatabase;
}
void LocalDatabase::insertIntoTable(const SwapRecord* swaprecord){
    QSqlQuery qry;
    addNewTable(nameTable,"");
    qry.prepare("INSERT INTO " + nameTable + " ("
                                         " time,"
                                         " bss,"
                                         " username,"
                                         " old_cab,"
                                         " old_pin,"
                                         " new_cab,"
                                         " new_pin,"
                                         " state, "
                                         " isSync)"
                                         " VALUES (?,?,?,?,?,?,?,?,?);");
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
    qDebug() << qry.executedQuery();
   if(!qry.exec()) qDebug() << "cannot insert into table"<<nameTable ;
   else qDebug() << "added to table "<<nameTable;
}
void LocalDatabase::addNewTable(QString nametable, QString fields)
{

    QString command ="CREATE TABLE " +
            nametable +
            " (id INTEGER PRIMARY KEY AUTOINCREMENT null,"
            " time varchar(200),"
            " bss varchar(200),"
            " username varchar(200),"
            " old_cab interger,"
            " old_pin varchar(200),"
            " new_cab interger,"
            " new_pin varchar(200),"
            " state integer,"
            " isSync bool);";
    QSqlQuery qry;
    if(!qry.exec(command)) qDebug()<< "cannot create new table!"<<nametable;
    else qDebug()<< "created new table:" << nametable;
}

