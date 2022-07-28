/********************************************************************************
** Form generated from reading UI file 'continue.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTINUE_H
#define UI_CONTINUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Continue
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnContinue;
    QProgressBar *timeoutBar;
    QLabel *lblIconInform;
    QLabel *lblTextInform;
    QLabel *labelCountDowTimeout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Continue)
    {
        if (Continue->objectName().isEmpty())
            Continue->setObjectName(QStringLiteral("Continue"));
        Continue->resize(800, 1280);
        Continue->setStyleSheet(QString::fromUtf8("#centralwidget{\n"
"border-image: url(:/img/UI/images/Custom Size \342\200\223 9.png);\n"
"}"));
        centralwidget = new QWidget(Continue);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(50, 920, 701, 151));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnCancel = new QPushButton(horizontalLayoutWidget);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnCancel->sizePolicy().hasHeightForWidth());
        btnCancel->setSizePolicy(sizePolicy);
        btnCancel->setStyleSheet(QLatin1String("background: transparent;\n"
"background-image: url(:/img/UI/images/SELEX SBS icon/Group 395.png);\n"
"background-repeat: no-repeat;\n"
"text-decoration: none;\n"
"background-position:left top;\n"
"background-position: center;"));

        horizontalLayout->addWidget(btnCancel);

        horizontalSpacer = new QSpacerItem(70, 19, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnContinue = new QPushButton(horizontalLayoutWidget);
        btnContinue->setObjectName(QStringLiteral("btnContinue"));
        sizePolicy.setHeightForWidth(btnContinue->sizePolicy().hasHeightForWidth());
        btnContinue->setSizePolicy(sizePolicy);
        btnContinue->setStyleSheet(QLatin1String("background: transparent;\n"
"background-image: url(:/img/UI/images/SELEX SBS icon/Group 371.png);\n"
"background-repeat: no-repeat;\n"
"text-decoration: none;\n"
"background-position:left top;\n"
"background-position: center;"));

        horizontalLayout->addWidget(btnContinue);

        timeoutBar = new QProgressBar(centralwidget);
        timeoutBar->setObjectName(QStringLiteral("timeoutBar"));
        timeoutBar->setGeometry(QRect(0, 1240, 800, 15));
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
        lblIconInform = new QLabel(centralwidget);
        lblIconInform->setObjectName(QStringLiteral("lblIconInform"));
        lblIconInform->setGeometry(QRect(340, 410, 140, 140));
        lblIconInform->setStyleSheet(QStringLiteral("image: url(:/img/UI/images/SELEX SBS icon/done.png);"));
        lblTextInform = new QLabel(centralwidget);
        lblTextInform->setObjectName(QStringLiteral("lblTextInform"));
        lblTextInform->setGeometry(QRect(55, 110, 691, 141));
        QFont font;
        font.setFamily(QStringLiteral("UTM BryantLG"));
        font.setPointSize(29);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        lblTextInform->setFont(font);
        lblTextInform->setStyleSheet(QLatin1String("QLabel {\n"
"qproperty-alignment: AlignCenter;\n"
"color: rgb(0, 255, 224);\n"
"}"));
        labelCountDowTimeout = new QLabel(centralwidget);
        labelCountDowTimeout->setObjectName(QStringLiteral("labelCountDowTimeout"));
        labelCountDowTimeout->setGeometry(QRect(510, 1208, 281, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("UTM BryantLG"));
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        labelCountDowTimeout->setFont(font1);
        labelCountDowTimeout->setStyleSheet(QStringLiteral("color: rgb(15, 45, 208);"));
        Continue->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Continue);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Continue->setStatusBar(statusbar);

        retranslateUi(Continue);

        QMetaObject::connectSlotsByName(Continue);
    } // setupUi

    void retranslateUi(QMainWindow *Continue)
    {
        Continue->setWindowTitle(QApplication::translate("Continue", "MainWindow", Q_NULLPTR));
        btnCancel->setText(QString());
        btnContinue->setText(QString());
        lblIconInform->setText(QString());
        lblTextInform->setText(QApplication::translate("Continue", "\304\220\341\273\225i pin th\303\240nh c\303\264ng\n"
" b\341\272\241n c\303\263 mu\341\273\221n ti\341\272\277p t\341\273\245c?", Q_NULLPTR));
        labelCountDowTimeout->setText(QApplication::translate("Continue", "Th\341\273\235i gian c\303\262n l\341\272\241i:20gi\303\242y", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Continue: public Ui_Continue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTINUE_H
