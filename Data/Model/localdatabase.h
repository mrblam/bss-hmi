#ifndef LOCALDATABASE_H
#define LOCALDATABASE_H
#include <QObject>
#include <QString>
#include <QtSql>
#include "swaprecord.h"
#include <QTime>
#include <QTimer>
#include <QDate>
class LocalDatabase: public QObject
{
    Q_OBJECT
private:

    QString data;
    QString nameTable= "table1";
    QString nameDatabase = "testDatabase";
    QSqlQuery commandSql;
    QSqlDatabase database;
    QTimer timeoutDatabase;
public:
    explicit LocalDatabase(QObject *parent = nullptr);
    static LocalDatabase* getLocalDatabase();
    void setNameDatabase(QString value);
    QString getNameDatabase();

    void addNewTable(QString nametable, QString fields);
public slots:
    void debug();
    void insertIntoTable(const SwapRecord* swaprecord);

};

#endif // LOCALDATABASE_H
