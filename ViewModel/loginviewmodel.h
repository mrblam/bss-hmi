#ifndef LOGINVIEWMODEL_H
#define LOGINVIEWMODEL_H

#include <QObject>
#include "Model/user.h"

class LoginViewModel : public QObject
{
    Q_OBJECT
private:
    User* user;
public:
    explicit LoginViewModel(QObject *parent = nullptr);
    void setUsername(const QString name);
    void setUserPassword(const QString pass);
signals:
    void onUsernameChanged(const QString name);
    void onPasswordChanged(const QString pass);

};

#endif // LOGINVIEWMODEL_H
