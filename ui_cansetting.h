/********************************************************************************
** Form generated from reading UI file 'cansetting.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANSETTING_H
#define UI_CANSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CANsetting
{
public:
    QGridLayout *gridLayout;
    QPushButton *YesBtn;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QComboBox *index;
    QLabel *label_7;
    QLabel *label_5;
    QComboBox *CanCom;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QComboBox *cantype;
    QLabel *label_6;
    QLabel *label_4;
    QComboBox *baundRate;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line;
    QPushButton *cancelBtn;

    void setupUi(QWidget *CANsetting)
    {
        if (CANsetting->objectName().isEmpty())
            CANsetting->setObjectName(QStringLiteral("CANsetting"));
        CANsetting->resize(511, 272);
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        CANsetting->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/USB Micro B.png"), QSize(), QIcon::Normal, QIcon::Off);
        CANsetting->setWindowIcon(icon);
        CANsetting->setStyleSheet(QString::fromUtf8("QWidget{\n"
" background-color:rgb(243, 245, 255);\n"
"}\n"
"QPushButton{\n"
"        background-color:rgb(245, 245, 184);\n"
"                   border-style:outset;                \n"
"                   border-width:4px;\n"
"                   border-radius:10px;\n"
"                   border-color:rgb(199, 199, 199);    \n"
"                   color:rgba(0,0,0,160);\n"
"	               font: bold 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"                    padding:6px;\n"
"                  \n"
"                   }\n"
"QComboBox{\n"
"background-color:rgba(244,240,233,255);border-color:rgba(0,0,0,255);color: rgba(0, 37, 89,255);border-style:outset ;border-width:1px;border-radius:4px;font:13px \"Times New Roman\";font-style:normal;font-weight: bold;text-decoration:blink;\n"
"\n"
"}\n"
"QPushButton:hover{\n"
"  background-color:rgb(148, 0, 0);             \n"
"                   border-color:rgb(200, 200, 200);    \n"
"                   color:rgb(255, 255, 255);	          \n"
"\n"
"}\n"
""
                        "QPushButton:pressed{\n"
"  background-color:rgb(245, 245, 184);\n"
"                   border-style:inset;                \n"
"                   border-width:4px;\n"
"                   border-radius:10px;\n"
"                   color:rgb(58, 58, 58);      \n"
"\n"
"}\n"
"\n"
""));
        gridLayout = new QGridLayout(CANsetting);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        YesBtn = new QPushButton(CANsetting);
        YesBtn->setObjectName(QStringLiteral("YesBtn"));
        YesBtn->setMinimumSize(QSize(99, 0));

        gridLayout->addWidget(YesBtn, 5, 2, 1, 1);

        label = new QLabel(CANsetting);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(13);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(CANsetting);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        label_3->setFont(font2);

        verticalLayout_2->addWidget(label_3);

        index = new QComboBox(CANsetting);
        index->setObjectName(QStringLiteral("index"));
        index->setMinimumSize(QSize(60, 20));

        verticalLayout_2->addWidget(index);

        label_7 = new QLabel(CANsetting);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_2->addWidget(label_7);

        label_5 = new QLabel(CANsetting);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font2);

        verticalLayout_2->addWidget(label_5);

        CanCom = new QComboBox(CANsetting);
        CanCom->setObjectName(QStringLiteral("CanCom"));
        CanCom->setMinimumSize(QSize(60, 20));

        verticalLayout_2->addWidget(CanCom);


        gridLayout->addLayout(verticalLayout_2, 1, 4, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(CANsetting);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font2);
        label_2->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(label_2);

        cantype = new QComboBox(CANsetting);
        cantype->setObjectName(QStringLiteral("cantype"));
        cantype->setMinimumSize(QSize(99, 20));

        verticalLayout->addWidget(cantype);

        label_6 = new QLabel(CANsetting);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        label_4 = new QLabel(CANsetting);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font2);

        verticalLayout->addWidget(label_4);

        baundRate = new QComboBox(CANsetting);
        baundRate->setObjectName(QStringLiteral("baundRate"));
        baundRate->setMinimumSize(QSize(99, 20));

        verticalLayout->addWidget(baundRate);


        gridLayout->addLayout(verticalLayout, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 5, 1, 1);

        line = new QFrame(CANsetting);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 2, 0, 4, 6);

        cancelBtn = new QPushButton(CANsetting);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(60, 0));

        gridLayout->addWidget(cancelBtn, 5, 4, 1, 1);


        retranslateUi(CANsetting);

        QMetaObject::connectSlotsByName(CANsetting);
    } // setupUi

    void retranslateUi(QWidget *CANsetting)
    {
        CANsetting->setWindowTitle(QApplication::translate("CANsetting", "Form", Q_NULLPTR));
        YesBtn->setText(QApplication::translate("CANsetting", "\347\241\256\345\256\232", Q_NULLPTR));
        label->setText(QApplication::translate("CANsetting", "CAN\345\215\241\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        label_3->setText(QApplication::translate("CANsetting", "\350\256\276\345\244\207\347\264\242\345\274\225", Q_NULLPTR));
        index->clear();
        index->insertItems(0, QStringList()
         << QApplication::translate("CANsetting", "0", Q_NULLPTR)
         << QApplication::translate("CANsetting", "1", Q_NULLPTR)
         << QApplication::translate("CANsetting", "2", Q_NULLPTR)
         << QApplication::translate("CANsetting", "3", Q_NULLPTR)
         << QApplication::translate("CANsetting", "4", Q_NULLPTR)
         << QApplication::translate("CANsetting", "5", Q_NULLPTR)
         << QApplication::translate("CANsetting", "6", Q_NULLPTR)
         << QApplication::translate("CANsetting", "7", Q_NULLPTR)
         << QApplication::translate("CANsetting", "8", Q_NULLPTR)
         << QApplication::translate("CANsetting", "9", Q_NULLPTR)
         << QApplication::translate("CANsetting", "10", Q_NULLPTR)
         << QApplication::translate("CANsetting", "11", Q_NULLPTR)
         << QApplication::translate("CANsetting", "12", Q_NULLPTR)
        );
        index->setCurrentText(QApplication::translate("CANsetting", "0", Q_NULLPTR));
        label_7->setText(QString());
        label_5->setText(QApplication::translate("CANsetting", "\351\200\232\351\201\223\351\200\211\346\213\251", Q_NULLPTR));
        CanCom->clear();
        CanCom->insertItems(0, QStringList()
         << QApplication::translate("CANsetting", "0", Q_NULLPTR)
         << QApplication::translate("CANsetting", "1", Q_NULLPTR)
        );
        label_2->setText(QApplication::translate("CANsetting", "\350\256\276\345\244\207\347\261\273\345\236\213", Q_NULLPTR));
        cantype->clear();
        cantype->insertItems(0, QStringList()
         << QApplication::translate("CANsetting", "USBCAN-II+", Q_NULLPTR)
         << QApplication::translate("CANsetting", "USBCAN-I+", Q_NULLPTR)
         << QApplication::translate("CANsetting", "USBCAN-2A", Q_NULLPTR)
         << QApplication::translate("CANsetting", "USBCAN-2C", Q_NULLPTR)
         << QApplication::translate("CANsetting", "CANalyst-II", Q_NULLPTR)
        );
        label_6->setText(QString());
        label_4->setText(QApplication::translate("CANsetting", "\346\263\242\347\211\271\347\216\207\351\200\211\346\213\251", Q_NULLPTR));
        baundRate->clear();
        baundRate->insertItems(0, QStringList()
         << QApplication::translate("CANsetting", "10Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "20Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "40Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "50Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "80Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "100Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "125Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "200Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "250Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "400Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "500Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "666Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "800Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "1000Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "33.33Kbps", Q_NULLPTR)
         << QApplication::translate("CANsetting", "66.66Kbps", Q_NULLPTR)
        );
        baundRate->setCurrentText(QApplication::translate("CANsetting", "10Kbps", Q_NULLPTR));
        cancelBtn->setText(QApplication::translate("CANsetting", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CANsetting: public Ui_CANsetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANSETTING_H
