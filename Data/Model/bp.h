#ifndef BP_H
#define BP_H
#include <QString>
#include "basemodel.h"

typedef enum BP_STATE_t{
    BP_ST_INIT=0,
    BP_ST_IDLE,
    BP_ST_ID_ASSIGN_START,
    BP_ST_ID_ASSIGN_WAIT_CONFIRM,
    BP_ST_ID_ASSIGN_CONFIRMED,
    BP_ST_ID_ASSIGN_WAIT_SLAVE_SELECT,
    BP_ST_START_AUTHENTICATE,
    BP_ST_AUTHENTICATING,
    BP_ST_SOFTSTART,
    BP_ST_SYSTEM_BOOST_UP,
    BP_ST_STANDBY,
    BP_ST_DISCHARGING,
    BP_ST_CHARGING,
    BP_ST_FAULT,
    BP_ST_SHIPMODE
} BP_STATE;

typedef enum BP_STATUS_t{
    BP_STT_OK				= 0,
    BP_STT_OCD 				= 1,
    BP_STT_SCD 				= 2,
    BP_STT_OV 				= 4,
    BP_STT_UV 				= 8,
    BP_STT_OVRD_ALERT 		= 16,
    BP_STT_DEVICE_XREADY	= 32,
    BP_STT_RSVD 			= 64,
    BP_STT_CC_READY 		= 128
}BP_STATUS;

class BP:public BaseModel
{
private:
    BP_STATUS status;
    BP_STATE state;
    uint32_t soc;
    uint32_t soh;
    uint32_t cycles;
    int32_t current;
    uint32_t voltage;
    int32_t temp;
public:
    explicit BP();

    uint32_t getSoc() const;
    void setSoc(const uint32_t &value);

    uint32_t getSoh() const;
    void setSoh(const uint32_t &value);

    uint32_t getCycles() const;
    void setCycles(const uint32_t &value);

//    int16_t getTemp() const;
//    void setTemp(const int16_t &value);


    // BaseModel interface
public:
    void toJson(QJsonObject& json) const;
    void fromJson(const QJsonObject& json);
    int32_t parse(const QByteArray &data,const char sep);
    int32_t getCurrent() const;
    void setCurrent(const int32_t &value);
    uint32_t getVoltage() const;
    void setVoltage(const uint32_t &value);
    int32_t getTemp() const;
    void setTemp(const int32_t &value);
    BP_STATUS getStatus() const;
    void setStatus(const BP_STATUS &value);
    BP_STATE getState() const;
    void setState(const BP_STATE &value);
    void operator = (const BP &bss );
};

#endif // BP_H
