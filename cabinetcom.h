#ifndef CABINETCOM_H
#define CABINETCOM_H
#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>
#include "Data/Model/bp.h"
#include "Data/Model/bss.h"
#include "Data/Model/cabinet.h"
#include "Util/cabcomhelper.h"
#include <QTimer>
#include "Data/Model/swaprecord.h"
#include "Data/Reposistory/SwapRecordRepo/bsshttpmethod.h"
#include "Data/Reposistory/SwapRecordRepo/connectmonitor.h"
typedef enum USB_PORT_NAME {
    USB_PORT_0 = 0,
    USB_PORT_1 =1,
}USB_PORT_NAME;
typedef enum COM_STATE{
    COM_ST_DISCONNECTED=0,
    COM_ST_PORT_ERROR=1,
    COM_ST_DATA_TIMEOUT=2,
    COM_ST_CONNECTED=3
}COM_STATE ;
typedef enum SYNC_STATE{
    SYNC_STATE_READ_BSS_STATE=0,
    SYNC_STATE_READ_ALL_OBJECT,
    SYNC_STATE_READ_CABINETS,
}SYNC_STATE;
typedef enum SYNC_CABINET_STATE{
    SYNC_CABINET_STATE_SET_INIT=0,
    SYNC_CABINET_STATE_SET_BP_ASSIGN_ID,
    SYNC_CABINET_STATE_READ_CABINET,
    SYNC_CABINET_STATE_SET_AUTHORIZE,
    SYNC_CABINET_STATE_SET_EMPTY,
    SYNC_CABINET_STATE_FINISH,
} SYNC_CABINET_STATE;

class CabinetCom : public QObject
{
    Q_OBJECT
private:
    SwapRecord* swapRecord;
    QThread* processThread;
    BSS* bssModel;
    bool swappingFlag;
    bool loginFlag;
    CabComHelper comHelper;
    COM_STATE comState;
    SYNC_STATE syncState;
    SYNC_CABINET_STATE syncCabinetState;
    QSerialPort port;
    const QString port_name = "/dev/ttyUSB0";
    const QString port_name1 = "/dev/ttyUSB1";
    USB_PORT_NAME currentPortName = USB_PORT_0;
    uint32_t changePortTimeout;
    QByteArray rxBuffer;
    QTimer processTimer;
    QTimer heartbeatTicker;
    uint32_t heartbeatCounter;
    uint32_t fail_recover_timeout_ms;
    bool isOnlyCharge;
    bool continueSwap;
public:

    uint32_t getChangePortTimeout ();
    USB_PORT_NAME getCurrentPortName ();
    const QString getChangePortName(USB_PORT_NAME port);
    void setChangePortTimeout(uint32_t value);
    static CabinetCom* getCabCom();
    CabinetCom(QObject *parent = nullptr);
    COM_STATE getComState() const;
    void setComState(const COM_STATE &value);
    void start(const QString& portname);
    void start();
    QSerialPort *getPort();
    void setBssModel(BSS *value);
    BSS *getBssModel() const;
    void setSyncState(SYNC_STATE syncState);
    SYNC_STATE getSyncState() const;
    void setSyncCabinetState(SYNC_CABINET_STATE syncCabinetState);
    SYNC_CABINET_STATE getSyncCabinetState() const;
    void bpAuthFailConfirm(const Cabinet* cab);
    void bpAuthSuccessConfirm(const Cabinet* cab);
    void writeCabinetDoorState(const Cabinet* cab,DOOR_STATE state);

    CabComHelper* getComHelper();

    SwapRecord *getSwapRecord() const;
    void setSwapRecord(SwapRecord *value);

    bool getSwappingFlag() const;
    void setSwappingFlag(bool value);
    bool getContinueSwap();
    void setContinueSwap(const bool& value);
    bool getLoginFlag() const;
    void setLoginFlag(const bool& loginFlag);

private:
    void cabComWritePackage(const QByteArray& data);
    void processReceivedData();
    void writeBSSState(BSS_STATE state);
    void readBSSAllObjectSubDataCode();
    bool syncCabinet(Cabinet* cab);
    void setBssAssigned(const Cabinet* cab);
    void readBSSState();
    void readBPData(const BP* bp);
    void writeBSSCabNum(const uint32_t num);
    void writeCabinetState(const Cabinet* cab,CABINET_OP_STATE state);
    void readCabinetState(const Cabinet* cab);
    void requestDataSyncUpdate();
    void requestDataSyncWithoutUpdate();
    void updateConfigCabState(Cabinet* cab);
    void updateBssFromRemote(BSS* remote,BSS* local);
    void updateBPFromRemote(BP* bp,BP* local);
    void updateCabinetFromRemote(Cabinet* cab,Cabinet* local);
    void switchToBSSState(const BSS_STATE& state);
    void processSwapState();
signals:
    //void onBssTiltChanged(BSS* bss);
    void onBSSChanged(const BSS* bss);
    void onBPChanged(const BP* bp,const QString& sn);
    void onCabinetChanged(const Cabinet* cab);
    void onComStateChanged(const COM_STATE& state);
    void onNewBatteryInserted(const Cabinet* cab);
    void onBatteryIDAssignSuccess(const Cabinet* cab);
    void onNewBatteryAccepted(const Cabinet* cab);
    void onBatteryDetach(const Cabinet* cab);
    void onBatteryCheckFail(const Cabinet* cab);
    void onCabinetComFail();
    void onSwapRecordChanged(const SwapRecord* swapRecord);


private slots:
    void getComData();
    void processBSSStateMachine();
    void saveCabinetData(const Cabinet* cab);
    void saveBPData(const BP* bp);
    void saveBSSData(const BSS* bss);
    void startCabinetIDAssign(Cabinet* cab);
    void startBPAuth(Cabinet* cab);
    void getTiltSensor(const BSS* bss);
    void onComFail();

public slots:
    void configBSS(const BSS* bss);
    void configCabinet(const Cabinet* cab);
    void configBP(const BP* bp);
    void userSwappingCancel();
    void userSwappingRequest();
};

#endif // CABINETCOM_H
