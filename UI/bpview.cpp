#include "bpview.h"
#include "ui_bpview.h"
#include "Data/Model/bp.h"
#include "UI/swapview.h"
static int heightLabelPicPower = 0;
static bool warmingUp= false;
BPView::BPView(const Cabinet* cab,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BPView)
{
    ui->setupUi(this);
    this->cab=(Cabinet*)cab;
    userActionTimeout=new QTimer(this);
    bpViewTimeoutProgressBar = new QTimer(this);
    connect(bpViewTimeoutProgressBar, &QTimer::timeout, this, &BPView::setValueProgressBar);
    connect(userActionTimeout,&QTimer::timeout,this,&BPView::onUserActionTimeout);
    connect(this, &BPView::destroyed, userActionTimeout , &QTimer::deleteLater);
    userActionTimeout->start(20000);
    bpViewTimeoutProgressBar->start(10);
    showBPData();
    SoundExecution::getSoundExecution()->play(BP_VIEW);
    connectMonitor::getConnectionMonitor()->checkui(UI_DISPLAY_BP_VIEW,true);
}

BPView::~BPView()
{
    connectMonitor::getConnectionMonitor()->checkui(UI_DISPLAY_BP_VIEW,false);
    delete ui;
}

void BPView::setValueProgressBar(){
    this->ui->timeoutBar->setValue(userActionTimeout->remainingTime());    
    if(!warmingUp){
        if(heightLabelPicPower < 175){
        this->ui->labelPicPower->setGeometry(406,424-heightLabelPicPower,237,heightLabelPicPower);
        heightLabelPicPower++;
        return;
        }
        warmingUp = true;
        return;
    }
    if(!warmingUp) return;
    if(heightLabelPicPower < (this->cab->getBp()->getSoc()*175/100)) return;
    this->ui->labelPicPower->setGeometry(406,424-heightLabelPicPower,237,heightLabelPicPower);
    heightLabelPicPower --;

}
void BPView::on_btnSwap_clicked()
{
#if 1
   SwapView* swapView=(SwapView*)this->parent();
   swapView->onUserSwapRequest();
   closeBPView();
#endif
}

void BPView::on_btnCancel_clicked()
{
   SwapView* swapView=(SwapView*)this->parent();
   swapView->onUserSwapCancel();

   closeBPView();
}

void BPView::onUserActionTimeout()
{
   SwapView* swapView=(SwapView*)this->parent();
   swapView->onUserSwapCancel();
   closeBPView();
}

void BPView::showBPData()
{
    int SOH=100;
    int32_t Temp = 25;
    this->ui->lblBatSN->setText(this->cab->getBp()->getSerialNumber());
    this->ui->labelCabinNum->setText(QString::number(this->cab->getId()+1));
    this->ui->labelSOC->setText(QString::number(this->cab->getBp()->getSoc()) + "%");
    this->ui->lblSOH->setText(QString::number(SOH));
    this->ui->lblTemp->setText(QString::number(Temp));
    this->ui->lblCycles->setText(QString::number(this->cab->getBp()->getVoltage()));
}

void BPView::closeBPView()
{
    bpViewTimeoutProgressBar->stop();
    userActionTimeout->stop();
    warmingUp = false;
    heightLabelPicPower = 0;
    close();
}

void BPView::on_btnSwap_pressed()
{
    this->ui->btnSwap->setStyleSheet("background: transparent;"
                                      "background-image:url(:/img/UI/images/SELEX SBS icon/Group 372.png);"
                                      "background-repeat: no-repeat;"
                                      "");
}

void BPView::on_btnSwap_released()
{
    this->ui->btnSwap->setStyleSheet("background: transparent;"
                                      "background-image:url(:/img/UI/images/SELEX SBS icon/Group 371.png);"
                                      "background-repeat: no-repeat;"
                                      "");
}

void BPView::on_btnCancel_pressed()
{
    this->ui->btnCancel->setStyleSheet("background: transparent;"
                                      "background-image:url(:/img/UI/images/SELEX SBS icon/Group 373.png);"
                                      "background-repeat: no-repeat;"
                                      "");
}

void BPView::on_btnCancel_released()
{
    this->ui->btnCancel->setStyleSheet("background: transparent;"
                                      "background-image:url(:/img/UI/images/SELEX SBS icon/Group 370.png);"
                                      "background-repeat: no-repeat;"
                                      "");
}

void BPView::on_timeoutBar_valueChanged(int value)
{
    this->ui->labelCountDowTimeout->setText("Thời gian còn lại:"+ QString::number(int(value/1000)) + "giây");
    if(value > (this->ui->timeoutBar->maximum()/ 5*2)) {
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

