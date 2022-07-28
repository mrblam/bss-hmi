#include "userview.h"
#include "ui_userview.h"
#include "UI/swapview.h"
#include "bpview.h"

User *UserView::getUserModel() const
{
    return userModel;
}

UserView::UserView(const User* user,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserView)
{
    ui->setupUi(this);
    CabinetCom* cab = CabinetCom::getCabCom();
    if(cab->getBssModel()->getCabinets().at(5)->getOpState()== CAB_OP_ST_EMPTY){
        //this->ui->btnOnlyCharge->setText("Xạc tại chỗ");
    }
    else{
        //this->ui->btnOnlyCharge->setText("Nhận lại pin");
    }
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    userModel=new User();
    userModel->setUsername(user->getUsername());
    userModel->setPassword(user->getPassword());
    this->ui->lblUserName->setText(user->getUsername());
    timeoutProgressBar = new QTimer(this);
    userActionTimeout=new QTimer(this);
    connect(timeoutProgressBar, &QTimer::timeout, this, &UserView::setTimeoutProgressBarValue);
    connect(userActionTimeout,&QTimer::timeout,this,&UserView::onUserActionTimeout);
    connect(this, &UserView::destroyed, userActionTimeout , &QTimer::deleteLater);
    userActionTimeout->start(20000);
    timeoutProgressBar->start(10);
    SoundExecution::getSoundExecution()->play(USER_VIEW);
    connectMonitor::getConnectionMonitor()->checkui(UI_DISPLAY_USER_VIEW,true);
}

UserView::~UserView()
{
    connectMonitor::getConnectionMonitor()->checkui(UI_DISPLAY_USER_VIEW,false);
    delete ui;
}
void UserView::setTimeoutProgressBarValue(){
    this->ui->timeoutBar->setValue(userActionTimeout->remainingTime());
}
void UserView::on_btnSwap_clicked()
{
    if(CabinetCom::getCabCom()->getSyncState() != SYNC_STATE_READ_BSS_STATE) return;
    CabinetCom* cab = CabinetCom::getCabCom();
    cab->getSwapRecord()->setState(SWAP_RECORD_ST_SELECT_EMPTY_CAB);
    SwapView* swapView = new SwapView(cab);
    swapView->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    swapView->showFullScreen();
    closeUserView();
}

void UserView::on_btnLogout_clicked()
{
    closeUserView();
    SoundExecution::getSoundExecution()->play(THANK_YOU_USING_SERVICE);
}

//void UserView::on_btnCheckBattery_clicked()
//{
//    CabinetCom* cab= CabinetCom::getCabCom();
//    cab->getSwapRecord()->setState(SWAP_RECORD_ST_CHARGE_ONLY);
//    SwapView* swapView = new SwapView(cab);
//    swapView->setWindowFlags(Qt::Window | Qt::FramelessWindowHint) ;
//    swapView->showFullScreen();
//    closeUserView();
//}

void UserView::onUserActionTimeout()
{
    closeUserView();
}

void UserView::closeUserView()
{
   timeoutProgressBar->stop();
   userActionTimeout->stop();
   close();
}

void UserView::on_btnOnlyCharge_clicked()
{
//    CabinetCom* cab= CabinetCom::getCabCom();
//    cab->getSwapRecord()->setState(SWAP_RECORD_ST_CHARGE_ONLY);
//    SwapView* swapView = new SwapView(cab);
//    swapView->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
//    swapView->showFullScreen();
//    closeUserView();
}


void UserView::on_btnSwap_pressed()
{
    if(CabinetCom::getCabCom()->getSyncState() != SYNC_STATE_READ_BSS_STATE) return;
    this->ui->btnSwap->setStyleSheet("background: transparent;"
                                     "background-image:url(:/img/UI/images/SELEX SBS icon/Group 372.png);"
                                     "background-repeat: no-repeat;"
                                     "background-position:left top;"
                                     "background-position:center;");
}

void UserView::on_btnSwap_released()
{
    if(CabinetCom::getCabCom()->getSyncState() != SYNC_STATE_READ_BSS_STATE) return;
    this->ui->btnSwap->setStyleSheet("background: transparent;"
                                     "background-image:url(:/img/UI/images/SELEX SBS icon/Group 371.png);"
                                     "background-repeat: no-repeat;"
                                     "background-position:left top;"
                                     "background-position:center;");
}

void UserView::on_btnLogout_released()
{
    this->ui->btnLogout->setStyleSheet("background: transparent;"
                                       "background-image:url(:/img/UI/images/SELEX SBS icon/Group 370.png);"
                                       "background-repeat: no-repeat;"
                                       "background-position:left top;"
                                       "background-position:center;");
}

void UserView::on_btnLogout_pressed()
{
    this->ui->btnLogout->setStyleSheet("background: transparent;"
                                       "background-image:url(:/img/UI/images/SELEX SBS icon/Group 373.png);"
                                       "background-repeat: no-repeat;"
                                       "background-position:left top;"
                                       "background-position:center;");
}

void UserView::on_timeoutBar_valueChanged(int value)
{
    this->ui->labelCountDowTimeout->setText("Thời gian còn lại:"+ QString::number(int(value/1000)) + "giây");
    if(value > (this->ui->timeoutBar->maximum() / 5 * 2 )){
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
        this->ui->labelCountDowTimeout->setStyleSheet("color: red;");
    }
}
