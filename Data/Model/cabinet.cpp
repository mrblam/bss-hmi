#include "cabinet.h"
#include <QDebug>

FAN_STATE Cabinet::getFanState() const
{
    return fanState;
}

void Cabinet::setFanState(const FAN_STATE &value)
{
    fanState = value;
}

DOOR_STATE Cabinet::getDoorState() const
{
    return doorState;
}

void Cabinet::setDoorState(const DOOR_STATE &value)
{
    doorState = value;
}

CABINET_OP_STATE Cabinet::getOpState() const
{
    return opState;
}

void Cabinet::setOpState(const CABINET_OP_STATE &value)
{
    switch (value) {
    case CAB_OP_ST_INIT:
        bp->setState(BP_ST_INIT);
        bp->setSerialNumber("0");
        break;
    case CAB_OP_ST_BP_ID_ASSIGN:
    case CAB_OP_ST_BP_ID_AUTHORIZE:
    case CAB_OP_ST_EMPTY:
    case CAB_OP_ST_INACTIVE:
        break;
    default:
        break;
    }
    opState = value;
}

int32_t Cabinet::getTemp() const
{
    return temp;
}

void Cabinet::setTemp(const int32_t &value)
{
    temp = value;
}

BP *Cabinet::getBp() const
{
    return bp;
}

void Cabinet::operator =(const Cabinet &cab)
{
   setOpState(cab.getOpState());
   setDoorState(cab.getDoorState());
   setFanState(cab.getFanState());
   setId(cab.getId());
   setTemp(cab.getTemp());
}

/*
 * 	<op_state>,<door_state>,<fan_state>,<temp>,<bat_sn>
 */
int32_t Cabinet::parse(const QByteArray &data,const char sep)
{
    if(data.length()<=0) return -1;

    QList<QByteArray> fields=data.split(sep);
    if(fields.length()<=4) return -1;
    bool ok=false;
    bool changed=false;

    CABINET_OP_STATE op_state=(CABINET_OP_STATE)fields.at(0).toUInt(&ok);
    if(!ok) return -1;
    if( op_state!= this->opState){
        this->opState=op_state;
        changed=true;
    }


    DOOR_STATE door_state=(DOOR_STATE)fields.at(1).toUInt(&ok);
    if(!ok) return -1;
    if( door_state!= this->doorState){
        this->doorState=door_state;
        changed=true;
    }

    FAN_STATE fan_state=(FAN_STATE)fields.at(2).toUInt(&ok);
    if(!ok) return -1;
    if( fan_state!= this->fanState){
        this->fanState=fan_state;
        changed=true;
    }

    int32_t temp=fields.at(3).toInt(&ok);
    if(!ok) return -1;
    if( temp!= this->temp){
        this->temp=temp;
        changed=true;
    }

    QString bat_sn=fields.at(4);
    if(this->bp!=nullptr){
        this->bp->setSerialNumber(bat_sn);
    }
    if(changed) return 1;
    return 0;
}

void Cabinet::toJson(QJsonObject &json) const
{
    json["id"]=(double) getId();
    json["door_state"]=(double)doorState;
    json["fan_state"]=(double)fanState;
    json["temp"]=(double) temp;
    json["op_state"]=(double)opState;
}

void Cabinet::fromJson(const QJsonObject &json)
{
    if (json.contains("id") && json["id"].isDouble()){
        setId(json["id"].toInt());
        qDebug()<<"Set cabinet id: " <<QString::number(getId());
    }

    if (json.contains("door_state") && json["door_state"].isDouble()){
        doorState=(DOOR_STATE) json["door_state"].toInt();
        qDebug()<<"Set cabinet door state: " <<QString::number(doorState);
    }

    if (json.contains("fan_state") && json["fan_state"].isDouble()){

        fanState=(FAN_STATE) json["fan_state"].toInt();
        qDebug()<<"Set cabinet fan state: " <<QString::number(fanState);
    }

    if (json.contains("op_state") && json["op_state"].isDouble()){

        opState=(CABINET_OP_STATE) json["op_state"].toInt();
        qDebug()<<"Set cabinet op state: " <<QString::number(opState);
    }
}

void Cabinet::setBp(BP *value)
{
    bp = value;
}

Cabinet::Cabinet(BP* bp)
{
    this->bp=bp;
    this->doorState=DOOR_ST_CLOSE;
    this->fanState=FAN_ST_OFF;
    this->opState=CAB_OP_ST_INACTIVE;
}
