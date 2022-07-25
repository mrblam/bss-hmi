#include "interprocesscom.h"

interprocesscom::interprocesscom(QObject *parent) : QObject(parent)
  , tcpSocket(new QTcpSocket(this))
{
//        dataStream.setDevice(tcpSocket);
//        dataStream.setVersion(QDataStream::Qt_5_0);
    tcpServer = new QTcpServer(this);

    if (!this->tcpServer->listen(QHostAddress::Any,TCP_SERVER_PORT_WRITE))
    {
        qDebug() << tr("Unable to start the server: %1.").arg(tcpServer->errorString()) ;
        return;
    }
    qDebug() << "  port is " << tcpServer->serverPort();

    connect(tcpServer, &QTcpServer::newConnection, this, &interprocesscom::sendMessage);
    connect(tcpSocket, &QIODevice::readyRead, this, &interprocesscom::readFortune);
    connect(&heartbeatrequest,&QTimer::timeout,this,&interprocesscom::requestNewFortune);
    heartbeatrequest.start(1000);
//  connect(tcpSocket, &QAbstractSocket::SocketError(),this, &interprocesscom::displayError);
}
void interprocesscom::requestNewFortune()
{

    if(tcpSocket->waitForConnected(3000))
    {
        qDebug() << "da ket noi app1 " ;
    }
    else
    {
        qDebug() << "ko ket noi";
    }

}
void interprocesscom::readFortune()

{
    qDebug() << "co tin hieu readyRead,du lieu nhan duoc la : ";
    tcpSocket->waitForReadyRead(3000);
    qDebug() << "Reading : " << tcpSocket->bytesAvailable();
    qDebug() << tcpSocket->readAll();
    tcpSocket->close();
//        dataStream.startTransaction();
//        qDebug() << dataStream;
//        QString str;
//        qint32 a;
//        dataStream >> str >> a ;
//        qDebug() << "data "<< str << a ;
//        QString nextFortune;
//        dataStream >> nextFortune;
//        if (!dataStream.commitTransaction())
//            qDebug() << dataStream.commitTransaction();
//            return;
//        if (nextFortune == currentFortune) {
//            QTimer::singleShot(0, this, &interprocesscom::requestNewFortune);
//            return;
//        }
//        currentFortune = nextFortune;
//        qDebug() << "hmi nhan dc "<< currentFortune;
}
void interprocesscom::sendMessage(const char *data)
{
    tcpSocket->abort();
    tcpSocket->connectToHost("localhost",TCP_SERVER_PORT_READ);
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();

    clientConnection->write(data);
    qDebug() << "server send" << clientConnection;
}
