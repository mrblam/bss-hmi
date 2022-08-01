#include "cabinetcom.h"

#define HEARTBEAT_TICKER_INTERVAL_mS            500UL
#define PROCESS_TICKER_INTERVAL_mS              200UL

static uint32_t init_cab_id=0;
static uint32_t is_door_changed_close = 0;
static uint32_t swap_return_cnt = 0;

CabinetCom::CabinetCom(QObject *parent) : QObject(parent)
{
    setSwappingFlag(false);
    setLoginFlag(false);
    this->comState=COM_ST_DISCONNECTED;
    this->syncState = SYNC_STATE_READ_BSS_STATE;
    this->syncCabinetState = SYNC_CABINET_STATE_SET_INIT;
    this->port.setBaudRate(QSerialPort::Baud115200);
    if(this->port.isOpen()){
        this->port.close();
    }
    this->processThread=new QThread(this);
    connect(this, &CabinetCom::onBSSChanged, this, &CabinetCom::getTiltSensor);
    connect(this,&CabinetCom::onBPChanged,this,&CabinetCom::saveBPData);
    connect(this,&CabinetCom::onBSSChanged,this,&CabinetCom::saveBSSData);
    connect(this,&CabinetCom::onCabinetChanged,this,&CabinetCom::saveCabinetData);
    connect(&this->comHelper,&CabComHelper::onFail,this,&CabinetCom::onComFail);
    connect(&heartbeatTicker,&QTimer::timeout,this,&CabinetCom::processBSSStateMachine);
    swapRecord=new SwapRecord();
}

