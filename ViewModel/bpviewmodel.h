#ifndef BPVIEWMODEL_H
#define BPVIEWMODEL_H

#include <QObject>
#include "Data/Model/bp.h"
#include "cabinetcom.h"

class BPViewModel : public QObject
{
    Q_OBJECT
private:
    BP* bp;
    CabinetCom* cabCom;
public:
    explicit BPViewModel(CabinetCom* cab,QObject *parent = nullptr);
public:
    void setBPSerialNumber(const QString sn);
    void setBPSoc(const uint32_t soc);
    void setBPSoh(const uint32_t soh);
    void setBPCycles(const uint32_t cycles);
    void setBPTemp(const int16_t temp);

signals:
    void onSerialChanged(const QString sn);
    void onSocChanged(const uint32_t soc);
    void onSohChanged(const uint32_t soh);
    void onCyclesChanged(const uint32_t cycles);
    void onTempChanged(const int16_t temp);

private slots:
    void updateBP(const BP* bp);
};


#endif // BPVIEWMODEL_H
