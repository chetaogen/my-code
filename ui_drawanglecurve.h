/********************************************************************************
** Form generated from reading UI file 'drawanglecurve.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWANGLECURVE_H
#define UI_DRAWANGLECURVE_H

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

class Ui_DrawAngleCurve
{
public:
    QGridLayout *gridLayout;
    QCustomPlot *plot;
    QScrollBar *verticalScrollBar;
    QScrollBar *horizontalScrollBar;

    void setupUi(QWidget *DrawAngleCurve)
    {
        if (DrawAngleCurve->objectName().isEmpty())
            DrawAngleCurve->setObjectName(QStringLiteral("DrawAngleCurve"));
        DrawAngleCurve->resize(400, 300);
        QIcon icon;
        icon.addFile(QStringLiteral(":/curvePic.png"), QSize(), QIcon::Normal, QIcon::Off);
        DrawAngleCurve->setWindowIcon(icon);
        gridLayout = new QGridLayout(DrawAngleCurve);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        plot = new QCustomPlot(DrawAngleCurve);
        plot->setObjectName(QStringLiteral("plot"));

        gridLayout->addWidget(plot, 0, 0, 1, 1);

        verticalScrollBar = new QScrollBar(DrawAngleCurve);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setOrientation(Qt::Vertical);

        gridLayout->addWidget(verticalScrollBar, 0, 1, 1, 1);

        horizontalScrollBar = new QScrollBar(DrawAngleCurve);
        horizontalScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
        horizontalScrollBar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalScrollBar, 1, 0, 1, 1);


        retranslateUi(DrawAngleCurve);

        QMetaObject::connectSlotsByName(DrawAngleCurve);
    } // setupUi

    void retranslateUi(QWidget *DrawAngleCurve)
    {
        DrawAngleCurve->setWindowTitle(QApplication::translate("DrawAngleCurve", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DrawAngleCurve: public Ui_DrawAngleCurve {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWANGLECURVE_H
