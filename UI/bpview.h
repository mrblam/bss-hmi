#ifndef BPVIEW_H
#define BPVIEW_H
#include "Data/Reposistory/SwapRecordRepo/soundexecution.h"
#include <QMainWindow>
#include "Data/Model/bp.h"
#include "Data/Model/cabinet.h"
#include "Data/Reposistory/SwapRecordRepo/connectmonitor.h"
namespace Ui {
class BPView;
}

class BPView : public QMainWindow
{
    Q_OBJECT
private:
    Cabinet* cab;
    QTimer* bpViewTimeoutProgressBar;
    QTimer* userActionTimeout;
public:
    explicit BPView(const Cabinet*cab,QWidget *parent = nullptr);
    ~BPView();

private slots:
    void on_btnSwap_clicked();

    void on_btnCancel_clicked();
    void onUserActionTimeout();
    void on_btnSwap_pressed();

    void on_btnSwap_released();

    void on_btnCancel_pressed();
    void setValueProgressBar();
    void on_btnCancel_released();

    void on_timeoutBar_valueChanged(int value);

private:
    void showBPData();
    void closeBPView();
private:
    Ui::BPView *ui;
};

#endif // BPVIEW_H
