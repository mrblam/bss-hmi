#ifndef BASEMODEL_H
#define BASEMODEL_H
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

typedef enum NODE_OP_STATEATE{
    NODE_ST_NO_ERROR=0,
    NODE_ST_FAIL	=1
}NODE_ERROR_STATE ;
class BaseModel
{
private:
    QString serialNumber;
    uint32_t id;
    uint32_t errorCode;
    NODE_ERROR_STATE errorState;
public:
    void toJson(QJsonObject& json) const ;
    void fromJson(const QJsonObject& json);
    int32_t parse(const QByteArray& data,const char sep=',');

    QString getSerialNumber() const;
    void setSerialNumber(const QString &value);
    uint32_t getErrorCode() const;
    void setErrorCode(const uint32_t &value);
    NODE_ERROR_STATE getErrorState() const;
    void setErrorState(const NODE_ERROR_STATE &value);
    uint32_t getId() const;
    void setId(const uint32_t &value);
};

#endif // BASEMODEL_H
