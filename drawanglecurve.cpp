#include "drawanglecurve.h"
#include "ui_drawanglecurve.h"
#include"globalvars.h"
#include<QDebug>
DrawAngleCurve::DrawAngleCurve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawAngleCurve)
{
    ui->setupUi(this);
    ui->plot->setContextMenuPolicy(Qt::CustomContextMenu);//自定义菜单
    this->setWindowTitle("关节角度曲线图");
    setGeometry(400,250,1200,800);
    ui->horizontalScrollBar->setRange(0, 12000);
    ui->verticalScrollBar->setRange(-1800,1800);
    ui->plot->setAutoFillBackground(true);
    connect(ui->plot,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenuRequest(QPoint)));
    connect(ui->plot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
    connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));
    connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
    connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));

    //图例设置
    ui->plot->legend->setVisible(true);
    ui->plot->legend->setFont(QFont("Microsoft YaHei",9));
    ui->plot->legend->setBrush(QColor(255,255,255,0));//图例背景透明
    ui->plot->legend->setBorderPen(Qt::NoPen);//图例边框隐藏
    ui->plot->legend->setSelectableParts(QCPLegend::spItems);
    ui->plot->plotLayout()->setRowStretchFactor(1,0.001);
    ui->plot->legend->setRowSpacing(-3);
    ui->plot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignRight|Qt::AlignTop);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);//缩放
    //坐标轴设置
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->plot->xAxis->setTicker(timeTicker);
    ui->plot->yAxis->setRange(-180, 180, Qt::AlignCenter);
    ui->plot->axisRect()->setupFullAxesBox();//矩形盒区域样式
    ui->plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->plot->xAxis->setLabelFont(QFont("Microsoft YaHei", 9));
    ui->plot->yAxis->setLabelFont(QFont("Microsoft YaHei", 9));
    ui->plot->yAxis->setLabel("角 度 /°");
    ui->plot->xAxis->setLabel("time/s");
    ui->plot->yAxis->ticker()->setTickCount(15);//15个主刻度
    ui->plot->yAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability);//可读性优于设置

    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(Qt::red));
    ui->plot->graph(0)->setAntialiasedFill(true);//设置抗锯齿
    ui->plot->graph(0)->setName("Theta 1");

    ui->plot->addGraph();
    ui->plot->graph(1)->setPen(QPen(Qt::darkYellow));
    ui->plot->graph(1)->setAntialiasedFill(true);
    ui->plot->graph(1)->setName("Theta 2");

    ui->plot->addGraph();
    ui->plot->graph(2)->setPen(QPen(Qt::black));
    ui->plot->graph(2)->setAntialiasedFill(true);
    ui->plot->graph(2)->setName("Theta 3");

    ui->plot->addGraph();
    ui->plot->graph(3)->setPen(QPen(Qt::green));
    ui->plot->graph(3)->setAntialiasedFill(true);
    ui->plot->graph(3)->setName("Theta 4");

    ui->plot->addGraph();
    ui->plot->graph(4)->setName("Theta 5");
    ui->plot->graph(4)->setPen(QPen(Qt::blue));
    ui->plot->graph(4)->setAntialiasedFill(true);

    ui->plot->addGraph();
    ui->plot->graph(5)->setPen(QPen(Qt::cyan));
    ui->plot->graph(5)->setAntialiasedFill(true);
    ui->plot->graph(5)->setName("Theta 6");

//    ui->plot->addGraph();
//    ui->plot->graph(6)->setPen(QPen(Qt::magenta));
//    ui->plot->graph(6)->setAntialiasedFill(true);
//    ui->plot->graph(6)->setName("Theta 7");
    connect(&dataTimer,SIGNAL(timeout()),this,SLOT(realtimeDataSlot()));

}

DrawAngleCurve::~DrawAngleCurve()
{
    delete ui;
}

void DrawAngleCurve::realtimeDataSlot()
{

    static QTime timeStart = QTime::currentTime();
    // calculate two new data points:
    double key = timeStart.msecsTo(QTime::currentTime())/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.001) // at most add point every 1ms
    {
      // add data to lines:
      ui->plot->graph(0)->addData(key, angleOutput[1]);
      ui->plot->graph(1)->addData(key, angleOutput[2]);
      ui->plot->graph(2)->addData(key, angleOutput[3]);
      ui->plot->graph(3)->addData(key, angleOutput[4]);
      ui->plot->graph(4)->addData(key, angleOutput[5]);
      ui->plot->graph(5)->addData(key, angleOutput[6]);
      //ui->plot->graph(6)->addData(key, angleOutput[7]);



      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->plot->xAxis->setRange(key, 60, Qt::AlignRight);
    ui->plot->replot();


}

void DrawAngleCurve::contextMenuRequest(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    double legendCounts = ui->plot->legend->selectTest(pos, false);
    double graphCounts = ui->plot->graph()->selectTest(pos,false);

    //图例菜单
    if (( legendCounts >= 0) || ( graphCounts >= 0))
    {
        menu->addAction("显示", this, SLOT(showGraph()));
        menu->addAction("隐藏", this, SLOT(hideGraph()));
    }

    menu->popup(ui->plot->mapToGlobal(pos));

}

void DrawAngleCurve::showGraph()
{
    for (int i=0; i<ui->plot->graphCount(); ++i)
    {
        QCPGraph *graphItem = ui->plot->graph(i);

        if (graphItem->selected())
        {
            graphItem->setVisible(true);
        }
    }
    ui->plot->replot();
}

void DrawAngleCurve::hideGraph()
{
    for (int i=0; i< ui->plot->graphCount(); ++i)
    {
        QCPGraph *graphItem = ui->plot->graph(i);

        if (graphItem->selected())
        {
            graphItem->setVisible(false);
        }
    }
    ui->plot->replot();
}

void DrawAngleCurve::horzScrollBarChanged(int value)
{
    if (qAbs(ui->plot->xAxis->range().center()-value/100.0) > 0.01)
    {
      ui->plot->xAxis->setRange(value/100.0, ui->plot->xAxis->range().size(), Qt::AlignCenter);
      ui->plot->replot();
    }
}

void DrawAngleCurve::vertScrollBarChanged(int value)
{
    if (qAbs(ui->plot->yAxis->range().center()+value/100.0) > 0.01)
    {
      ui->plot->yAxis->setRange(-value/100.0, ui->plot->yAxis->range().size(), Qt::AlignCenter);
      ui->plot->replot();
    }
}

void DrawAngleCurve::xAxisChanged(QCPRange range)
{
    ui->horizontalScrollBar->setValue(qRound(range.center()*100.0));
    ui->horizontalScrollBar->setPageStep(qRound(range.size()*100.0));
}

void DrawAngleCurve::yAxisChanged(QCPRange range)
{
    ui->verticalScrollBar->setValue(qRound(-range.center()*100.0));
    ui->verticalScrollBar->setPageStep(qRound(range.size()*100.0));
}

void DrawAngleCurve::selectionChanged()
{
    // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->plot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            ui->plot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->plot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->plot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->plot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->plot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->plot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            ui->plot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->plot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->plot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->plot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // 将图形的选择与相应图例项的选择同步
    for (int i=0; i<ui->plot->graphCount(); ++i)
    {
        QCPGraph *graph = ui->plot->graph(i);
        QCPPlottableLegendItem *item = ui->plot->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected())
        {
            item->setSelected(true);
            //注意：这句需要Qcustomplot2.0系列版本
            graph->setSelection(QCPDataSelection(graph->data()->dataRange()));

        }
    }


}
