/********************************************************************************
** Form generated from reading UI file 'drawtorquecurve.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWTORQUECURVE_H
#define UI_DRAWTORQUECURVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_DrawTorqueCurve
{
public:
    QGridLayout *gridLayout;
    QCustomPlot *plot;
    QScrollBar *verticalScrollBar;
    QScrollBar *horizontalScrollBar;

    void setupUi(QWidget *DrawTorqueCurve)
    {
        if (DrawTorqueCurve->objectName().isEmpty())
            DrawTorqueCurve->setObjectName(QStringLiteral("DrawTorqueCurve"));
        DrawTorqueCurve->resize(400, 300);
        QIcon icon;
        icon.addFile(QStringLiteral(":/ChartPic.png"), QSize(), QIcon::Normal, QIcon::Off);
        DrawTorqueCurve->setWindowIcon(icon);
        gridLayout = new QGridLayout(DrawTorqueCurve);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        plot = new QCustomPlot(DrawTorqueCurve);
        plot->setObjectName(QStringLiteral("plot"));

        gridLayout->addWidget(plot, 0, 0, 1, 1);

        verticalScrollBar = new QScrollBar(DrawTorqueCurve);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setOrientation(Qt::Vertical);

        gridLayout->addWidget(verticalScrollBar, 0, 1, 1, 1);

        horizontalScrollBar = new QScrollBar(DrawTorqueCurve);
        horizontalScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
        horizontalScrollBar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalScrollBar, 1, 0, 1, 1);


        retranslateUi(DrawTorqueCurve);

        QMetaObject::connectSlotsByName(DrawTorqueCurve);
    } // setupUi

    void retranslateUi(QWidget *DrawTorqueCurve)
    {
        DrawTorqueCurve->setWindowTitle(QApplication::translate("DrawTorqueCurve", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DrawTorqueCurve: public Ui_DrawTorqueCurve {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWTORQUECURVE_H
