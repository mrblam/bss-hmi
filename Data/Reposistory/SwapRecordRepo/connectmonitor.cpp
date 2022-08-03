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
            connectToLocalServer(":UI,BP view open*");
            qDebug()<<"BP view open";
        }
        else
        {
            connectToLocalServer(":UI,BP view close*");
            qDebug()<<"BP view close";
        }
        break;

    case UI_DISPLAY_CONTINUE:
        if(status)
        {
            connectToLocalServer(":UI,Display continue open*");
            qDebug()<<"UI display continue open";
        }
        else
        {
            connectToLocalServer(":UI,Display continue close*");
            qDebug()<<"UI display continue close";
        }
        break;

    case UI_DISPLAY_LOGIN:
        if(status)
        {
            connectToLocalServer(":S,L,O*");
            qDebug()<<"LOGIN OPEN";
        }
        else
        {
            connectToLocalServer(":S,L,C*");
            qDebug()<<"LOGIN CLOSE";
        }
        break;
    case UI_DISPLAY_SWAPRECORD:
        if(status)
        {
            connectToLocalServer(":UI,Dislay swaprecord open*");
            qDebug()<<"UI_DISPLAY_SWAPRECORD Open";
        }
        else
        {
            connectToLocalServer(":UI,Dislay swaprecord close*");
            qDebug()<<"UI dislay swaprecord close";
        }
        break;

    case UI_DISPLAY_USER_VIEW:
        if(status)
        {
            connectToLocalServer(":UI,Dislay user view open*");
            qDebug()<<"UI dislay user view open";
        }
        else
        {
            connectToLocalServer(":UI,Dislay user view close*");
            qDebug()<<"UI dislay user view close";
        }
        break;

    case UI_DISPLAY_DEFAULT:
        if(status)
        {

//            buildMsgToRequest("S",'s');
            connectToLocalServer(":S,D,O*");
            qDebug()<<"UI dislay default";
        }
        else
        {
            connectToLocalServer(":S,D,C*");
            qDebug()<<"UI dislay default";
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

void connectMonitor::buildMsgToRequest(const char *data,const char &sub)
{

    buff.append(":");
    buff.append(data);
    buff.append(',');
    buff.append(sub);
    buff.append(',');
    buff.append('O');
    buff.append('*');


}

connectMonitor* connectMonitor:: getConnectionMonitor(){
    static connectMonitor* self;
    if(self==nullptr){
        self=new connectMonitor();
    }
    return self;
}
