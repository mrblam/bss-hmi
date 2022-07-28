#ifndef SWAPRECORDREPO_H
#define SWAPRECORDREPO_H
#include <Data/Datasource/localsqlitedb.h>
#include <QObject>
#include "Data/Model/swaprecord.h"
#include "Data/Model/user.h"
#define TOTAL_CHECKING_DATABASE 5
typedef enum UPDATE_STATE{

}UPDATE_STATE;
class SwapRecordRepo  :public QObject
{
    Q_OBJECT
private:
    uint32_t currentCheckingPosition;
private:
    LocalSQLiteDb* localSqLiteDb;
    User* user;
    QTimer timeoutCheckingDb;
    QSqlDatabase Database;
private:
    bool executeCommand(const QString& command);
    void prepareInsert(QString& command, const QString& tableName, QJsonObject& json);
    void prepareUpdate(QString& command, const QString& tableName, QJsonObject& json, const uint32_t& id);
    void prepareGet(QString& command);
    void prepareCreateTable(QString& command,const QString& tableName);
    int getLastRow(const QString& tableName);
    LocalSQLiteDb* getLocalSqLiteDb() const;
    User* getUser();
public:
    SwapRecordRepo( QObject *parent = nullptr);
    void createTable(const QString& tableName );
    void createDb (const QString& DBName);
    static SwapRecordRepo* getNewSwapRecordRepo();
    void checkDataSending();
public:
    void insert(const QJsonObject& json, const QString& tableName);
    void update(const uint32_t& id, const QJsonObject& json , const QString& tableName);
    void get();
signals:
    void onUpdateMqttServer(LocalSQLiteDb* sqLiteDb);
public slots:
    void onUpdateSwapRecord(const SwapRecord *swapRecord);
    void okSend(const uint32_t& id );
};

#endif // SWAPRECORDREPO_H
