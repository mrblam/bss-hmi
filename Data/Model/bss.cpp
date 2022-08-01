#include "bss.h"
#include "stdlib.h"
#include <QJsonArray>
#include <QDebug>
BSS::BSS()
{
    setId(0);
   this->cabinetNum=0;
    this->cabinets=QVector<Cabinet*>();
    this->state=BSS_ST_INIT;
}

BSS::BSS(uint32_t cab_num)
{
    setId(0);
    this->cabinets= QVector<Cabinet*>();
    this->cabinetNum=cabinets.length();
    this->cabinetNum=cab_num;
    this->tiltState = TILT_ST_INACTIVE;
    for(uint32_t i=0;i<this->cabinetNum;i++){
        BP* bp=new BP();
        bp->setId(i);
        Cabinet* cab=new Cabinet(bp);
        cab->setOpState(CAB_OP_ST_INIT);
        cab->setId(i);
        cab->setDoorState(DOOR_ST_CLOSE);
        cab->setFanState(FAN_ST_ON);
        cabinets.append(cab);
    }
    setSerialNumber("BSS-V4.0");
    setState(BSS_ST_INIT);
}

uint32_t BSS::getCabinetNum() const
{
    return cabinetNum;
}

void BSS::operator =(const BSS &bss)
{

    setState(bss.getState());
    this->cabinetNum=bss.getCabinetNum();
    setId(bss.getId());
    setLat(bss.getLat());
    //setLon(bss.getLon());
    setLon(0);

    setErrorCode(bss.getErrorCode());
}

TILT_SS_STATE BSS::getTiltState() const
{
    return tiltState;
}

void BSS::setTiltState(const TILT_SS_STATE &value)
{
    tiltState = value;
}
TILT_SS_STATE BSS::getOldTiltState() const
{
    return oldTiltState;
}

void BSS::setOldTiltState(const TILT_SS_STATE &value)
{
    oldTiltState = value;
}

BSS_STATE BSS::getState() const
{
    return state;
}

void BSS::setState(const BSS_STATE &value)
{
    switch (value) {
    case BSS_ST_INIT:
        break;
    default:
        break;
    }
    state = value;

}

uint32_t BSS::getActiveCabNum() const
{
    return (0);
}

QVector<Cabinet *> BSS::getCabinets() const
{
    return cabinets;
}

void BSS::toJson(QJsonObject &json) const
{
    json["serial_number"]=getSerialNumber();
    json["cabinet_nums"]=(double)cabinetNum;
    json["lon"]=0;//lon;
    json["lat"]=0;//lat;
    json["temp"]=(double) storageTemp;
    json["op_state"]=(double) getErrorState();
    json["error_code"]=(double)getErrorCode();
    json["tilt"] = (double)getTiltState();
    QJsonArray cabinetArray;
    for (const Cabinet* cab : cabinets) {
        QJsonObject cabObject;
        cab->toJson(cabObject);
        cabinetArray.append(cabObject);
    }
    json["cabinets"] = cabinetArray;
}

void BSS::fromJson(const QJsonObject &json)
{
    if (json.contains("cabinet_nums") && json["cabinet_nums"].isDouble())
            cabinetNum = json["cabinet_nums"].toInt();

    if (json.contains("serial_number") && json["serial_number"].isString())
        setSerialNumber(json["serial_number"].toString());
}

int32_t BSS::getStorageTemp() const
{
    return storageTemp;
}

void BSS::setStorageTemp(const int32_t &value)
{
    storageTemp = value;
}

double BSS::getLat() const
{
    return lat;
}

void BSS::setLat(double value)
{
    lat = value;
}

double BSS::getLon() const{
    return lon;
}

void BSS::setLon(double value)
{
    lon = value;
}

/*
 * <serial_number>,<cab_number>,<state>,<tilt_ss_state>,[<fan1_state>,<fan2_state>],[<lamp1_state>,<lamp2_state],[<temp1>,<temp2>,<temp3>]
 */

int32_t BSS::parse(const QByteArray &data,const char sep)
{
    if(data.length()<=0) return -1;

    QList<QByteArray> fields=data.split(sep);
    if(fields.length()<=5) return -1;
    bool ok=false;
    bool changed=false;

    uint32_t cab_num=fields.at(0).toUInt(&ok);
    if(!ok) return -1;
    if( cab_num!= this->cabinetNum){
        this->cabinetNum=cab_num;
        changed=true;
    }

    BSS_STATE new_state=(BSS_STATE)fields.at(1).toUInt(&ok);
    if(!ok) return -1;
    if( new_state!=this->state){
        qDebug()<<"bss:176: HAS Changed State";
        this->state=new_state;
        changed=true;
    }

    TILT_SS_STATE new_tilt_state=(TILT_SS_STATE)fields.at(2).toUInt(&ok);
    if(!ok) return -1;
    if( new_tilt_state != this->getTiltState()){
        this->setTiltState(new_tilt_state);
        changed=true;
    }
    if(changed) return 1;
    return 0;
}
