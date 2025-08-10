/********************************************************************************
** Form generated from reading UI file 'usbcan.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USBCAN_H
#define UI_USBCAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_USBCAN
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QComboBox *cmdDeviceIndex;
    QComboBox *cmbDeviceType;
    QComboBox *cmbBaudrate;
    QLabel *label_3;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QDialog *USBCAN)
    {
        if (USBCAN->objectName().isEmpty())
            USBCAN->setObjectName(QStringLiteral("USBCAN"));
        USBCAN->resize(495, 138);
        verticalLayout = new QVBoxLayout(USBCAN);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(USBCAN);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(25, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(24, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 5, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        cmdDeviceIndex = new QComboBox(groupBox);
        cmdDeviceIndex->setObjectName(QStringLiteral("cmdDeviceIndex"));
        cmdDeviceIndex->setContextMenuPolicy(Qt::ActionsContextMenu);

        gridLayout->addWidget(cmdDeviceIndex, 0, 7, 1, 1);

        cmbDeviceType = new QComboBox(groupBox);
        cmbDeviceType->setObjectName(QStringLiteral("cmbDeviceType"));
        cmbDeviceType->setFocusPolicy(Qt::WheelFocus);
        cmbDeviceType->setContextMenuPolicy(Qt::PreventContextMenu);
        cmbDeviceType->setInsertPolicy(QComboBox::InsertAtBottom);
        cmbDeviceType->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout->addWidget(cmbDeviceType, 0, 1, 1, 1);

        cmbBaudrate = new QComboBox(groupBox);
        cmbBaudrate->setObjectName(QStringLiteral("cmbBaudrate"));
        cmbBaudrate->setContextMenuPolicy(Qt::CustomContextMenu);

        gridLayout->addWidget(cmbBaudrate, 0, 4, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 6, 1, 1);


        verticalLayout->addWidget(groupBox);

        widget = new QWidget(USBCAN);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(76, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_3->addWidget(pushButton, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(76, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_3->addWidget(pushButton_2, 0, 3, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(76, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 0, 4, 1, 1);


        verticalLayout->addWidget(widget);


        retranslateUi(USBCAN);
        QObject::connect(pushButton, SIGNAL(clicked()), USBCAN, SLOT(accept()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), USBCAN, SLOT(reject()));

        QMetaObject::connectSlotsByName(USBCAN);
    } // setupUi

    void retranslateUi(QDialog *USBCAN)
    {
        USBCAN->setWindowTitle(QApplication::translate("USBCAN", "CAN\345\217\202\346\225\260\345\210\235\345\247\213\345\214\226", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("USBCAN", "USBCAN-II\345\210\235\345\247\213\345\214\226", Q_NULLPTR));
        label->setText(QApplication::translate("USBCAN", "\350\256\276\345\244\207\347\261\273\345\236\213", Q_NULLPTR));
        label_2->setText(QApplication::translate("USBCAN", "\346\263\242\347\211\271\347\216\207", Q_NULLPTR));
        label_3->setText(QApplication::translate("USBCAN", "CAN\351\200\232\351\201\223", Q_NULLPTR));
        pushButton->setText(QApplication::translate("USBCAN", "OK", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("USBCAN", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class USBCAN: public Ui_USBCAN {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USBCAN_H
