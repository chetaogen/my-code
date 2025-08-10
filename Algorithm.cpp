#include "Algorithm.h"
#include "math.h"
#include <Eigen/Core>
#include <cmath>
#include <string.h>
#include<QDebug>
#include"globalvars.h"
using namespace std;

const double d[6+1] = {0,0.1336, 0, 0, 0, 0.026, 0.113}; //两杆x轴之间的距离。为了和DH公式的下标对应，0不用，d[1]-d[7]可用
const double a[6] = {0, 0.054, 0.364, 0.204,0.042, 0}; //杆i长度，对应杆两端z轴之间的距离
const double alpha[6] = {0, -90*PI/180, 0, 0, 90*PI/180,90*PI/180}; //杆的扭角，对应杆两端z轴之间的角度，弧度
const double m[6+1] = {0, 1.496, 1.033, 0.430, 0.494, 0.501, 0.301}; //Quality parameters of each part
const double g = 9.81; //Gravitational acceleration





Algorithm::Algorithm()
{

}

void Algorithm::NewtonEulerian(double *angleInput, double *torque_Output)
{
    //qDebug()<<"shuchu";
    double velInput[6+1]{};
    double accInput[6+1]{};
    Eigen::Vector3d vectorZ;
    vectorZ<< 0, 0, 1;
    //The inertia tensor of the center of mass of each component
    Eigen::Matrix3d IC[7];
    IC[0]<<0,0,0,
           0,0,0,
           0,0,0;
    IC[1]<<2448.621, 34.086,  -778.568,
             34.086, 4088.558,   42.996,
            -778.568,   42.996,  2096.246;
       IC[1]=IC[1]*pow(10,-6);

    IC[2]<< 443.98, 21.954,  350.663,
           21.954,19477.045, 2.217  ,
           350.663,  2.217,19634.63;
      IC[2]=IC[2]*pow(10,-6);


    IC[3]<<125.113,    1.784,    52.335,
           1.784, 2423.832,    0.616,
            52.335,   0.616, 2475.719;
      IC[3]=IC[3]*pow(10,-6);

    IC[4]<< 426.046,   215.691,  -20.934,
           215.691,    429.260,  17.124,
             -20.984,   17.124, 708.209;
      IC[4]=IC[4]*pow(10,-6);

    IC[5]<< 659.171,    -0.001,  0.0006,
               -0.001, 410.512, 224.484,
             0.0006 ,224.484,573.010;
      IC[5]=IC[5]*pow(10,-6);

    IC[6]<< 133.157,        0.0,      0.0,
                 0.0,  633.967,      0.0,
                 0.0,        0.0, 196.139;
      IC[6]=IC[6]*pow(10,-6);


    //The coordinates of the center of mass of each part
    Eigen::Vector3d PC[7];
    PC[0]<<0, 0, 0;
        PC[0]=PC[0]*pow(10,-3);
    PC[1]<<44.282, -2.259,-11.798;
        PC[1]=PC[1]*pow(10,-3);

    PC[2]<<254.905,-0.1034,1.5096;
        PC[2]=PC[2]*pow(10,-3);

    PC[3]<<133.772, -0.0837, -6.3563;
        PC[3]=PC[3]*pow(10,-3);
    PC[4]<<13.8457,-16.376, 9.8539;
        PC[4]=PC[4]*pow(10,-3);
    PC[5]<<-2.433,44.1713, -44.5111;
        PC[5]=PC[5]*pow(10,-3);
    PC[6]<<0.0, 0.0, -40.812;
        PC[6]=PC[6]*pow(10,-3);

    //joint position vector
        Eigen::Vector3d Pos[8]{};
    for(int i=1;i<=6;i++)
    {
        Pos[i](0,0) = a[i-1];
        Pos[i](1,0) = -sin(alpha[i - 1]) * d[i];
        Pos[i](2,0) = cos(alpha[i - 1]) * d[i];

    }

    //NewtonEulerian Initial conditions
    Eigen::Vector3d w[7];
    w[0]<<0, 0, 0;
    Eigen::Vector3d wd[7];
    wd[0]<<0, 0, 0;
    Eigen::Vector3d vd[7];
    vd[0]<<0, 0, g;
    Eigen::Vector3d vcd[7];

    Eigen::Vector3d jointForce[7];
    Eigen::Vector3d jointTorque[7];


        Eigen::Matrix3d R[7];//两杆之间的变换矩阵,R[0]不用
        for (int i=1;i<=7;i++)
        {
            R[i](0, 0) = cos(angleInput[i]);
            R[i](0, 1) = -sin(angleInput[i]);
            R[i](0, 2) = 0;
            R[i](1, 0) = sin(angleInput[i]) * cos(alpha[i-1]);
            R[i](1, 1) = cos(angleInput[i]) * cos(alpha[i-1]);
            R[i](1, 2) = -sin(alpha[i-1]);
            R[i](2, 0) = sin(angleInput[i]) * sin(alpha[i-1]);
            R[i](2, 1) = cos(angleInput[i]) * sin(alpha[i-1]);
            R[i](2, 2) = cos(alpha[i-1]);

            //NewtonEulerian extrapolate
            w[i] = R[i].inverse()*w[i-1] + velInput[i]*vectorZ;
            wd[i] = R[i].inverse()*wd[i-1] + (R[i].inverse()*w[i-1]).cross(velInput[i]*vectorZ) + accInput[i]*vectorZ;
            vd[i] = R[i].inverse()*wd[i-1] + R[i].inverse()*(wd[i-1].cross(Pos[i]) +wd[i-1]. cross(wd[i-1].cross(Pos[i])) + vd[i-1]);
            vcd[i] = wd[i].cross(PC[i]) + wd[i].cross(wd[i].cross(PC[i])) + vd[i];


            jointForce[i] = m[i]*vcd[i];
            jointTorque[i] = IC[i]*wd[i] + w[i].cross(IC[i]*w[i]);

        }
        R[7]<<1, 0, 0,
              0, 1, 0,
              0, 0, 1;
       // vcd[7] = wd[7].cross(PC[7]) + wd[7].cross(wd[7].cross(PC[7])) + vd[7];

        Eigen::Vector3d endforce[8]{};

        Eigen::Vector3d endtorque[8]{};



        for(int j=6;j>=1;j--)
        {
           endforce[j] = R[j+1]*endforce[j+1] + jointForce[j];
           endtorque[j] = jointTorque[j] + R[j+1]*endtorque[j+1] + PC[j].cross(jointForce[j]) +Pos[j+1].cross(R[j+1]*endforce[j+1]);
           torque_Output[j] = endtorque[j].dot(vectorZ);


        }
        torque_Output[0]=0.0;
       // qDebug()<<"力矩"<<torque_Output[1]<<torque_Output[2]<<torque_Output[3]<<torque_Output[4]<<torque_Output[5]<<torque_Output[6];

    }