void CabinetCom::processBSSStateMachine()//loop
{
    heartbeatCounter+=HEARTBEAT_TICKER_INTERVAL_mS;
    if(heartbeatCounter>=10000){
        heartbeatCounter=0;
        this->bssModel->setErrorCode(BSS_ERR_COM_DATA_TIMEOUT);
        switchToBSSState(BSS_ST_FAIL);
        emit onBSSChanged(this->bssModel);
        emit onComStateChanged(comState);
        qDebug()<<"Cabinet loss connect.";

        start();
        return;
    }

    if(comHelper.getProtocolState()==CAB_PROTOCOL_ST_WAIT_RESPONSE){
        return;
    }
//    connectMonitor::getConnectionMonitor()->checkUI(UI_DISPLAY_DEFAULT,true);
    Cabinet* initCab=nullptr;
    switch (this->bssModel->getState()) {
    case BSS_ST_INIT:
        writeBSSState(BSS_ST_MAINTAIN);
        break;
    case BSS_ST_MAINTAIN:
        if(init_cab_id>=bssModel->getCabinetNum()){
            switchToBSSState(BSS_ST_SYNC);
            swapRecord->setState(SWAP_RECORD_ST_FINISH);
            break;
        }

        initCab=bssModel->getCabinets().at(init_cab_id);
        if(initCab->getOpState()==CAB_OP_ST_EMPTY){
            init_cab_id++;
            break;
        }
        updateConfigCabState(initCab);
        if(initCab->getBp()->getState()!=BP_ST_INIT){
            emit onNewBatteryAccepted(initCab);
            init_cab_id++;
            break;
        }
        break;
    case BSS_ST_FAIL:
        fail_recover_timeout_ms+=HEARTBEAT_TICKER_INTERVAL_mS;
        if(fail_recover_timeout_ms>=5000){
            comHelper.setProtocolState(CAB_PROTOCOL_ST_IDLE);
            switchToBSSState(BSS_ST_INIT);
        }
        break;
    case BSS_ST_SYNC:
        if(getLoginFlag() && getSyncState() == SYNC_STATE_READ_BSS_STATE){
            if(getSwappingFlag()){
                qDebug() << "swapping";
                processSwapState();
                break;
            }
            qDebug()<<"sync without update";
            requestDataSyncWithoutUpdate();
            break;
        }
        qDebug() << "sync with update";
        requestDataSyncUpdate();
        break;
    default:
        break;
    }
}
void CabinetCom::requestDataSyncUpdate(){
    static bool cabUpdate = true;
    static uint32_t syncCabinetNumber=0;
    switch (getSyncState()) {
    case SYNC_STATE_READ_BSS_STATE:
        readBSSState();
        setSyncState(SYNC_STATE_READ_ALL_OBJECT);
        break;
    case SYNC_STATE_READ_ALL_OBJECT:
        readBSSAllObjectSubDataCode();
        setSyncState(SYNC_STATE_READ_CABINETS);
        break;
    case SYNC_STATE_READ_CABINETS:
        qDebug()<< "number of Cabinet Number:"<<syncCabinetNumber;

        if(cabUpdate){
            readCabinetState(bssModel->getCabinets().at(syncCabinetNumber));
            cabUpdate = false;
            break;
        }
        if(syncCabinet(bssModel->getCabinets().at(syncCabinetNumber))){
            syncCabinetNumber++;
            cabUpdate = true;
            if(getLoginFlag()){
                if(syncCabinetNumber >= bssModel->getCabinetNum()){
                    syncCabinetNumber = 0;
                    setSyncState(SYNC_STATE_READ_BSS_STATE);
                }
                setSyncState(SYNC_STATE_READ_BSS_STATE);
                break;
            }
        }
        if(syncCabinetNumber >= bssModel->getCabinetNum()){
            syncCabinetNumber = 0;
            setSyncState(SYNC_STATE_READ_BSS_STATE);
        }

        break;
    default:
        break;
    }
}
bool CabinetCom::syncCabinet(Cabinet *cab){
    static bool bpSynced=true;
    if(cab->getOpState()== CAB_OP_ST_STANDBY)
    {
        if(bpSynced){
            readCabinetState(cab);
            bpSynced=false;
            return false;
        }
        setSyncCabinetState(SYNC_CABINET_STATE_SET_INIT);
        readBPData(cab->getBp());
        bpSynced=true;
        return true;
    }
    if(cab->getOpState() == CAB_OP_ST_CHARGING){
        setSyncCabinetState(SYNC_CABINET_STATE_SET_INIT);
        readCabinetState(cab);
        return true;
    }
    static uint32_t countdownReadingCabinets = 0;
    switch (getSyncCabinetState()) {
        case SYNC_CABINET_STATE_SET_INIT:
            writeCabinetState(cab, CAB_OP_ST_INIT);
            setSyncCabinetState(SYNC_CABINET_STATE_SET_BP_ASSIGN_ID);
            break;
        case SYNC_CABINET_STATE_SET_BP_ASSIGN_ID:
            startCabinetIDAssign(cab);
            setSyncCabinetState(SYNC_CABINET_STATE_READ_CABINET);
            countdownReadingCabinets =20;
            break;
        case SYNC_CABINET_STATE_READ_CABINET:
            readCabinetState(cab);
            if(cab->getOpState() == CAB_OP_ST_BP_ID_AUTHORIZE){
                emit onCabinetChanged(cab);
                setSyncCabinetState(SYNC_CABINET_STATE_SET_AUTHORIZE);
                break;
            }//test tinh nang khoa swap btn
            if(cab->getOpState() == CAB_OP_ST_EMPTY) {
                emit onCabinetChanged(cab);
                setSyncCabinetState(SYNC_CABINET_STATE_SET_INIT);
                return true;
                break;
            }

            if(countdownReadingCabinets >0) {
                countdownReadingCabinets--;
                break;
            }
            else{
                setSyncCabinetState(SYNC_CABINET_STATE_SET_EMPTY);
                break;
            }
            break;
        case SYNC_CABINET_STATE_SET_AUTHORIZE:
            bpAuthSuccessConfirm(cab);
            setSyncCabinetState(SYNC_CABINET_STATE_READ_CABINET);
            break;
        case SYNC_CABINET_STATE_SET_EMPTY:
            writeCabinetState(cab, CAB_OP_ST_EMPTY);
            setSyncCabinetState(SYNC_CABINET_STATE_SET_INIT);
            return true;
            break;
        case SYNC_CABINET_STATE_FINISH:
            break;
        default:
            break;
    }
    return false;
}
void CabinetCom::requestDataSyncWithoutUpdate(){
    static bool bpSynced=false;
    static uint32_t syncCabId=0;
        if(syncCabId==0){
            readBSSState();
            syncCabId++;
        }
        else if(syncCabId ==1){
            readBSSAllObjectSubDataCode();
            syncCabId++;
        }
        else{
            if(bssModel->getCabinets().at(syncCabId-2)->getOpState()==CAB_OP_ST_STANDBY)
            {
                if(bpSynced==true){
                    readCabinetState(bssModel->getCabinets().at(syncCabId-2));
                    bpSynced=false;
                }
                else
                {
                    readBPData(bssModel->getCabinets().at(syncCabId-2)->getBp());
                    bpSynced=true;
                    syncCabId++;
                }
            }
            else
            {
                readCabinetState(bssModel->getCabinets().at(syncCabId-2));
                syncCabId++;
            }
        }

        if(syncCabId>=(bssModel->getCabinetNum()+2)){
            syncCabId=0;
        }
}

