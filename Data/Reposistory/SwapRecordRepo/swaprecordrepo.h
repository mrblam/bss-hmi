#ifndef SWAPRECORDREPO_H
#define SWAPRECORDREPO_H
#include <Data/Datasource/localsqlitedb.h>
#include <QObject>
#include "Data/Model/swaprecord.h"
#define TOTAL_CHECKING_DATABASE 5
typedef enum UPDATE_STATE{

}UPDATE_STATE;
class SwapRecordRepo  :public QObject
{
    Q_OBJECT
private:
    uint32_t currentCheckingPosition;
private:
    LocalSQLiteDb* SqLiteDb;
    //LocalSQLiteDb testdb;
    QSqlQuery* qry;
    QTimer timeoutCheckingDb;
    QSqlDatabase Database;
public:
    SwapRecordRepo( QObject *parent = nullptr);
    void setNewDatabase( const QString& nameDb, const QString& nameTb, const QList<QString>& ls);
    void createTable(LocalSQLiteDb* db );
    void insertData(const SwapRecord* swapRecord);
    void updateData(const  SwapRecord* swaprecord);
    void createDb (LocalSQLiteDb* db);
    static SwapRecordRepo* getNewSwapRecordRepo();
    void checkDataSending();

    //QList<QString> getRowData(const )
signals:
    void onUpdateMqttServer(LocalSQLiteDb* sqLiteDb);
private slots:

public slots:
    void debug();
    void updatetoDb(const SwapRecord *swapRecord);
    void updateToMqttServer() const;
    void okSend(const uint32_t& id );
};

#endif // SWAPRECORDREPO_H