double Algorithm::Admittance(double K, double B, double M, double dis_exp, double vel_exp, double acc_exp, double delta_force, double delta_t)
{
//    double vel_pre=0.0;
//    double dis_pre=0.0;
//    double acc_pre = acc_exp + 1/(M) * (-1 * delta_force + B *(vel_exp - vel_pre) + K * (dis_exp - dis_pre));
//    double vel = vel_pre + acc_pre * delta_t;
//    double dis = dis_pre + vel_pre * delta_t;
//    vel_pre = vel;
//    dis_pre = dis;
     double acc_pre=0.0;
     acc_pre =  1/(M) * (1 * delta_force );
     double dis=0.0;
     dis=acc_pre*1;
     qDebug()<<"dis 4:"<<dis<<endl;
     return dis;

}

void Algorithm::kinematics(double *theta_input, Matrix4d *T06_output)
{
    Eigen::Matrix4d T[7];//两杆之间的变换矩阵,T[0]不用
    for (int i = 1; i <= 6; i++)
    {
            T[i](0, 0) = cos(theta_input[i]); //cos(x), x为弧度
            T[i](0, 1) = -sin(theta_input[i]);//sin(x), x为弧度
            T[i](0, 2) = 0;
            T[i](0, 3) = a[i-1];
            T[i](1, 0) = sin(theta_input[i]) * cos(alpha[i - 1]);
            T[i](1, 1) = cos(theta_input[i]) * cos(alpha[i - 1]);
            T[i](1, 2) = -sin(alpha[i - 1]);
            T[i](1, 3) = -sin(alpha[i - 1]) * d[i];
            T[i](2, 0) = sin(theta_input[i]) * sin(alpha[i - 1]);
            T[i](2, 1) = cos(theta_input[i]) * sin(alpha[i - 1]);
            T[i](2, 2) = cos(alpha[i - 1]);
            T[i](2, 3) = cos(alpha[i - 1]) * d[i];
            T[i](3, 0) = 0;
            T[i](3, 1) = 0;
            T[i](3, 2) = 0;
            T[i](3, 3) = 1;
    }
    Eigen::Matrix4d T06 = T[1]*T[2]*T[3]*T[4]*T[5]*T[6]; //T06描述了末端连杆坐标系{6}相对于基坐标系{0}的位姿
  coordinates[0]=T06(0,3)*1000;
  coordinates[1]=T06(1,3)*1000;
  coordinates[2]=T06(2,3)*1000;


}

