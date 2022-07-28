
#include "swapview.h"
#include "ui_swapview.h"
#include "bpview.h"

#include <QDebug>
//static uint32_t cab_arr[15] = {3,5,4,7,9,8,10,11,13,12,14,0,1,2,6};
static uint32_t cab_arr[6] = {0,1,2,3,4,5};

SwapView::SwapView(CabinetCom* cab, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SwapView)
{
    //this->ui->lblHeader->setVisible(false);
    animationTimer = new QTimer();
    //this->deleteLater();
    this ->setAttribute( Qt::WA_DeleteOnClose, true );
    this->cabCom=cab;
    ui->setupUi(this);

    if(this->cabCom->getComState()!=COM_ST_CONNECTED){
        this->cabCom->getSwapRecord()->setState(SWAP_RECORD_STATE_COM_FAIL);
    }
    else{
        connect(this->cabCom,&CabinetCom::onCabinetComFail,this,&SwapView::onComFail);
        connect(this->cabCom,&CabinetCom::onSwapRecordChanged,this,&SwapView::guiUpdateSwapState);
        connect(animationTimer, &QTimer::timeout, this, &SwapView::animationSlot);
    }
    animationTimer->start(7);
    this->ui->lblIcon->setVisible(false);
    //this->cabCom->getSwapRecord()->setState(SWAP_RECORD_ST_SELECT_EMPTY_CAB);
    guiUpdateSwapState(this->cabCom->getSwapRecord());// mo ra khoang trong
    startTimeoutTimer(1000);
    connectMonitor::getConnectionMonitor()->checkUI(UI_DISPLAY_SWAPRECORD,true);
}

