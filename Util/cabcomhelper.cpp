#include "cabcomhelper.h"
#include <QDebug>

CAB_PROTOCOL_STATE CabComHelper::getProtocolState() const
{
    return protocolState;
}

void CabComHelper::setProtocolState(const CAB_PROTOCOL_STATE &value)
{
    protocolState = value;
    if(value==CAB_PROTOCOL_ST_WAIT_RESPONSE){
        isBusy=true;
    }
    else{
        isBusy=false;
    }
}

void CabComHelper::receiveData(const QByteArray &new_data){   
    //qDebug()<<"Data received: " <<new_data;
    rxBuffer.append(new_data);
}

Cabinet *CabComHelper::getRemoteCabinet()
{
   return &remoteCabinet;
}

BSS *CabComHelper::getRemoteBSS()
{

    return &remoteBSS;
}

BP *CabComHelper::getRemoteBP()
{
    return &remoteBP;
}
/*cmdCode+code++sub+index*/
CabComHelper::CabComHelper(QObject* parent):QObject(parent)
{
    cmdHeader.cmdCode=CMD_READ;
    cmdHeader.objMux.code=BSS_DATA_CODE;
    cmdHeader.objMux.index=0;
    cmdHeader.objMux.sub=BSS_STATE_DATA_CODE;
    remoteCabinet.setBp(new BP());
}

int32_t CabComHelper::parseRxData()
{
    if(getProtocolState() != CAB_PROTOCOL_ST_WAIT_RESPONSE) {
        rxBuffer.clear();
        return (-1);
    }

    if(rxBuffer.length()<=0) return (-1);
    int32_t start=rxBuffer.indexOf(SOM);
    int32_t finish=rxBuffer.indexOf(EOM);

    if(finish<start){
        rxBuffer.remove(0,start);
        return (-1);
    }

    QByteArray pack=rxBuffer.mid(start+1,finish-start-1);
    qDebug()<< "--> " +pack;
    rxBuffer.clear();

    QList<QByteArray> fields=pack.split(FIELD_DELIMITER);
    if(fields.at(0).at(0) != cmdHeader.cmdCode||(fields.at(1).at(0) != cmdHeader.objMux.code) ||
            (fields.at(2) !=cmdHeader.objMux.index) ||
            (fields.at(3).at(0) !=cmdHeader.objMux.sub)){
        return -1;
    }

    if(cmdHeader.cmdCode==CMD_WRITE){
        if(fields.at(4).at(0)!='O'){
            setProtocolFailState(COM_ERR_WRITE);
            return (0);
        }

        switch (cmdHeader.objMux.code) {
        case BSS_DATA_CODE:
            if(cmdHeader.objMux.sub==BSS_STATE_DATA_CODE){
                localBss->setState(remoteBSS.getState());
                break;
            }
            if(cmdHeader.objMux.sub==BSS_ID_ASSIGN_CODE){
                localCabinet->setOpState(remoteCabinet.getOpState());
                break;
            }
            if(cmdHeader.objMux.sub==BSS_AUTH_CODE){
                localCabinet->setOpState(remoteCabinet.getOpState());
                break;
            }
           break;
        case CAB_DATA_CODE:
            if(cmdHeader.objMux.sub==CAB_OP_CODE){
                localCabinet->setOpState(remoteCabinet.getOpState());
                break;
            }
            if(cmdHeader.objMux.sub==CAB_DOOR_CODE){
                localCabinet->setDoorState(remoteCabinet.getDoorState());
                break;
            }
            break;
        case BP_DATA_CODE:
            break;
        default:
            setProtocolFailState(COM_ERR_CMD_NO_SUPPORT);
            return (0);
        }
        setProtocolSuccessState();
        return (0);
    }

    switch (cmdHeader.objMux.code) {
    case BSS_DATA_CODE:
        return bssParseSubData(&remoteBSS,pack);
    case CAB_DATA_CODE:
        return cabParseSubData(&remoteCabinet,pack);
    case BP_DATA_CODE:
        return bpParseSubData(&remoteBP,pack);
    default:
        setProtocolFailState(COM_ERR_CMD_NO_SUPPORT);
        return (0);
    }

    return (0);
}

