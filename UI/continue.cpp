#include "continue.h"
#include "ui_continue.h"
#include "QTimer"
Continue::Continue(const CabinetCom* cab, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Continue)
{
    ui->setupUi(this);
    this->cab=(CabinetCom*)cab;
    if(this->cab->getSwapRecord()->getErrCode() == SWAP_NO_ERR){
        this->ui->lblTextInform->setText("Đổi pin thành công\n bạn có muốn tiếp tục?");
        this->ui->lblIconInform->setStyleSheet("image: url(:/img/UI/images/SELEX SBS icon/done.png);");
    }
    if(this->cab->getSwapRecord()->getErrCode() == SWAP_ERR_CHECKING_BP_TIMEOUT){
        this->ui->lblTextInform->setText("Không nhận dạng được pin\n bạn có muốn thử đổi pin lại?");
        this->ui->lblIconInform->setStyleSheet("image: url(:/img/UI/images/SELEX SBS icon/Group 383.png);");
    }
    timeoutContinueProgressBar = new QTimer();
    continueActionTimeout = new QTimer(this);
    connect(timeoutContinueProgressBar, &QTimer::timeout, this, &Continue::setValueTimeoutProgressBar);
    connect(continueActionTimeout,&QTimer::timeout,this,&Continue::on_actionTimeout);
    connect(this, &Continue::destroyed, continueActionTimeout , &QTimer::deleteLater);
    continueActionTimeout->start(10000);
    timeoutContinueProgressBar->start(10);
}

Continue::~Continue()
{
    delete ui;
}
void Continue::setValueTimeoutProgressBar(){
    this->ui->timeoutBar->setValue(this->continueActionTimeout->remainingTime());
}

void Continue::on_btnContinue_clicked()
{
    this->cab->getSwapRecord()->setState(SWAP_RECORD_ST_SELECT_EMPTY_CAB);
    this->cab->setSwappingFlag(true);
    SwapView* swapView = new SwapView(this->cab);
    swapView->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    swapView->showFullScreen();
    closeContinueView();
}

void Continue::on_btnCancel_clicked()
{
    //finish
    this->cab->setLoginFlag(false);
    closeContinueView();
}

void Continue::on_actionTimeout(){
    //finishon_timeoutBar_valueChanged
    this->cab->setLoginFlag(false);
    closeContinueView();
}

void Continue::closeContinueView(){
    continueActionTimeout->stop();
    timeoutContinueProgressBar->stop();
    close();
}


void Continue::on_btnContinue_pressed()
{
    this->ui->btnContinue->setStyleSheet("background: transparent;"
                                       "background-image:url(:/img/UI/images/SELEX SBS icon/Group 372.png);"
                                       "background-repeat: no-repeat;"
                                       "background-position:left top;"
                                       "background-position:center;");
}
void Continue::on_btnContinue_released()
{
  this->ui->btnContinue->setStyleSheet("background: transparent;"
                                       "background-image:url(:/img/UI/images/SELEX SBS icon/Group 371.png);"
                                       "background-repeat: no-repeat;"
                                       "background-position:left top;"
                                       "background-position:center;");
}



void Continue::on_btnCancel_pressed()
{
    this->ui->btnCancel->setStyleSheet("background: transparent;"
                                       "background-image:url(:/img/UI/images/SELEX SBS icon/Group 394.png);"
                                       "background-repeat: no-repeat;"
                                       "background-position:left top;"
                                       "background-position:center;");
}

void Continue::on_btnCancel_released()
{
    this->ui->btnCancel->setStyleSheet("background: transparent;"
                                       "background-image:url(:/img/UI/images/SELEX SBS icon/Group 395.png);"
                                       "background-repeat: no-repeat;"
                                       "background-position:left top;"
                                       "background-position:center;");
}

void Continue::on_timeoutBar_valueChanged(int value)
{
    this->ui->labelCountDowTimeout->setText("Thời gian còn lại:"+ QString::number(int(value/1000)) + "giây");
    if(value > this->ui->timeoutBar->maximum()/5){
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

