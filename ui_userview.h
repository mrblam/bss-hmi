/********************************************************************************
** Form generated from reading UI file 'userview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERVIEW_H
#define UI_USERVIEW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserView
{
public:
    QWidget *centralwidget;
    QLabel *lblUserName;
    QLabel *lblUserAvatar;
    QWidget *horizontalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnSwap;
    QPushButton *btnOnlyCharge;
    QPushButton *btnLogout;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_7;
    QLabel *label_2;
    QLabel *label_8;
    QLabel *label_3;
    QLabel *label_9;
    QProgressBar *timeoutBar;
    QLabel *labelCountDowTimeout;

    void setupUi(QMainWindow *UserView)
    {
        if (UserView->objectName().isEmpty())
            UserView->setObjectName(QStringLiteral("UserView"));
        UserView->resize(800, 1280);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UserView->sizePolicy().hasHeightForWidth());
        UserView->setSizePolicy(sizePolicy);
        UserView->setStyleSheet(QLatin1String("#centralwidget{\n"
"border-image:url(:/img/UI/images/userview.png) 0 0 0 0 stretch stretch;\n"
"}"));
        centralwidget = new QWidget(UserView);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(2, 0));
        centralwidget->setStyleSheet(QStringLiteral(""));
        lblUserName = new QLabel(centralwidget);
        lblUserName->setObjectName(QStringLiteral("lblUserName"));
        lblUserName->setGeometry(QRect(160, 190, 681, 81));
        QFont font;
        font.setFamily(QStringLiteral("UTM BryantLG"));
        font.setPointSize(40);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        font.setKerning(true);
        lblUserName->setFont(font);
        lblUserName->setLayoutDirection(Qt::LeftToRight);
        lblUserName->setAutoFillBackground(false);
        lblUserName->setStyleSheet(QStringLiteral("color: rgb(32, 74, 135);"));
        lblUserName->setTextFormat(Qt::PlainText);
        lblUserName->setAlignment(Qt::AlignCenter);
        lblUserAvatar = new QLabel(centralwidget);
        lblUserAvatar->setObjectName(QStringLiteral("lblUserAvatar"));
        lblUserAvatar->setGeometry(QRect(75, 156, 211, 191));
        lblUserAvatar->setStyleSheet(QStringLiteral("image: url(:/img/UI/images/SELEX SBS icon/Group 409.png);"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(470, 450, 251, 511));
        verticalLayout = new QVBoxLayout(horizontalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btnSwap = new QPushButton(horizontalLayoutWidget);
        btnSwap->setObjectName(QStringLiteral("btnSwap"));
        btnSwap->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(100);
        sizePolicy1.setVerticalStretch(100);
        sizePolicy1.setHeightForWidth(btnSwap->sizePolicy().hasHeightForWidth());
        btnSwap->setSizePolicy(sizePolicy1);
        btnSwap->setMinimumSize(QSize(0, 60));
        btnSwap->setMaximumSize(QSize(16777215, 150));
        QFont font1;
        font1.setFamily(QStringLiteral("DejaVu Sans"));
        font1.setPointSize(16);
        font1.setBold(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        btnSwap->setFont(font1);
        btnSwap->setContextMenuPolicy(Qt::PreventContextMenu);
        btnSwap->setLayoutDirection(Qt::RightToLeft);
        btnSwap->setStyleSheet(QLatin1String("background: transparent;\n"
"background-image: url(:/img/UI/images/SELEX SBS icon/Group 371.png);\n"
"background-repeat: no-repeat;\n"
"text-decoration: none;\n"
"background-position:left top;\n"
"background-position: center;"));
        btnSwap->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        btnSwap->setFlat(true);

        verticalLayout->addWidget(btnSwap);

        btnOnlyCharge = new QPushButton(horizontalLayoutWidget);
        btnOnlyCharge->setObjectName(QStringLiteral("btnOnlyCharge"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnOnlyCharge->sizePolicy().hasHeightForWidth());
        btnOnlyCharge->setSizePolicy(sizePolicy2);
        btnOnlyCharge->setMinimumSize(QSize(0, 60));
        btnOnlyCharge->setMaximumSize(QSize(16777215, 150));
        btnOnlyCharge->setFont(font1);
        btnOnlyCharge->setStyleSheet(QLatin1String("background: transparent;\n"
"background-image: url(:/img/UI/images/SELEX SBS icon/Group 364.png);\n"
"background-repeat: no-repeat;\n"
"text-decoration: none;\n"
"background-position:left top;\n"
"background-position: center;\n"
"\n"
""));
        btnOnlyCharge->setFlat(true);

        verticalLayout->addWidget(btnOnlyCharge);

        btnLogout = new QPushButton(horizontalLayoutWidget);
        btnLogout->setObjectName(QStringLiteral("btnLogout"));
        sizePolicy2.setHeightForWidth(btnLogout->sizePolicy().hasHeightForWidth());
        btnLogout->setSizePolicy(sizePolicy2);
        btnLogout->setMinimumSize(QSize(0, 60));
        btnLogout->setMaximumSize(QSize(16777215, 150));
        btnLogout->setFont(font1);
        btnLogout->setStyleSheet(QLatin1String("background: transparent;\n"
"background-image: url(:/img/UI/images/SELEX SBS icon/Group 370.png);\n"
"background-repeat: no-repeat;\n"
"text-decoration: none;\n"
"background-position:left top;\n"
"background-position: center;\n"
"\n"
""));
        btnLogout->setFlat(true);

        verticalLayout->addWidget(btnLogout);

        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(95, 500, 301, 441));
        QFont font2;
        font2.setFamily(QStringLiteral("UTM BryantLG"));
        font2.setBold(true);
        font2.setWeight(75);
        layoutWidget->setFont(font2);
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 63));
        QFont font3;
        font3.setFamily(QStringLiteral("UTM BryantLG"));
        font3.setPointSize(20);
        font3.setBold(true);
        font3.setWeight(75);
        label->setFont(font3);
        label->setStyleSheet(QLatin1String("color: rgb(141, 198, 255);\n"
"text-align:right;"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setEnabled(true);
        label_7->setMinimumSize(QSize(0, 40));
        label_7->setFont(font3);
        label_7->setStyleSheet(QStringLiteral("color: rgb(32, 74, 135);"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_7);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(0, 63));
        label_2->setFont(font3);
        label_2->setCursor(QCursor(Qt::BlankCursor));
        label_2->setStyleSheet(QStringLiteral("color: rgb(141, 198, 255);"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(0, 40));
        label_8->setFont(font3);
        label_8->setStyleSheet(QStringLiteral("color: rgb(32, 74, 135)"));
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_8);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(0, 63));
        label_3->setFont(font3);
        label_3->setStyleSheet(QStringLiteral("color: rgb(141, 198, 255);"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(0, 40));
        label_9->setFont(font3);
        label_9->setStyleSheet(QStringLiteral("color: rgb(32, 74, 135)"));
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_9);

        timeoutBar = new QProgressBar(centralwidget);
        timeoutBar->setObjectName(QStringLiteral("timeoutBar"));
        timeoutBar->setGeometry(QRect(0, 1260, 810, 15));
        timeoutBar->setStyleSheet(QLatin1String("QProgressBar::chunk {\n"
"	background-color: 	qlineargradient( x1: 0, y1 : 0, x2: 1,  y2: 0, stop:0.8 cyan, stop:0.9 white, stop: 0.95 cyan );		\n"
"	border-radius:4px;\n"
"}\n"
"QProgressBar {\n"
"	border: 0px; \n"
"	border-radius: 4px;\n"
"	background: rgb(136, 138, 133); \n"
"	padding: 0px; \n"
"	margin-right: 4px;\n"
"}"));
        timeoutBar->setMaximum(20000);
        timeoutBar->setValue(20000);
        timeoutBar->setTextVisible(false);
        labelCountDowTimeout = new QLabel(centralwidget);
        labelCountDowTimeout->setObjectName(QStringLiteral("labelCountDowTimeout"));
        labelCountDowTimeout->setGeometry(QRect(510, 1228, 281, 31));
        QFont font4;
        font4.setFamily(QStringLiteral("UTM BryantLG"));
        font4.setPointSize(15);
        font4.setBold(true);
        font4.setWeight(75);
        labelCountDowTimeout->setFont(font4);
        labelCountDowTimeout->setStyleSheet(QStringLiteral("color: rgb(15, 45, 208);"));
        UserView->setCentralWidget(centralwidget);

        retranslateUi(UserView);

        QMetaObject::connectSlotsByName(UserView);
    } // setupUi

    void retranslateUi(QMainWindow *UserView)
    {
        UserView->setWindowTitle(QApplication::translate("UserView", "MainWindow", Q_NULLPTR));
        lblUserName->setText(QApplication::translate("UserView", "Nguyen Van Bay", Q_NULLPTR));
        lblUserAvatar->setText(QString());
        btnSwap->setText(QString());
        btnOnlyCharge->setText(QString());
        btnLogout->setText(QString());
        label->setText(QApplication::translate("UserView", "H\341\272\241ng th\303\240nh vi\303\252n", Q_NULLPTR));
        label_7->setText(QApplication::translate("UserView", "B\341\272\241ch kim", Q_NULLPTR));
        label_2->setText(QApplication::translate("UserView", "Lo\341\272\241i thu\303\252 bao", Q_NULLPTR));
        label_8->setText(QApplication::translate("UserView", "Tr\341\272\243 tr\306\260\341\273\233c", Q_NULLPTR));
        label_3->setText(QApplication::translate("UserView", "S\341\273\221 d\306\260", Q_NULLPTR));
        label_9->setText(QApplication::translate("UserView", "500,000", Q_NULLPTR));
        labelCountDowTimeout->setText(QApplication::translate("UserView", "Th\341\273\235i gian c\303\262n l\341\272\241i:20gi\303\242y", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UserView: public Ui_UserView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERVIEW_H
