#ifndef CONNECTMONITOR_H
#define CONNECTMONITOR_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QProcess>
#include <QTimer>
// IPC app1 (server) --- HMI (client)
#define TCP_SERVER_PORT_WRITE 54321
// IPC app1 (client) --- HMI (server)
#define TCP_SERVER_PORT_READ    12345
typedef enum UI_DISPLAY{
    UI_DISPLAY_LOGIN,
    UI_DISPLAY_SWAPRECORD,
    UI_DISPLAY_BP_VIEW,
    UI_DISPLAY_USER_VIEW,
    UI_DISPLAY_CONTINUE
}UI_DISPLAY ;
class connectMonitor : public QObject
{
    Q_OBJECT
public:
    explicit connectMonitor(QObject *parent = nullptr);
    static connectMonitor* getConnectionMonitor();
    void checkui(UI_DISPLAY uiDisplay, bool status);
    void connectToLocalServer();
//    void
public slots:
    void readMessage();


private:
    QTimer heartbeatrequest;
    QTimer heartbeatSend;
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer = nullptr;
    QString currentFortune;
};

#endif // CONNECTMONITOR_H