void CabinetCom::updateConfigCabState(Cabinet *cab)
{
    switch (cab->getOpState()) {
    case CAB_OP_ST_CHARGING:
        readBPData(cab->getBp());
        break;
    case CAB_OP_ST_STANDBY:
        readBPData(cab->getBp());
        break;
    case CAB_OP_ST_EMPTY:
        readCabinetState(cab);
        break;
    case CAB_OP_ST_BP_ID_ASSIGN:
        readCabinetState(cab);
        break;
    case CAB_OP_ST_BP_ID_AUTHORIZE:
        if(cab->getBp()->getSerialNumber()=="0"){
           readCabinetState(cab);
           break;
        }
        startBPAuth(cab);
        break;
    case CAB_OP_ST_INIT:
        startCabinetIDAssign(cab);
        break;
    default:
        break;
    }
}


void CabinetCom::processSwapState()
{
    swapRecord->incTimeoutCounter(HEARTBEAT_TICKER_INTERVAL_mS);
    switch (swapRecord->getState()) {
    case SWAP_RECORD_ST_CHARGE_ONLY:
        if((swapRecord->getOldCab()!=nullptr) && (swapRecord->getOldCab()->getOpState()!=CAB_OP_ST_INIT)){
            if(swapRecord->isTimeout()){
                swapRecord->setErrCode(SWAP_ERR_INIT_OLD_CAB_FAIL);
                swapRecord->setState(SWAP_RECORD_ST_FINISH);
                swapRecord->setStatusWriteRecord(UPDATE);
                emit onSwapRecordChanged(swapRecord);
                break;
            }
            writeCabinetState(swapRecord->getOldCab(),CAB_OP_ST_INIT);
            break;
        }
        break;
    case SWAP_RECORD_ST_SELECT_EMPTY_CAB:

        if((swapRecord->getOldCab()!=nullptr) && (swapRecord->getOldCab()->getOpState()!=CAB_OP_ST_INIT)){
            if(swapRecord->isTimeout()){
                swapRecord->setErrCode(SWAP_ERR_INIT_OLD_CAB_FAIL);
                swapRecord->setState(SWAP_RECORD_ST_FINISH);
                swapRecord->setStatusWriteRecord(UPDATE);
                emit onSwapRecordChanged(swapRecord);
                break;
            }
            writeCabinetState(swapRecord->getOldCab(),CAB_OP_ST_INIT);
            break;
        }
        if(swapRecord->isTimeout()){
            swapRecord->setErrCode(SWAP_ERR_OLD_CAB_OPEN_DOOR_FAIL);
            swapRecord->setState(SWAP_RECORD_ST_RETURN);
            emit onSwapRecordChanged(swapRecord);
            break;
        }

        if(swapRecord->getOldCab()==nullptr) break;
        writeCabinetDoorState(swapRecord->getOldCab(),DOOR_ST_OPEN);
        if(swapRecord->getOldCab()->getDoorState()==DOOR_ST_OPEN){
            swapRecord->getOldCab()->setDoorState(DOOR_ST_CLOSE); // ???
            is_door_changed_close = 0;
            swapRecord->setState(SWAP_RECORD_ST_WAITING_OLD_BP);
            swapRecord->setStatusWriteRecord(INSERT);
            emit onSwapRecordChanged(swapRecord);
        }
        break;
    case SWAP_RECORD_ST_WAITING_OLD_BP:
        if(swapRecord->isTimeout()){
            swapRecord->setErrCode(SWAP_ERR_INSERT_BP_TIMEOUT);
            swapRecord->setState(SWAP_RECORD_ST_RETURN);
            is_door_changed_close=0;
            emit onSwapRecordChanged(swapRecord);
            break;
        }

        if((swapRecord->getOldCab()->getDoorState()==DOOR_ST_OPEN)){
            is_door_changed_close++;
        }

        if((swapRecord->getOldCab()->getDoorState()==DOOR_ST_CLOSE)
                &&(is_door_changed_close>2)){
            swapRecord->setState(SWAP_RECORD_ST_CHECKING_BP);
            swapRecord->setStatusWriteRecord(UPDATE);
            emit onSwapRecordChanged(swapRecord);
            is_door_changed_close = 0;
            break;
        }
        readCabinetState(swapRecord->getOldCab());
        break;
    case SWAP_RECORD_ST_CHECKING_BP:
        if(swapRecord->isTimeout()){
            swapRecord->setErrCode(SWAP_ERR_CHECKING_BP_TIMEOUT);
            swapRecord->setState(SWAP_RECORD_ST_RETURN);
            emit onSwapRecordChanged(swapRecord);
            break;
        }
        if((swapRecord->getOldCab()->getBp()->getState()!= BP_ST_INIT)){
            //swapRecord->setOldPack(BP_ST_CHARGING);
            swapRecord->setState(SWAP_RECORD_ST_BP_ACCEPTED);
            swapRecord->setStatusWriteRecord(UPDATE);
            emit onSwapRecordChanged(swapRecord);
            break;
        }
        updateConfigCabState(swapRecord->getOldCab());
        break;
    case SWAP_RECORD_ST_DELIVERY:
        if(swapRecord->isTimeout()){writeCabinetDoorState(swapRecord->getOldCab(),DOOR_ST_OPEN);
            swapRecord->setErrCode(SWAP_ERR_DELIVERY_FAIL);
            swapRecord->setState(SWAP_RECORD_ST_RETURN);
            swap_return_cnt=0;
            swapRecord->setStatusWriteRecord(UPDATE);
            emit onSwapRecordChanged(swapRecord);
            break;
        }
        if(swapRecord->getNewCab()!=nullptr && swapRecord->getNewCab()->getDoorState() == DOOR_ST_CLOSE) //neu co new cab
        {
            writeCabinetDoorState(swapRecord->getNewCab(),DOOR_ST_OPEN);
            break;
        }
        swap_return_cnt++;
        if(swapRecord->getNewCab()==nullptr){
            readCabinetState(swapRecord->getOldCab());
        }
        else
        {
            readCabinetState(swapRecord->getNewCab());
        }
        if(swap_return_cnt < 5) break;
        if(swapRecord->getNewCab() == nullptr){
            swapRecord->setErrCode(SWAP_ERR_BP_RUNOUT);
            swapRecord->setState(SWAP_RECORD_ST_RETURN);
            swapRecord->setStatusWriteRecord(UPDATE);
            swap_return_cnt = 0;
            emit onSwapRecordChanged(swapRecord);
         }
        else{
            swapRecord->getNewCab()->setOpState(CAB_OP_ST_EMPTY);
            swapRecord->setErrCode(SWAP_NO_ERR);
            swapRecord->setState(SWAP_RECORD_ST_SUCCESS);
            swapRecord->setStatusWriteRecord(UPDATE);
            swap_return_cnt = 0;
            emit onSwapRecordChanged(swapRecord);
        }
        break;
    case SWAP_RECORD_ST_RETURN:
        if(swapRecord->isTimeout()){
            swapRecord->setErrCode(SWAP_ERR_RETURN_FAIL);
            swapRecord->setState(SWAP_RECORD_ST_FINISH);
            swap_return_cnt = 0;
            is_door_changed_close = 0;
            swapRecord->setStatusWriteRecord(UPDATE);
            emit onSwapRecordChanged(swapRecord);
            break;
        }

        if(swapRecord->getErrCode() == SWAP_ERR_OLD_CAB_OPEN_DOOR_FAIL){
            swapRecord->setState(SWAP_RECORD_ST_FINISH);
            emit onSwapRecordChanged(swapRecord);
        }
        if(swap_return_cnt == 0){
            writeCabinetDoorState(swapRecord->getOldCab(),DOOR_ST_OPEN);
            swapRecord->getOldCab()->setDoorState(DOOR_ST_CLOSE);
            swap_return_cnt++;
            break;
        }
        if(swapRecord->getErrCode()== SWAP_ERR_CHECKING_BP_TIMEOUT){
            swap_return_cnt =0;
            is_door_changed_close = 0;
            swapRecord->setState(SWAP_RECORD_ST_FINISH);
            swapRecord->setStatusWriteRecord(UPDATE);
            emit onSwapRecordChanged(swapRecord);
            break;
        }
        if(swapRecord->getOldCab()->getDoorState()==DOOR_ST_OPEN){
            is_door_changed_close++;
        }
        if((swapRecord->getOldCab()->getDoorState()==DOOR_ST_CLOSE)
                && (is_door_changed_close>2)){
            swapRecord->setState(SWAP_RECORD_ST_FINISH);
            is_door_changed_close = 0;
            swap_return_cnt=0;
            swapRecord->setStatusWriteRecord(UPDATE);
            emit onSwapRecordChanged(swapRecord);
            break;
        }
        if(swapRecord->getErrCode() == SWAP_ERR_INSERT_BP_TIMEOUT){
            writeCabinetState(swapRecord->getOldCab(), CAB_OP_ST_EMPTY);
            swapRecord->setState(SWAP_RECORD_ST_FINISH);
            is_door_changed_close = 0;
            swap_return_cnt=0;
            emit onSwapRecordChanged(swapRecord);
            break;
        }
        readCabinetState(swapRecord->getOldCab());
        break;
    case SWAP_RECORD_ST_BP_ACCEPTED:
        readBPData(swapRecord->getOldCab()->getBp());
        break;
    case SWAP_RECORD_ST_FINISH:
        break;
    case SWAP_RECORD_ST_SUCCESS:
        if(swapRecord->isTimeout()){
            swapRecord->setErrCode(SWAP_ERR_DOOR_NOT_CLOSE);
            swapRecord->setState(SWAP_RECORD_ST_FINISH);
            swapRecord->setStatusWriteRecord(UPDATE);
            emit onSwapRecordChanged(swapRecord);
            break;
        }
        if(swapRecord->getNewCab()->getDoorState() == DOOR_ST_CLOSE){
            swapRecord->setErrCode(SWAP_NO_ERR);
            swapRecord->setState(SWAP_RECORD_ST_FINISH);
            swapRecord->setStatusWriteRecord(UPDATE);
            emit onSwapRecordChanged(swapRecord);
            break;
        }
        readCabinetState(swapRecord->getNewCab());
        break;
    case SWAP_RECORD_ST_FAIL:
            if(swapRecord->isTimeout()){
                swapRecord->setState(SWAP_RECORD_ST_FINISH);
                emit onSwapRecordChanged(swapRecord);
            }
        break;
    default:
        break;
    }
}

