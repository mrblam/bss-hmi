QT       += core gui mqtt serialport network sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 disable-desktop
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Data/Datasource/linkdirector.cpp \
    Data/Model/basemodel.cpp \
    Data/Model/bp.cpp \
    Data/Model/bss.cpp \
    Data/Model/cabinet.cpp \
    Data/Model/charger.cpp \
    Data/Model/localdatabase.cpp \
    Data/Model/swaprecord.cpp \
    Data/Model/user.cpp \
    Data/Reposistory/SwapRecordRepo/bsshttpmethod.cpp \
    Data/Reposistory/SwapRecordRepo/connectmonitor.cpp \
    Data/Reposistory/SwapRecordRepo/soundexecution.cpp \
    Data/Reposistory/SwapRecordRepo/swaprecordrepo.cpp \
    UI/bpview.cpp \
    UI/login.cpp \
    UI/mainwindow.cpp \
    UI/swapview.cpp \
    UI/userview.cpp \
    Util/cabcomhelper.cpp \
    bssmqttclient.cpp \
    cabinetcom.cpp \
    main.cpp \
    Data/Datasource/localsqlitedb.cpp \
    UI/continue.cpp

HEADERS += \
    Data/Datasource/linkdirector.h \
    Data/Datasource/soundsDatasource.h \
    Data/Model/basemodel.h \
    Data/Model/bp.h \
    Data/Model/bss.h \
    Data/Model/cabinet.h \
    Data/Model/charger.h \
    Data/Model/localdatabase.h \
    Data/Model/swaprecord.h \
    Data/Model/user.h \
    Data/Reposistory/SwapRecordRepo/bsshttpmethod.h \
    Data/Reposistory/SwapRecordRepo/connectmonitor.h \
    Data/Reposistory/SwapRecordRepo/soundexecution.h \
    Data/Reposistory/SwapRecordRepo/swaprecordrepo.h \
    UI/bpview.h \
    UI/login.h \
    UI/mainwindow.h \
    UI/swapview.h \
    UI/userview.h \
    Util/cabcomhelper.h \
    bssmqttclient.h \
    cabinetcom.h \
    Data/Datasource/localsqlitedb.h \
    UI/continue.h

FORMS += \
    UI/login.ui \
    UI/swapview.ui \
    UI/bpview.ui \
    UI/mainwindow.ui \
    UI/userview.ui \
    UI/bpview.ui \
    UI/continue.ui
UI_DIR=$$PWD

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


DISTFILES += \
    UI/img/Custom Size - 29.png \
    UI/img/Custom Size - 30.png \
    UI/img/Custom Size - 9.png \
    UI/img/Custom Size – 1.png \
    UI/img/Custom Size – 11.png \
    UI/img/Custom Size – 12.png \
    UI/img/Custom Size – 13.png \
    UI/img/Custom Size – 14.png \
    UI/img/Custom Size – 15.png \
    UI/img/Custom Size – 16.png \
    UI/img/Custom Size – 17.png \
    UI/img/Custom Size – 18.png \
    UI/img/Custom Size – 19.png \
    UI/img/Custom Size – 29.png \
    UI/img/Custom Size – 5.png \
    UI/img/Custom Size – 6.png \
    UI/img/Custom Size – 7.png \
    UI/img/Custom Size – 8.png \
    UI/img/Custom Size – 9.png \
    UI/img/battery station3.158.png

RESOURCES += \
    sources.qrc
