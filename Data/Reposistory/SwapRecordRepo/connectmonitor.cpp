#include "connectmonitor.h"

connectMonitor::connectMonitor(QObject *parent) : QObject(parent)
{
    tcpSocket = new QTcpSocket();

    connect(tcpSocket,&QIODevice::readyRead,this,&connectMonitor::readMessage);
    connect(&heartbeatSend,&QTimer::timeout,this,&connectMonitor::connectToLocalServer);
    heartbeatSend.start(5000);

}

void connectMonitor::checkui(UI_DISPLAY uiDisplay, bool status)
{
    switch (uiDisplay) {
    case UI_DISPLAY_BP_VIEW:
        if(status) qDebug()<<"BPVIEW OPEN";
        else qDebug()<<"BP_VIEW_CLOSE";
        break;
    case UI_DISPLAY_CONTINUE:
        break;
    case UI_DISPLAY_LOGIN:
        if(status)
        {
            //sendMessage();
            qDebug()<<"LOGIN OPEN";
        }
        else qDebug()<<"LOGIN CLOSE";
        break;
    case UI_DISPLAY_SWAPRECORD:
        break;
    case UI_DISPLAY_USER_VIEW:
        break;
    default:
        break;
    }
}

void connectMonitor::connectToLocalServer()
{



    tcpSocket = new QTcpSocket(this);
        tcpSocket->connectToHost(QHostAddress::AnyIPv4, 12345);

        if(tcpSocket->waitForConnected(3000))
        {
            qDebug() << "Connected!";

            // send
            tcpSocket->write("hello server\r\n\r\n\r\n\r\n");
            tcpSocket->waitForBytesWritten(1000);
            tcpSocket->waitForReadyRead(3000);
            qDebug() << "Reading: " << tcpSocket->bytesAvailable();

            qDebug() << tcpSocket->readAll();

            tcpSocket->close();
        }
        else
        {
            qDebug() << "Not connected!";
        }

}

void connectMonitor::readMessage()
{
    tcpSocket->waitForReadyRead(2000);
    qDebug() << "Bytes available : " << tcpSocket->bytesAvailable();
    qDebug() << "Du lieu nhan duoc tu hmi-monitor : " << tcpSocket->readAll();
    tcpSocket->close();
}

connectMonitor* connectMonitor:: getConnectionMonitor(){
    static connectMonitor* self;
    if(self==nullptr){
        self=new connectMonitor();
    }
    return self;
}