void CabinetCom::switchToBSSState(const BSS_STATE &state)
{
    switch (state) {
    case BSS_ST_INIT:
        init_cab_id=0;
        setSwappingFlag(false);
        setLoginFlag(false);
        for(uint32_t i=0;i<bssModel->getCabinetNum();i++){
            bssModel->getCabinets().at(i)->setOpState(CAB_OP_ST_INIT);
        }
        bssModel->setState(BSS_ST_INIT);
        writeBSSState(BSS_ST_MAINTAIN);
        break;
    case BSS_ST_MAINTAIN:
        setSwappingFlag(false);
        setLoginFlag(false);
        bssModel->setState(BSS_ST_MAINTAIN);
        break;
    case BSS_ST_FAIL:
        processTimer.stop();
        rxBuffer.clear();
        comHelper.setProtocolState(CAB_PROTOCOL_ST_IDLE);
        bssModel->setErrorState(NODE_ST_FAIL);
        bssModel->setState(BSS_ST_FAIL);
        if(getSwappingFlag() == true){
            swapRecord->setState(SWAP_RECORD_ST_FAIL);
            emit onSwapRecordChanged(swapRecord);
        }
        fail_recover_timeout_ms=0;
        break;
    case BSS_ST_SYNC:
        writeBSSState(BSS_ST_SYNC);
        break;
    default:
        break;
    }
    emit onBSSChanged(bssModel);
}