int32_t CabComHelper::bssParseSubData(BSS *bss, const QByteArray &pack_data)//bss remote
{
//bss = remotebss
    bool ok = false;
    int result = -1;
    BSS_STATE state=BSS_ST_FAIL;
    QList<QByteArray> fileds=pack_data.split(FIELD_DELIMITER);//tach thanh cac truong theo delimiter ","
    QByteArray data=fileds.at(4);
    for(int i=0;i<4;i++){
        fileds.removeFirst();
    }
    QByteArray subData=fileds.join(FIELD_DELIMITER);
    switch (cmdHeader.objMux.sub) {
    case BSS_STATE_DATA_CODE:
        state=(BSS_STATE)data.toUInt(&ok);
        if(!ok){
            setProtocolFailState(COM_ERR_PARSE);
            return (0);
        }
        bss->setState(state);
        setProtocolSuccessState();
        break;
    case BSS_CAB_NUM_DATA_CODE:
        if(!ok){
            setProtocolFailState(COM_ERR_PARSE);
            return (0);
        }
        setProtocolSuccessState();
        break;
    case ALL_OBJECT_SUB_DATA_CODE:
        result= bss->parse(subData,FIELD_DELIMITER);
        if(result >0){
            qDebug() <<"new tilt state";
            return 1;
        }
        break;

    default:
        setProtocolFailState(COM_ERR_CMD_NO_SUPPORT);
        return (0);
    }
    return (1);
}

int32_t CabComHelper::cabParseSubData(Cabinet *cab, const QByteArray &pack_data)
{
    CABINET_OP_STATE op_state;
    DOOR_STATE door_state;
    bool ok=false;
    int result=-1;
    int index=cmdHeader.objMux.index.toInt(&ok);
    if(!ok){
        setProtocolFailState(COM_ERR_PARSE);
        return (0);
    }
    cab->setId(index);

    QList<QByteArray> fileds=pack_data.split(FIELD_DELIMITER);
    QByteArray data=fileds.at(4);
    for(int i=0;i<4;i++){
        fileds.removeFirst();
    }
    QByteArray subData=fileds.join(FIELD_DELIMITER);

    switch (cmdHeader.objMux.sub) {
    case CAB_OP_CODE:
        op_state=(CABINET_OP_STATE)data.toUInt(&ok);
        if(!ok){
            setProtocolFailState(COM_ERR_PARSE);
            return (0);
        }
        cab->setOpState(op_state);
        setProtocolSuccessState();
        break;
    case CAB_DOOR_CODE:
        door_state=(DOOR_STATE)data.toUInt(&ok);
        if(!ok){
            setProtocolFailState(COM_ERR_PARSE);
            return (0);
        }
        cab->setDoorState(door_state);
        setProtocolSuccessState();

        break;
    case ALL_OBJECT_SUB_DATA_CODE:
        result= cab->parse(subData,FIELD_DELIMITER);
        if(result >=0){
            setProtocolSuccessState();
        }
        else{
            setProtocolFailState(COM_ERR_PARSE);
            return (0);
        }
        break;

    default:
        setProtocolFailState(COM_ERR_CMD_NO_SUPPORT);
        return (0);
    }

    return (2);
}

int32_t CabComHelper::bpParseSubData(BP *bp, const QByteArray &pack_data)
{
    int result=-1;

    QList<QByteArray> fileds=pack_data.split(FIELD_DELIMITER);
    QByteArray data=fileds.at(4);
    for(int i=0;i<4;i++){
        fileds.removeFirst();
    }
    QByteArray subData=fileds.join(FIELD_DELIMITER);

    switch (cmdHeader.objMux.sub) {
    case ALL_OBJECT_SUB_DATA_CODE:
        result=bp->parse(subData,FIELD_DELIMITER);
        if(result>=0){
            setProtocolSuccessState();
        }
        else{
            setProtocolFailState(COM_ERR_PARSE);
           return (0);
        }
        break;
    default:
        setProtocolFailState(COM_ERR_CMD_NO_SUPPORT);
        return (0);
    }
    return (3);
}

void CabComHelper::cabBuildWriteSubObject(QByteArray* buff,const Cabinet *cab, const char &sub, const QByteArray &data)
{
    ObjectMux mux;
    mux.code=CAB_DATA_CODE;
    mux.index=QString::number(cab->getId()).toUtf8();
    mux.sub=sub;

    buildWriteCMDData(buff,mux,data);
}

void CabComHelper::bssBuildWriteSubObject(QByteArray *buff,const BSS *bss, const char &sub, const QByteArray &data)
{
    ObjectMux mux;
    mux.code=BSS_DATA_CODE;
    mux.index=QString::number(bss->getId()).toUtf8();
    mux.sub=sub;
    buildWriteCMDData(buff,mux,data);
}

