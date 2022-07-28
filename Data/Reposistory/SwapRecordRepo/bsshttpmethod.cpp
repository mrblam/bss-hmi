#include "bsshttpmethod.h"

BssHttpMethod::BssHttpMethod(QObject *parent) : QObject(parent)
{
    setUrlSwapRecord(URL_SWAP_RECORD);
    setUrlLogin(URL_LOGIN);
    this->userModel = User::getUser();
    this->manager = new QNetworkAccessManager();
    request.setRawHeader(getRawHeader(), getContentType());
    connect(this->manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));
}

void BssHttpMethod::onLoginSendRequest(User* user) {
    QByteArray arr;
    user->toArray(arr);
    post(getUrlLogin(),arr);
}
void BssHttpMethod::updateSwapRecord(const SwapRecord* swapRecord){
    QByteArray arr;
    QJsonObject json;
    getUser()->toJson(json);
    swapRecord->toJson(json);
    updateJson(json, dataSwapRecordRemote);
    swapRecord->toArray(arr,dataSwapRecordRemote);
    switch (swapRecord->getState()) {
    case SWAP_RECORD_ST_SELECT_EMPTY_CAB:
        break;
    case SWAP_RECORD_ST_WAITING_OLD_BP:
        post(getUrlSwapRecord(),arr);
        break;
    case SWAP_RECORD_ST_CHECKING_BP:
        break;
    case SWAP_RECORD_ST_BP_ACCEPTED:
        put(getUrlSwapRecord(), arr, getId());
        break;
    case SWAP_RECORD_ST_DELIVERY:
        break;
    case SWAP_RECORD_ST_RETURN:
        put(getUrlSwapRecord(),arr, getId());
        dataSwapRecordRemote = QJsonObject();
        break;
    case SWAP_RECORD_ST_SUCCESS:
        put(getUrlSwapRecord(),arr, getId());
        dataSwapRecordRemote = QJsonObject();
        break;
    case SWAP_RECORD_ST_FINISH:
        break;
    case SWAP_RECORD_ST_FAIL:
        break;
    case SWAP_RECORD_STATE_COM_FAIL:
        break;
    case SWAP_RECORD_ST_CHARGE_ONLY:
        break;
    default:
        break;
    }


}
void BssHttpMethod::updateJson(const QJsonObject& fromJson, QJsonObject& toJson){
    QStringList keyList = fromJson.keys();
    for (QString key : keyList){
        if(fromJson[key].isString() && fromJson[key] != "null" && fromJson[key] != "0"){
            toJson[key] = fromJson[key];
        }
        if(fromJson[key].isBool()){
            toJson[key] = fromJson[key];
        }
        if(fromJson[key].isDouble() && fromJson[key] != double(-1)){
            toJson[key] = fromJson[key];
        }
    }
}
void BssHttpMethod::get(const QString &url, const QByteArray &data){
    (void)url;
    (void)data;
}
void BssHttpMethod::post(const QString& url, const QByteArray& data){
    request.setUrl(QUrl(url));
    request.setRawHeader("Content-Type", "application/json");
    qDebug()<<"POST:"<<data;
    manager->post(request,data);
}
void BssHttpMethod::put(const QString &url, const QByteArray &data){
    request.setUrl(QUrl(url));
    request.setRawHeader("Content-Type", "application/json");
    qDebug()<<"data puts"<<data;
    manager->put(request,data);
}

void BssHttpMethod::put(const QString &url, const QByteArray &data, const uint32_t &id){
    QString putUrl = url;
    putUrl.append("/");
    putUrl.append(QString::number(id));
    request.setUrl(QUrl(putUrl));
    request.setRawHeader("Content-Type", "application/json");
    qDebug()<<"data puts"<<data;
    manager->put(request,data);
}
void BssHttpMethod::managerFinished(QNetworkReply *reply) {
    //checking connect
    QJsonDocument doc= QJsonDocument::fromJson(reply->readAll());
    QJsonObject replyJson = doc.object();
    if(!(replyJson.contains("message") && replyJson["message"].isString())) return;
    if(replyJson["message"].toString().startsWith("update")){
        qDebug()<<"put:"<<replyJson;
        return;
    }
    if(replyJson["message"].toString().startsWith("create")){
        if(!replyJson.contains("data")) return;
        QJsonObject swapDataJson = replyJson["data"].toObject();
        setId(swapDataJson["id"].toDouble());
        qDebug()<<"post:"<< swapDataJson;
        return;
    }
    if(replyJson["message"].toString().startsWith("login")){
        getUser()->fromJson(replyJson);
        QJsonObject check;
        getUser()->toJson(check);
        qDebug()<<"login:"<<check;
        emit onLoginSuccess(getUser());
        return;
    }
    if(replyJson["message"].toString().startsWith("username or password incorrect")){
        emit onLoginFail(getUser());
        return;
     }
}
 void BssHttpMethod::checkLoginRequest(const bool &isLoginSuccess){
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
void BssHttpMethod::setId(const uint32_t &id){
    this->id = id;
}
uint32_t BssHttpMethod::getId() const{
    return this->id;
}
