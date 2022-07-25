#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "bssmqttclient.h"
#include "Data/Reposistory/SwapRecordRepo/bsshttpmethod.h"
#include "Data/Model/user.h"
#include <QList>
#include "cabinetcom.h"
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
    void on_txtUsername_textChanged(const QString &arg1);

    void on_txtPassword_textChanged(const QString &arg1);

    void on_btnLogin_pressed();

    void on_btnLogin_released();

    void on_btnCancel_pressed();

    void on_btnCancel_released();

    void on_txtUsername_returnPressed();

    void on_txtUsername_cursorPositionChanged(int arg1, int arg2);

    void on_txtUsername_selectionChanged();

    void on_txtUsername_textEdited(const QString &arg1);

    void on_txtUsername_customContextMenuRequested(const QPoint &pos);

    void on_txtUsername_windowIconTextChanged(const QString &iconText);
    void setValueTimeoutBar();
    void on_timeoutBar_valueChanged(int value);

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
