#include "bp.h"
#include <QList>

BP_STATE BP::getState() const
{
    return state;
}

void BP::setState(const BP_STATE &value)
{
    state = value;
}

void BP::operator =(const BP &bp)
{
    setSerialNumber(bp.getSerialNumber());
    setCycles(bp.getCycles());
    setState(bp.getState());
    setId(bp.getId());
    setSoc(bp.getSoc());
    setSoh(bp.getSoh());
    setVoltage(bp.getVoltage());
    setStatus(bp.getStatus());
}

BP_STATUS BP::getStatus() const
{
    return status;
}

void BP::setStatus(const BP_STATUS &value)
{
    status = value;
}

BP::BP()
{
    setSerialNumber("BP_XX");
    soc=90;
    soh=100;
    status=BP_STT_OK;
    state=BP_ST_INIT;
}

uint32_t BP::getSoc() const
{
    return soc;
}

void BP::setSoc(const uint32_t &value)
{
    soc = value;
}

uint32_t BP::getSoh() const
{
    return soh;
}

void BP::setSoh(const uint32_t &value)
{
    soh = value;
}

uint32_t BP::getCycles() const
{
    return cycles;
}

void BP::setCycles(const uint32_t &value)
{
    cycles = value;
}

void BP::toJson(QJsonObject& json) const
{
    json["serial_number"]=getSerialNumber();
    json["soc"]=(double)soc;
    json["soh"]=(double)soh;
    json["cycles"]=(double)cycles;
    json["cur"]=(double)current;
    json["vol"]=(double)voltage;
}

void BP::fromJson(const QJsonObject &json)
{

}

/*
 * <serial_number>,<state>,<status>,<vol>,<cur>,<cycles>,<soc>,<soh>,[<c1_vol>,<c2_vol>,.....,<cn_vol>],[<temp1>,<temp2>,<temp3>,....,<tempn>]
 *
 */

int32_t BP::parse(const QByteArray &data,const char sep)
{
    if(data.length()<=0) return -1;
    QList<QByteArray> fields=data.split(sep);
    if(fields.length()<=9) return -1;
    bool ok=false;
    bool changed=false;

    setSerialNumber(QString(fields.at(0)));

    BP_STATE state=(BP_STATE)fields.at(1).toUInt(&ok);
    if(!ok) return -1;
    if(state != this->state){
        this->state=state;
        changed=true;
    }

    BP_STATUS status=(BP_STATUS)fields.at(2).toUInt(&ok);
    if(!ok) return -1;
    if(status != this->status){
        this->status=status;
        changed=true;
    }

    uint32_t vol=fields.at(3).toUInt(&ok);
    if(!ok) return -1;
    if(vol != this->voltage){
        this->voltage=vol;
        changed=true;
    }

    int32_t cur=fields.at(4).toInt(&ok);
    if(!ok) return -1;
    if(cur != this->current){
        this->current=cur;
        changed=true;
    }

    uint32_t cycles=fields.at(5).toUInt(&ok);
    if(!ok) return -1;
    if(cycles != this->cycles){
        this->cycles=cycles;
        changed=true;
    }


    uint32_t soc=fields.at(6).toUInt(&ok);
    if(!ok) return -1;
    if(soc != this->soc){
        this->soc=soc;
        changed=true;
    }

    uint32_t soh=fields.at(7).toUInt(&ok);
    if(!ok) return -1;
    if(soh != this->soh){
        this->soh=soh;
        changed=true;
    }

    int32_t temp=fields.at(6).toInt(&ok);
    if(!ok) return -1;
    if(temp != this->temp){
        this->temp=temp;
        changed=true;
    }


    if(changed) return 1;
    return 0;
}

int32_t BP::getCurrent() const
{
    return current;
}

void BP::setCurrent(const int32_t &value)
{
    current = value;
}

uint32_t BP::getVoltage() const
{
    return voltage;
}

void BP::setVoltage(const uint32_t &value)
{
    voltage = value;
}

int32_t BP::getTemp() const
{
    return temp;
}

void BP::setTemp(const int32_t &value)
{
    temp = value;
}

