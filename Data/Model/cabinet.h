#ifndef CABINET_H
#define CABINET_H
#include "bp.h"

typedef enum FAN_STATE{
    FAN_ST_OFF			=0,
    FAN_ST_ON			=1,
    FAN_ST_FAIL			=2
}FAN_STATE;

typedef enum DOOR_STATE{
    DOOR_ST_CLOSE=0,
    DOOR_ST_OPEN=1
}DOOR_STATE ;

typedef enum CABINET_OP_STATE{
    CAB_OP_ST_INACTIVE		= 0,
    CAB_OP_ST_EMPTY 		= 1,
    CAB_OP_ST_BP_ID_ASSIGN	= 2,
    CAB_OP_ST_BP_ID_AUTHORIZE	= 3,
    CAB_OP_ST_STANDBY= 4,
    CAB_OP_ST_CHARGING 	= 5,
    CAB_OP_ST_INIT				=6,
} CABINET_STATE;

class Cabinet:public BaseModel
{
private:
    BP* bp;
    FAN_STATE fanState;
    DOOR_STATE doorState;
    CABINET_OP_STATE opState;
    int32_t temp;

public:
    explicit Cabinet(BP * bp=nullptr);

    FAN_STATE getFanState() const;
    void setFanState(const FAN_STATE &value);
    DOOR_STATE getDoorState() const;
    void setDoorState(const DOOR_STATE &value);
    CABINET_OP_STATE getOpState() const;
    void setOpState(const CABINET_OP_STATE &value);
    int32_t getTemp() const;
    void setTemp(const int32_t &value);
    BP *getBp() const;
    void operator = (const Cabinet &bss );

    // BaseModel interface
public:

    int32_t parse(const QByteArray &data,const char sep);

    // BaseModel interface
public:
    void toJson(QJsonObject &json) const;
    void fromJson(const QJsonObject &json);
    void setBp(BP *value);
};

#endif // CABINET_H
