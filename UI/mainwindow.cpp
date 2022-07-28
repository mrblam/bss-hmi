#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "UI/swapview.h"
#include "UI/login.h"
#include <QPainter>

MainWindow::MainWindow(CabinetCom* cabCom,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    isForward = true;
    hasLoginClick = false;
    timeoutClick = 0;
    position = 1;
    ui->setupUi(this);
    this->cabCom=cabCom;
    connect(this->cabCom,&CabinetCom::onBSSChanged,this,&MainWindow::onBSSStateChanged);
    connect(this->cabCom,&CabinetCom::onBSSChanged,this, &MainWindow::onBSSTiltChange);
    connect (&animationTimer, &QTimer::timeout, this,&MainWindow::animationSlot);
    animationTimer.start(20);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onBSSTiltChange(const BSS *bss){
    (void)bss;
//    if(bss->getTiltState()!=TILT_ST_ACTIVE) {
//        this->ui->btnLogin->setText("");
//        this->ui->btnLogin->setEnabled(true);
//        return;
//    }
//    qDebug() <<"has tilt";
//    this->ui->btnLogin->setText("Trạm nghiêng");
//    this->ui->btnLogin->setEnabled(false);
}
void MainWindow::onBSSStateChanged(const BSS* bss){

    switch (bss->getState()) {
        case BSS_ST_MAINTAIN:
        this->ui->btnLogin->setText("Hệ thống đang bảo trì");
        this->ui->btnLogin->setStyleSheet("background: transparent;"
                                          "border:none;"
                                          "border-image:url(:/img/UI/images/SELEX SBS icon/Group 161.png);"
                                          "background-repeat: no-repeat;"
                                          "text-decoration: none;");
        this->ui->btnLogin->setEnabled(false);
        break;
    case BSS_ST_SYNC:
        this->ui->btnLogin->setText("");
        this->ui->btnLogin->setEnabled(true);
        break;
    case BSS_ST_FAIL:
        this->ui->btnLogin->setText("Hệ thống lỗi");
        this->ui->btnLogin->setStyleSheet("background: transparent;"
                                          "border:none;"
                                          "border-image:url(:/img/UI/images/SELEX SBS icon/Group 161.png);"
                                          "background-repeat: no-repeat;"
                                          "text-decoration: none;");
        this->ui->btnLogin->setEnabled(true);
        break;
    case BSS_ST_INIT:
        this->ui->btnLogin->setText("Đang khởi tạo");
        this->ui->btnLogin->setStyleSheet(  "background: transparent;"
                                            "border:none;"
                                            "border-image:url(:/img/UI/images/SELEX SBS icon/Group 161.png);"
                                            "background-repeat: no-repeat;"
                                            "text-decoration: none;");
        this->ui->btnLogin->setEnabled(true);
        break;
    default:
        break;
    }
}
void MainWindow::on_btnLogin_clicked()
{
//    Login* loginView=new Login(BSSMqttClient::getBSSMqttClient());
//    loginView->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
//    loginView->showFullScreen();
}


void MainWindow::on_btnLogin_pressed()
{
    if(timeoutClick != 0) return;
    hasLoginClick = true;
    timeoutClick = 100;
    if(position<0) position =0;
    this->ui->btnLogin->setDisabled(true);
    this->ui->btnLogin->setStyleSheet("background: transparent;"
                                      "border:none;"
                                      "border-image:url(:/img/UI/images/SELEX SBS icon/Group -10.png);"
                                      "background-repeat: no-repeat;"
                                      "text-decoration: none;");

}
void MainWindow::on_btnLogin_released()
{
//    this->ui->btnLogin->setStyleSheet("background: transparent;"
//                                      "border:none;"
//                                      "background-image:url(:/img/UI/images/SELEX SBS icon/Group 161.png);"
//                                      "background-repeat: no-repeat;"
//                                      "text-decoration: none;");
}
void MainWindow::animationSlot(){
    if(this->cabCom->getSwappingFlag()) return;
    if(timeoutClick >0 )timeoutClick --;
    if(position >0) {
        this->ui->btnLogin->resize(566+position,471+position);
        this->ui->btnLogin->move(110-position/2,700-position);

    }
    if(position>70) {
        isForward = false;
    }
    if(position<=-10 ){
        isForward=true;
        this->ui->btnLogin->setEnabled(false);
        this->ui->btnLogin->setEnabled(true);
    }
    if(position >40){
          if(isForward)position++;
          else position--;
    }
    else{
        if(isForward)position +=2;
        else position -=2;
    }


    if(hasLoginClick){

        Login* loginView=new Login(BSSMqttClient::getBSSMqttClient());
        loginView->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        loginView->showFullScreen();
        this->cabCom->setLoginFlag(true);
        hasLoginClick = false;
        this->ui->btnLogin->setEnabled(true);
        this->ui->btnLogin->setStyleSheet("background: transparent;"
                                          "border:none;"
                                          "border-image:url(:/img/UI/images/SELEX SBS icon/Group 161.png);"
                                          "background-repeat: no-repeat;"
                                          "text-decoration: none;");
    }
}

