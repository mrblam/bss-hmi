#ifndef USER_H
#define USER_H
#include <QString>
#include <QList>
#include <QDebug>
#include "basemodel.h"

class User:public BaseModel
{
private:
    QString username;
    QString password;
    bool isSuccessLogin;
    QString message;
    uint32_t id;
    QString tocken;
public:
    explicit User();
    bool getIsSuccessLogin() const;
    void setIsSuccessLogin(const bool& isSuccessLogin);
    QString getUsername() const;
    void setUsername(const QString &value);
    QString getPassword() const;
    void setPassword(const QString &value);
    void setId(const uint32_t& id);
    uint32_t getId() const;
    void setTocken(const QString& tocken);
    QString getTocken()const;
    void setSuccess(const bool& success);
    bool getSuccess() const;
    void setMessage(const QString& message);
    QString getMessage() const;
    // BaseModel interface
public:
    void toArray(QByteArray& arr) const;
    void toJson(QJsonObject &json) const;
    void fromJson(const QJsonObject &json);
    void fromByteArr(const QByteArray& byteArray);
    int32_t parse(const QByteArray &data, const char sep);
};

#endif // USER_H
