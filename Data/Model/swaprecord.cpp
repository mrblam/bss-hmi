#include "swaprecord.h"

QString SwapRecord::getOldPack() const
{
    return oldPack;
}

void SwapRecord::setOldPack(const QString &value)
{
    oldPack = value;
}

QString SwapRecord::getNewPack() const
{
    return newPack;
}

void SwapRecord::setNewPack(const QString &value)
{
    newPack = value;
}

QString SwapRecord::getBss() const
{
    return bss;
}

void SwapRecord::setBss(const QString &value)
{
    bss = value;
}

SWAP_RECORD_STATE SwapRecord::getState() const
{
    return state;
}
void SwapRecord::setStatusWriteRecord(const STATUS_WRITE_SWAPRECORD &value)
{
    statusWriteRecord = value;
}
STATUS_WRITE_SWAPRECORD SwapRecord::getStatusWriteRecord() const
{
    return statusWriteRecord;
}
void SwapRecord::setState(const SWAP_RECORD_STATE &value)
{
    switch (value) {
    case SWAP_RECORD_ST_RETURN:
        timeout_ms=20000;
        break;
    case SWAP_RECORD_ST_CHARGE_ONLY:
        timeout_ms=20000;
        break;
    case SWAP_RECORD_ST_CHECKING_BP:
        timeout_ms=9000;
        break;
    case SWAP_RECORD_ST_WAITING_OLD_BP:
        timeout_ms =40000;
        break;
    case SWAP_RECORD_ST_DELIVERY:
        timeout_ms =20000;
        break;
    case SWAP_RECORD_ST_BP_ACCEPTED:
        timeout_ms=300000;
        break;
    case SWAP_RECORD_ST_SELECT_EMPTY_CAB:
        setErrCode(SWAP_NO_ERR);
        timeout_ms=20000;
        break;
    case SWAP_RECORD_ST_SUCCESS:
        setErrCode(SWAP_NO_ERR);
        timeout_ms =20000;
        break;
    case SWAP_RECORD_ST_FINISH:
        timeout_ms=5000;
        break;
    case SWAP_RECORD_STATE_COM_FAIL:
        timeout_ms=10000;
        break;
    case SWAP_RECORD_ST_FAIL:
        timeout_ms=10000;
        break;
    }
    state = value;
    resetTimeoutCounter();
}
void SwapRecord::toArray(QByteArray &arr) const{
    QJsonObject json;
    toJson(json);
    QJsonDocument doc(json);
    arr = doc.toJson(QJsonDocument::Indented);
}
void SwapRecord::toArray(QByteArray &arr, QJsonObject& json) const{
    toJson(json);
    QJsonDocument doc(json);
    arr = doc.toJson(QJsonDocument::Indented);
}
void SwapRecord::toJson(QJsonObject &json) const
{
    if(oldCab!=nullptr){
    json["old_bat"]=oldCab->getBp()->getSerialNumber();
    json["old_cab"]=(double)oldCab->getId();
    }
    else{
        json["old_bat"]="null";
        json["old_cab"]=(double)(-1);

    }
    if(newCab!=nullptr){
        json["new_bat"]=newCab->getBp()->getSerialNumber();
        json["new_cab"]=(double)newCab->getId();
    }else{
        json["new_bat"]="null";
        json["new_cab"]=(double)(-1);

    }
    json["state"]=(double) state;
    json["error"]=(double) errCode;
    json["bss"]=bss;
}

void SwapRecord::fromJson(const QJsonObject &json)
{

    if (json.contains("old_bp") && json["old_bp"].isString()){
        oldCab->getBp()->setSerialNumber(json["old_bp"].toString());
    }

    if (json.contains("new_bp") && json["new_bp"].isString()){
        oldCab->getBp()->setSerialNumber(json["new_bp"].toString());
    }

    if (json.contains("bss") && json["bss"].isString()){
        bss=json["bss"].toString();
    }

    if (json.contains("user") && json["user"].isString()){
        user=json["user"].toString();
    }

    if (json.contains("state") && json["state"].isDouble()){
        state=(SWAP_RECORD_STATE) json["state"].toInt();
    }
}

int32_t SwapRecord::parse(const QByteArray &data, const char sep)
{
    return -1;
}

QString SwapRecord::getUser() const
{
    return user;
}

void SwapRecord::setUser(const QString &value)
{
    user = value;
}

Cabinet *SwapRecord::getNewCab() const
{
    return newCab;
}

void SwapRecord::setNewCab(Cabinet *value)
{
    newCab = value;
}

void SwapRecord::resetTimeoutCounter()
{
    timeoutCounter=0;
}

void SwapRecord::incTimeoutCounter(const uint32_t i)
{
    timeoutCounter+=i;
    if(timeoutCounter > timeout_ms){
        timeoutCounter=timeout_ms+1;
    }
}

Cabinet *SwapRecord::getOldCab() const
{
    return oldCab;
}

void SwapRecord::setOldCab(Cabinet *value)
{
    oldCab = value;
}

uint32_t SwapRecord::getTimeout() const
{
    return timeout_ms;
}

void SwapRecord::setTimeout(const uint32_t &value)
{
    timeout_ms = value;
}

uint32_t SwapRecord::getTimeoutCounter() const
{
    return timeoutCounter;
}

bool SwapRecord::isTimeout()
{
    if(timeoutCounter >= timeout_ms){
        return true;
    }
    return false;
}

SWAP_ERROR_CODE SwapRecord::getErrCode() const
{
    return errCode;
}

void SwapRecord::setErrCode(const SWAP_ERROR_CODE &value)
{
    errCode = value;
}

SwapRecord::SwapRecord()
{
    setState(SWAP_RECORD_ST_SELECT_EMPTY_CAB);
    setErrCode(SWAP_NO_ERR);
    oldPack="";
    newPack="";
    bss="";
    setOldCab(nullptr);
    setNewCab(nullptr);
}
