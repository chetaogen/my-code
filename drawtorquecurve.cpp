#include "drawtorquecurve.h"
#include "ui_drawtorquecurve.h"
#include"globalvars.h"
#include<QDebug>
#include<QPen>
DrawTorqueCurve::DrawTorqueCurve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawTorqueCurve)
{
    ui->setupUi(this);
    ui->plot->setContextMenuPolicy(Qt::CustomContextMenu);//自定义菜单
    this->setWindowTitle("关节力矩曲线图");
    setGeometry(400,250,1200,800);
    ui->horizontalScrollBar->setRange(0, 12000);
    ui->verticalScrollBar->setRange(-400,400);
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
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    //坐标轴设置
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->plot->xAxis->setTicker(timeTicker);
    ui->plot->yAxis->setRange(-20, 20, Qt::AlignCenter);
    ui->plot->axisRect()->setupFullAxesBox();//矩形盒区域样式
    ui->plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->plot->xAxis->setLabelFont(QFont("Microsoft YaHei", 9));
    ui->plot->yAxis->setLabelFont(QFont("Microsoft YaHei", 9));
    ui->plot->yAxis->setLabel("力 矩 /N·m");
    ui->plot->xAxis->setLabel("time/s");
    ui->plot->yAxis->ticker()->setTickCount(10);//10个主刻度
    ui->plot->yAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability);//可读性优于设置


    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(Qt::red));
    ui->plot->graph(0)->setAntialiasedFill(true);//设置抗锯齿
    ui->plot->graph(0)->setName("e_Torque 1");

    ui->plot->addGraph();
    ui->plot->graph(1)->setPen(QPen(Qt::darkYellow));
    ui->plot->graph(1)->setAntialiasedFill(true);
    ui->plot->graph(1)->setName("e-Torque 2");

    ui->plot->addGraph();
    ui->plot->graph(2)->setPen(QPen(Qt::black));
    ui->plot->graph(2)->setAntialiasedFill(true);
    ui->plot->graph(2)->setName("e_Torque 3");

    ui->plot->addGraph();
    ui->plot->graph(3)->setPen(QPen(Qt::green));
    ui->plot->graph(3)->setAntialiasedFill(true);
    ui->plot->graph(3)->setName("e_Torque 4");

    ui->plot->addGraph();
    ui->plot->graph(4)->setName("e_Torque 5");
    ui->plot->graph(4)->setPen(QPen(Qt::blue));
    ui->plot->graph(4)->setAntialiasedFill(true);

    ui->plot->addGraph();
    ui->plot->graph(5)->setPen(QPen(Qt::cyan));
    ui->plot->graph(5)->setAntialiasedFill(true);
    ui->plot->graph(5)->setName("e_Torque 6");

//    ui->plot->addGraph();
//    ui->plot->graph(6)->setPen(QPen(Qt::magenta));
//    ui->plot->graph(6)->setAntialiasedFill(true);
//    ui->plot->graph(6)->setName("e_Torque 7");

    QPen pen;
    pen.setWidth(1.5);
    ui->plot->addGraph();
    pen.setColor(QColor(255,170,100));
    pen.setStyle(Qt::DashDotDotLine);
    ui->plot->graph(6)->setPen(pen);
    ui->plot->graph(6)->setAntialiasedFill(true);//设置抗锯齿
    ui->plot->graph(6)->setName("r_Torque 1");

    ui->plot->addGraph();
    pen.setColor(QColor(255,215,0));
    pen.setStyle(Qt::DashDotDotLine);
    ui->plot->graph(7)->setPen(pen);
    ui->plot->graph(7)->setAntialiasedFill(true);
    ui->plot->graph(7)->setName("r_Torque 2");

    ui->plot->addGraph();
    pen.setColor(QColor(255,0,255));
    pen.setStyle(Qt::DashDotDotLine);
    ui->plot->graph(8)->setPen(pen);
    ui->plot->graph(8)->setAntialiasedFill(true);
    ui->plot->graph(8)->setName("r_Torque 3");

    ui->plot->addGraph();
    pen.setColor(QColor(34,139,34));
    pen.setStyle(Qt::DashDotDotLine);
    ui->plot->graph(9)->setPen(pen);
    ui->plot->graph(9)->setAntialiasedFill(true);
    ui->plot->graph(9)->setName("r_Torque 4");

    ui->plot->addGraph();
    pen.setColor(QColor(30,144,255));
    pen.setStyle(Qt::DashDotDotLine);
    ui->plot->graph(10)->setPen(pen);
    ui->plot->graph(10)->setName("r_Torque 5");;
    ui->plot->graph(10)->setAntialiasedFill(true);

    ui->plot->addGraph();
    pen.setColor(QColor(0,139,139));
    pen.setStyle(Qt::DashDotDotLine);
    ui->plot->graph(11)->setPen(pen);
    ui->plot->graph(11)->setAntialiasedFill(true);
    ui->plot->graph(11)->setName("r_Torque 6");

