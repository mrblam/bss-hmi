/********************************************************************************
** Form generated from reading UI file 'swapview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWAPVIEW_H
#define UI_SWAPVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SwapView
{
public:
    QWidget *centralwidget;
    QLabel *lblState;
    QLabel *lblHeader;
    QLabel *bpPin;
    QLabel *lblIcon;

    void setupUi(QMainWindow *SwapView)
    {
        if (SwapView->objectName().isEmpty())
            SwapView->setObjectName(QStringLiteral("SwapView"));
        SwapView->resize(800, 1280);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SwapView->sizePolicy().hasHeightForWidth());
        SwapView->setSizePolicy(sizePolicy);
        SwapView->setCursor(QCursor(Qt::ArrowCursor));
        SwapView->setStyleSheet(QString::fromUtf8("#centralwidget{border-image:url(:/img/UI/images/Custom Size \342\200\223 7.png) 0 0 0 0 stretch stretch;}\n"
""));
        centralwidget = new QWidget(SwapView);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        centralwidget->setStyleSheet(QStringLiteral(""));
        lblState = new QLabel(centralwidget);
        lblState->setObjectName(QStringLiteral("lblState"));
        lblState->setGeometry(QRect(314, 143, 100, 100));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(173);
        sizePolicy2.setHeightForWidth(lblState->sizePolicy().hasHeightForWidth());
        lblState->setSizePolicy(sizePolicy2);
        QPalette palette;
        QBrush brush(QColor(0, 255, 224, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 0));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(0, 255, 224, 128));
        brush2.setStyle(Qt::NoBrush);
        //palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush3(QColor(0, 255, 224, 128));
        brush3.setStyle(Qt::NoBrush);
       // palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush4(QColor(0, 255, 224, 128));
        brush4.setStyle(Qt::NoBrush);
        //palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush4);
        lblState->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("UTM BryantLG"));
        font.setPointSize(62);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        lblState->setFont(font);
        lblState->setStyleSheet(QStringLiteral("background: transparent;  color: rgb(0, 255, 224);"));
        lblState->setScaledContents(false);
        lblState->setAlignment(Qt::AlignCenter);
        lblHeader = new QLabel(centralwidget);
        lblHeader->setObjectName(QStringLiteral("lblHeader"));
        lblHeader->setGeometry(QRect(48, 97, 711, 191));
        QFont font1;
        font1.setFamily(QStringLiteral("UTM BryantLG"));
        font1.setPointSize(32);
        font1.setBold(true);
        font1.setWeight(75);
        lblHeader->setFont(font1);
        lblHeader->setStyleSheet(QLatin1String("background: transparent; \n"
"color:rgb(0, 255, 224)"));
        lblHeader->setAlignment(Qt::AlignCenter);
        bpPin = new QLabel(centralwidget);
        bpPin->setObjectName(QStringLiteral("bpPin"));
        bpPin->setGeometry(QRect(225, 705, 271, 120));
        bpPin->setStyleSheet(QLatin1String("background: transparent;\n"
"background-image: url(:/img/UI/images/SELEX SBS icon/battery station3.158.png);\n"
"background-repeat: no-repeat;\n"
"text-decoration: none;\n"
"background-position:left top;\n"
""));
        lblIcon = new QLabel(centralwidget);
        lblIcon->setObjectName(QStringLiteral("lblIcon"));
        lblIcon->setGeometry(QRect(50, 430, 691, 441));
        lblIcon->setStyleSheet(QLatin1String("	background: transparent;\n"
"   background-image:url(:/img/UI/images/SELEX SBS icon/Group 381.png);\n"
"   background-repeat: no-repeat;\n"
"text-decoration: none;\n"
"background-position:left top;\n"
"background-position: center;"));
        SwapView->setCentralWidget(centralwidget);

        retranslateUi(SwapView);

        QMetaObject::connectSlotsByName(SwapView);
    } // setupUi

    void retranslateUi(QMainWindow *SwapView)
    {
        SwapView->setWindowTitle(QApplication::translate("SwapView", "MainWindow", Q_NULLPTR));
        lblState->setText(QApplication::translate("SwapView", "1", Q_NULLPTR));
        lblHeader->setText(QApplication::translate("SwapView", "Header", Q_NULLPTR));
        bpPin->setText(QString());
        lblIcon->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SwapView: public Ui_SwapView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWAPVIEW_H
