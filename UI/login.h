#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "bssmqttclient.h"
#include "Data/Reposistory/SwapRecordRepo/bsshttpmethod.h"
#include "Data/Model/user.h"
#include <QList>
#include "cabinetcom.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <Data/Reposistory/SwapRecordRepo/soundexecution.h>
#include <Data/Reposistory/SwapRecordRepo/connectmonitor.h>
namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT
private:

    CabinetCom* cabCom;
    BssHttpMethod* bssHttpMethod;
    BSSMqttClient* mqttClient;
    QTimer* loginTimeoutTimer;
    QTimer* runProgressBar;
    //QVector <User*> listUserLazadaHub;
public:

    explicit Login(BSSMqttClient* mqttClient, QWidget *parent = nullptr);
    ~Login();

private slots:
    void acceptLogin(const User* user);
    void rejectLogin();
    void on_btnLogin_clicked();
    void on_btnCancel_clicked();
    void onRemoteLogin(const User* user);
    void onLoginTimeout();

    void on_btnLogin_pressed();

    void on_btnLogin_released();

    void on_btnCancel_pressed();

    void on_btnCancel_released();

    void setValueTimeoutBar();
    void on_timeoutBar_valueChanged(int value);
signals:
    void onChangeStatus(UI_DISPLAY uiDisplay, bool status);
private:
    Ui::Login *ui;
};

#endif // LOGIN_H