void Algorithm::inverse_kinematics(Matrix4d *T06_input, double *theta_output)
{
    const double  theta1_max = 180*PI/180;
    const double  theta1_min = -180*PI/180;

      const double  theta2_max = -23.3*PI/180;
      const double  theta2_min = -100.6*PI/180;


      //const double  theta3_max = 80.1*PI/180;
      //const double  theta3_min = 21.4*PI/180;

    const double  theta3_max = 60.0*PI/180;
    const double  theta3_min = 17.0*PI/180;

    const double  theta4_max = 71.5*PI/180;
    const double  theta4_min = -22.9*PI/180;

    const double  theta5_max = 146.4*PI/180;
    const double  theta5_min = 53.0*PI/180;

    const double  theta6_max = 180*PI/180;
    const double  theta6_min = -180*PI/180;

    const double TOLERANCE = 0.001; //由于PI值为约数，三角函数计算也只是约数，定义此变量作为阈值

    double theta[2+1][5+1];//theta[0]和theta[][0]系列不用。两杆之间的角度，对应x轴之间的角度。8组解，每组解七个角，用于逆运动学计算关节角度
//    Eigen::Matrix4d T01;//基座到连杆1的转换矩阵

    Eigen::Matrix4d T06 = *T06_input;
    double nx, ny, nz, ox, oy, oz, ax, ay, az, px, py, pz;
    nx = T06(0, 0); ox = T06(0, 1); ax = T06(0, 2); px = T06(0, 3);
    ny = T06(1, 0); oy = T06(1, 1); ay = T06(1, 2); py = T06(1, 3);
    nz = T06(2, 0); oz = T06(2, 1); az = T06(2, 2); pz = T06(2, 3);
    T06(3, 0) = 0;  T06(3, 1) = 0;  T06(3, 2) = 0;  T06(3, 3) = 1;
////////////////改
    int iteration = 0;
    bool sucess = false; //是否结算处合适的逆解
    //double theta1_error[2]={2*PI , 2*PI};

    std::map<int, double> theta_select;

    double theta2 = 0 ;//作为已知量

step0://calculate theta1;

    double theta1 = atan2(py-d[6]*ay, px-d[6]*ax);
    theta[1][1] = theta1;
    theta[2][1] = theta1;
    theta[3][1] = theta1;
    theta[4][1] = theta1;

step1: //calculate theta5;

    double theta5 = atan2(py-d[7]*ay, px-d[7]*ax);
    theta[1][5] = theta5;
    theta[2][5] = theta5;
    theta[3][5] = theta5;
    theta[4][5] = theta5;
    //std::cout<<"theta1:"<<theta1<<endl;

step2: //calculate theta6;theta6 scope: 53.09°~146.32°;theta6范围在acos求解范围内，因此可得到唯一准确结果
    double theta6 = acos( ax*sin(theta1) - ay*cos(theta1) );
    theta[1][6] = theta6;
    theta[2][6] = theta6;
    theta[3][6] = theta6;
    theta[4][6] = theta6;
    //std::cout<<"theta6:"<<theta6<<endl;

step3: // calculate theta7;theta7 scope: -180°~180°;theta7通过atan2获得,因此可得到唯一准确结果
    double theta7 = atan2( (ox*sin(theta1)-oy*cos(theta1))/sin(theta6) , (ny*cos(theta1)-nx*sin(theta1))/sin(theta6) );

    theta[1][7] = theta7;
    theta[2][7] = theta7;
    theta[3][7] = theta7;
    theta[4][7] = theta7;
    //std::cout<<"theta7:"<<theta7<<endl;


step4: //calculate theta2345;theta2345 scope: -84.79°~188.16°;若theta2345属于180°~197.6°时,等于atan2结果+2*PI

       double theta2345_first = atan2(-az/sin(theta6) , oz*cos(theta7) + nz*sin(theta7));
       double theta2345_second = atan2(-az/sin(theta6) , oz*cos(theta7) + nz*sin(theta7)) + 2*PI;
       //std::cout<<"theta2345_first:"<<theta2345_first<<endl;
       //std::cout<<"theta2345_second:"<<theta2345_second<<endl;

step5: //calculate theta3;theta3 scope: 21.49°~80.08°, theta23 scope: -79.09°~59.71°

       double M = pz - d[1] + a[2]*sin(theta2) + a[5]*sin(theta2345_first) - d[6]*cos(theta2345_first) + d[7]*sin(theta2345_first)*sin(theta6);
       double N = px*cos(theta1) + py*sin(theta1) - a[1] - a[2]*cos(theta2) - a[5]*cos(theta2345_first) - d[6]*sin(theta2345_first) - d[7]*cos(theta2345_first)*sin(theta6);
       double phi = atan2(N/sqrt(M*M + N*N), M/sqrt(M*M + N*N));
       double R = (a[4]*a[4] - M*M - a[3]*a[3] - N*N)/(2*a[3]*sqrt(M*M + N*N)); //因为a[4]<a[3],故恒为负值
//       std::cout<<"m:"<<M<<endl;
//       std::cout<<"n:"<<N<<endl;
//       std::cout<<"R:"<<R<<endl;

       //R_first经判断恒为负值,因此asin(R_first)取值范围-180°-0°,因此theta23值为一下两种情况
       double theta23_first = asin(R) + phi;
       if( R < -1.0 )  theta23_first = asin(-1.0) + phi;
       double theta3_first = theta23_first - theta2;
       theta[1][3] = theta23_first - theta2;
       theta[2][3] = theta23_first - theta2;


       double theta23_second = -PI - asin(R) + phi;
       if( R < -1.0 )  theta23_second = -PI - asin(-1.0) + phi;
       double theta3_second = theta23_second - theta2;
       theta[3][3] = theta23_second - theta2;
       theta[4][3] = theta23_second - theta2;
//       std::cout<<"theta23_first:"<<angle(theta2345_first)<<endl;
//       std::cout<<"theta23_second:"<<angle(theta23_second)<<endl;


step6://calculate theta4;theta4 scope: 17.1°~59.98°,theta234 scope: -61.99°~116.69°;theta234通过atan2获得,因此可得到一准确结果
       double theta234_first = atan2( (M + a[3]*sin(theta23_first))*(-1/a[4]),
                                      (N - a[3]*cos(theta23_first))/a[4]
                                    );
       double theta4_first = theta234_first - theta23_first;
       theta[1][4] = theta4_first;
       theta[2][4] = theta4_first;

       double theta234_second = atan2( (M + a[3]*sin(theta23_second))*(-1/a[4]),
                                       (N - a[3]*cos(theta23_second))/a[4]
                                     );
       double theta4_second = theta234_second -  theta23_second;
       theta[3][4] = theta4_second;
       theta[4][4] = theta4_second;


step7://calculate theta5;theta5 scope: -22.8°~71.47°
       double theta5_first = theta2345_first - theta2 - theta3_first - theta4_first;
       theta[1][5] = theta5_first;

       double theta5_second = theta2345_second - theta2- theta3_first - theta4_first;
       theta[2][5] = theta5_second;

       double theta5_third = theta2345_first - theta2- theta3_second - theta4_second;
       theta[3][5] = theta5_third;

       double theta5_fourth = theta2345_second - theta2- theta3_second - theta4_second;
       theta[4][5] = theta5_fourth;


step8: //判断各个关节角度的范围是否符合要求

       for(int j=1; j<=4; j++)
       {
//           cout<<"theta["<<j<<"][1]="<<angle(theta[j][1])<<endl;
//           cout<<"theta["<<j<<"][2]="<<angle(theta[j][2])<<endl;
//           cout<<"theta["<<j<<"][3]="<<angle(theta[j][3])<<endl;
//           cout<<"theta["<<j<<"][4]="<<angle(theta[j][4])<<endl;
//           cout<<"theta["<<j<<"][5]="<<angle(theta[j][5])<<endl;
//           cout<<"theta["<<j<<"][6]="<<angle(theta[j][6])<<endl;
//           cout<<"theta["<<j<<"][7]="<<angle(theta[j][7])<<endl;
//           cout<<"\n"<<endl;

           // 将角度与关节极限位置比较，避免出现 -1.5e-05 这种约等于0的数，对后面的关节角范围判断产生干扰
           if( abs( theta[j][1] ) <= TOLERANCE/10 )
                 theta[j][1] =0;

           if( abs( theta[j][2] ) <= TOLERANCE/10 )
                 theta[j][2] =0;

           if( abs( theta[j][3] ) <= TOLERANCE/10 )
                 theta[j][3] =0;

           if( abs( theta[j][4] ) <= TOLERANCE/10 )
                 theta[j][4] =0;

           if( abs( theta[j][5] ) <= TOLERANCE/10 )
                 theta[j][5] =0;

           if( abs( theta[j][6] ) <= TOLERANCE/10 )
                 theta[j][6] =0;


           if(
                   theta[j][1]    <=  theta1_max   && theta[j][1] >= theta1_min
                   && theta[j][2] <  theta2_max   && theta[j][2] > theta2_min
                   && theta[j][3] <  theta3_max   && theta[j][3] > theta3_min
                   && theta[j][4] <  theta4_max   && theta[j][4] > theta4_min
                   && theta[j][5] <  theta5_max   && theta[j][5] > theta5_min
                   && theta[j][6] <  theta6_max   && theta[j][6] > theta6_min

              )
           {
               theta_select.insert(pair<int, double>(j, abs( ArmEndDistanceCalculate( theta[j], *T06_input))));
//               double dis = abs( ArmEndDistanceCalculate( theta[j], *T07_input));
//               Eigen::Matrix4d T_end;
//               kinematics(theta[j], &T_end);
//               std::cout<<j<<":"<<dis<<endl;
//               std::cout<<j<<":"<<T_end<<endl;
               sucess = true;
           }
       }

       //if(sucess == false)   goto step0;//如果没有结算出合适的解，返回step0 重新结算
       if( theta_select.size()==0 &&
           theta2 <= theta2_max   &&
           theta2 >= theta2_min )   goto step0;//如果没有结算出合适的解，返回step0 重新结算

step9://输出被选中的关节角度组
       double minValue = theta_select.begin()->second;
       int selectNo = theta_select.begin()->first;
       for(map<int,double>::iterator it = theta_select.begin(); it != theta_select.end(); it++)
       {
           // 选择最优逆解的算法：计算逆解对应的末端位置与期望末端位置的距离，距离最小的那组逆解即为所选
           if(minValue > it->second )
           {
               minValue = it->second;
               selectNo = it->first;
//               std::cout<<"minValue:"<<minValue<<"\n"<<endl;
           }
       }

      for(int i=1; i<=7; i++){
         theta_output[i] = theta[selectNo][i];
      }
      std::cout<<"selectNo:"<<selectNo<<"\n"<<endl;
      theta_select.clear();
}

