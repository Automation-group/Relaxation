/********************************************************************************
** Form generated from reading UI file 'mainDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDLG_H
#define UI_MAINDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MainDialog
{
public:
    QGridLayout *gridLayout_4;
    QLabel *label_5;
    QLineEdit *leSerialPortName;
    QPushButton *pbOpen;
    QPushButton *pbClose;
    QSpacerItem *horizontalSpacer_8;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pbEnableMotor;
    QPushButton *pbDisableMotor;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QToolButton *tbMoveUp;
    QToolButton *tbMoveDown;
    QCheckBox *cbInvertion;
    QFrame *line;
    QLabel *label_3;
    QSpinBox *sbStepCount;
    QToolButton *tbUp;
    QToolButton *tbDown;
    QSpacerItem *horizontalSpacer_7;
    QToolButton *tbStop;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *lForwardLimit;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lReverseLimit;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_4;
    QLabel *lOverloading;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lOverheat;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QDoubleSpinBox *dsbSpeed;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pbReadSpeed;
    QPushButton *pbWriteSpeed;
    QLabel *label_9;
    QSpinBox *sbCounter;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pbReadCounter;
    QPushButton *pbWriteCounter;

    void setupUi(QDialog *MainDialog)
    {
        if (MainDialog->objectName().isEmpty())
            MainDialog->setObjectName(QString::fromUtf8("MainDialog"));
        MainDialog->resize(594, 379);
        gridLayout_4 = new QGridLayout(MainDialog);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_5 = new QLabel(MainDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 0, 0, 1, 1);

        leSerialPortName = new QLineEdit(MainDialog);
        leSerialPortName->setObjectName(QString::fromUtf8("leSerialPortName"));

        gridLayout_4->addWidget(leSerialPortName, 0, 1, 1, 1);

        pbOpen = new QPushButton(MainDialog);
        pbOpen->setObjectName(QString::fromUtf8("pbOpen"));

        gridLayout_4->addWidget(pbOpen, 0, 2, 1, 1);

        pbClose = new QPushButton(MainDialog);
        pbClose->setObjectName(QString::fromUtf8("pbClose"));
        pbClose->setEnabled(false);

        gridLayout_4->addWidget(pbClose, 0, 3, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(5, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_8, 0, 4, 1, 1);

        groupBox_4 = new QGroupBox(MainDialog);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setEnabled(true);
        verticalLayout_2 = new QVBoxLayout(groupBox_4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pbEnableMotor = new QPushButton(groupBox_4);
        pbEnableMotor->setObjectName(QString::fromUtf8("pbEnableMotor"));

        verticalLayout_2->addWidget(pbEnableMotor);

        pbDisableMotor = new QPushButton(groupBox_4);
        pbDisableMotor->setObjectName(QString::fromUtf8("pbDisableMotor"));

        verticalLayout_2->addWidget(pbDisableMotor);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout_4->addWidget(groupBox_4, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(MainDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setEnabled(true);
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tbMoveUp = new QToolButton(groupBox_2);
        tbMoveUp->setObjectName(QString::fromUtf8("tbMoveUp"));

        gridLayout_3->addWidget(tbMoveUp, 0, 0, 1, 3);

        tbMoveDown = new QToolButton(groupBox_2);
        tbMoveDown->setObjectName(QString::fromUtf8("tbMoveDown"));

        gridLayout_3->addWidget(tbMoveDown, 0, 3, 1, 2);

        cbInvertion = new QCheckBox(groupBox_2);
        cbInvertion->setObjectName(QString::fromUtf8("cbInvertion"));

        gridLayout_3->addWidget(cbInvertion, 1, 0, 1, 5);

        line = new QFrame(groupBox_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 2, 0, 1, 5);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 3, 0, 1, 2);

        sbStepCount = new QSpinBox(groupBox_2);
        sbStepCount->setObjectName(QString::fromUtf8("sbStepCount"));
        sbStepCount->setMinimum(1);
        sbStepCount->setMaximum(999999999);
        sbStepCount->setSingleStep(100);

        gridLayout_3->addWidget(sbStepCount, 3, 2, 1, 3);

        tbUp = new QToolButton(groupBox_2);
        tbUp->setObjectName(QString::fromUtf8("tbUp"));

        gridLayout_3->addWidget(tbUp, 4, 0, 1, 1);

        tbDown = new QToolButton(groupBox_2);
        tbDown->setObjectName(QString::fromUtf8("tbDown"));

        gridLayout_3->addWidget(tbDown, 4, 1, 1, 2);

        horizontalSpacer_7 = new QSpacerItem(53, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_7, 4, 3, 1, 1);

        tbStop = new QToolButton(groupBox_2);
        tbStop->setObjectName(QString::fromUtf8("tbStop"));

        gridLayout_3->addWidget(tbStop, 4, 4, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 1, 1, 1, 2);

        groupBox = new QGroupBox(MainDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setEnabled(true);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(9, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        lForwardLimit = new QLabel(groupBox);
        lForwardLimit->setObjectName(QString::fromUtf8("lForwardLimit"));

        gridLayout->addWidget(lForwardLimit, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(9, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        lReverseLimit = new QLabel(groupBox);
        lReverseLimit->setObjectName(QString::fromUtf8("lReverseLimit"));

        gridLayout->addWidget(lReverseLimit, 1, 2, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(9, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 1, 1, 1);

        lOverloading = new QLabel(groupBox);
        lOverloading->setObjectName(QString::fromUtf8("lOverloading"));

        gridLayout->addWidget(lOverloading, 2, 2, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 3, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(3, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 1, 1, 1);

        lOverheat = new QLabel(groupBox);
        lOverheat->setObjectName(QString::fromUtf8("lOverheat"));

        gridLayout->addWidget(lOverheat, 3, 2, 1, 1);


        gridLayout_4->addWidget(groupBox, 1, 3, 1, 2);

        groupBox_3 = new QGroupBox(MainDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setEnabled(true);
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        dsbSpeed = new QDoubleSpinBox(groupBox_3);
        dsbSpeed->setObjectName(QString::fromUtf8("dsbSpeed"));
        dsbSpeed->setMinimum(8);
        dsbSpeed->setMaximum(32000);
        dsbSpeed->setValue(400);

        gridLayout_2->addWidget(dsbSpeed, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(87, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 2, 1, 1);

        pbReadSpeed = new QPushButton(groupBox_3);
        pbReadSpeed->setObjectName(QString::fromUtf8("pbReadSpeed"));

        gridLayout_2->addWidget(pbReadSpeed, 0, 3, 1, 1);

        pbWriteSpeed = new QPushButton(groupBox_3);
        pbWriteSpeed->setObjectName(QString::fromUtf8("pbWriteSpeed"));

        gridLayout_2->addWidget(pbWriteSpeed, 0, 4, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 1, 0, 1, 1);

        sbCounter = new QSpinBox(groupBox_3);
        sbCounter->setObjectName(QString::fromUtf8("sbCounter"));
        sbCounter->setMinimum(-99999999);
        sbCounter->setMaximum(999999999);
        sbCounter->setSingleStep(10);

        gridLayout_2->addWidget(sbCounter, 1, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(87, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 1, 2, 1, 1);

        pbReadCounter = new QPushButton(groupBox_3);
        pbReadCounter->setObjectName(QString::fromUtf8("pbReadCounter"));

        gridLayout_2->addWidget(pbReadCounter, 1, 3, 1, 1);

        pbWriteCounter = new QPushButton(groupBox_3);
        pbWriteCounter->setObjectName(QString::fromUtf8("pbWriteCounter"));

        gridLayout_2->addWidget(pbWriteCounter, 1, 4, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 2, 0, 1, 5);


        retranslateUi(MainDialog);
        QObject::connect(pbEnableMotor, SIGNAL(clicked(bool)), pbDisableMotor, SLOT(setDisabled(bool)));
        QObject::connect(pbEnableMotor, SIGNAL(clicked(bool)), pbEnableMotor, SLOT(setEnabled(bool)));
        QObject::connect(pbDisableMotor, SIGNAL(clicked(bool)), pbEnableMotor, SLOT(setDisabled(bool)));
        QObject::connect(pbDisableMotor, SIGNAL(clicked(bool)), pbDisableMotor, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(MainDialog);
    } // setupUi

    void retranslateUi(QDialog *MainDialog)
    {
        MainDialog->setWindowTitle(QApplication::translate("MainDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainDialog", "\320\237\320\276\321\201\320\273\320\265\320\264\320\276\320\262\320\260\321\202\320\265\320\273\321\214\320\275\321\213\320\271 \320\277\320\276\321\200\321\202", 0, QApplication::UnicodeUTF8));
        pbOpen->setText(QApplication::translate("MainDialog", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        pbClose->setText(QApplication::translate("MainDialog", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("MainDialog", "\320\250\320\260\320\263\320\276\320\262\321\213\320\271 \320\264\320\262\320\270\320\263\320\260\321\202\320\265\320\273\321\214", 0, QApplication::UnicodeUTF8));
        pbEnableMotor->setText(QApplication::translate("MainDialog", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        pbDisableMotor->setText(QApplication::translate("MainDialog", "\320\222\321\213\320\272\320\273\321\216\321\207\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainDialog", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        tbMoveUp->setText(QApplication::translate("MainDialog", "\320\224\320\262\320\270\320\266\320\265\320\275\320\270\320\265 \320\262\320\262\320\265\321\200\321\205", 0, QApplication::UnicodeUTF8));
        tbMoveDown->setText(QApplication::translate("MainDialog", "\320\224\320\262\320\270\320\266\320\265\320\275\320\270\320\265 \320\262\320\275\320\270\320\267", 0, QApplication::UnicodeUTF8));
        cbInvertion->setText(QApplication::translate("MainDialog", "\320\230\320\275\320\262\320\265\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\275\320\260\320\277\321\200\320\262\320\273\320\265\320\275\320\270\320\265 \n"
" \320\264\320\262\320\270\320\266\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainDialog", "\320\241\320\264\320\265\320\273\320\260\321\202\321\214 \321\210\320\260\320\263\320\276\320\262", 0, QApplication::UnicodeUTF8));
        tbUp->setText(QApplication::translate("MainDialog", "\320\222\320\262\320\265\321\200\321\205", 0, QApplication::UnicodeUTF8));
        tbDown->setText(QApplication::translate("MainDialog", "\320\222\320\275\320\270\320\267", 0, QApplication::UnicodeUTF8));
        tbStop->setText(QApplication::translate("MainDialog", "\320\241\321\202\320\276\320\277", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainDialog", "\320\237\321\200\320\265\320\264\321\203\320\277\321\200\320\265\320\266\320\264\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainDialog", "\320\241\321\200\320\260\320\261\320\276\321\202\320\260\320\273\n"
"\320\262\320\265\321\200\321\205\320\275\320\270\320\271\n"
"\320\272\320\276\320\275\321\206\320\265\320\262\320\270\320\272", 0, QApplication::UnicodeUTF8));
        lForwardLimit->setText(QApplication::translate("MainDialog", "????", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainDialog", "\320\241\321\200\320\260\320\261\320\276\321\202\320\260\320\273\n"
"\320\275\320\270\320\266\320\275\320\270\320\271\n"
"\320\272\320\276\321\206\320\265\320\262\320\270\320\272", 0, QApplication::UnicodeUTF8));
        lReverseLimit->setText(QApplication::translate("MainDialog", "????", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainDialog", "\320\237\320\265\321\200\320\265\320\263\321\200\321\203\320\267", 0, QApplication::UnicodeUTF8));
        lOverloading->setText(QApplication::translate("MainDialog", "????", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainDialog", "\320\237\320\265\321\200\320\265\320\263\321\200\320\265\320\262", 0, QApplication::UnicodeUTF8));
        lOverheat->setText(QApplication::translate("MainDialog", "????", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainDialog", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainDialog", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214 \320\262\321\200\320\260\321\211\320\265\320\275\320\270\321\217 \n"
" \320\264\320\262\320\270\320\263\320\260\321\202\320\265\320\273\321\217", 0, QApplication::UnicodeUTF8));
        dsbSpeed->setSuffix(QApplication::translate("MainDialog", "\321\210\320\260\320\263/\321\201", 0, QApplication::UnicodeUTF8));
        pbReadSpeed->setText(QApplication::translate("MainDialog", "\320\247\320\270\321\202\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        pbWriteSpeed->setText(QApplication::translate("MainDialog", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainDialog", "\320\241\321\207\320\265\321\202\321\207\320\270\320\272 \321\210\320\260\320\263\320\276\320\262", 0, QApplication::UnicodeUTF8));
        sbCounter->setSuffix(QApplication::translate("MainDialog", "\321\210\320\260\320\263", 0, QApplication::UnicodeUTF8));
        pbReadCounter->setText(QApplication::translate("MainDialog", "\320\247\320\270\321\202\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        pbWriteCounter->setText(QApplication::translate("MainDialog", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainDialog: public Ui_MainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDLG_H
