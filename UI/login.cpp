#include "login.h"
#include "ui_login.h"
#include "UI/swapview.h"
#include "userview.h"
#include <QPainter>
#include <QList>
#include <QVector>
#include <QStringList>
uint8_t is_staff_login = 0;
uint8_t cab_id = 0;
QVector <QStringList> listDataUserLazadaHub = {
    {"Test", "0"},
    {"Giang", "1234"},
    {"Quang", "1234"},
    {"User3", "pass3"},
    {"User4", "pass4"},
    {"User5", "pass5"},
    {"User6", "pass6"},
};
Login::Login(BSSMqttClient* mqttClient, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    this->bssHttpMethod = BssHttpMethod::getBssHttpMenthod();
    this->cabCom = CabinetCom::getCabCom();
    this->ui->lblLoginStatus->setText("");
    this->mqttClient=mqttClient;
    QObject::connect(this->mqttClient,&BSSMqttClient::onUserLogin,this,&Login::onRemoteLogin);
    loginTimeoutTimer=new QTimer(this);
    runProgressBar = new QTimer(this);
    QObject::connect(loginTimeoutTimer,&QTimer::timeout,this,&Login::onLoginTimeout);
    connect(this, &Login::destroyed, loginTimeoutTimer , &QTimer::deleteLater);
    connect(runProgressBar,&QTimer::timeout, this, &Login::setValueTimeoutBar);
    connect(this->bssHttpMethod, &BssHttpMethod::onLoginSuccess,this,&Login::acceptLogin);
    connect(this->bssHttpMethod,&BssHttpMethod::onLoginFail, this,&Login::rejectLogin);
    loginTimeoutTimer->start(60000);
    runProgressBar->start(10);
    ui->btnLogin->setFocus();
}

Login::~Login()
{
    delete ui;
}
void Login::setValueTimeoutBar(){
    this->ui->timeoutBar->setValue(loginTimeoutTimer->remainingTime());
}
void Login::on_btnLogin_clicked()
{
    QString username=ui->txtUsername->text();
    QString password=ui->txtPassword->text();
    User* user = new User();
    user->setUsername(username);
    user->setPassword(password);
    bssHttpMethod->setUser(user);
    for (int i=0; i< listDataUserLazadaHub.length(); i++)
    {
        if(((username == listDataUserLazadaHub[i][0]) && (password == listDataUserLazadaHub[i][1])) || (username=="Test" && password.toInt()>=0 && password.toInt() < 15)){
            if(username=="Test"){
                is_staff_login = 1;
                cab_id = password.toUInt()-1;
            }
            acceptLogin(user);
            return;
        }
    }
    bssHttpMethod->onLoginSendRequest(user);
}
void Login::acceptLogin(const User *user){
    CabinetCom::getCabCom()->getSwapRecord()->setUser(user->getUsername());
    this->ui->lblLoginStatus->setText("");
    UserView* userView=new UserView(user);
    userView->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    userView->showFullScreen();
    close();
}
void Login::rejectLogin(){
    this->ui->txtUsername->setFocus();
    this->ui->lblLoginStatus->setText("Sai mật khẩu hoặc tài khoản");
}
void Login::on_btnCancel_clicked() {
    this->cabCom->setLoginFlag(false);
    loginTimeoutTimer->stop();
    runProgressBar->stop();
    close();
}

void Login::onRemoteLogin(const User *user) {
    UserView* userView=new UserView(user);
    userView->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    userView->showFullScreen();
    loginTimeoutTimer->stop();
    runProgressBar->stop();
    close();

}

void Login::onLoginTimeout()
{
    this->cabCom->setLoginFlag(false);
    loginTimeoutTimer->stop();
    runProgressBar->stop();
    close();
}

void Login::on_txtUsername_textChanged(const QString &arg1)
{
    (void)arg1;
//    loginTimeoutTimer->stop();
//    loginTimeoutTimer->start(10000);
}

void Login::on_txtPassword_textChanged(const QString &arg1)
{
    (void)arg1;
//   loginTimeoutTimer->stop();
//   loginTimeoutTimer->start(10000);
}

void Login::on_btnLogin_pressed()
{
    this->ui->btnLogin->setStyleSheet("background: transparent;"
                                      "background-image:url(:/img/UI/images/SELEX SBS icon/Group 365.png);"
                                      "background-repeat: no-repeat;"
                                      "background-position:left top;"
                                      "background-position:center;");
}

void Login::on_btnLogin_released()
{
    this->ui->btnLogin->setStyleSheet("background: transparent;"
                                      "background-image:url(:/img/UI/images/SELEX SBS icon/Group 368.png);"
                                      "background-repeat: no-repeat;"
                                      "background-position:left top;"
                                      "background-position:center;");
}

void Login::on_btnCancel_pressed()
{
    this->ui->btnCancel->setStyleSheet("background: transparent;"
                                      "background-image:url(:/img/UI/images/SELEX SBS icon/Group 366.png);"
                                      "background-repeat: no-repeat;"
                                       "background-position:left top;"
                                       "background-position:center;");
}

void Login::on_btnCancel_released()
{
    this->ui->btnCancel->setStyleSheet( "background: transparent;"
                                        "background-image:url(:/img/UI/images/SELEX SBS icon/Group 367.png);"
                                        "background-repeat: no-repeat;"
                                        "background-position:left top;"
                                        "background-position:center;");
}

void Login::on_txtUsername_returnPressed()
{

}

void Login::on_txtUsername_cursorPositionChanged(int arg1, int arg2)
{
    //has text inside changed
}

void Login::on_txtUsername_selectionChanged()
{
    //qDebug()<<"HASSSSSSSSSSSSSSSSSSSSSSSSSSSSS";
}

void Login::on_txtUsername_textEdited(const QString &arg1)
{
    //qDebug()<<"textedited";
}

void Login::on_txtUsername_customContextMenuRequested(const QPoint &pos)
{
    //qDebug()<<"custom";
}

void Login::on_txtUsername_windowIconTextChanged(const QString &iconText)
{
    //qDebug()<<"ICON CHANGE";
}

void Login::on_timeoutBar_valueChanged(int value)
{
    this->ui->labelCountDowTimeout->setText("Thời gian còn lại:"+ QString::number(int(value/1000)) + "giây");
    if(value > (this->ui->timeoutBar->maximum()/ 5)) {
        this->ui->timeoutBar->setStyleSheet("QProgressBar::chunk {"
                                      "background-color: qlineargradient( x1: 0, y1 : 0, x2: 1,  y2: 0, stop:0.5 cyan, stop:0.9 white);"
                                      "border-radius:4px;}"
                                      "QProgressBar {"
                                      "border: 0px;"
                                      "border-radius: 4px;"
                                      "background: rgb(136, 138, 133);"
                                      "padding: 0px;"
                                      "margin-right: 4px;}");

    this->ui->labelCountDowTimeout->setStyleSheet("color: rgb(15, 45, 208);");
    }
    else {
        this->ui->timeoutBar->setStyleSheet("QProgressBar::chunk {"
                                      "background-color: qlineargradient( x1: 0, y1 : 0, x2: 1,  y2: 0, stop:0.5 red, stop:0.9 white);"
                                      "border-radius:4px;}"
                                      "QProgressBar {"
                                      "border: 0px;"
                                      "border-radius: 4px;"
                                      "background: rgb(136, 138, 133);"
                                      "padding: 0px;"
                                      "margin-right: 4px;}");
    this->ui->labelCountDowTimeout->setStyleSheet("color:red;");
    }
//    else ui->timeoutBar->setStyleSheet("QProgressBar::chunk { background: red; }");
}