//    ui->plot->addGraph();
//    pen.setColor(QColor(186,85,211));
//    pen.setStyle(Qt::DashDotDotLine);
//    ui->plot->graph(13)->setPen(pen);
//    ui->plot->graph(13)->setAntialiasedFill(true);
//    ui->plot->graph(13)->setName("r_Torque 7");


    connect(&dataTimer,SIGNAL(timeout()),this,SLOT(realtimeDataSlot()));
}

DrawTorqueCurve::~DrawTorqueCurve()
{
    delete ui;
}

void DrawTorqueCurve::realtimeDataSlot()
{

    static QTime timeStart = QTime::currentTime();
    // calculate two new data points:
    double key = timeStart.msecsTo(QTime::currentTime())/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.001) // at most add point every 1ms
    {
      // add data to lines:

      ui->plot->graph(0)->addData(key, chart_e_Torque[1]);//理论力矩
      ui->plot->graph(1)->addData(key, chart_e_Torque[2]);
      ui->plot->graph(2)->addData(key, chart_e_Torque[3]);
      ui->plot->graph(3)->addData(key, chart_e_Torque[4]);
      ui->plot->graph(4)->addData(key, chart_e_Torque[5]);
      ui->plot->graph(5)->addData(key, chart_e_Torque[6]);


     // ui->plot->graph(6)->addData(key,  chart_r_Torque[1]);//反馈力矩
     // ui->plot->graph(7)->addData(key,  chart_r_Torque[2]);
     // ui->plot->graph(8)->addData(key,  chart_r_Torque[3]);
     // ui->plot->graph(9)->addData(key, chart_r_Torque[4]);
     // ui->plot->graph(10)->addData(key, chart_r_Torque[5]);
     // ui->plot->graph(11)->addData(key, chart_r_Torque[6]);



      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->plot->xAxis->setRange(key, 60, Qt::AlignRight);
    ui->plot->replot();


}

void DrawTorqueCurve::contextMenuRequest(QPoint pos)
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

void DrawTorqueCurve::showGraph()
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

void DrawTorqueCurve::hideGraph()
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

void DrawTorqueCurve::horzScrollBarChanged(int value)
{
    if (qAbs(ui->plot->xAxis->range().center()-value/100.0) > 0.01)
    {
      ui->plot->xAxis->setRange(value/100.0, ui->plot->xAxis->range().size(), Qt::AlignCenter);
      ui->plot->replot();
    }
}

void DrawTorqueCurve::vertScrollBarChanged(int value)
{
    if (qAbs(ui->plot->yAxis->range().center()+value/100.0) > 0.01)
    {
      ui->plot->yAxis->setRange(-value/100.0, ui->plot->yAxis->range().size(), Qt::AlignCenter);
      ui->plot->replot();
    }
}

void DrawTorqueCurve::xAxisChanged(QCPRange range)
{
    ui->horizontalScrollBar->setValue(qRound(range.center()*100.0));
    ui->horizontalScrollBar->setPageStep(qRound(range.size()*100.0));
}

void DrawTorqueCurve::yAxisChanged(QCPRange range)
{
    ui->verticalScrollBar->setValue(qRound(-range.center()*100.0));
    ui->verticalScrollBar->setPageStep(qRound(range.size()*100.0));
}

void DrawTorqueCurve::selectionChanged()
{
    if (ui->plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->plot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            ui->plot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->plot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->plot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->plot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

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
            graph->setSelection(QCPDataSelection(graph->data()->dataRange()));

        }
    }
}
