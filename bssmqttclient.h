#ifndef BSSMQTTCLIENT_H
#define BSSMQTTCLIENT_H

#include <QObject>
#include "Data/Model/bss.h"
#include "Data/Model/bp.h"
#include "Data/Model/cabinet.h"
#include <QtMqtt>
#include "Data/Model/swaprecord.h"
#include "Data/Model/user.h"
#include "Data/Datasource/localsqlitedb.h"
class BSSMqttClient : public QObject
{
    Q_OBJECT
private:
    QMqttClient mqttClient;
    BSS* bssModel;
    BP* bpModel;
    Cabinet* cabinetModel;
    User* userModel;
    QTimer timerCheckingMessageReceive;
    QMqttSubscription* mqttSub;

public:
    explicit BSSMqttClient(const QString& host="localhost",const uint16_t port=1883,const QString& user="",const QString& pass="",QObject *parent = nullptr);
public:
    void setBss(const BSS* bss);
    void setHost(const QString& host);
    static BSSMqttClient* getBSSMqttClient();
    void setPort(const uint32_t port);
    void setMqttUser(const QString& user);
    void setMqttPass(const QString& pass);
    void mqttRespont(const uint32_t& answearCode,const User* user);
signals:
    void bssChanged(const BSS* bss);
    void bpChanged(const BP* bp);
    void onUserLogin(const User* user);
    void onDonePublicData(const uint32_t& id);
public slots:
    void updateBSS(const BSS* bss);
    void updateBp(const BP* bp);
    void updateSwapRecord(const SwapRecord* swapRecord);
    void start();
    void syncLocaldbToServerdb(LocalSQLiteDb* localSQLiteDb);
private slots:

    void mqttStateChanged(const QMqttClient::ClientState& state);
    void mqttErrorChanged(const QMqttClient::ClientError& error);
    void mqttConnected();
    void mqttMessageReceived(const QByteArray &msg, const QMqttTopicName &topic);
};

#endif // BSSMQTTCLIENT_H
