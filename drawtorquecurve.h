#ifndef DRAWTORQUECURVE_H
#define DRAWTORQUECURVE_H
#include"qcustomplot.h"
#include <QWidget>
#include<QTimer>
namespace Ui {
class DrawTorqueCurve;
}

class DrawTorqueCurve : public QWidget
{
    Q_OBJECT

public:
    explicit DrawTorqueCurve(QWidget *parent = 0);
    ~DrawTorqueCurve();

    QTimer dataTimer;
private slots:
    void horzScrollBarChanged(int value);
    void vertScrollBarChanged(int value);
    void xAxisChanged(QCPRange range);
    void yAxisChanged(QCPRange range);
    void selectionChanged();
    void realtimeDataSlot();
    void contextMenuRequest(QPoint pos);// 设置显示/隐藏菜单
    void showGraph();// 选中图例中的项，或者选中曲线时
    void hideGraph();// 被选中的曲线隐藏

private:
    Ui::DrawTorqueCurve *ui;
};

#endif // DRAWTORQUECURVE_H
