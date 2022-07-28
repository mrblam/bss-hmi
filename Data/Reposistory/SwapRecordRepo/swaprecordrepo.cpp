#include "swaprecordrepo.h"

SwapRecordRepo::SwapRecordRepo( QObject *parent)  : QObject(parent)
{
    this->localSqLiteDb = new LocalSQLiteDb();
    this->user = User::getUser();
    currentCheckingPosition =0;
    const QString& nameTable = "swaprecord";
    const QString& nameDb = "localdatabase.db";
    createDb(nameDb);
    createTable(nameTable);
    localSqLiteDb->setNameTable(nameTable);
    //QObject::connect(&timeoutCheckingDb, &QTimer::timeout, this, &SwapRecordRepo::checkDataSending);
    //timeoutCheckingDb.start(1000);
}
void SwapRecordRepo::createDb(const QString &DBName){
    Database = QSqlDatabase::addDatabase("QSQLITE");
    Database.setDatabaseName(MAIN_LINK + DBName);
    if(!Database.open()){
        qDebug() <<"ERR: cannot create new:" <<DBName;
    }
    else qDebug() << "SUCCESS: created new:" <<DBName;
}

void SwapRecordRepo::createTable(const QString &tableName){
    QSqlQuery qry;
    QString prepareCommand;
    prepareCreateTable(prepareCommand,tableName);
    if(!qry.exec(prepareCommand)) qDebug()<< "ERR: cannot create new table"<<tableName;
    else qDebug()<< "SUCCESS: created new table " <<tableName;

}
void SwapRecordRepo::prepareCreateTable(QString &command,const QString& tableName){
    QStringList listKey;
    for(int i =0; i < getLocalSqLiteDb()->getKey().length(); i++){
        QString key = getLocalSqLiteDb()->getKey().at(i);
        if(key == "isDone" || key == "isSync")
            key.append(" bool");
        else if(key == "old_cab" || key == "new_cab" || key == "state")
            key.append(" int");
        else key.append(" varchar(30)");
        listKey <<key;
    }
    QString listKeyString = listKey.join(",");
    command.append(CREATE_TABLE);
    command.append(SPACE);
    command.append(tableName);
    command.append(SPACE);
    command.append(FIRST_COL);
    command.append(DELIMITER);
    command.append(listKeyString);
    command.append(LAST_COL);
    qDebug()<<"Command Create Table"<< command;
}
void SwapRecordRepo::onUpdateSwapRecord(const SwapRecord *swapRecord) {
    QJsonObject json;
    getUser()->toJson(json);
    swapRecord->toJson(json);
    getLocalSqLiteDb()->fromJson(json);
    insert(json, getLocalSqLiteDb()->getNameTable());
}
void SwapRecordRepo::insert(const QJsonObject& json, const QString& tableName) {
    QJsonObject jsonObject = json;
    QString command="";
    qDebug()<<"json insert to database"<<jsonObject;
    prepareInsert(command,tableName,jsonObject);
    if(executeCommand(command)) qDebug() << "INSERT SUCCESS:"<<jsonObject;
    qDebug() << "INSERT ERROR:"<< jsonObject;
}
void SwapRecordRepo::prepareInsert(QString &command, const QString& tableName, QJsonObject& json){
    QStringList listValue;
    command = "INSERT INTO " + tableName + " (";
    command.append(getLocalSqLiteDb()->getKey().join(","));
    command.append(")");
    command.append(" VALUES (");
    getLocalSqLiteDb()->toJson(json);
    for(int i=0;i<json.keys().length();i++){
        QString key = getLocalSqLiteDb()->getKey().at(i);
        qDebug()<<key;
        if(json.contains(key)){
            if(json[key].isBool())
                listValue << QString::number(json[key].toBool());
            else if(json[key].isString())
                listValue << "'"+json[key].toString()+"'";
            else if(json[key].isDouble()){
                listValue << QString::number(json[key].toDouble());
            }
            else qDebug()<< "ERR: type not support at key:"<< key;
        }
    }
    command.append(listValue.join(","));
    command.append(LAST_COL);
}
bool SwapRecordRepo::executeCommand(const QString &command){
    QSqlQuery qry;
    qry.prepare(command);
    return qry.exec(command);
}
void SwapRecordRepo::update(const uint32_t& id, const QJsonObject& json, const QString& tableName){
    QJsonObject jsonObject = json;
    QString command="";
    qDebug()<<"Json update to Database"<<jsonObject;
    prepareUpdate(command,tableName,jsonObject, id);
    if(executeCommand(command)) qDebug() << "UPDATE SUCCESS:"<<jsonObject;
    qDebug() << "UPDATE ERR:"<< jsonObject;
}
void SwapRecordRepo::prepareUpdate(QString &command, const QString &tableName, QJsonObject &json, const uint32_t &id){
    (void)command;
    (void) tableName;
    (void)json;
    (void)id;
}
int SwapRecordRepo::getLastRow(const QString& tableName){
    QSqlQuery qry;
    qry.prepare("SELECT * from "+ tableName +"  order by id desc;");
    if(!qry.exec()){
        qDebug()<< "Err: cannot get last row id";
        return -1;
    }
    qry.next();
    return qry.value("id").toDouble();
}
//void SwapRecordRepo::checkDataSending()
//{
//    QSqlQuery qry;
//    qry.prepare("SELECT MAX(id) from 'swaprecord';");
//    qry.exec();
//    qry.next();
//    int index = qry.value("MAX(id)").toInt();
//    index = index - currentCheckingPosition;
//    if(index <= 0)
//    {
//        currentCheckingPosition = 0;
//        return;
//    }
//    qry.clear();
//    qry.prepare("SELECT * from 'swaprecord' WHERE id='"+ QString::number(index) +"';" );
//    qry.exec();
//    qry.next();
//    if(!qry.value("isDone").toBool())
//    {
//        currentCheckingPosition>=TOTAL_CHECKING_DATABASE?currentCheckingPosition=1:currentCheckingPosition++;
//        return;
//    }
//        if(!qry.value("isSync").toBool())
//    {
//        SqLiteDb->setId(qry.value("id").toUInt());
//        SqLiteDb->setTime(qry.value("time").toString());
//        SqLiteDb->setBss(qry.value("bss").toString());
//        SqLiteDb->setuserName(qry.value("username").toString());
//        SqLiteDb->setoldCab(qry.value("old_cab").toString());
//        SqLiteDb->setoldPin(qry.value("old_pin").toString());
//        SqLiteDb->setnewCab(qry.value("new_cab").toString());
//        SqLiteDb->setnewPin(qry.value("new_pin").toString());
//        SqLiteDb->setState(qry.value("state").toString());
//        emit onUpdateMqttServer(SqLiteDb);
//    }
//    currentCheckingPosition>=TOTAL_CHECKING_DATABASE?currentCheckingPosition=1:currentCheckingPosition++;
//}
void SwapRecordRepo::okSend(const uint32_t &id)
{
    QSqlQuery qry;
    QString command="UPDATE 'swaprecord' SET isSync=1 WHERE id="+QString::number(id)+";";
    qry.prepare(command);
    qry.exec();
}
SwapRecordRepo* SwapRecordRepo:: getNewSwapRecordRepo()
{
    static SwapRecordRepo* self;
    if(self==nullptr){
        self=new SwapRecordRepo();
    }
    return self;
}
LocalSQLiteDb* SwapRecordRepo::getLocalSqLiteDb() const{
    return this->localSqLiteDb;
}
User* SwapRecordRepo::getUser(){
    return this->user;
}
