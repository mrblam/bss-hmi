#include "bpviewmodel.h"

BPViewModel::BPViewModel(CabinetCom* cab,QObject *parent) : QObject(parent)
{
    bp=new  BP();
    this->cabCom=cab;
    connect(this->cabCom,&CabinetCom::onBPChanged,this,&BPViewModel::updateBP);
}

void BPViewModel::setBPSerialNumber(const QString sn)
{
    this->bp->setSerialNumber(sn);
    emit this->onSerialChanged(sn);
}

void BPViewModel::setBPSoc(const uint32_t soc)
{
    this->bp->setSoc(soc);
    emit this->onSocChanged(soc);
}

void BPViewModel::setBPSoh(const uint32_t soh)
{
    this->bp->setSoh(soh);
    emit this->onSohChanged(soh);
}

void BPViewModel::setBPCycles(const uint32_t cycles)
{

    this->bp->setCycles(cycles);
    emit this->onCyclesChanged(cycles);
}

void BPViewModel::setBPTemp(const int16_t temp)
{

    this->bp->setCycles(temp);
    emit this->onTempChanged(temp);
}

void BPViewModel::updateBP(const BP *bp)
{
    setBPCycles(bp->getCycles());
    setBPSerialNumber(bp->getSerialNumber());
    setBPSoc(bp->getSoc());
    setBPSoh(bp->getSoh());
}
