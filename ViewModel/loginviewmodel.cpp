#include "loginviewmodel.h"

LoginViewModel::LoginViewModel(QObject *parent) : QObject(parent)
{

    user=new User();
}

void LoginViewModel::setUsername(const QString name)
{

    this->user->setUsername(name);
    emit this->onUsernameChanged(name);
}

void LoginViewModel::setUserPassword(const QString pass)
{
    this->user->setPassword(pass);
    emit this->onPasswordChanged(pass);
}