double Algorithm::ArmEndDistanceCalculate(double *theta_input, Matrix4d T06_input)
{
    Eigen::Matrix4d T06_output;
    kinematics(theta_input, &T06_output);
    return  ( sqrt(  (T06_output(0,3)- T06_input(0,3))*(T06_output(0,3)- T06_input(0,3))
                   + (T06_output(1,3)- T06_input(1,3))*(T06_output(1,3)- T06_input(1,3))
                   + (T06_output(2,3)- T06_input(2,3))*(T06_output(2,3)- T06_input(2,3))
                  )
              );
}



double Algorithm::PID(double Kp, double Ki, double Kd, double MaxLimit, double MinLimit, double currenterror, double lasterror, double preerror, double DesireValue)
{
    double dError,pError,Temp,iError;

    pError= currenterror;//比例项，当前误差 = 期望值 - 当前采样值
    iError= currenterror - lasterror;//积分项, 当前误差 - 上次误差
    dError= currenterror- 2 * lasterror + preerror;//微分项，当前误差 - 2*上次误差 + 上上次误差
    Temp=Kp * pError+ Ki * iError + Kd * dError+DesireValue;//增量式PID

    if(Temp>=MaxLimit)  Temp=MaxLimit;
    else if (Temp<=MinLimit) Temp=MinLimit;

    return Temp;
}