void CabinetCom::startCabinetIDAssign(Cabinet* cab) {
    QByteArray data;
    QByteArray subData;
    subData.append(QString::number(cab->getId()).toUtf8());
    comHelper.bssBuildWriteSubObject(&data,bssModel,BSS_ID_ASSIGN_CODE,subData);
    comHelper.setLocalBss(bssModel);
    comHelper.setLocalCabinet(cab);
    comHelper.getRemoteCabinet()->setOpState(CAB_OP_ST_BP_ID_ASSIGN);
    cabComWritePackage(data);
}
void CabinetCom::startBPAuth(Cabinet *cab)
{
    bpAuthSuccessConfirm(cab);
}

void CabinetCom::onComFail()
{
    switchToBSSState(BSS_ST_FAIL);
    emit onCabinetComFail();
}

void CabinetCom::bpAuthFailConfirm(const Cabinet* cab)
{
    QByteArray data;
    QByteArray subData;
    subData.append(QString::number(cab->getId()).toUtf8());
    subData.append(FIELD_DELIMITER);
    subData.append(QString::number(BSS_AUTH_FAIL_CODE).toUtf8());
    comHelper.bssBuildWriteSubObject(&data,bssModel,BSS_AUTH_CODE,subData);
    comHelper.setLocalBss(bssModel);
    comHelper.setLocalCabinet(bssModel->getCabinets().at(cab->getId()));
    comHelper.getRemoteCabinet()->setOpState(CAB_OP_ST_EMPTY);
    cabComWritePackage(data);
}

