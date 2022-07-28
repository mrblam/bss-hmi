/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *complex;
    QLineEdit *txtUsername;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *txtPassword;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnLogin;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;
    QLabel *lblLoginStatus;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QProgressBar *timeoutBar;
    QLabel *labelCountDowTimeout;

    void setupUi(QMainWindow *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(800, 1280);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Login->sizePolicy().hasHeightForWidth());
        Login->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("UTM Hanzel"));
        Login->setFont(font);
        Login->setCursor(QCursor(Qt::ArrowCursor));
        Login->setStyleSheet(QLatin1String("#centralwidget{\n"
"	border-image:url(:/img/UI/images/login) 0 0 0 0 stretch stretch;\n"
"}\n"
""));
        centralwidget = new QWidget(Login);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(600, 1024));
        centralwidget->setStyleSheet(QStringLiteral(""));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 870, 781, 316));
        complex = new QVBoxLayout(verticalLayoutWidget);
        complex->setObjectName(QStringLiteral("complex"));
        complex->setContentsMargins(0, 0, 0, 9);
        txtUsername = new QLineEdit(verticalLayoutWidget);
        txtUsername->setObjectName(QStringLiteral("txtUsername"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txtUsername->sizePolicy().hasHeightForWidth());
        txtUsername->setSizePolicy(sizePolicy1);
        txtUsername->setMinimumSize(QSize(600, 60));
        QFont font1;
        font1.setFamily(QStringLiteral("SFU Helvetica"));
        font1.setPointSize(19);
        txtUsername->setFont(font1);
        txtUsername->setAutoFillBackground(false);
        txtUsername->setStyleSheet(QLatin1String("background: transparent;  color: rgb(0, 0, 0);\n"
"border: none;"));
        txtUsername->setAlignment(Qt::AlignCenter);

        complex->addWidget(txtUsername);

        verticalSpacer_3 = new QSpacerItem(20, 4, QSizePolicy::Minimum, QSizePolicy::Preferred);

        complex->addItem(verticalSpacer_3);

        txtPassword = new QLineEdit(verticalLayoutWidget);
        txtPassword->setObjectName(QStringLiteral("txtPassword"));
        sizePolicy1.setHeightForWidth(txtPassword->sizePolicy().hasHeightForWidth());
        txtPassword->setSizePolicy(sizePolicy1);
        txtPassword->setMinimumSize(QSize(600, 60));
        QFont font2;
        font2.setFamily(QStringLiteral("SFU Helvetica"));
        font2.setPointSize(19);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        txtPassword->setFont(font2);
        txtPassword->setStyleSheet(QLatin1String("background: transparent;  color: rgb(0, 0, 0);\n"
"border: none;"));
        txtPassword->setEchoMode(QLineEdit::Password);
        txtPassword->setAlignment(Qt::AlignCenter);

        complex->addWidget(txtPassword);

        verticalSpacer_2 = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Preferred);

        complex->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, -1, 0, -1);
        horizontalSpacer_5 = new QSpacerItem(85, 30, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        btnLogin = new QPushButton(verticalLayoutWidget);
        btnLogin->setObjectName(QStringLiteral("btnLogin"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnLogin->sizePolicy().hasHeightForWidth());
        btnLogin->setSizePolicy(sizePolicy2);
        btnLogin->setMinimumSize(QSize(0, 115));
        QFont font3;
        font3.setFamily(QStringLiteral("DejaVu Sans Mono"));
        font3.setPointSize(16);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setUnderline(false);
        font3.setWeight(50);
        font3.setStrikeOut(false);
        btnLogin->setFont(font3);
        btnLogin->setLayoutDirection(Qt::LeftToRight);
        btnLogin->setAutoFillBackground(false);
        btnLogin->setStyleSheet(QLatin1String("background: transparent;\n"
"background-image: url(:/img/UI/images/SELEX SBS icon/Group 368.png);\n"
"background-repeat: no-repeat;\n"
"text-decoration: none;\n"
"background-position:left top;\n"
"background-position: center;\n"
"\n"
""));
        btnLogin->setFlat(true);

        horizontalLayout->addWidget(btnLogin);

        horizontalSpacer_3 = new QSpacerItem(90, 28, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btnCancel = new QPushButton(verticalLayoutWidget);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnCancel->sizePolicy().hasHeightForWidth());
        btnCancel->setSizePolicy(sizePolicy3);
        btnCancel->setMinimumSize(QSize(0, 115));
        QFont font4;
        font4.setFamily(QStringLiteral("DejaVu Sans Mono"));
        font4.setPointSize(16);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setWeight(50);
        btnCancel->setFont(font4);
        btnCancel->setStyleSheet(QLatin1String("background: transparent;\n"
"background-image: url(:/img/UI/images/SELEX SBS icon/Group 367.png);\n"
"background-repeat: no-repeat;\n"
"background-position:left top;\n"
"background-position:center;\n"
"\n"
"\n"
""));
        btnCancel->setFlat(true);

        horizontalLayout->addWidget(btnCancel);

        horizontalSpacer_6 = new QSpacerItem(58, 27, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);


        complex->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Preferred);

        complex->addItem(verticalSpacer);

        lblLoginStatus = new QLabel(verticalLayoutWidget);
        lblLoginStatus->setObjectName(QStringLiteral("lblLoginStatus"));
        sizePolicy3.setHeightForWidth(lblLoginStatus->sizePolicy().hasHeightForWidth());
        lblLoginStatus->setSizePolicy(sizePolicy3);
        lblLoginStatus->setMinimumSize(QSize(600, 26));
        QFont font5;
        font5.setFamily(QStringLiteral("UTM BryantLG"));
        font5.setPointSize(15);
        font5.setBold(true);
        font5.setItalic(false);
        font5.setWeight(75);
        lblLoginStatus->setFont(font5);
        lblLoginStatus->setStyleSheet(QStringLiteral("background: transparent;  color: rgb(32, 74, 135);"));
        lblLoginStatus->setAlignment(Qt::AlignCenter);

        complex->addWidget(lblLoginStatus);

        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 120, 781, 460));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        timeoutBar = new QProgressBar(centralwidget);
        timeoutBar->setObjectName(QStringLiteral("timeoutBar"));
        timeoutBar->setEnabled(true);
        timeoutBar->setGeometry(QRect(0, 1262, 810, 15));
        QFont font6;
        font6.setPointSize(8);
        timeoutBar->setFont(font6);
        timeoutBar->setStyleSheet(QLatin1String("QProgressBar::chunk {\n"
"	 background-color: 	qlineargradient( x1: 0, y1 : 0, x2: 1,  y2: 0,    stop:0.8 cyan, stop:0.9 white, stop: 0.95 cyan);		\n"
"	 border-radius:4px;\n"
"}  \n"
"QProgressBar {\n"
"	border: 0px; \n"
"	border-radius: 4px;\n"
"	background: rgb(136, 138, 133); \n"
"	padding: 0px; \n"
"	margin-right: 4px;\n"
"}"));
        timeoutBar->setMaximum(60000);
        timeoutBar->setValue(60000);
        timeoutBar->setTextVisible(false);
        timeoutBar->setOrientation(Qt::Horizontal);
        timeoutBar->setInvertedAppearance(false);
        timeoutBar->setTextDirection(QProgressBar::TopToBottom);
        labelCountDowTimeout = new QLabel(centralwidget);
        labelCountDowTimeout->setObjectName(QStringLiteral("labelCountDowTimeout"));
        labelCountDowTimeout->setGeometry(QRect(510, 1230, 281, 31));
        QFont font7;
        font7.setFamily(QStringLiteral("UTM BryantLG"));
        font7.setPointSize(15);
        font7.setBold(true);
        font7.setWeight(75);
        labelCountDowTimeout->setFont(font7);
        labelCountDowTimeout->setStyleSheet(QStringLiteral("color: rgb(15, 45, 208);"));
        Login->setCentralWidget(centralwidget);
        QWidget::setTabOrder(txtUsername, txtPassword);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QMainWindow *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "BSS-Login", Q_NULLPTR));
        txtUsername->setText(QString());
        txtUsername->setPlaceholderText(QApplication::translate("Login", "T\303\252n s\341\273\255 d\341\273\245ng", Q_NULLPTR));
        txtPassword->setText(QString());
        txtPassword->setPlaceholderText(QApplication::translate("Login", "M\341\272\255t kh\341\272\251u", Q_NULLPTR));
        btnLogin->setText(QString());
        btnCancel->setText(QString());
        lblLoginStatus->setText(QApplication::translate("Login", "Sai mat khau hoac tai khoan", Q_NULLPTR));
        labelCountDowTimeout->setText(QApplication::translate("Login", "Th\341\273\235i gian c\303\262n l\341\272\241i:60 gi\303\242y", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
