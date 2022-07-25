#ifndef BSS_H
#define BSS_H

#include "cabinet.h"
#include "stdint.h"
#include <QList>
typedef enum BSS_ERROR_CODE{
    BSS_NO_ERROR				=0,
    BSS_ERR_COM_PORT            =1,
    BSS_ERR_COM_DATA_TIMEOUT	=2
}BSS_ERROR_CODE;

 /* <serial_number>,<cab_number>,<active_cab>,<state>,<tilt_ss_state>,<fan_state>,<charger_state>,<lamp_state>,<temp> */
typedef enum BSS_STATE{
   BSS_ST_MAINTAIN  =1,
   BSS_ST_FAIL		=2,
   BSS_ST_INIT		=3,
   BSS_ST_SYNC      =0,
}BSS_STATE ;

typedef enum TILT_SS_STATE{
    TILT_ST_INACTIVE		=0,
    TILT_ST_ACTIVE			=1,
    TILT_ST_FAIL			=2,
} TILT_SS_STATE;

class BSS:public BaseModel
{
public:
    explicit BSS();
    BSS(uint32_t cab_num);
    uint32_t getCabinetNum() const;

private:
    uint32_t  cabinetNum;
    BSS_STATE state;
    TILT_SS_STATE tiltState;
    TILT_SS_STATE oldTiltState;
    QVector<Cabinet*> cabinets;
    double lon;
    double lat;
    int32_t storageTemp;

    // BaseModel interface
public:
    int32_t parse(const QByteArray &data,const char sep);

    double getLon() const;
    void setLon(double value);
    double getLat() const;
    void setLat(double value);
    int32_t getStorageTemp() const;
    void setStorageTemp(const int32_t &value);
    QVector<Cabinet *> getCabinets() const;

    // BaseModel interface
public:
    void toJson(QJsonObject &json) const;
    void fromJson(const QJsonObject &json);
    uint32_t getActiveCabNum() const;
    BSS_STATE getState() const;
    void setState(const BSS_STATE &value);
    TILT_SS_STATE getTiltState() const;
    void setTiltState(const TILT_SS_STATE &value);
    TILT_SS_STATE getOldTiltState() const;
    void setOldTiltState(const TILT_SS_STATE &value);
    void operator = (const BSS &bss );

};

#endif // BSS_H
