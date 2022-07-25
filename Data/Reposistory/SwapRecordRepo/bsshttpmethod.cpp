#include "bsshttpmethod.h"

BssHttpMethod::BssHttpMethod(QObject *parent) : QObject(parent)
{
    setUrlSwapRecord("http://3.0.16.198:8080/rest-api/swap_records");
    setUrlLogin("http://18.139.114.128:8080/api/auth/login");
    bssSendStatus = BSS_SEND_STATUS_LOGIN;
    this->userModel = new User();
    this->manager = new QNetworkAccessManager();
    request.setRawHeader(getRawHeader(), getContentType());
    connect(this->manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));
}

void BssHttpMethod::onLoginSendRequest(User* user) {
    QByteArray arr;
    user->toArray(arr);
    setBssSendStatus(BSS_SEND_STATUS_LOGIN);
    postToServer(getUrlLogin(),arr); 
}

void BssHttpMethod::updateSwapRecord(const SwapRecord* swapRecord){
    if(swapRecord->getState() ==SWAP_RECORD_ST_SELECT_EMPTY_CAB) return;
    QByteArray arr;
    QJsonObject json;
    getUser()->toJson(json);
    swapRecord->toArray(arr,json);
    switch (getBssSendStatus()) {
    case BSS_SEND_STATUS_SWAP_POST:{
        postToServer(getUrlSwapRecord(), arr);
        setBssSendStatus(BSS_SEND_STATUS_SWAP_PUT);
        break;
    }
    case BSS_SEND_STATUS_SWAP_PUT:{
        QString urlPut = getUrlSwapRecord().append("/");
        urlPut.append(QString::number(getId()));
        putToServer(urlPut,arr);
        break;
    }
    default:
        break;
    }
}

void BssHttpMethod::postToServer(const QString& url, const QByteArray& data){
    request.setUrl(QUrl(url));
    request.setRawHeader("Content-Type", "application/json");
    qDebug()<<"data post:"<<data;
    manager->post(request,data);
}
void BssHttpMethod::putToServer(const QString &url, const QByteArray &data){
    request.setUrl(QUrl(url));
    request.setRawHeader("Content-Type", "application/json");
    qDebug()<<"data puts"<<data;
    manager->put(request,data);
}

void BssHttpMethod::managerFinished(QNetworkReply *reply) {
    //checking connect
    switch (getBssSendStatus()) {
    case BSS_SEND_STATUS_LOGIN:{
        QJsonDocument dataUser= QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonUser = dataUser.object();
        getUser()->fromJson(jsonUser);
        QJsonObject check;
        getUser()->toJson(check);
        qDebug()<<"user receive"<<check;
        checkLogin(getUser()->getIsSuccessLogin());
        break;
    }
    case BSS_SEND_STATUS_SWAP_POST:{
        if(reply->error()){
            break;
        }
        QJsonDocument dataSwap= QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonSwap = dataSwap.object();
        if(!jsonSwap.contains("data")) break;
        QJsonObject data = jsonSwap["data"].toObject();
        setId(data["id"].toDouble());
        qDebug()<<jsonSwap;
        break;
    }
    case BSS_SEND_STATUS_SWAP_PUT:{
        if(reply->error()){
            break;
        }
        QJsonDocument dataSwap= QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonPut = dataSwap.object();
        qDebug()<<jsonPut;
        break;
    }
    default:{
        break;
    }
    }
}
void BssHttpMethod::checkLogin(const bool &isLoginSuccess){
    if(isLoginSuccess){
        emit onLoginSuccess(getUser());
        return;
    }
    emit onLoginFail(getUser());
}

QNetworkAccessManager* BssHttpMethod::getManage() const{
    return this->manager;

}
QNetworkRequest BssHttpMethod::getRequest() const{
    return this->request;
}
void BssHttpMethod::setUrlSwapRecord(const QString& urlSwapRecord){
    this->urlSwapRecord = urlSwapRecord;
}
QString BssHttpMethod::getUrlSwapRecord() const{
    return this->urlSwapRecord;
}
void BssHttpMethod::setRawHeader(const QByteArray& header){
    this->rawHeader = header;
}
QByteArray BssHttpMethod::getRawHeader() const{
    return this->rawHeader;
}
void BssHttpMethod::setContentType(const QByteArray &contentType){
    this->contentType = contentType;
}
QByteArray BssHttpMethod::getContentType() const{
    return this->contentType;
}
void BssHttpMethod::setUser(User* userModel){
    this->userModel = userModel;
}
User* BssHttpMethod::getUser() const{
    return this->userModel;
}

BssHttpMethod* BssHttpMethod::getBssHttpMenthod(){
    static BssHttpMethod* self;
    if(self == nullptr){
        self =new BssHttpMethod();
    }
    return self;
}
void BssHttpMethod::setUrlLogin(const QString &urlLogin){
    this->urlLogin = urlLogin;
}
QString BssHttpMethod::getUrlLogin() const {
    return this->urlLogin;
}
BSS_SEND_STATUS BssHttpMethod::getBssSendStatus() const{
    return this->bssSendStatus;
}
void BssHttpMethod::setBssSendStatus(const BSS_SEND_STATUS& bssSendStatus){
    this->bssSendStatus= bssSendStatus;
}
void BssHttpMethod::setId(const uint32_t &id){
    this->id = id;
}
uint32_t BssHttpMethod::getId() const{
    return this->id;
}
