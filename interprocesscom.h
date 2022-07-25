#ifndef INTERPROCESSCOM_H
#define INTERPROCESSCOM_H
#include <QObject>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QDataStream>
#include <QAbstractSocket>
#include <QTimer>
#include <QTcpServer>
#include "UI/mainwindow.h"
#include <cabinetcom.h>
// ICP
#define TCP_SERVER_PORT_READ 12345
#define TCP_SERVER_PORT_WRITE 54321

class interprocesscom : public QObject
{
    Q_OBJECT

public:
    explicit interprocesscom(QObject *parent = nullptr);

public slots:

    void requestNewFortune();
    void readFortune();
    void sendMessage(const char *data);

private:
    QTimer heartbeatrequest;
    QTcpSocket *tcpSocket = nullptr;
    QTcpServer *tcpServer = nullptr;
    QDataStream dataStream;
    QString currentFortune;
    MainWindow *mainwindow(CabinetCom* cabCom,QWidget *parent = nullptr);
};
#endif // INTERPROCESSCOM_H