void SwapView::guiUpdateSwapState(const SwapRecord* swapRecord)
{
    static BPView* bp_view=nullptr;

    switch (this->cabCom->getSwapRecord()->getState()) {
    case SWAP_RECORD_ST_CHARGE_ONLY:
        qDebug()<<"SWAP_RECORD_ST_CHARGE_ONLY";
        if(this->cabCom->getBssModel()->getCabinets().at(7)->getOpState()==CAB_OP_ST_EMPTY){
            this->cabCom->getSwapRecord()->setOldCab(this->cabCom->getBssModel()->getCabinets().at(7));
            this->ui->lblHeader->setText("Xin mời quý khách cho pin khoang\n\n");
            this->ui->lblState->setText(QString::number((this->cabCom->getSwapRecord()->getOldCab()->getId())+1));
            //this->cabCom->setSwappingFlag(true);
            break;
            }
        this->ui->lblHeader->setText("Mời nhận lại pin\n\n");
        //this->cabCom->getSwapRecord()->setState(SWAP_RECORD_ST_CONTINUE);
        break;
    case SWAP_RECORD_ST_SELECT_EMPTY_CAB:
#if 1
        if(is_staff_login){
            this->cabCom->getSwapRecord()->setOldCab(this->cabCom->getBssModel()->getCabinets().at(cab_id));
            is_staff_login=0;
        }
        else{
            for(uint32_t j=0; j<this->cabCom->getBssModel()->getCabinetNum(); j++){
                uint32_t i = cab_arr[j];
                if(this->cabCom->getBssModel()->getCabinets().at(i)->getOpState()==CAB_OP_ST_EMPTY){
                    this->cabCom->getSwapRecord()->setOldCab(this->cabCom->getBssModel()->getCabinets().at(i));
                    QList<QUrl> list;
                    list << PUT_BAT_IN_CAB;
                    if(this->cabCom->getSwapRecord()->getOldCab()->getId() < uint32_t(cabNumberSound.length())){
                        list << cabNumberSound.at(this->cabCom->getSwapRecord()->getOldCab()->getId());
                    }
                    list << CLOSE_DOOR;
                    SoundExecution::getSoundExecution()->play(list);
                    break;
                }
            }

        }

#endif
        //this->ui->lblHeader->setText("Xin mời quý khách cho pin khoang\n\n");
//        this->ui->btnAction->setText("Hủy");
//        this->ui->btnAction->setEnabled(true);
        this->ui->bpPin->setVisible(true);
        this->ui->lblHeader->setVisible(false);
        this->ui->lblIcon->setVisible(false);
        this->ui->lblState->setText(QString::number((this->cabCom->getSwapRecord()->getOldCab()->getId())+1));
        this->cabCom->setSwappingFlag(true);
        this->oldCabNum = this->cabCom->getSwapRecord()->getOldCab()->getId() +1;
        break;
    case SWAP_RECORD_ST_WAITING_OLD_BP:
        this->ui->lblHeader->setVisible(false);
        this->ui->bpPin->setVisible(true);

        break;
    case SWAP_RECORD_ST_CHECKING_BP:
        SoundExecution::getSoundExecution()->play(CHECKING_BAT);
        this->ui->centralwidget->setStyleSheet("#centralwidget {border-image: url(:/img/UI/images/Custom Size – 14.png) 0 0 0 0 stretch stretch;}");
        this->ui->bpPin->setVisible(false);
        this->ui->lblState->setVisible(false);
        this->ui->lblHeader->setText("Hệ thống đang kiểm tra pin\n Xin chờ trong giây lát.\n");
        this->ui->lblHeader->setVisible(true);
        this->ui->lblIcon->setVisible(true);
        this->ui->lblIcon->setStyleSheet(   "background: transparent;"
                                            "background-image:url(:/img/UI/images/SELEX SBS icon/Group 381.png);"
                                            "background-repeat: no-repeat;"
                                            "text-decoration: none;"
                                            "background-position:left top;"
                                            "background-position: center;");
        //this->ui->btnAction->setEnabled(true);
        break;
    case SWAP_RECORD_ST_BP_ACCEPTED:
        this->ui->lblHeader->setText("Xác thực pin thành công.");
        //this->ui->btnAction->setEnabled(false);
        bp_view=new BPView(this->cabCom->getSwapRecord()->getOldCab(),this);
        bp_view ->setAttribute( Qt::WA_DeleteOnClose, true );
        bp_view->showFullScreen();
        break;
    case SWAP_RECORD_ST_DELIVERY:
        this->ui->centralwidget->setStyleSheet("#centralwidget{border-image: url(:/img/UI/images/Custom Size – 7.png) 0 0 0 0 stretch stretch;}");
        this->ui->bpPin->setVisible(true);
        this->ui->lblIcon->setVisible(false);
        if(this->cabCom->getSwapRecord()->getNewCab()!=nullptr){
            if(swapRecord->getNewCab()->getBp()->getVoltage()>=65500 ){
            this->ui->lblHeader->setText("Mời quý khách lấy pin mới\nở ô\n");
            this->ui->lblHeader->setVisible(false);
            this->ui->lblState->setText(QString::number((this->cabCom->getSwapRecord()->getNewCab()->getId())+1));
            this->ui->lblState->setVisible(true);
            QList<QUrl> list;
            list << OPEN_DOOR;
            if(this->cabCom->getSwapRecord()->getOldCab()->getId() < uint32_t(cabNumberSound.length())){
                list << cabNumberSound.at(this->cabCom->getSwapRecord()->getNewCab()->getId());
            }
            SoundExecution::getSoundExecution()->play(list);
            //this->ui->btnAction->setEnabled(false);
            }
        }
        else{
            SoundExecution::getSoundExecution()->play(BAT_RUN_OUT);
            //this->ui->btnAction->setEnabled(true);
            //this->ui->lblState->setText(QString(this->cabCom->getSwapRecord()->getOldCab()->getId()+1));
            this->ui->lblHeader->setText("Khoang pin hết.\nXin quý khách thông cảm");
            this->ui->centralwidget->setStyleSheet("#centralwidget {border-image: url(:/img/UI/images/Custom Size – 14.png) 0 0 0 0 stretch stretch;}");
            this->ui->lblIcon->setStyleSheet("background: transparent;"
                                             "background-image:url(:/img/UI/images/SELEX SBS icon/Group 383.png);"
                                             "background-repeat: no-repeat;"
                                             "text-decoration: none;"
                                             "background-position:left top;"
                                             "background-position: center;");
            this->ui->lblIcon->setVisible(true);
            this->ui->bpPin->setVisible(false);
            this->ui->lblHeader->setVisible(true);
        }

        break;
    case SWAP_RECORD_ST_RETURN:
        this->ui->bpPin->setVisible(false);
        this->ui->lblIcon->setVisible(true);
        this->ui->centralwidget->setStyleSheet("#centralwidget {border-image: url(:/img/UI/images/Custom Size – 14.png) 0 0 0 0 stretch stretch;}");
        this->ui->lblIcon->setStyleSheet("background: transparent;"
                                         "background-image:url(:/img/UI/images/SELEX SBS icon/Group 383.png);"
                                         "background-repeat: no-repeat;"
                                         "text-decoration: none;"
                                         "background-position:left top;"
                                         "background-position: center;");
        if(!(this->cabCom->getSwapRecord()->getErrCode() == SWAP_ERR_BP_RUNOUT)) this->ui->lblHeader->setText("Xin mời nhận lại pin\n và đóng cửa khoang pin");
        this->ui->lblHeader->setVisible(true);
        this->ui->lblState->setVisible(false);
        break;
    case SWAP_RECORD_ST_SUCCESS:
        //this->ui->btnAction->setEnabled(false);
        this->ui->lblHeader->setVisible(false);
        this->ui->bpPin->setVisible(true);
        //this->ui->lblHeader->setText("Vui lòng đóng cửa khoang pin"); // để đăng xuất!
        break;
    case SWAP_RECORD_ST_FAIL:
        break;
    case SWAP_RECORD_ST_FINISH:
        finishSwapSession();
        break;
    case SWAP_RECORD_STATE_COM_FAIL:
        break;
    }
}

