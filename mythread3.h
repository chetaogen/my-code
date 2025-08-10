#ifndef MYTHREAD3_H
#define MYTHREAD3_H

#include <QThread>
#include <QTime>
#include <math.h>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include"ControlCAN.h"
#include"Algorithm.h"

class mythread3 : public QThread
{
    Q_OBJECT
public:
    explicit mythread3(QThread *parent = nullptr);
    void stop();
    void AngleReadOrder();
    void AngleDataResove(VCI_CAN_OBJ *ReceiveData_USBCAN);
    void TorqueCalulat_Transmit(double *TransTorque);
    void Torque_Transmit2(int motorID, double TransTorque);
    void TorqueDataResove(VCI_CAN_OBJ *ReceiveData_USBCAN);
    void InitParmeter();
    double ImpedanceCalculate(double Delta_q, double static_Torque, double K, double D,double Limit);
    void Judgment_Continue();
    double useAngle[8];
    double torqueOut[8];
    void getDelta_Q();
    void getMtorque();
    bool button1;
    bool button2;



signals:
   void emitSignal();

protected:
    void run();
    void M_sleep(unsigned int msec);

private:
  volatile bool stopFlag;

public slots:
};

#endif // MYTHREAD3_H
