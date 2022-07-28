#ifndef USERVIEW_H
#define USERVIEW_H
#include "Data/Reposistory/SwapRecordRepo/soundexecution.h"
#include <QMainWindow>
#include <Data/Model/user.h>
#include "cabinetcom.h"
namespace Ui {
class UserView;
}

class UserView : public QMainWindow
{
    Q_OBJECT
private:
    QTimer* timeoutProgressBar;
    User* userModel;
    QTimer* userActionTimeout;
public:
    explicit UserView(const User* user, QWidget *parent = nullptr);
    ~UserView();

    User *getUserModel() const;

private slots:
    void on_btnSwap_clicked();
    void setTimeoutProgressBarValue();
    void on_btnLogout_clicked();
    void onUserActionTimeout();
    void closeUserView();
    void on_btnOnlyCharge_clicked();
    void on_btnSwap_pressed();
    void on_btnSwap_released();
    void on_btnLogout_released();
    void on_btnLogout_pressed();
    void on_timeoutBar_valueChanged(int value);
private:
    Ui::UserView *ui;
};

#endif // USERVIEW_H
