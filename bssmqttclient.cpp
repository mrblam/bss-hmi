

#include "bssmqttclient.h"
BSSMqttClient::BSSMqttClient(const QString& host, const uint16_t port, const QString &user, const QString &pass, QObject *parent) : QObject(parent)
{
    mqttClient.setHostname(host);
    mqttClient.setPort(port);
    mqttClient.setUsername(user);
    mqttClient.setPassword(pass);
    bssModel=new BSS(15);
    bpModel=new BP();
    cabinetModel=new Cabinet();
    userModel=new User();

}
void BSSMqttClient::setBss(const BSS *bss){
    bssModel->setSerialNumber(bss->getSerialNumber());
}
BSSMqttClient *BSSMqttClient::getBSSMqttClient(){
   static BSSMqttClient* self;
   if(self==nullptr){
       self=new BSSMqttClient();
   }
   return self;
}
void BSSMqttClient::setHost(const QString &host){
   mqttClient.setHostname(host);
}

void BSSMqttClient::setPort(const uint32_t port)
{
   mqttClient.setPort(port) ;
}

void BSSMqttClient::setMqttUser(const QString &user){
   mqttClient.setUsername(user);
}

void BSSMqttClient::setMqttPass(const QString &pass){
   mqttClient.setPassword(pass);
}

void BSSMqttClient::updateBSS(const BSS *bss)
{
    if(mqttClient.state()!=QMqttClient::Connected) return;

    QJsonObject bss_json;
    bss->toJson(bss_json);
    QByteArray topicPayload=QJsonDocument(bss_json).toJson(QJsonDocument::Indented);
    QString topic="dt/swapping/bss/" + bss->getSerialNumber()+"/info";
    if(mqttClient.publish(QMqttTopicName(topic),topicPayload) == -1){
            qDebug() << "Error: Could not publish message";
    }
}

void BSSMqttClient::updateBp(const BP *bp)
{
    if(mqttClient.state()!=QMqttClient::Connected) return;

    QJsonObject bp_json;
    bp->toJson(bp_json);
    QByteArray topicPayload=QJsonDocument(bp_json).toJson(QJsonDocument::Indented);
    if(mqttClient.publish(QMqttTopicName("dt/battery/info"),topicPayload) == -1){
            qDebug() << "Error: Could not publish message";
    }
}
void BSSMqttClient::updateSwapRecord(const SwapRecord *swapRecord)
{
    if(mqttClient.state()!=QMqttClient::Connected) return;
    QJsonObject swap_json;
    swapRecord->toJson(swap_json);
    QByteArray topicPayload=QJsonDocument(swap_json).toJson(QJsonDocument::Indented);
    QString topic="dt/swapping/bss/" +swapRecord->getBss() + "/record";

    if(mqttClient.publish(QMqttTopicName(topic),topicPayload) == -1){
            qDebug() << "Error: Could not publish message";
    }
    //qDebug() << "OK SEND ad/swapping/bss/"
}

void BSSMqttClient::start()
{
    //QMqttSubscription* subscription = mqttClient.subscribe(QMqttTopicFilter("dt/database/100/info"));

    //QObject::connect(subscription, &QMqttSubscription::messageReceived, this, &BSSMqttClient::checkingMessageReceive);
    //connect(subScription, &QMqttSubscription::stateChanged, this, &BSSMqttClient::updateStatus);
    QObject::connect(&mqttClient, &QMqttClient::stateChanged,this,&BSSMqttClient::mqttStateChanged);
    QObject::connect(&mqttClient, &QMqttClient::errorChanged,this,&BSSMqttClient::mqttErrorChanged);
    QObject::connect(&mqttClient, &QMqttClient::messageReceived,this,&BSSMqttClient::mqttMessageReceived);
    QObject::connect(&mqttClient, &QMqttClient::connected,this,&BSSMqttClient::mqttConnected);

    //QObject::connect(&timerCheckingMessageReceive, &QTimer::timeout, this, &BSSMqttClient::checkingMessageReceive);
    //timerCheckingMessageReceive.start(1000);

    mqttClient.connectToHost();
}

void BSSMqttClient::mqttStateChanged(const QMqttClient::ClientState& state)
{
       if(state == QMqttClient::Disconnected)
            qDebug() << " State: Disconnected";
        else if(state == QMqttClient::Connecting)
            qDebug() << " State: Connecting";
        else if(state == QMqttClient::Connected)
            qDebug() << " State: Connected";
}

void BSSMqttClient::mqttErrorChanged(const QMqttClient::ClientError& error)
{
        qDebug() << error;
}

void BSSMqttClient::mqttConnected()
{

    //const QMqttTopicFilter filter{"cmd/swaping/bss-v1.0/#"};
    const QMqttTopicFilter filter{"cmd/bss/"+bssModel->getSerialNumber()+"/login/request"};
    qDebug()<<"Connected to local Mqtt Broker";
    QMqttSubscription *subscription = mqttClient.subscribe(filter);
    if(!subscription){
            qDebug() << "Could not subscribe";
    }

}
void BSSMqttClient::mqttRespont(const uint32_t& answearCode, const User* user){
    if(mqttClient.state()!=QMqttClient::Connected) return;
    QJsonObject user_json;
    user_json["bss-sn"]= bssModel->getSerialNumber();
    user_json["user_name"]=user->getUsername();
    user_json["result_code"]=(double)answearCode;
    QByteArray topicPayload=QJsonDocument(user_json).toJson(QJsonDocument::Indented);
    QString topic= "cmd/bss/"+bssModel->getSerialNumber()+"/login/response";
    if(mqttClient.publish(QMqttTopicName(topic),topicPayload) == -1){
            qDebug() << "Error: Could not publish message";
    }
}
void BSSMqttClient::mqttMessageReceived(const QByteArray &msg, const QMqttTopicName &topic)
{
    QJsonDocument doc = QJsonDocument::fromJson(msg);
    if(doc.isNull()) return;
    QJsonObject obj = doc.object();
    if(obj.isEmpty()) return;
    if(topic.name()=="cmd/swaping/bss"){
    }
    qDebug()<<obj;
    if(topic.name()=="cmd/bss/"+bssModel->getSerialNumber()+"/login/request"){
        userModel->fromJson(obj);
        mqttRespont(200,userModel);
        emit onUserLogin(userModel);
    }
}
void BSSMqttClient::syncLocaldbToServerdb(LocalSQLiteDb *localSQLiteDb)
{
    if(mqttClient.state()!=QMqttClient::Connected) return;

    QJsonObject db_json;
    localSQLiteDb->toJson(db_json);
    QByteArray topicPayload=QJsonDocument(db_json).toJson(QJsonDocument::Indented);
    if(mqttClient.publish(QMqttTopicName("dt/database/" + localSQLiteDb->getBss()+"/info"),topicPayload) != -1){
        emit onDonePublicData(localSQLiteDb->getId());
    }
}
