#ifndef BSSHTTP_H
#define BSSHTTP_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include "Data/Model/bss.h"
#include "Data/Model/user.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>
#include "Data/Model/swaprecord.h"
#include "Data/Datasource/localsqlitedb.h"

typedef enum BSS_SEND_STATUS{
    BSS_SEND_STATUS_LOGIN =0,
    BSS_SEND_STATUS_SWAP_POST,
    BSS_SEND_STATUS_SWAP_PUT,
    BSS_SEND_STATUS_GET_LIST_USER,
}BSS_SEND_STATUS;

class BssHttpMethod : public QObject
{
    Q_OBJECT
private:
    BSS_SEND_STATUS bssSendStatus;
    QString urlSwapRecord;
    QString urlLogin;
    QByteArray rawHeader;
    QByteArray contentType;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    User* userModel;
    QTimer syncLoop;
    uint32_t id;

private:
    void praseDataRecFromServer(const QString& dataReceive);
    void checkLogin(const bool& isLoginSuccess);
private slots:
    void managerFinished(QNetworkReply *reply);
public:
     QNetworkAccessManager* getManage() const;
     QNetworkRequest getRequest() const;
     void setUrlSwapRecord(const QString& urlSwapRecord);
     QString getUrlSwapRecord() const;
     void setRawHeader(const QByteArray& header);
     QByteArray getRawHeader() const;
     void setContentType(const QByteArray& contentType);
     QByteArray getContentType() const;
     void setUser(User* userModel);
     User* getUser() const;
     void setUrlLogin(const QString& urlLogin);
     QString getUrlLogin() const;
     void setId(const uint32_t& id);
     uint32_t getId() const;
     BSS_SEND_STATUS getBssSendStatus() const;
     void setBssSendStatus(const BSS_SEND_STATUS& bssSendStatus);
public:
    explicit BssHttpMethod(QObject *parent = nullptr);
    static BssHttpMethod* getBssHttpMenthod();
    void postToServer(const QString& url, const QByteArray& data);
    void putToServer(const QString& url, const QByteArray& data);
    void onLoginSendRequest(User* user);
signals:
    void serverAnswear();
    void onLoginSuccess(const User* user);
    void onLoginFail(const User* user);
    void onUpdateSwapFail();
    void onUpdateSwapSuccess(const SwapRecord* swapRecord);
public slots:
    void updateSwapRecord(const SwapRecord* swapRecord);

};

#endif // BSSHTTP_H
