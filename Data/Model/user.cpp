#include "user.h"

User::User()
{
    setUsername("Starlake");
    setPassword("admin");
    setTocken("1234");
    setId(0);
    setMessage("wrong password or username");
    isSuccessLogin = false;
}
void User::setIsSuccessLogin(const bool &isSuccessLogin){
    this->isSuccessLogin = isSuccessLogin;
}
bool User::getIsSuccessLogin() const{
    return this->isSuccessLogin;
}
void User::setTocken(const QString& tocken){
    this->tocken = tocken;
}
QString User::getTocken()const{
    return  this->tocken;
}
QString User::getUsername() const
{
    return username;
}

void User::setUsername(const QString &value)
{
    username = value;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &value)
{
    password = value;
}
void User::setId(const uint32_t& id){
    this->id= id;
}
uint32_t User::getId() const{
    return this->id;
}
void User::toJson(QJsonObject &json) const
{
    json["username"]= username;
    json["password"]= password;
    json["user"] = (double)getId();
//    json["tocken"] = getTocken();
//    json["isSuccess"] = getIsSuccessLogin();
//    json["message"] = getMessage();

}
void User::toArray(QByteArray &arr) const{
    QJsonObject json;
    toJson(json);
    QJsonDocument doc(json);
    arr = doc.toJson(QJsonDocument::Indented);
}
QString User::getMessage() const{
    return this->message;
}
void User::setMessage(const QString &message){
    this->message = message;
}
void User::fromJson(const QJsonObject &json)
{
    if (json.contains("success") && json["success"].isBool()){
         setIsSuccessLogin(json["success"].toBool());
    }
    if(json.contains("user_name") && json["user_name"].isString()){
        setUsername(json["user_name"].toString());
    }
   if (json.contains("message") && json["message"].isString()){
        setMessage(json["message"].toString());
   }
   if(!json.contains("data")) return;
   QJsonObject data = json["data"].toObject();
   if(data.contains("user_id") && data["user_id"].isDouble()){
       setId(data["user_id"].toDouble());
   }
   if(data.contains("access_token") && data["access_token"].isString()){
       setTocken(data["access_token"].toString());
   }
}
void User::fromByteArr(const QByteArray &byteArray ){
//    QList<QByteArray> list = byteArray.split(',');
//    for (int i=0; i<list.length();i++){
//        qDebug()<< list.at(i);
//    }
}
int32_t User::parse(const QByteArray &data, const char sep)
{
    (void)data;
    (void)sep;
   return -1;
}

