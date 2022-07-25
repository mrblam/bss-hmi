#ifndef LOCALSQLITEDB_H
#define LOCALSQLITEDB_H
#include <QString>
#include <QTime>
#include <QTimer>
#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDate>
#include <QDebug>
#include <QJsonArray>
#include<QJsonObject>
#include <QArrayData>
#include <QList>

#define DELIMITER   ","
#define FIRST_COL   "(id INTEGER PRIMARY KEY AUTOINCREMENT null"
#define LAST_COL    ");"
#define SPACE       " "
#define CREATE_TABLE "CREATE TABLE"

class LocalSQLiteDb
{
private:
    QString test;
    QString nameTable;
    QString nameDatabase;
    QList<QString> listColInsert;
    QList<QString> listColCreate;
    uint32_t idDb;
    QString time;
    QString bss;
    QString username;
    QString oldCab;
    QString oldPin;
    QString newCab;
    QString newPin;
    QString state;

public:


    LocalSQLiteDb();
    void setId(const uint32_t& id);
    void setTime(const QString& value);
    void setBss(const QString& value);
    void setuserName(const QString& value);
    void setoldCab(const QString& value);
    void setoldPin(const QString& value);
    void setnewCab(const QString& value);
    void setnewPin(const QString& value);
    void setState(const QString& value);
    void setNameTable( const QString& value);
    void setNameDatabase( const QString& value);
    void setListColInsert(const QList <QString>& ls);
    void setListColCreate(const QList<QString>& ls);

    uint32_t getId();
    QList<QString> getListColInsert();
    QList<QString> getListColUpdate();
    QList<QString> getLishColCreate();
    QString getTime();
    QString getUsername();
    QString getBss();
    QString getoldCab();
    QString getoldPin();
    QString getnewCab();
    QString getnewPin();
    QString getstate();
    QString getNameDatabase();
    QString getNameTable();
    void setTest(const QString& value );
    void toJson( QJsonObject& json);
    void fromJson(QString& reult, const QJsonObject& json, const QString& value);
};

#endif // LOCALSQLITEDB_H