void CabinetCom::bpAuthSuccessConfirm(const Cabinet* cab)
{
    QByteArray data;
    QByteArray subData;
    subData.append(BSS_AUTH_SUCCESS_CODE);
    comHelper.bssBuildWriteSubObject(&data,bssModel,BSS_AUTH_CODE,subData);
    comHelper.setLocalBss(bssModel);
    comHelper.setLocalCabinet(bssModel->getCabinets().at(cab->getId()));
    comHelper.getRemoteCabinet()->setOpState(CAB_OP_ST_STANDBY);
    cabComWritePackage(data);
}
void CabinetCom::start()
{
    comState=COM_ST_DISCONNECTED;
    if(this->port.isOpen()){
        this->port.close();
    }
        //qDebug() <<"timeout"<<getChangePortTimeout();
    if(getChangePortTimeout() >=2){
        if(getCurrentPortName() != USB_PORT_1 ){
            this->port.setPortName(getChangePortName(USB_PORT_1));
            qDebug() << "change comport tty_USB_1 ";
        }
        else{
            qDebug() << "change comport tty_USB_0 ";
            this->port.setPortName(getChangePortName(USB_PORT_0));
        }
        changePortTimeout=0;
    }
    else this->port.setPortName(getChangePortName(getCurrentPortName()));

    if (!this->port.open(QIODevice::ReadWrite)) {
        qDebug()<<"Can't open cabinet com port.";
        comState=COM_ST_PORT_ERROR;
        changePortTimeout++;
        processTimer.stop();
        this->bssModel->setErrorState(NODE_ST_FAIL);
        this->bssModel->setErrorCode(BSS_ERR_COM_PORT);
        emit onBSSChanged(this->bssModel);
        emit onComStateChanged(comState);
    }
    else{
        connect(&this->port,&QSerialPort::readyRead,this,&CabinetCom::getComData);
        connect(&this->processTimer,&QTimer::timeout,this,&CabinetCom::processReceivedData);
        qDebug()<<"Cabinet port connected";
        comState=COM_ST_CONNECTED;
        changePortTimeout=0;
        emit onComStateChanged(comState);
        this->bssModel->setErrorState(NODE_ST_NO_ERROR);
        emit onBSSChanged(this->bssModel);
        processTimer.start(PROCESS_TICKER_INTERVAL_mS);
    }
    heartbeatCounter=0;
    heartbeatTicker.start(HEARTBEAT_TICKER_INTERVAL_mS);
}
void CabinetCom::start(const QString& portname)
{
    qDebug()<<"Start open port: " <<portname;
    comState=COM_ST_DISCONNECTED;
    if(this->port.isOpen()){
        this->port.close();
        this->port.setPortName(portname);
    }
    this->port.setPortName(portname);
    if (!this->port.open(QIODevice::ReadWrite)) {
        qDebug()<<"Can't open cabinet com port.";
        //qDebug() << "error code = " << port->error();
        comState=COM_ST_PORT_ERROR;
        processTimer.stop();
        this->bssModel->setErrorState(NODE_ST_FAIL);
        this->bssModel->setErrorCode(BSS_ERR_COM_PORT);
        emit onBSSChanged(this->bssModel);
        emit onComStateChanged(comState);
    }else{
        connect(&this->port,&QSerialPort::readyRead,this,&CabinetCom::getComData);
        connect(&this->processTimer,&QTimer::timeout,this,&CabinetCom::processReceivedData);
        qDebug()<<"Cabinet port connected";
        comState=COM_ST_CONNECTED;
        emit onComStateChanged(comState);
        this->bssModel->setErrorState(NODE_ST_NO_ERROR);
        emit onBSSChanged(this->bssModel);
        processTimer.start(PROCESS_TICKER_INTERVAL_mS);
    }
    heartbeatCounter=0;
    heartbeatTicker.start(HEARTBEAT_TICKER_INTERVAL_mS);
}

void CabinetCom::saveCabinetData(const Cabinet *cab)
{
    Cabinet* cabRepo=bssModel->getCabinets().at(cab->getId());
    cabRepo->setOpState(cab->getOpState());
}

void CabinetCom::saveBPData(const BP *bp)
{
    (void)bp;

}

void CabinetCom::saveBSSData(const BSS *bss)
{
    (void)bss;

}
void CabinetCom::getTiltSensor(const BSS *bss){
    if(bss->getTiltState() == TILT_ST_ACTIVE){
        qDebug() << "has Tilt";
    }
}
void CabinetCom::processReceivedData() //loop
{
    int32_t pack_found=0;
    BP* remoteBPModel;
    BSS* remoteBSSModel;
    Cabinet* remoteCabModel;

    BP* localBPModel=comHelper.getLocalBP();
    BSS* localBSSModel =comHelper.getLocalBss();
    Cabinet* localCabModel =comHelper.getLocalCabinet();

    pack_found=comHelper.parseRxData();
    if(pack_found<=0) return;

    switch (pack_found) {
    case 1://after change
        remoteBSSModel=comHelper.getRemoteBSS();
        updateBssFromRemote(remoteBSSModel,localBSSModel);
        break;
    case 2:
        remoteCabModel = comHelper.getRemoteCabinet();
        updateCabinetFromRemote(remoteCabModel,localCabModel);
        break;
    case 3:
        remoteBPModel = comHelper.getRemoteBP();
        updateBPFromRemote(remoteBPModel,localBPModel);
        break;
    default:
        return;
    }
}

