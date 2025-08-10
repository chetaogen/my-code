#ifndef MYTHREAD2_H
#define MYTHREAD2_H
#include<QThread>
#include <QObject>
#include<QtCore>
#include"ControlCAN.h"

class MyThread2 : public QThread
{
    Q_OBJECT
public:
    explicit MyThread2(QThread *parent = nullptr);
    void  stop();
    void AngleReadOrder();
    void AngleDataResove(VCI_CAN_OBJ *ReceiveData_USBCAN);
    void TorqueDataResove(VCI_CAN_OBJ *ReceiveData_USBCAN);
    void CalculateDesiredPosition(VCI_CAN_OBJ *ReceiveData_USBCAN);
    void PIDControlSend();
    void DataResolveSend(int motorID, double Value);

    double PID_Dynamic[8]{};
    double PID_Torque[8]{};





private:
    volatile bool stopFlag; // 线程运行标识
protected:
    void run();
    void M_sleep(unsigned int msec);
signals:
    
public slots:
};

#endif // MYTHREAD2_H
