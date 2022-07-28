#ifndef CABCOMHELPER_H
#define CABCOMHELPER_H

#include <QObject>
#include "Data/Model/basemodel.h"
#include "Data/Model/bss.h"
#include "Data/Model/cabinet.h"
#include "Data/Model/bp.h"

#define SOM							':'
#define EOM							'*'
#define FIELD_DELIMITER				','

/* define command type */
#define CMD_READ					'R'
#define CMD_WRITE					'W'
#define CMD_AUTH					'A'

#define ALL_OBJECT_SUB_DATA_CODE		'A'
/* define for object and sub object code */

/* cabinet and sub object data */
#define CAB_DATA_CODE						'C'
#define CAB_TEMP_CODE						'T'
#define CAB_FAN_CODE						'F'
#define CAB_DOOR_CODE						'D'
#define CAB_OP_CODE							'O'

/*bss and sub object data */
#define BSS_DATA_CODE						'S'
/* sub objects */
#define BSS_ID_ASSIGN_CODE					'I'
#define BSS_ID_ASSIGN_START_CMD_CODE		'S'
#define BSS_STATE_DATA_CODE					'S'
#define BSS_SYNC_REQUEST_DATA_CODE			'Y'
#define BSS_CAB_NUM_DATA_CODE				'N'

#define BSS_AUTH_CODE						'U'
#define BSS_AUTH_START_CMD_CODE				'S'
#define BSS_AUTH_FAIL_CODE					'F'
#define BSS_AUTH_SUCCESS_CODE				'O'

/*battery pack and sub object data */
#define BP_DATA_CODE						'B'
/* sub objects */
#define BP_SOC_DATA_CODE					'P'
#define BP_SOC_DATA_CODE					'P'
#define BP_SOH_DATA_CODE					'H'


typedef enum COM_ERROR_CODE{
    COM_NO_ERROR							=0,
    COM_ERR_PARSE							=1,
    COM_ERR_TIMEOUT							=2,
    COM_ERR_WRITE							=3,
    COM_ERR_CMD_NO_SUPPORT					=4
}COM_ERROR_CODE;

//rs0a
typedef enum CAB_PROTOCOL_STATE{
    CAB_PROTOCOL_ST_IDLE=0,
    CAB_PROTOCOL_ST_WAIT_RESPONSE=1,
    CAB_PROTOCOL_ST_SUCCESS=2,
    CAB_PROTOCOL_ST_FAIL=3,
    CAB_PROTOCOL_ST_TIMEOUT=4

}CAB_PROTOCOL_STATE ;

typedef struct ObjectMux_t ObjectMux;

struct ObjectMux_t{
    char code;
    char sub;
    QByteArray index;
};

typedef struct CabCMDHeader_t CabCMDHeader;

struct CabCMDHeader_t{
    char cmdCode;
    ObjectMux objMux;
};

class CabComHelper :public QObject
{
    Q_OBJECT
private:
    COM_ERROR_CODE errorCode;
    Cabinet remoteCabinet;
    BSS remoteBSS;
    BP remoteBP;

    Cabinet* localCabinet;
    BSS* localBss;
    BP* localBP;
    bool isBusy;

    CAB_PROTOCOL_STATE protocolState;
    CabCMDHeader cmdHeader;
    QByteArray rxBuffer;
    void buildReadCMDData(QByteArray* buff, const ObjectMux& obj_mux );
    void buildWriteCMDData(QByteArray* buff, const ObjectMux& obj_mux,const QByteArray& data);
    void setProtocolFailState(const COM_ERROR_CODE& error);
    void setProtocolSuccessState();
public:
    CabComHelper(QObject* parent=nullptr);
    int32_t parseRxData();
    int32_t bssParseSubData(BSS* bss,const QByteArray& data);
    int32_t cabParseSubData(Cabinet* bss,const QByteArray& data);
    int32_t bpParseSubData(BP* bss,const QByteArray& data);
    void cabBuildWriteSubObject(QByteArray* buff,const Cabinet* cab,const char& sub,const QByteArray& data);
    void bssBuildWriteSubObject(QByteArray* buff,const BSS* bss,const char& sub,const QByteArray& data);
    void bpBuildWriteSubObject(QByteArray* buff,const BP* bp,const char& sub,const QByteArray& data);

    void cabBuildReadSubObject(QByteArray* buff,const Cabinet* cab,const char& sub);
    void bssBuildReadSubObject(QByteArray* buff,const BSS* bss,const char& sub);
    void bpBuildReadSubObject(QByteArray* buff,const BP* bp,const char& sub);


    CAB_PROTOCOL_STATE getProtocolState() const;
    void setProtocolState(const CAB_PROTOCOL_STATE &value);
    void receiveData(const QByteArray& new_data);

    Cabinet* getRemoteCabinet(void);
    BSS* getRemoteBSS(void);
    BP* getRemoteBP(void);

    Cabinet *getLocalCabinet() const;
    void setLocalCabinet(Cabinet *value);
    BSS *getLocalBss() const;
    void setLocalBss(BSS *value);
    BP *getLocalBP() const;
    void setLocalBP(BP *value);
    bool getIsBusy() const;
    void setIsBusy(bool value);

    COM_ERROR_CODE getErrorCode() const;
    void setErrorCode(const COM_ERROR_CODE &value);

signals:
    void onFail();
};

#endif // CABCOMHELPER_H
