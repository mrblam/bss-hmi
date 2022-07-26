﻿#include "UI/mainwindow.h"
#include "UI/bpview.h"
#include <QApplication>
#include "UI/login.h"
#include <QtNetwork/QNetworkProxy>
#include "QtMqtt"
#include "bssmqttclient.h"
#include <QFontDatabase>
#include <QWindow>
#include <cstring>
#include "Data/Reposistory/SwapRecordRepo/swaprecordrepo.h"
#include "Data/Reposistory/SwapRecordRepo/bsshttpmethod.h"
#include "interprocesscom.h"

//#include "Data/Datasource/localsqlitedb.h"
static void loadAppStyleSheet(const QString& path);
static void handleVisibleChanged();

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
    const QString bss_sn="bss_v1.0_0001";
    const QString port_name="/dev/ttyUSB0";
    const uint32_t cab_num=6;
    const QMqttTopicName topic{"dt/swaping/info"};
    const QString hostname{"selex.site"};
    const quint16 port = 1883;
    const QMqttTopicFilter filter{"cmd/swaping/#"};
    QApplication a(argc, argv);
    QObject::connect(QGuiApplication::inputMethod(), &QInputMethod::visibleChanged, &handleVisibleChanged);
    loadAppStyleSheet(":/UI/appStyle.css");

    /*Cabinet Comminication*/
    BSS* bss=new BSS(cab_num);
    bss->setState(BSS_ST_INIT);
    bss->setSerialNumber(bss_sn);
    CabinetCom* cabCom=CabinetCom::getCabCom();
    cabCom->setChangePortTimeout(0);
    cabCom->setBssModel(bss);
    cabCom->getSwapRecord()->setBss(bss->getSerialNumber());
    cabCom->start(port_name);// bat dau connect voi master ///luong giao tiep master

    /*Server Comminication*/
    BssHttpMethod* bssHttpMethod = BssHttpMethod::getBssHttpMenthod();
    QObject::connect(cabCom,&CabinetCom::onSwapRecordChanged,bssHttpMethod,&BssHttpMethod::updateSwapRecord);

    BSSMqttClient* mqttClient=BSSMqttClient::getBSSMqttClient();
    mqttClient->setBss(bss);
    mqttClient->setHost(hostname);
    mqttClient->setPort(port);
    mqttClient->setMqttUser("selex");
    mqttClient->setMqttPass("selex");
    const QList<QString> listSwapTableCreate ={"time varchar(200)","bss varchar(200)","username varchar(200)","old_cab varchar(200)","old_pin varchar(200)","new_cab varchar(200)","new_pin varchar(200)", "state varchar(200)", "isDone bool","isSync bool"};
    const QList<QString> listSwapTableInsert ={"time","bss","username","old_cab","old_pin","new_cab","new_pin", "state", "isDone" ,"isSync"};
    const QString& nameTable = "swaprecord";
    const QString& nameDb = "localdatabase.db";
    LocalSQLiteDb* sqlSwapRecordDb = new LocalSQLiteDb();
    sqlSwapRecordDb->setListColInsert(listSwapTableInsert);
    sqlSwapRecordDb->setListColCreate(listSwapTableCreate);
    sqlSwapRecordDb->setNameDatabase(nameDb);
    sqlSwapRecordDb->setNameTable(nameTable);
    SwapRecordRepo* swapRecordRepo = SwapRecordRepo::getNewSwapRecordRepo();
    swapRecordRepo->createDb(sqlSwapRecordDb);
    swapRecordRepo->createTable(sqlSwapRecordDb);

    QObject::connect(swapRecordRepo, &SwapRecordRepo::onUpdateMqttServer, mqttClient,&BSSMqttClient::syncLocaldbToServerdb);
    QObject::connect(mqttClient, &BSSMqttClient::onDonePublicData,swapRecordRepo,&SwapRecordRepo::okSend);
    QObject::connect(cabCom, &CabinetCom::onSwapRecordChanged, swapRecordRepo,&SwapRecordRepo::updatetoDb);
    QObject::connect(cabCom,&CabinetCom::onBSSChanged,mqttClient,&BSSMqttClient::updateBSS);
    QObject::connect(cabCom,&CabinetCom::onBPChanged,mqttClient,&BSSMqttClient::updateBp);
    QObject::connect(cabCom,&CabinetCom::onSwapRecordChanged,mqttClient,&BSSMqttClient::updateSwapRecord);
    mqttClient->start();
    MainWindow w(cabCom);
    interprocesscom client;
    QObject::connect(w(cabCom),&MainWindow::initSystem,client,&interprocesscom::sendMessage);

    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.showFullScreen();
    w.onBSSStateChanged(bss);
    return a.exec();
}

static void loadAppStyleSheet(const QString& path){
    QFile file(path);
     file.open(QFile::ReadOnly);
     QString styleSheet = QLatin1String(file.readAll());
     qApp->setStyleSheet(styleSheet);
}

static void handleVisibleChanged(){
    if (!QGuiApplication::inputMethod()->isVisible())
        return;
    for(QWindow * w: QGuiApplication::allWindows()){
        if(std::strcmp(w->metaObject()->className(), "QtVirtualKeyboard::InputView") == 0){
            if(QObject *keyboard = w->findChild<QObject *>("keyboard")){
                QRect r = w->geometry();
                r.moveTop(keyboard->property("y").toDouble());
                w->setMask(r);
                return;
            }
        }
    }
}
