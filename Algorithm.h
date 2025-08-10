#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Eigen/Eigen>
#include <cmath>
#include <string.h>
#include"mythread.h"
#include <QDateTime>


using namespace std;
using namespace Eigen;



class Algorithm
{


public:
    void NewtonEulerian(double *angleInput, double *torque_Output);
    double Admittance(double K, double B, double M, double dis_exp, double vel_exp, double acc_exp, double delta_force, double delta_t);
    void kinematics(double *theta_input,Eigen::Matrix4d *T06_output);
    void inverse_kinematics(Eigen::Matrix4d *T06_input, double* theta_output);
    double ArmEndDistanceCalculate(double *theta_input, Eigen::Matrix4d T06_input);
    double PID(double Kp, double Ki, double Kd, double MaxLimit, double MinLimit,double currenterror, double lasterror, double preerror,double DesireValue);

public:
    Algorithm();
};



#endif
