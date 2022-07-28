/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnLogin;
    QLabel *label;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(800, 1280);
        MainWindow->setMinimumSize(QSize(600, 1024));
        QFont font;
        font.setFamily(QStringLiteral("UTM Hanzel"));
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/UI/images/bp.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("background-image: url(:/img/UI/images/Custom Size \342\200\223 2.png);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setStyleSheet(QStringLiteral(""));
        btnLogin = new QPushButton(centralwidget);
        btnLogin->setObjectName(QStringLiteral("btnLogin"));
        btnLogin->setGeometry(QRect(110, 700, 566, 471));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnLogin->sizePolicy().hasHeightForWidth());
        btnLogin->setSizePolicy(sizePolicy);
        btnLogin->setMinimumSize(QSize(566, 64));
        QFont font1;
        font1.setFamily(QStringLiteral("UTM BryantLG"));
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        btnLogin->setFont(font1);
        btnLogin->setCursor(QCursor(Qt::BlankCursor));
        btnLogin->setAutoFillBackground(false);
        btnLogin->setStyleSheet(QLatin1String("QPushButton {\n"
"border:none;\n"
"	background: transparent;\n"
"   border-image:url(:/img/UI/images/SELEX SBS icon/Group 161.png);\n"
"   background-repeat: no-repeat;\n"
"text-decoration: none;\n"
"background-position:left top;\n"
"background-position: center;\n"
"\n"
"}\n"
"\n"
"	color: rgb(32, 74, 135);\n"
"\n"
""));
        btnLogin->setIconSize(QSize(200, 200));
        btnLogin->setAutoRepeat(false);
        btnLogin->setAutoRepeatDelay(300);
        btnLogin->setAutoDefault(false);
        btnLogin->setFlat(false);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 1120, 801, 61));
        label->setStyleSheet(QLatin1String("color: rgb(141, 198, 255);\n"
"background: transparent;\n"
"background-image:url(:/img/UI/images/SELEX SBS icon/Ellipse 5.png);\n"
"background-repeat: no-repeat;\n"
"text-decoration: none;"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        btnLogin->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "BSS", Q_NULLPTR));
        btnLogin->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        btnLogin->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
