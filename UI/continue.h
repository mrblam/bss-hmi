#ifndef CONTINUE_H
#define CONTINUE_H
#include "cabinetcom.h"
#include "UI/swapview.h"
#include <QMainWindow>

namespace Ui {
class Continue;
}

class Continue : public QMainWindow
{
    Q_OBJECT
private:
    CabinetCom* cab;
    QTimer* timeoutContinueProgressBar;
    QTimer* continueActionTimeout;
    void closeContinueView();
public:
    explicit Continue( const CabinetCom* cab,QWidget *parent = nullptr);
    ~Continue();

private slots:
    void on_actionTimeout();
    void on_btnContinue_clicked();

    void on_btnContinue_pressed();

    void on_btnContinue_released();

    void on_btnCancel_clicked();

    void on_btnCancel_pressed();

    void on_btnCancel_released();
    void setValueTimeoutProgressBar();

    void on_timeoutBar_valueChanged(int value);

private:
    Ui::Continue *ui;
};

#endif // CONTINUE_H
