#include "localsqlitedb.h"
LocalSQLiteDb::LocalSQLiteDb(){
    key  << "time"
         << "bss" << "username"
         << "old_cab" << "old_pin"
         << "new_cab" << "new_pin"
         << "state" << "isDone"
         << "isSync";
}
void LocalSQLiteDb::setNameTable(const QString& value)
{
        nameTable = value;
}
QString LocalSQLiteDb::getNameTable() const
{
    return nameTable;
}
QStringList LocalSQLiteDb::getKey() const{
    return this->key;
}
void LocalSQLiteDb::setNameDatabase(const QString& value)
{
    nameDatabase = value;
}
QString LocalSQLiteDb::getNameDatabase() const{
    return nameDatabase;
}

void LocalSQLiteDb::fromJson(const QJsonObject &json)
{
    QString time = QDate::currentDate().toString("yyyy:MM:dd") + " " + QTime::currentTime().toString();
    json["time"] = time;
    for(int i=0; i< getKey().length();i++){
       QString key = getKey().at(i);
       if(!json.contains(key)){
           if(key == "time")
               row[key] = time;
           else if(key == "isDone"  || key == "isSync")
               row[key] = bool(false);
           else if(key == "old_cab" || key == "new_cab")
               row[key] = double(-1);
           else
               row[key] = QString("none");
       }
       else{
           row[key] = json[key];
       }
   }
}
void LocalSQLiteDb::toJson(QJsonObject& json)
{
    json = row;
}

