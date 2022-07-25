#include "localsqlitedb.h"
LocalSQLiteDb::LocalSQLiteDb(){}
void LocalSQLiteDb::setNameTable(const QString& value)
{
        nameTable = value;
}
QString LocalSQLiteDb::getNameTable()
{
    return nameTable;
}

void LocalSQLiteDb::setNameDatabase(const QString& value)
{
    nameDatabase = value;
}
QString LocalSQLiteDb::getNameDatabase()
{
    return nameDatabase;
}

void LocalSQLiteDb::setListColInsert(const QList<QString>& ls)
{
    listColInsert = ls;
}
QList<QString> LocalSQLiteDb::getListColInsert()
{
    return listColInsert;
}

void LocalSQLiteDb::setListColCreate(const QList<QString>& ls)
{
    listColCreate = ls;
}
QList<QString> LocalSQLiteDb::getLishColCreate()
{
    return listColCreate;
}
uint32_t LocalSQLiteDb::getId()
{
    return  idDb;
}
void LocalSQLiteDb::setId(const uint32_t &id)
{
    idDb=id;
}
QString LocalSQLiteDb::getTime()
{
    return time;
}
void LocalSQLiteDb::setTime(const QString &value)
{
    time = value;
}
QString LocalSQLiteDb::getBss()
{
    return bss;
}
void LocalSQLiteDb::setBss(const QString &value)
{
    bss = value;
}
QString LocalSQLiteDb::getUsername()
{
    return username;
}
void LocalSQLiteDb::setuserName(const QString &value)
{
    username = value;
}
QString LocalSQLiteDb::getoldCab()
{
    return oldCab;
}
void LocalSQLiteDb::setoldCab(const QString &value)
{
    oldCab = value;
}

QString LocalSQLiteDb::getoldPin()
{
    return oldPin;
}
void LocalSQLiteDb::setoldPin(const QString &value)
{
    oldPin = value;
}

QString LocalSQLiteDb::getnewCab()
{
    return newCab;
}
void LocalSQLiteDb::setnewCab(const QString &value)
{
    newCab = value;
}
QString LocalSQLiteDb::getnewPin()
{
    return newPin;
}
void LocalSQLiteDb::setnewPin(const QString &value)
{
    newPin = value;
}
QString LocalSQLiteDb::getstate()
{
    return state;
}
void LocalSQLiteDb::setState(const QString &value)
{
    state = value;
}
void LocalSQLiteDb::fromJson(QString &reult, const QJsonObject &json, const QString &value)
{

}
void LocalSQLiteDb::toJson(QJsonObject& json)
{
    json["time"] = getTime();
    json["username"] = getUsername();
    json["bss"]= getBss();
    json["old_cab"]=getoldCab();
    json["old_pin"]=getoldPin();
    json["new_cab"]=getnewCab();
    json["new_pin"]=getnewPin();
    json["state"]=getstate();
}

