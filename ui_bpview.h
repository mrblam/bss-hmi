/********************************************************************************
** Form generated from reading UI file 'bpview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BPVIEW_H
#define UI_BPVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BPView
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnSwap;
    QPushButton *btnCancel;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelSerialnumber;
    QLabel *lblBatSN;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QLabel *labelTemp;
    QLabel *lblSOH;
    QLabel *lblTemp;
    QLabel *labelSOH;
    QSpacerItem *verticalSpacer_2;
    QLabel *labelT;
    QLabel *lblCycles;
    QLabel *labelSOC;
    QLabel *labelCabinNum;
    QProgressBar *timeoutBar;
    QLabel *labelPicPower;
    QLabel *labelCountDowTimeout;

    void setupUi(QMainWindow *BPView)
    {
        if (BPView->objectName().isEmpty())
            BPView->setObjectName(QStringLiteral("BPView"));
        BPView->resize(800, 1280);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BPView->sizePolicy().hasHeightForWidth());
        BPView->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("UTM Hanzel"));
        BPView->setFont(font);
        BPView->setStyleSheet(QLatin1String("#centralwidget{\n"
"	border-image:url(:/img/UI/images/Custom Size - 6.png);\n"
"}\n"
""));
        centralwidget = new QWidget(BPView);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        centralwidget->setFont(font);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(454, 600, 251, 361));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnSwap = new QPushButton(layoutWidget);
        btnSwap->setObjectName(QStringLiteral("btnSwap"));
        sizePolicy1.setHeightForWidth(btnSwap->sizePolicy().hasHeightForWidth());
        btnSwap->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamily(QStringLiteral("DejaVu Sans"));
        font1.setPointSize(16);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        btnSwap->setFont(font1);
        btnSwap->setCursor(QCursor(Qt::BlankCursor));
        btnSwap->setStyleSheet(QLatin1String("background: transparent;\n"
"background-image: url(:/img/UI/images/SELEX SBS icon/Group 371.png);\n"
"background-repeat: no-repeat;\n"
"text-decoration: none;\n"
"background-position:left top;\n"
""));
        btnSwap->setFlat(true);

        verticalLayout_2->addWidget(btnSwap);

        btnCancel = new QPushButton(layoutWidget);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        sizePolicy1.setHeightForWidth(btnCancel->sizePolicy().hasHeightForWidth());
        btnCancel->setSizePolicy(sizePolicy1);
        btnCancel->setFont(font1);
        btnCancel->setCursor(QCursor(Qt::BlankCursor));
        btnCancel->setStyleSheet(QLatin1String("background: transparent;\n"
"background-image: url(:/img/UI/images/SELEX SBS icon/Group 370.png);\n"
"background-repeat: no-repeat;\n"
"text-decoration: none;\n"
"background-position:left top;\n"
""));
        btnCancel->setFlat(true);

        verticalLayout_2->addWidget(btnCancel);

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(60, 600, 391, 361));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        labelSerialnumber = new QLabel(verticalLayoutWidget);
        labelSerialnumber->setObjectName(QStringLiteral("labelSerialnumber"));
        labelSerialnumber->setMinimumSize(QSize(216, 50));
        labelSerialnumber->setMaximumSize(QSize(500, 120));
        QFont font2;
        font2.setFamily(QStringLiteral("UTM BryantLG"));
        font2.setPointSize(20);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        labelSerialnumber->setFont(font2);
        labelSerialnumber->setCursor(QCursor(Qt::BlankCursor));
        labelSerialnumber->setStyleSheet(QStringLiteral("color: rgb(141, 198, 255);"));
        labelSerialnumber->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelSerialnumber);

        lblBatSN = new QLabel(verticalLayoutWidget);
        lblBatSN->setObjectName(QStringLiteral("lblBatSN"));
        lblBatSN->setMinimumSize(QSize(159, 50));
        lblBatSN->setMaximumSize(QSize(16777215, 120));
        QFont font3;
        font3.setFamily(QStringLiteral("UTM BryantLG"));
        font3.setPointSize(21);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setWeight(75);
        lblBatSN->setFont(font3);
        lblBatSN->setCursor(QCursor(Qt::BlankCursor));
        lblBatSN->setStyleSheet(QStringLiteral("color: rgb(32, 74, 135);"));
        lblBatSN->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblBatSN);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelTemp = new QLabel(verticalLayoutWidget);
        labelTemp->setObjectName(QStringLiteral("labelTemp"));
        labelTemp->setMinimumSize(QSize(216, 50));
        labelTemp->setMaximumSize(QSize(16777215, 120));
        labelTemp->setFont(font2);
        labelTemp->setCursor(QCursor(Qt::BlankCursor));
        labelTemp->setStyleSheet(QStringLiteral("color: rgb(141, 198, 255);"));
        labelTemp->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelTemp, 0, 0, 1, 1);

        lblSOH = new QLabel(verticalLayoutWidget);
        lblSOH->setObjectName(QStringLiteral("lblSOH"));
        lblSOH->setMinimumSize(QSize(159, 50));
        lblSOH->setMaximumSize(QSize(16777215, 120));
        lblSOH->setFont(font3);
        lblSOH->setCursor(QCursor(Qt::BlankCursor));
        lblSOH->setStyleSheet(QStringLiteral("color: rgb(32, 74, 135)"));
        lblSOH->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lblSOH, 2, 1, 1, 1);

        lblTemp = new QLabel(verticalLayoutWidget);
        lblTemp->setObjectName(QStringLiteral("lblTemp"));
        lblTemp->setEnabled(true);
        lblTemp->setMinimumSize(QSize(159, 50));
        lblTemp->setMaximumSize(QSize(16777215, 120));
        lblTemp->setFont(font3);
        lblTemp->setCursor(QCursor(Qt::BlankCursor));
        lblTemp->setStyleSheet(QStringLiteral("color: rgb(32, 74, 135)"));
        lblTemp->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lblTemp, 2, 0, 1, 1);

        labelSOH = new QLabel(verticalLayoutWidget);
        labelSOH->setObjectName(QStringLiteral("labelSOH"));
        QFont font4;
        font4.setFamily(QStringLiteral("UTM BryantLG"));
        font4.setPointSize(18);
        font4.setBold(true);
        font4.setWeight(75);
        labelSOH->setFont(font4);
        labelSOH->setStyleSheet(QStringLiteral("color: rgb(141, 198, 255);"));
        labelSOH->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelSOH, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        labelT = new QLabel(verticalLayoutWidget);
        labelT->setObjectName(QStringLiteral("labelT"));
        labelT->setMinimumSize(QSize(216, 50));
        labelT->setMaximumSize(QSize(16777215, 120));
        labelT->setFont(font2);
        labelT->setCursor(QCursor(Qt::BlankCursor));
        labelT->setStyleSheet(QStringLiteral("color: rgb(141, 198, 255);"));
        labelT->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelT);

        lblCycles = new QLabel(verticalLayoutWidget);
        lblCycles->setObjectName(QStringLiteral("lblCycles"));
        lblCycles->setMinimumSize(QSize(159, 50));
        lblCycles->setMaximumSize(QSize(16777215, 120));
        lblCycles->setFont(font3);
        lblCycles->setCursor(QCursor(Qt::BlankCursor));
        lblCycles->setStyleSheet(QStringLiteral("color: rgb(32, 74, 135)"));
        lblCycles->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblCycles);

        labelSOC = new QLabel(centralwidget);
        labelSOC->setObjectName(QStringLiteral("labelSOC"));
        labelSOC->setGeometry(QRect(410, 250, 233, 50));
        sizePolicy.setHeightForWidth(labelSOC->sizePolicy().hasHeightForWidth());
        labelSOC->setSizePolicy(sizePolicy);
        labelSOC->setMinimumSize(QSize(159, 50));
        labelSOC->setMaximumSize(QSize(16777215, 1677770));
        QFont font5;
        font5.setFamily(QStringLiteral("UTM BryantLG"));
        font5.setPointSize(29);
        font5.setBold(true);
        font5.setItalic(false);
        font5.setUnderline(false);
        font5.setWeight(75);
        font5.setStrikeOut(false);
        labelSOC->setFont(font5);
        labelSOC->setCursor(QCursor(Qt::BlankCursor));
        labelSOC->setStyleSheet(QLatin1String("color: rgb(211, 215, 207);\n"
"background: transparent;\n"
"background-repeat: no-repeat;\n"
"text-decoration: none;"));
        labelSOC->setAlignment(Qt::AlignCenter);
        labelCabinNum = new QLabel(centralwidget);
        labelCabinNum->setObjectName(QStringLiteral("labelCabinNum"));
        labelCabinNum->setGeometry(QRect(107, 258, 114, 101));
        QFont font6;
        font6.setFamily(QStringLiteral("UTM BryantLG"));
        font6.setPointSize(67);
        font6.setBold(true);
        font6.setWeight(75);
        labelCabinNum->setFont(font6);
        labelCabinNum->setStyleSheet(QStringLiteral("color: rgb(0, 255, 224);"));
        labelCabinNum->setAlignment(Qt::AlignCenter);
        timeoutBar = new QProgressBar(centralwidget);
        timeoutBar->setObjectName(QStringLiteral("timeoutBar"));
        timeoutBar->setGeometry(QRect(0, 1250, 800, 15));
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
        labelPicPower = new QLabel(centralwidget);
        labelPicPower->setObjectName(QStringLiteral("labelPicPower"));
        labelPicPower->setGeometry(QRect(406, 420, 237, 21));
        labelPicPower->setStyleSheet(QStringLiteral("border-image: url(:/img/UI/images/SELEX SBS icon/Group 408.png);"));
        labelCountDowTimeout = new QLabel(centralwidget);
        labelCountDowTimeout->setObjectName(QStringLiteral("labelCountDowTimeout"));
        labelCountDowTimeout->setGeometry(QRect(520, 1217, 281, 31));
        QFont font7;
        font7.setFamily(QStringLiteral("UTM BryantLG"));
        font7.setPointSize(15);
        font7.setBold(true);
        font7.setWeight(75);
        labelCountDowTimeout->setFont(font7);
        labelCountDowTimeout->setStyleSheet(QStringLiteral("color: rgb(15, 45, 208);"));
        BPView->setCentralWidget(centralwidget);
        labelPicPower->raise();
        layoutWidget->raise();
        verticalLayoutWidget->raise();
        labelSOC->raise();
        labelCabinNum->raise();
        timeoutBar->raise();
        labelCountDowTimeout->raise();

        retranslateUi(BPView);

        QMetaObject::connectSlotsByName(BPView);
    } // setupUi

    void retranslateUi(QMainWindow *BPView)
    {
        BPView->setWindowTitle(QApplication::translate("BPView", "MainWindow", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        BPView->setToolTip(QApplication::translate("BPView", "<html><head/><body><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btnSwap->setText(QString());
        btnCancel->setText(QString());
        labelSerialnumber->setText(QApplication::translate("BPView", "S\341\273\221 Seri", Q_NULLPTR));
        lblBatSN->setText(QApplication::translate("BPView", "BP-125487", Q_NULLPTR));
        labelTemp->setText(QApplication::translate("BPView", "Nhi\341\273\207t \304\221\341\273\231 pin", Q_NULLPTR));
        lblSOH->setText(QApplication::translate("BPView", "90%", Q_NULLPTR));
        lblTemp->setText(QApplication::translate("BPView", "30\302\260C", Q_NULLPTR));
        labelSOH->setText(QApplication::translate("BPView", "\304\220\341\273\231 b\341\273\201n pin", Q_NULLPTR));
        labelT->setText(QApplication::translate("BPView", "Chu k\341\273\263 n\341\272\241p x\341\272\243 c\303\262n l\341\272\241i", Q_NULLPTR));
        lblCycles->setText(QApplication::translate("BPView", "200", Q_NULLPTR));
        labelSOC->setText(QApplication::translate("BPView", "20%", Q_NULLPTR));
        labelCabinNum->setText(QApplication::translate("BPView", "9", Q_NULLPTR));
        labelPicPower->setText(QString());
        labelCountDowTimeout->setText(QApplication::translate("BPView", "Th\341\273\235i gian c\303\262n l\341\272\241i:20gi\303\242y", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BPView: public Ui_BPView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BPVIEW_H