void SwapView::startTimeoutTimer(const uint32_t ms)
{
    timeoutTimer=new QTimer();
    //connect(timeoutTimer,&QTimer::timeout,this,&SwapView::processSwapState);
    connect(this, &SwapView::destroyed, timeoutTimer , &QTimer::deleteLater);
    timeoutTimer->start(ms);
}


SwapView::~SwapView()
{
    connectMonitor::getConnectionMonitor()->checkUI(UI_DISPLAY_SWAPRECORD,false);
    delete ui;
}

void SwapView::onComStateChanged(const COM_STATE &newState)
{

    switch (newState) {
    case COM_ST_CONNECTED:
        break;
    case COM_ST_DISCONNECTED:
        break;
    case COM_ST_DATA_TIMEOUT:
        break;
    case COM_ST_PORT_ERROR:
        break;
    }

}

void SwapView::onComFail()
{
}

void SwapView::finishSwapSession()
{
//  this->cabCom->getSwapRecord()->setUser("");
    static Continue* ctn = nullptr;
    this->cabCom->setSwappingFlag(false);
    if((this->cabCom->getSwapRecord()->getErrCode() == SWAP_NO_ERR)||
       (this->cabCom->getSwapRecord()->getErrCode() == SWAP_ERR_CHECKING_BP_TIMEOUT)){
        ctn =new Continue(this->cabCom);
        ctn->setAttribute( Qt::WA_DeleteOnClose, true );
        ctn->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        ctn->showFullScreen();
    }
    else{
        this->cabCom->setLoginFlag(false);
    }
    animationTimer->stop();
    timeoutTimer->stop();
    close();



}


void SwapView::onUserSwapRequest()
{
    Cabinet* cab=nullptr;
    for(uint32_t j=0; j<this->cabCom->getBssModel()->getCabinetNum(); j++){
        uint32_t i = cab_arr[j];
        if(((this->cabCom->getBssModel()->getCabinets().at(i)->getOpState()==CAB_OP_ST_STANDBY)||
            (this->cabCom->getBssModel()->getCabinets().at(i)->getOpState()==CAB_OP_ST_CHARGING))&&
                (this->cabCom->getBssModel()->getCabinets().at(i)->getId()!= this->cabCom->getSwapRecord()->getOldCab()->getId()) &&
                (this->cabCom->getBssModel()->getCabinets().at(i)->getBp()->getVoltage() > 65500)){
            cab=this->cabCom->getBssModel()->getCabinets().at(i);
            break;
        }
    }
    this->cabCom->getSwapRecord()->setNewCab(cab);
    this->cabCom->getSwapRecord()->setState(SWAP_RECORD_ST_DELIVERY);
    guiUpdateSwapState(this->cabCom->getSwapRecord());
    this->cabCom->userSwappingRequest();
}

void SwapView::onUserSwapCancel()
{
    this->cabCom->getSwapRecord()->setState(SWAP_RECORD_ST_RETURN);
    guiUpdateSwapState(this->cabCom->getSwapRecord());
    this->cabCom->userSwappingCancel();
}

void SwapView::animationSlot(){
    if((this->cabCom->getSwapRecord()->getState() == SWAP_RECORD_ST_WAITING_OLD_BP)||
            (this->cabCom->getSwapRecord()->getState() == SWAP_RECORD_ST_CHECKING_BP)){
        numberPicture++;
        if(numberPicture <210)this->ui->bpPin->setGeometry(numberPicture+225,705,271-numberPicture,120);
        if(numberPicture >= 310) numberPicture =0;
    }

    if(this->cabCom->getSwapRecord()->getState() == SWAP_RECORD_ST_RETURN ||
       this->cabCom->getSwapRecord()->getState() == SWAP_RECORD_ST_SUCCESS ||
       this->cabCom->getSwapRecord()->getState()== SWAP_RECORD_ST_DELIVERY){
        if(numberPicture < 0) numberPicture =310;
            numberPicture--;
            if(numberPicture > 100 )
                this->ui->bpPin->setGeometry(numberPicture+125,705,371-numberPicture,120);
    }
}