void CabinetCom::writeBSSState(BSS_STATE state) {
    QByteArray data;
    QByteArray subData;
    subData.append(QString::number(state).toUtf8());
    comHelper.bssBuildWriteSubObject(&data,bssModel,BSS_STATE_DATA_CODE,subData);
    comHelper.setLocalBss(bssModel);
    comHelper.getRemoteBSS()->setState(state);
    cabComWritePackage(data);
}

void CabinetCom::readBSSAllObjectSubDataCode(){
    QByteArray data;
    comHelper.bssBuildReadSubObject(&data,bssModel,ALL_OBJECT_SUB_DATA_CODE);
    comHelper.setLocalBss(bssModel);
    cabComWritePackage(data);
}

void CabinetCom::readBSSState()
{
    QByteArray data;
    comHelper.bssBuildReadSubObject(&data,bssModel,BSS_STATE_DATA_CODE);
    comHelper.setLocalBss(bssModel);
    cabComWritePackage(data);
}

void CabinetCom::readBPData(const BP* bp) {
    QByteArray data;
    comHelper.bpBuildReadSubObject(&data,bp,ALL_OBJECT_SUB_DATA_CODE);
    comHelper.setLocalBP(bssModel->getCabinets().at(bp->getId())->getBp());
    cabComWritePackage(data);
}

void CabinetCom::writeBSSCabNum(const uint32_t num) {
    QByteArray data;
    QByteArray subData;
    subData.append(QString::number(num).toUtf8());
    comHelper.bssBuildWriteSubObject(&data,bssModel,BSS_CAB_NUM_DATA_CODE,subData);
    comHelper.setLocalBss(bssModel);
    cabComWritePackage(data);
}

void CabinetCom::writeCabinetState(const Cabinet* cab, CABINET_OP_STATE state) {
    QByteArray data;
    QByteArray subData;
    subData.append(QString::number(state).toUtf8());
    comHelper.cabBuildWriteSubObject(&data,cab,CAB_OP_CODE,subData);
    comHelper.setLocalCabinet(bssModel->getCabinets().at(cab->getId()));
    comHelper.getRemoteCabinet()->setOpState(state);
    cabComWritePackage(data);
}

void CabinetCom::readCabinetState(const Cabinet* cab) {
    QByteArray data;
    comHelper.cabBuildReadSubObject(&data,cab,ALL_OBJECT_SUB_DATA_CODE);
    comHelper.setLocalCabinet(bssModel->getCabinets().at(cab->getId()));
    cabComWritePackage(data);
}

void CabinetCom::writeCabinetDoorState(const Cabinet* cab, DOOR_STATE state)
{
    QByteArray data;
    QByteArray subData;
    subData.append(QString::number(state).toUtf8());
    comHelper.cabBuildWriteSubObject(&data,cab,CAB_DOOR_CODE,subData);
    comHelper.setLocalCabinet(bssModel->getCabinets().at(cab->getId()));
    comHelper.getRemoteCabinet()->setDoorState(state);
    cabComWritePackage(data);
}
void CabinetCom::updateBssFromRemote(BSS *remote, BSS *local) {
    if(remote->getState() != local->getState()){
        local->setState(remote->getState());
    }

    if(remote->getTiltState()!= local->getTiltState()){
        local->setTiltState(remote->getTiltState());
        qDebug()<<"Update remote local";
    }
    comHelper.setProtocolState(CAB_PROTOCOL_ST_IDLE);
    emit onBSSChanged(local);
}

void CabinetCom::updateBPFromRemote(BP *bp, BP *local)
{
    *local= *bp;
    comHelper.setProtocolState(CAB_PROTOCOL_ST_IDLE);
}

void CabinetCom::updateCabinetFromRemote(Cabinet *remote, Cabinet *local)
{
    if((local->getDoorState()!=remote->getDoorState()) && (remote->getDoorState()==DOOR_ST_CLOSE)){
        local->setDoorState(remote->getDoorState());
    }

    if((local->getOpState()!=remote->getOpState())&&(remote->getOpState()==CAB_OP_ST_BP_ID_ASSIGN)){
        local->setOpState(remote->getOpState());
        emit onNewBatteryInserted(local);
    }

    else if((local->getOpState()!=remote->getOpState())&&(remote->getOpState()==CAB_OP_ST_BP_ID_AUTHORIZE)){
        local->setOpState(remote->getOpState());
        emit onBatteryIDAssignSuccess(local);
    }

    else if((local->getOpState()!=remote->getOpState())&&(remote->getOpState()==CAB_OP_ST_STANDBY)){
        local->setOpState(remote->getOpState());
       // emit onNewBatteryAccepted(local);
    }
    else if((local->getOpState()!=remote->getOpState())&&(remote->getOpState()==CAB_OP_ST_EMPTY)){
        local->setOpState(remote->getOpState());
        emit onBatteryDetach(local);
    }
    local->setDoorState(remote->getDoorState());
    local->setFanState(remote->getFanState());
    local->setOpState(remote->getOpState());
    local->getBp()->setSerialNumber(remote->getBp()->getSerialNumber());
    comHelper.setProtocolState(CAB_PROTOCOL_ST_IDLE);
}
void CabinetCom::getComData(){
    if(this->port.bytesAvailable()>0){
        comHelper.receiveData(this->port.readAll());
        heartbeatCounter=0;
    }
}
void CabinetCom::configBSS(const BSS *bss)  {
    if(!this->port.isOpen()) return;
    (void)bss;
}

