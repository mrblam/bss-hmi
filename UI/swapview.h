#ifndef SWAPVIEW_H
#define SWAPVIEW_H

#include <QMainWindow>
#include "ViewModel/bpviewmodel.h"
#include "cabinetcom.h"
#include "UI/continue.h"
#include "Data/Model/cabinet.h"
#include "Data/Reposistory/SwapRecordRepo/bsshttpmethod.h"
namespace Ui {
class SwapView;
}

class SwapView : public QMainWindow
{
    Q_OBJECT
private:
    uint32_t oldCabNum;
    int numberPicture;
    CabinetCom* cabCom;
    uint32_t timeoutCounter;
    uint32_t timeout;
    QTimer* timeoutTimer;
    QTimer* animationTimer;

public:
    explicit SwapView(CabinetCom* cabCom,QWidget *parent = nullptr);
    ~SwapView();
    void processSwapState();
private:
    void startTimeoutTimer(const uint32_t ms);
private:
    Ui::SwapView *ui;
private slots:
    void onComStateChanged(const COM_STATE& newState);
    void onComFail();
    void on_btnAction_clicked();
    void finishSwapSession();
    void guiUpdateSwapState(const SwapRecord* swapRecord);
    void on_btnNo_clicked();
    void on_btnYes_clicked();
    void animationSlot();

public:
    void onUserSwapRequest();
    void onUserSwapCancel();

public slots:
signals:
    void startAnimation(const char *data);

};

extern uint8_t is_staff_login;
extern uint8_t cab_id;

#endif // SWAPVIEW_H
