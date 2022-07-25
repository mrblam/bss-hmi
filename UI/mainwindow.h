#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include <QMainWindow>
#include "Data/Model/bss.h"
#include "Data/Model/cabinet.h"
#include "cabinetcom.h"
#include <QMessageBox>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    int position=1;
    uint32_t timeoutClick;
    bool isForward;
    bool hasLoginClick;
    QTimer animationTimer;
    CabinetCom* cabCom;
signals:
    void initSystem(const char *data);

public:
    MainWindow(CabinetCom* cabCom,QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnLogin_clicked();
    void on_btnLogin_pressed();
    void on_btnLogin_released();
    void animationSlot();
public slots:
    void onBSSStateChanged(const BSS* bss);
    void onBSSTiltChange(const BSS* bss);
private:
    Ui::MainWindow *ui;

protected:
    void paintEvent(QPaintEvent *event);
};
#endif // MAINWINDOW_H