void CabinetCom::configCabinet(const Cabinet *cab){
    if(!this->port.isOpen()) return;
    QByteArray data;
    data.append(SOM);
    data.append(CMD_WRITE);
    data.append(FIELD_DELIMITER);
    data.append(CAB_DATA_CODE);
    data.append(FIELD_DELIMITER);
    data.append(QString::number(cab->getId()).toUtf8());
    data.append(FIELD_DELIMITER);
    data.append(CAB_DOOR_CODE);
    data.append(FIELD_DELIMITER);
    data.append(QString::number(cab->getDoorState()).toUtf8());
    data.append(EOM);
    this->port.write(data);
}

void CabinetCom::configBP(const BP *bp) {
    (void)bp;
}
void CabinetCom::userSwappingCancel() {
    emit onSwapRecordChanged(this->swapRecord);
}

void CabinetCom::userSwappingRequest()
{
    emit onSwapRecordChanged(this->swapRecord);
}

CabComHelper* CabinetCom::getComHelper()
{
    return &comHelper;
}


COM_STATE CabinetCom::getComState() const
{
    return comState;
}

void CabinetCom::setComState(const COM_STATE &value)
{
    comState = value;
}


void CabinetCom::setBssModel(BSS *value)
{
    bssModel = value;
}

BSS *CabinetCom::getBssModel() const
{
    return bssModel;
}
void CabinetCom::cabComWritePackage(const QByteArray &data)
{
    if(comState!=COM_ST_CONNECTED) return;
    port.write(data);
    comHelper.setProtocolState(CAB_PROTOCOL_ST_WAIT_RESPONSE);
    qDebug()<<QString(data);
}

SwapRecord *CabinetCom::getSwapRecord() const
{
    return swapRecord;
}

void CabinetCom::setSwapRecord(SwapRecord *value)
{
    swapRecord = value;
}

bool CabinetCom::getSwappingFlag() const
{
    return this->swappingFlag;
}
bool CabinetCom::getLoginFlag() const{
    return this->loginFlag;
}
void CabinetCom::setLoginFlag(const bool &loginFlag){
    this->loginFlag = loginFlag;
}
void CabinetCom::setSwappingFlag(bool value)
{
    this->swappingFlag = value;
}
CabinetCom * CabinetCom:: getCabCom()
{
    static CabinetCom* self;
    if(self==nullptr){
        self=new CabinetCom();
    }
    return self;
}

uint32_t CabinetCom::getChangePortTimeout()
{
    return changePortTimeout;
}
void CabinetCom::setChangePortTimeout(uint32_t value)
{
    changePortTimeout = value;
}
USB_PORT_NAME CabinetCom::getCurrentPortName()
{
    return currentPortName;
}
const QString CabinetCom::getChangePortName(USB_PORT_NAME port)
{
    if(port == USB_PORT_0)
    {
        qDebug() << "change port_name : ttyUSB0";
        currentPortName = USB_PORT_0;
        return port_name;
    }
    if(port == USB_PORT_1)  {
        qDebug() <<"change port_name : ttyUSB1";
        currentPortName = USB_PORT_1;
        return port_name1;
    }
    return "/dev/USBS0";
}
QSerialPort *CabinetCom::getPort()
{
    return &this->port;
}
void CabinetCom::setContinueSwap(const bool &value){
    continueSwap = value;
}
bool CabinetCom::getContinueSwap(){
    return continueSwap;
}
void CabinetCom::setSyncState(SYNC_STATE syncState){
    this->syncState = syncState;
}
SYNC_STATE CabinetCom::getSyncState() const{
    return this->syncState;
}
void CabinetCom::setSyncCabinetState(SYNC_CABINET_STATE syncCabinetState){
    this->syncCabinetState = syncCabinetState;
}
SYNC_CABINET_STATE CabinetCom::getSyncCabinetState() const {
    return this->syncCabinetState;
}
