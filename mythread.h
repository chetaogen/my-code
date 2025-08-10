#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QObject>
#include <QThread>
#include <QTimer>
#include <math.h>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <QTime>

#include"ControlCAN.h"
#include"Algorithm.h"

///////////////////////////////////////////

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QThread *parent = nullptr);

    void stop();
    void AngleReadOrder();
    void AngleDataResove(VCI_CAN_OBJ *ReceiveData_USBCAN);
    void TorqueCalulat_Transmit(double *TransTorque);
    void TorqueDataResove(VCI_CAN_OBJ *ReceiveData_USBCAN);

    void SingleSend(double *TransTorque);
    double useAngle[7];
    double inverse_calcu_angle[7];
    double torqueOut[7];

protected:
    void run();

private:
  volatile bool stopFlag;

signals:
   void emitSignal();




};

////////////////////////////////////////////////

#endif