void CabComHelper::bpBuildWriteSubObject(QByteArray *buff, const BP *bp, const char &sub, const QByteArray &data)
{
    ObjectMux mux;
    mux.code=BP_DATA_CODE;
    mux.index=QString::number(bp->getId()).toUtf8();
    mux.sub=sub;
    buildWriteCMDData(buff,mux,data);
}

void CabComHelper::cabBuildReadSubObject(QByteArray *buff, const Cabinet *cab, const char &sub)
{
    ObjectMux mux;
    mux.code=CAB_DATA_CODE;
    mux.index=QString::number(cab->getId()).toUtf8();
    mux.sub=sub;
    buildReadCMDData(buff,mux);
}

void CabComHelper::bssBuildReadSubObject(QByteArray *buff, const BSS *bss, const char &sub)
{
    ObjectMux mux;
    mux.code=BSS_DATA_CODE;
    mux.index=QString::number(bss->getId()).toUtf8();
    mux.sub=sub;
    buildReadCMDData(buff,mux);
}

void CabComHelper::bpBuildReadSubObject(QByteArray *buff, const BP *bp, const char &sub)
{
    ObjectMux mux;
    mux.code=BP_DATA_CODE;
    mux.index=QString::number(bp->getId()).toUtf8();
    mux.sub=sub;
    buildReadCMDData(buff,mux);
}

Cabinet *CabComHelper::getLocalCabinet() const
{
    return localCabinet;
}

void CabComHelper::setLocalCabinet(Cabinet *value)
{
    localCabinet = value;
    remoteCabinet=*value;
}

BSS *CabComHelper::getLocalBss() const
{
    return localBss;
}

void CabComHelper::setLocalBss(BSS *value)
{
    localBss = value;
    remoteBSS=*value;
}

BP *CabComHelper::getLocalBP() const
{
    return localBP;
}

void CabComHelper::setLocalBP(BP *value)
{
    localBP = value;
    remoteBP=*value;
}

bool CabComHelper::getIsBusy() const
{
    return isBusy;
}

void CabComHelper::setIsBusy(bool value)
{
    isBusy = value;
}

COM_ERROR_CODE CabComHelper::getErrorCode() const
{
    return errorCode;
}

void CabComHelper::setErrorCode(const COM_ERROR_CODE &value)
{
    errorCode = value;
}

void CabComHelper::buildReadCMDData(QByteArray *buff, const ObjectMux &obj_mux)
{

    cmdHeader.cmdCode=CMD_READ;
    cmdHeader.objMux.code=obj_mux.code;
    cmdHeader.objMux.index=obj_mux.index;
    cmdHeader.objMux.sub=obj_mux.sub;
    buff->append(SOM);
    buff->append(cmdHeader.cmdCode);
    buff->append(FIELD_DELIMITER);
    buff->append(cmdHeader.objMux.code);
    buff->append(FIELD_DELIMITER);
    buff->append(cmdHeader.objMux.index);
    buff->append(FIELD_DELIMITER);
    buff->append(cmdHeader.objMux.sub);
    buff->append(EOM);
}

void CabComHelper::buildWriteCMDData(QByteArray *buff, const ObjectMux &obj_mux, const QByteArray &data)
{
    cmdHeader.cmdCode=CMD_WRITE;
    cmdHeader.objMux.code=obj_mux.code;
    cmdHeader.objMux.index=obj_mux.index;
    cmdHeader.objMux.sub=obj_mux.sub;
    buff->append(SOM);
    buff->append(cmdHeader.cmdCode);
    buff->append(FIELD_DELIMITER);
    buff->append(cmdHeader.objMux.code);
    buff->append(FIELD_DELIMITER);
    buff->append(cmdHeader.objMux.index);
    buff->append(FIELD_DELIMITER);
    buff->append(cmdHeader.objMux.sub);
    if(data.length()>0){
        buff->append(FIELD_DELIMITER);
        buff->append(data);
    }
    buff->append(EOM);
}

void CabComHelper::setProtocolFailState(const COM_ERROR_CODE& error)
{
    errorCode=error;
    setProtocolState( CAB_PROTOCOL_ST_FAIL);
    qDebug()<<"Error: " << QString::number(error);
    emit onFail();
}

void CabComHelper::setProtocolSuccessState()
{
    errorCode=COM_NO_ERROR;
    setProtocolState( CAB_PROTOCOL_ST_IDLE);
}
