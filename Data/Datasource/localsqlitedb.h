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

//file local here
#include "linkdirector.h"

#define DELIMITER   ","
#define FIRST_COL   "(id INTEGER PRIMARY KEY AUTOINCREMENT null"
#define LAST_COL    ");"
#define SPACE       " "
#define CREATE_TABLE "CREATE TABLE IF NOT EXISTS"
typedef struct ingredientString{
    QString key;
    QString Value;
} ingredientString;
typedef struct ingredientNumber{
    QString key;
    double Value;
} ingredientNumber;
typedef struct Row {
    ingredientNumber id{"id",0};
    ingredientString time{"time",""};
    ingredientString bss{"bss",""};
    ingredientString username{"username",""};
    ingredientNumber oldCab{"old_cab", -1};
    ingredientString oldPin{"old_pin",""};
    ingredientNumber newCab{"new_cab",-1};
    ingredientString newPin{"new_pin",""};
    ingredientNumber state{"state",0};
    ingredientNumber isDone{"isDone",0};
    ingredientNumber isSync{"isSync",0};
} Row;

class LocalSQLiteDb
{
private:
    QStringList key;
    QJsonObject row;
    QString nameTable;
    QString nameDatabase;

public:
    LocalSQLiteDb();
    QStringList getKey() const;
    void setNameTable( const QString& value);
    void setNameDatabase( const QString& value);
    QString getNameTable() const;
    QString getNameDatabase() const;
    void toJson( QJsonObject& json);
    void fromJson(const QJsonObject& json);
};

#endif // LOCALSQLITEDB_H
