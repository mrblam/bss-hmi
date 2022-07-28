#include "basemodel.h"

NODE_ERROR_STATE BaseModel::getErrorState() const
{
    return errorState;
}

void BaseModel::setErrorState(const NODE_ERROR_STATE &value)
{
    errorState = value;
}

uint32_t BaseModel::getErrorCode() const
{
    return errorCode;
}

void BaseModel::setErrorCode(const uint32_t &value)
{
    errorCode = value;
}

uint32_t BaseModel::getId() const
{
    return id;
}

void BaseModel::setId(const uint32_t &value)
{
    id = value;
}

void BaseModel::toJson(QJsonObject &json) const
{
    (void)json;
}

void BaseModel::fromJson(const QJsonObject &json)
{
    (void)json;
}

int32_t BaseModel::parse(const QByteArray &data, const char sep)
{
    (void)data;
    (void)sep;
   return -1;
}

QString BaseModel::getSerialNumber() const
{
    return serialNumber;
}

void BaseModel::setSerialNumber(const QString &value)
{
    serialNumber = value;
}
