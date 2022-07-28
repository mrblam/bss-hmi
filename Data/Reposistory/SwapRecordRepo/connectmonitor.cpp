#include "connectmonitor.h"

connectMonitor::connectMonitor(QObject *parent) : QObject(parent)
{
    tcpSocket = new QTcpSocket();
//    connect(&heartbeatSend,&QTimer::timeout,this,&connectMonitor::connectToLocalServer);
//    heartbeatSend.start(5000);
}

void connectMonitor::checkUI(UI_DISPLAY uiDisplay, bool status)
{
    switch (uiDisplay){
    case UI_DISPLAY_BP_VIEW:
        if(status)
        {
            connectToLocalServer("BP view open");
            qDebug()<<"BP view open";
        }
        else
        {
            connectToLocalServer("BP view close");
            qDebug()<<"BP view close";
        }
        break;

    case UI_DISPLAY_CONTINUE:
        if(status)
        {
            connectToLocalServer("UI display continue open");
            qDebug()<<"UI display continue open";
        }
        else
        {
            connectToLocalServer("UI display continue close");
            qDebug()<<"UI display continue close";
        }
        break;

    case UI_DISPLAY_LOGIN:
        if(status)
        {
            connectToLocalServer("UI dislay login open");
            qDebug()<<"LOGIN OPEN";
        }
        else
        {
            connectToLocalServer("UI dislay login close");
            qDebug()<<"LOGIN CLOSE";
        }
        break;
    case UI_DISPLAY_SWAPRECORD:
        if(status)
        {
            connectToLocalServer("UI dislay swaprecord open");
            qDebug()<<"UI_DISPLAY_SWAPRECORD Open";
        }
        else
        {
            connectToLocalServer("UI dislay swaprecord close");
            qDebug()<<"UI dislay swaprecord close";
        }
        break;

    case UI_DISPLAY_USER_VIEW:
        if(status)
        {
            connectToLocalServer("UI dislay user view open");
            qDebug()<<"UI dislay user view open";
        }
        else
        {
            connectToLocalServer("UI dislay user view close");
            qDebug()<<"UI dislay user view close";
        }
        break;

    default:
        break;
    }
}

void connectMonitor::connectToLocalServer(const char* data)
{
    tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost(QHostAddress::AnyIPv4,TCP_SERVER_PORT);
    if(tcpSocket->waitForConnected(3000))
    {
        qDebug() << "Connected!";
        tcpSocket->write(data);
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

connectMonitor* connectMonitor:: getConnectionMonitor(){
    static connectMonitor* self;
    if(self==nullptr){
        self=new connectMonitor();
    }
    return self;
}
