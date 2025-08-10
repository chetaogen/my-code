#ifndef CANSETTING_H
#define CANSETTING_H

#include <QWidget>

namespace Ui {
class CANsetting;
}

class CANsetting : public QWidget
{
    Q_OBJECT

public:
    explicit CANsetting(QWidget *parent = 0);
    ~CANsetting();
    int CANtype;//CAN卡类型
    int index;//索引号
    int baundRate;//波特率
    int devicCOM;//端口号

private slots:
    void on_YesBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::CANsetting *ui;
};

#endif // CANSETTING_H
