#ifndef SWAPRECORD_H
#define SWAPRECORD_H

#include "basemodel.h"
#include "cabinet.h"
typedef enum STATUS_WRITE_SWAPRECORD {
    INSERT =0,
    UPDATE =1
} STATUS_WRITE_SWAPRECORD;
typedef enum SWAP_RECORD_STATE{
    SWAP_RECORD_ST_SELECT_EMPTY_CAB         =0,
    //SWAP_RECORD_ST_STANDBY_CAB              =0,
    SWAP_RECORD_ST_WAITING_OLD_BP			=1,
    SWAP_RECORD_ST_CHECKING_BP				=2,
    SWAP_RECORD_ST_BP_ACCEPTED				=3,
    SWAP_RECORD_ST_DELIVERY					=5,
    SWAP_RECORD_ST_RETURN					=6,
    SWAP_RECORD_ST_SUCCESS					=9,
    SWAP_RECORD_ST_FINISH					=10,
    SWAP_RECORD_ST_FAIL						=11,
    SWAP_RECORD_STATE_COM_FAIL				=12,
    //SWAP_RECORD_ST_SELECT_EMPTY_CAB			=13,
    SWAP_RECORD_ST_CONTINUE                 =14,
    SWAP_RECORD_ST_CHARGE_ONLY              =15,
}SWAP_RECORD_STATE;

typedef enum SWAP_ERROR_CODE{
    SWAP_NO_ERR						=0,
    SWAP_ERR_INIT_OLD_CAB_FAIL		=1,
    SWAP_ERR_OLD_CAB_OPEN_DOOR_FAIL	=2,
    SWAP_ERR_INSERT_BP_TIMEOUT		=3,
    SWAP_ERR_CHECKING_BP_TIMEOUT	=4,
    SWAP_ERR_AUTH_FAIL				=5,
    SWAP_ERR_BP_RUNOUT				=6,
    SWAP_ERR_DELIVERY_FAIL			=7,
    SWAP_ERR_RETURN_FAIL			=8,
    SWAP_ERR_CONTINUE_FAIL          =9,
    SWAP_ERR_ONLY_CHARGE_FAIL       =10,
    SWAP_ERR_DOOR_NOT_CLOSE         =11,
}SWAP_ERROR_CODE ;


class SwapRecord : public BaseModel
{
private:
    STATUS_WRITE_SWAPRECORD statusWriteRecord;
    SWAP_RECORD_STATE state;
    SWAP_ERROR_CODE errCode;
    QString oldPack;
    QString newPack;
    QString bss;
    QString user;
    Cabinet* oldCab;
    Cabinet* newCab;
    uint32_t timeout_ms;
    uint32_t timeoutCounter;
public:
    SwapRecord();
    QString getOldPack() const;
    void setOldPack(const QString &value);
    QString getNewPack() const;
    void setNewPack(const QString &value);
    QString getBss() const;
    void setBss(const QString &value);
    SWAP_RECORD_STATE getState() const;
    void setState(const SWAP_RECORD_STATE &value);
    void setStatusWriteRecord(const STATUS_WRITE_SWAPRECORD& value);
    STATUS_WRITE_SWAPRECORD getStatusWriteRecord() const;
//    uint32_t getTimeout_ms() const;
//    uint32_t getTimeoutCounter() const;
    // BaseModel interface
public:
    void toArray(QByteArray& arr, QJsonObject& json) const;
    void toArray(QByteArray& arr) const;
    void toJson(QJsonObject &json) const;
    void fromJson(const QJsonObject &json);
    int32_t parse(const QByteArray &data, const char sep);
    QString getUser() const;
    void setUser(const QString &value);
    Cabinet *getOldCab() const;
    void setOldCab(Cabinet *value);
    Cabinet *getNewCab() const;
    void setNewCab(Cabinet *value);
public:
    void resetTimeoutCounter();
    void incTimeoutCounter(const uint32_t i);
    uint32_t getTimeout() const;
    void setTimeout(const uint32_t &value);
    uint32_t getTimeoutCounter() const;
    bool isTimeout();
    SWAP_ERROR_CODE getErrCode() const;
    void setErrCode(const SWAP_ERROR_CODE &value);
};

#endif // SWAPRECORD_H
