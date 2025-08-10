//利用PID控制器实现电机轨迹规划（五次项傅里叶级数轨迹）的运行
//运行前需在参数界面对想要控制的电机打开使能
#include "mythread2.h"
#include<QDebug>
#include"globalvars.h"
#include"globalfunction.h"

#include"windows.h"
MyThread2::MyThread2(QThread *parent) : QThread(parent)
{
    stopFlag=false;
    gl_1_MotionPIDStruct.MaxPIDoutput=180;
    gl_1_MotionPIDStruct.MinPIDoutput=-180;

    gl_2_MotionPIDStruct.MaxPIDoutput=150;
    gl_2_MotionPIDStruct.MinPIDoutput=-20;


    gl_3_MotionPIDStruct.MaxPIDoutput=110;
    gl_3_MotionPIDStruct.MinPIDoutput=-80;

    gl_4_MotionPIDStruct.MaxPIDoutput=150;
    gl_4_MotionPIDStruct.MinPIDoutput=-50;

    gl_5_MotionPIDStruct.MaxPIDoutput=180;
    gl_5_MotionPIDStruct.MinPIDoutput=0;

    gl_6_MotionPIDStruct.MaxPIDoutput=180;
    gl_6_MotionPIDStruct.MinPIDoutput=-180;

}

void MyThread2::stop()
{
    stopFlag=true;
}

void MyThread2::AngleReadOrder()
{
    for(int i=0;i<6;i++)
    {
        a_TransmitData_USBCAN[i].Data[0]=0x92;
        for(int j=1;j<8;j++)
        {
            a_TransmitData_USBCAN[i].Data[j]=0x00;
        }
    }
    Array_Transmit_USBCANdevice();


}


void MyThread2::AngleDataResove(VCI_CAN_OBJ *ReceiveData_USBCAN)
{
    VCI_CAN_OBJ RecvData = *ReceiveData_USBCAN;
    float value;
    int data7=RecvData.Data[7];
    double desirevalue;
    switch (RecvData.ID)
    {
    case NO_1_motorID:
        if(data7==0)
        {
            value=RecvData.Data[1]+RecvData.Data[2]*256.0+RecvData.Data[3]*256.0*256.0;
            desirevalue=-value*0.01/7;
        }
        else if(data7 == 255)
        {
            value=(255-RecvData.Data[1])+(255-RecvData.Data[2])*256.0+(255-RecvData.Data[3])*256.0*256.0;
            desirevalue=value*0.01/7;
        }
        angleOutput[1]=desirevalue;
        desirevalue=rad(desirevalue);
        gl_1_MotionPIDStruct.m_SampledData_PID.push_back(desirevalue);
        gl_1_MotionPIDStruct.m_time.push_back(gl_Time.at(0));

        break;

    case NO_2_motorID:
        if(data7==0)
        {
            value=RecvData.Data[1]+RecvData.Data[2]*256.0+RecvData.Data[3]*256.0*256.0;
            desirevalue=-value*0.01/7-146;
        }
        else if(data7 == 255)
        {
            value=(255-RecvData.Data[1])+(255-RecvData.Data[2])*256.0+(255-RecvData.Data[3])*256.0*256.0;
            desirevalue=value*0.01/7-146;
        }
        if(desirevalue<-30 && desirevalue>-160)
        {
            angleOutput[2]=desirevalue;
            desirevalue=rad(desirevalue);
            gl_2_MotionPIDStruct.m_SampledData_PID.push_back(desirevalue);
            gl_2_MotionPIDStruct.m_time.push_back(gl_Time.at(0));


        }
        else
         qDebug()<<"angle2_wrong:"<<desirevalue<<endl;
        break;



    case NO_3_motorID:
        if(data7==0)
        {
            value=RecvData.Data[4]+RecvData.Data[5]*256.0;
            desirevalue=value*0.01;
        }
        else if(data7 == 255)
        {
            value=(255-RecvData.Data[4])+(255-RecvData.Data[5])*256.0;
            desirevalue=-value*0.01;
        }

        if(desirevalue>0 && desirevalue<120)
        {
            angleOutput[3]=desirevalue;
            desirevalue=rad(desirevalue);
            gl_3_MotionPIDStruct.m_SampledData_PID.push_back(desirevalue);
            gl_3_MotionPIDStruct.m_time.push_back(gl_Time.at(0));


        }
        else
         qDebug()<<"angle3_wrong:"<<desirevalue<<endl;
        break;

    case NO_4_motorID:
        if(data7==0)
        {
            value=RecvData.Data[1]+RecvData.Data[2]*256.0;
            desirevalue=-value*0.01;
        }
        else if(data7 == 255)
        {
            value=(255-RecvData.Data[1])+(255-RecvData.Data[2])*256.0;
            desirevalue=value*0.01;
        }
        if(desirevalue<140 && desirevalue>-61)
        {
            angleOutput[4]=desirevalue;
            desirevalue=rad(desirevalue);
            gl_4_MotionPIDStruct.m_SampledData_PID.push_back(desirevalue);
            gl_4_MotionPIDStruct.m_time.push_back(gl_Time.at(0));


        }
        else
         qDebug()<<"angle5_wrong:"<<desirevalue<<endl;
        break;

    case NO_5_motorID:
        if(data7==0)
        {
            value=RecvData.Data[1]+RecvData.Data[2]*256.0;
            desirevalue=-value*0.01;
        }
        else if(data7 == 255)
        {
            value=(255-RecvData.Data[1])+(255-RecvData.Data[2])*256.0;
            desirevalue=value*0.01;
        }
        if(desirevalue<220 && desirevalue>-22)
        {
            angleOutput[5]=desirevalue;
            desirevalue=rad(desirevalue);
            gl_5_MotionPIDStruct.m_SampledData_PID.push_back(desirevalue);
            gl_5_MotionPIDStruct.m_time.push_back(gl_Time.at(0));


        }
        else
         qDebug()<<"angle5_wrong:"<<desirevalue<<endl;
        break;
    case NO_6_motorID:
        if(data7==0)
        {
            value=RecvData.Data[1]+RecvData.Data[2]*256.0;
            desirevalue=value*0.01;
        }
        else if(data7 == 255)
        {
            value=(255-RecvData.Data[1])+(255-RecvData.Data[2])*256.0;
            desirevalue=-value*0.01;
        }
       angleOutput[6]=desirevalue;
       desirevalue=rad(desirevalue);
       gl_6_MotionPIDStruct.m_SampledData_PID.push_back(desirevalue);
       gl_6_MotionPIDStruct.m_time.push_back(gl_Time.at(0));


        break;
    default:
        break;
    }
}

void MyThread2::TorqueDataResove(VCI_CAN_OBJ *ReceiveData_USBCAN)
{
    VCI_CAN_OBJ RecvData = *ReceiveData_USBCAN;
    double value;
    double desirevalue;
    switch (RecvData.ID)
    {
    case NO_1_motorID:
        value=255-RecvData.Data[2]+(255-RecvData.Data[3])*256.0;
        desirevalue=-value*(33.0/2048.0)*1.80;                                  //根据电流换算扭矩
        chart_r_Torque[1]=desirevalue;
        //qDebug()<<"chart_r_Torque[1]:"<<chart_r_Torque[1]<<endl;
        break;

    case NO_2_motorID:
        value=RecvData.Data[2]+RecvData.Data[3]*256.0;
        desirevalue=value*(33.0/2048.0)*1.80;
         chart_r_Torque[2]=desirevalue;
         // qDebug()<<"chart_r_Torque[2]:"<<chart_r_Torque[2]<<endl;
        break;

    case NO_3_motorID:
        value=255-RecvData.Data[2]+(255-RecvData.Data[3])*256.0;
        desirevalue=value/100*0.86;
         chart_r_Torque[3]=desirevalue;
          //qDebug()<<"chart_r_Torque[4]:"<<chart_r_Torque[4]<<endl;
        break;
    case NO_4_motorID:
        value=RecvData.Data[2]+RecvData.Data[3]*256.0;
        desirevalue=value*(24.0/2000.0);
         chart_r_Torque[4]=desirevalue;
        // qDebug()<<"chart_r_Torque[5]:"<<chart_r_Torque[5]<<endl;
        break;
    case NO_5_motorID:
        if( angleOutput[5]<69)
        {
           value=RecvData.Data[2]+RecvData.Data[3]*256.0;
        }
        if(angleOutput[5]>105)
        {
            value=255-RecvData.Data[2]+(255-RecvData.Data[3])*256.0;
        }

        desirevalue=value*(24.0/2000.0);
        chart_r_Torque[5]=desirevalue;
        //qDebug()<<"chart_r_Torque[6]:"<<chart_r_Torque[6]<<endl;
        break;
    case NO_6_motorID:
        if( angleOutput[6]<0)
        {
           value=RecvData.Data[2]+RecvData.Data[3]*256.0;
        }
        else if(angleOutput[6]>0)
        {
            value=255-RecvData.Data[2]+(255-RecvData.Data[3])*256.0;
        }
        desirevalue=value*(24.0/2000.0);
        chart_r_Torque[6]=desirevalue;
       // qDebug()<<"chart_r_Torque[7]:"<<chart_r_Torque[7]<<endl;
        break;
    default:
        break;
    }
}

void MyThread2::CalculateDesiredPosition(VCI_CAN_OBJ *ReceiveData_USBCAN)
{
    //五阶傅里叶级数激励轨迹 q(t)=q0+∑(a_k*sin(k*w*t)+b_k*cos(k*w*t))
    double desiredValue=0.0;
    VCI_CAN_OBJ RecvData = *ReceiveData_USBCAN;
    switch (RecvData.ID)
    {
    case NO_1_motorID:
        if(gl_1_MotionPIDStruct.m_Enable==true)
        {
            desiredValue=gl_1_MotionPIDStruct.m_q0
                 +gl_1_MotionPIDStruct.m_a[0]*sin(gl_1_MotionPIDStruct.m_wf*gl_Time.at(0))+gl_1_MotionPIDStruct.m_b[0]*cos(gl_1_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_1_MotionPIDStruct.m_a[1]*sin(2*gl_1_MotionPIDStruct.m_wf*gl_Time.at(1))+gl_1_MotionPIDStruct.m_b[1]*cos(2*gl_1_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_1_MotionPIDStruct.m_a[2]*sin(3*gl_1_MotionPIDStruct.m_wf*gl_Time.at(2))+gl_1_MotionPIDStruct.m_b[2]*cos(3*gl_1_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_1_MotionPIDStruct.m_a[3]*sin(4*gl_1_MotionPIDStruct.m_wf*gl_Time.at(3))+gl_1_MotionPIDStruct.m_b[3]*cos(4*gl_1_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_1_MotionPIDStruct.m_a[4]*sin(5*gl_1_MotionPIDStruct.m_wf*gl_Time.at(4))+gl_1_MotionPIDStruct.m_b[4]*cos(5*gl_1_MotionPIDStruct.m_wf*gl_Time.at(0));
          gl_1_MotionPIDStruct.m_DesiredData_PID.push_back(desiredValue);

        }


        break;

    case NO_2_motorID:
        if(gl_2_MotionPIDStruct.m_Enable==true)
        {
            desiredValue=gl_2_MotionPIDStruct.m_q0
                 +gl_2_MotionPIDStruct.m_a[0]*sin(gl_2_MotionPIDStruct.m_wf*gl_Time.at(0))+gl_2_MotionPIDStruct.m_b[0]*cos(gl_2_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_2_MotionPIDStruct.m_a[1]*sin(2*gl_2_MotionPIDStruct.m_wf*gl_Time.at(1))+gl_2_MotionPIDStruct.m_b[1]*cos(2*gl_2_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_2_MotionPIDStruct.m_a[2]*sin(3*gl_2_MotionPIDStruct.m_wf*gl_Time.at(2))+gl_2_MotionPIDStruct.m_b[2]*cos(3*gl_2_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_2_MotionPIDStruct.m_a[3]*sin(4*gl_2_MotionPIDStruct.m_wf*gl_Time.at(3))+gl_2_MotionPIDStruct.m_b[3]*cos(4*gl_2_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_2_MotionPIDStruct.m_a[4]*sin(5*gl_2_MotionPIDStruct.m_wf*gl_Time.at(4))+gl_2_MotionPIDStruct.m_b[4]*cos(5*gl_2_MotionPIDStruct.m_wf*gl_Time.at(0));
          gl_2_MotionPIDStruct.m_DesiredData_PID.push_back(desiredValue);

        }

        break;

    case NO_3_motorID:
        if(gl_3_MotionPIDStruct.m_Enable==true)
        {
            desiredValue=gl_3_MotionPIDStruct.m_q0
                 +gl_3_MotionPIDStruct.m_a[0]*sin(gl_3_MotionPIDStruct.m_wf*gl_Time.at(0))+gl_3_MotionPIDStruct.m_b[0]*cos(gl_3_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_3_MotionPIDStruct.m_a[1]*sin(2*gl_3_MotionPIDStruct.m_wf*gl_Time.at(1))+gl_3_MotionPIDStruct.m_b[1]*cos(2*gl_3_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_3_MotionPIDStruct.m_a[2]*sin(3*gl_3_MotionPIDStruct.m_wf*gl_Time.at(2))+gl_3_MotionPIDStruct.m_b[2]*cos(3*gl_3_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_3_MotionPIDStruct.m_a[3]*sin(4*gl_3_MotionPIDStruct.m_wf*gl_Time.at(3))+gl_3_MotionPIDStruct.m_b[3]*cos(4*gl_3_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_3_MotionPIDStruct.m_a[4]*sin(5*gl_3_MotionPIDStruct.m_wf*gl_Time.at(4))+gl_3_MotionPIDStruct.m_b[4]*cos(5*gl_3_MotionPIDStruct.m_wf*gl_Time.at(0));
          gl_3_MotionPIDStruct.m_DesiredData_PID.push_back(desiredValue);

        }


        break;

    case NO_4_motorID:
        if(gl_4_MotionPIDStruct.m_Enable==true)
        {
            desiredValue=gl_4_MotionPIDStruct.m_q0
                 +gl_4_MotionPIDStruct.m_a[0]*sin(  gl_4_MotionPIDStruct.m_wf*gl_Time.at(0))+gl_4_MotionPIDStruct.m_b[0]*cos(  gl_4_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_4_MotionPIDStruct.m_a[1]*sin(2*gl_4_MotionPIDStruct.m_wf*gl_Time.at(1))+gl_4_MotionPIDStruct.m_b[1]*cos(2*gl_4_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_4_MotionPIDStruct.m_a[2]*sin(3*gl_4_MotionPIDStruct.m_wf*gl_Time.at(2))+gl_4_MotionPIDStruct.m_b[2]*cos(3*gl_4_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_4_MotionPIDStruct.m_a[3]*sin(4*gl_4_MotionPIDStruct.m_wf*gl_Time.at(3))+gl_4_MotionPIDStruct.m_b[3]*cos(4*gl_4_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_4_MotionPIDStruct.m_a[4]*sin(5*gl_4_MotionPIDStruct.m_wf*gl_Time.at(4))+gl_4_MotionPIDStruct.m_b[4]*cos(5*gl_4_MotionPIDStruct.m_wf*gl_Time.at(0));
          gl_4_MotionPIDStruct.m_DesiredData_PID.push_back(desiredValue);

        }

        break;

    case NO_5_motorID:
        if(gl_5_MotionPIDStruct.m_Enable==true)
        {
            desiredValue=gl_5_MotionPIDStruct.m_q0
                 +gl_5_MotionPIDStruct.m_a[0]*sin(  gl_5_MotionPIDStruct.m_wf*gl_Time.at(0))+gl_5_MotionPIDStruct.m_b[0]*cos(  gl_5_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_5_MotionPIDStruct.m_a[1]*sin(2*gl_5_MotionPIDStruct.m_wf*gl_Time.at(1))+gl_5_MotionPIDStruct.m_b[1]*cos(2*gl_5_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_5_MotionPIDStruct.m_a[2]*sin(3*gl_5_MotionPIDStruct.m_wf*gl_Time.at(2))+gl_5_MotionPIDStruct.m_b[2]*cos(3*gl_5_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_5_MotionPIDStruct.m_a[3]*sin(4*gl_5_MotionPIDStruct.m_wf*gl_Time.at(3))+gl_5_MotionPIDStruct.m_b[3]*cos(4*gl_5_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_5_MotionPIDStruct.m_a[4]*sin(5*gl_5_MotionPIDStruct.m_wf*gl_Time.at(4))+gl_5_MotionPIDStruct.m_b[4]*cos(5*gl_5_MotionPIDStruct.m_wf*gl_Time.at(0));
          gl_5_MotionPIDStruct.m_DesiredData_PID.push_back(desiredValue);

        }
        break;

    case NO_6_motorID:
        if(gl_6_MotionPIDStruct.m_Enable==true)
        {
            desiredValue=gl_6_MotionPIDStruct.m_q0
                 +gl_6_MotionPIDStruct.m_a[0]*sin(  gl_6_MotionPIDStruct.m_wf*gl_Time.at(0))+gl_6_MotionPIDStruct.m_b[0]*cos(  gl_6_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_6_MotionPIDStruct.m_a[1]*sin(2*gl_6_MotionPIDStruct.m_wf*gl_Time.at(1))+gl_6_MotionPIDStruct.m_b[1]*cos(2*gl_6_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_6_MotionPIDStruct.m_a[2]*sin(3*gl_6_MotionPIDStruct.m_wf*gl_Time.at(2))+gl_6_MotionPIDStruct.m_b[2]*cos(3*gl_6_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_6_MotionPIDStruct.m_a[3]*sin(4*gl_6_MotionPIDStruct.m_wf*gl_Time.at(3))+gl_6_MotionPIDStruct.m_b[3]*cos(4*gl_6_MotionPIDStruct.m_wf*gl_Time.at(0))
                 +gl_6_MotionPIDStruct.m_a[4]*sin(5*gl_6_MotionPIDStruct.m_wf*gl_Time.at(4))+gl_6_MotionPIDStruct.m_b[4]*cos(5*gl_6_MotionPIDStruct.m_wf*gl_Time.at(0));
          gl_6_MotionPIDStruct.m_DesiredData_PID.push_back(desiredValue);

        }

        break;



    default:
        break;
    }
}


void MyThread2::DataResolveSend(int motorID, double Value)
{
    int  Tao;
    BYTE ControlData4;
    BYTE ControlData5;
    Value=fabs(Value);

    switch (motorID)
    {
    case NO_1_motorID:
        Tao=Value/1.80*(2000.0/32);
        ControlData5=BYTE(Tao>>8);
        ControlData4=BYTE(Tao&(0xFF));
        gl_TransmitData_USBCAN.ID=IDNum[0];
        gl_TransmitData_USBCAN.Data[4]=ControlData4;
        gl_TransmitData_USBCAN.Data[5]=ControlData5;
        Transmit_USBCANdevice();
        break;
    case NO_2_motorID:
        Tao=Value/1.80*(2000.0/32);
        ControlData5=BYTE(Tao>>8);
        ControlData4=BYTE(Tao&(0xFF));
        gl_TransmitData_USBCAN.ID=IDNum[1];
        gl_TransmitData_USBCAN.Data[4]=ControlData4;
        gl_TransmitData_USBCAN.Data[5]=ControlData5;
        Transmit_USBCANdevice();
        break;


    case NO_3_motorID:
        Tao=Value/0.86*100;
        ControlData5=0xFF-BYTE(Tao>>8);
        ControlData4=0XFF-BYTE(Tao&(0xFF));
        gl_TransmitData_USBCAN.ID=IDNum[2];
        gl_TransmitData_USBCAN.Data[4]=ControlData4;
        gl_TransmitData_USBCAN.Data[5]=ControlData5;
        Transmit_USBCANdevice();
        break;
    case NO_4_motorID:
        Tao=Value*(2000.0/24);
        ControlData5=BYTE(Tao>>8);
        ControlData4=BYTE(Tao&(0xFF));
        gl_TransmitData_USBCAN.ID=IDNum[3];
        gl_TransmitData_USBCAN.Data[4]=ControlData4;
        gl_TransmitData_USBCAN.Data[5]=ControlData5;
        Transmit_USBCANdevice();
        break;
    case NO_5_motorID:
        Tao=Value*(2000.0/24);
        if(Tao<0)
        {
            ControlData5=BYTE(Tao>>8);
            ControlData4=BYTE(Tao&(0xFF));
        }
        else if( Tao>0)
        {
            ControlData5=0xFF-BYTE(Tao>>8);
            ControlData4=0XFF-BYTE(Tao&(0xFF));
        }

        gl_TransmitData_USBCAN.ID=IDNum[4];
        gl_TransmitData_USBCAN.Data[4]=ControlData4;
        gl_TransmitData_USBCAN.Data[5]=ControlData5;
        Transmit_USBCANdevice();
        break;
    case NO_6_motorID:
        Tao=Value*(2000.0/24);
        ControlData5=BYTE(Tao>>8);
        ControlData4=BYTE(Tao&(0xFF));
        gl_TransmitData_USBCAN.ID=IDNum[5];
        gl_TransmitData_USBCAN.Data[4]=ControlData4;
        gl_TransmitData_USBCAN.Data[5]=ControlData5;
        Transmit_USBCANdevice();
        break;
    default:
        break;
    }
}



void MyThread2::PIDControlSend()
{
    for(int i=1;i<=6;i++)
    {
        PID_Dynamic[i]=rad(angleOutput[i]);
    }

    if(gl_1_MotionPIDStruct.m_Enable==true)
    {
        if(!gl_1_MotionPIDStruct.m_DesiredData_PID.empty() && !gl_1_MotionPIDStruct.m_SampledData_PID.empty())
        {
            gl_1_MotionPIDStruct.m_curerror=gl_1_MotionPIDStruct.m_DesiredData_PID.back()- gl_1_MotionPIDStruct.m_SampledData_PID.back();
            gl_1_MotionPIDStruct.m_DesiredData_PID.erase(gl_1_MotionPIDStruct.m_DesiredData_PID.begin());
            gl_1_MotionPIDStruct.m_SampledData_PID.erase(gl_1_MotionPIDStruct.m_SampledData_PID.begin());

            gl_1_MotionPIDStruct.m_PIDout=gl_Algorithm.PID(gl_1_MotionPIDStruct.m_Kp,
                                                           gl_1_MotionPIDStruct.m_Ki,
                                                           gl_1_MotionPIDStruct.m_Kd,
                                                           gl_1_MotionPIDStruct.MaxPIDoutput,
                                                           gl_1_MotionPIDStruct.MinPIDoutput,
                                                           gl_1_MotionPIDStruct.m_curerror,
                                                           gl_1_MotionPIDStruct.m_lasterror,
                                                           gl_1_MotionPIDStruct.m_preerror,
                                                           gl_1_MotionPIDStruct.m_SampledData_PID.back()
                                                           );
            gl_1_MotionPIDStruct.m_preerror=gl_1_MotionPIDStruct.m_lasterror;
            gl_1_MotionPIDStruct.m_lasterror=gl_1_MotionPIDStruct.m_curerror;


            PID_Dynamic[1]=gl_1_MotionPIDStruct.m_PIDout;
            gl_Algorithm.NewtonEulerian(PID_Dynamic,PID_Torque);//动力学算法，基于角度输出关节力矩
            DataResolveSend(NO_1_motorID,PID_Torque[1]);//电机的力矩控制指令

        }
    }
    else
        { Transmit_USBCANdevice2(NO_1_motorID);}

    if(gl_2_MotionPIDStruct.m_Enable==true)
    {
        if(!gl_2_MotionPIDStruct.m_DesiredData_PID.empty() && !gl_2_MotionPIDStruct.m_SampledData_PID.empty())
        {
            gl_2_MotionPIDStruct.m_curerror=gl_2_MotionPIDStruct.m_DesiredData_PID.back()- gl_2_MotionPIDStruct.m_SampledData_PID.back();
            gl_2_MotionPIDStruct.m_DesiredData_PID.erase(gl_2_MotionPIDStruct.m_DesiredData_PID.begin());
            gl_2_MotionPIDStruct.m_SampledData_PID.erase(gl_2_MotionPIDStruct.m_SampledData_PID.begin());

            gl_2_MotionPIDStruct.m_PIDout=gl_Algorithm.PID(gl_2_MotionPIDStruct.m_Kp,
                                                           gl_2_MotionPIDStruct.m_Ki,
                                                           gl_2_MotionPIDStruct.m_Kd,
                                                           gl_2_MotionPIDStruct.MaxPIDoutput,
                                                           gl_2_MotionPIDStruct.MinPIDoutput,
                                                           gl_2_MotionPIDStruct.m_curerror,
                                                           gl_2_MotionPIDStruct.m_lasterror,
                                                           gl_2_MotionPIDStruct.m_preerror,
                                                           gl_2_MotionPIDStruct.m_SampledData_PID.back());
            gl_2_MotionPIDStruct.m_preerror=gl_2_MotionPIDStruct.m_lasterror;
            gl_2_MotionPIDStruct.m_lasterror=gl_2_MotionPIDStruct.m_curerror;

            PID_Dynamic[2]=gl_2_MotionPIDStruct.m_PIDout;
            gl_Algorithm.NewtonEulerian(PID_Dynamic,PID_Torque);
            DataResolveSend(NO_1_motorID,PID_Torque[2]);

        }
    }
    else
        { Transmit_USBCANdevice2(NO_2_motorID);}

    if(gl_3_MotionPIDStruct.m_Enable==true)
    {
        if(!gl_3_MotionPIDStruct.m_DesiredData_PID.empty() && !gl_3_MotionPIDStruct.m_SampledData_PID.empty())
        {
            gl_3_MotionPIDStruct.m_curerror=gl_3_MotionPIDStruct.m_DesiredData_PID.back()- gl_3_MotionPIDStruct.m_SampledData_PID.back();
            gl_3_MotionPIDStruct.m_DesiredData_PID.erase(gl_3_MotionPIDStruct.m_DesiredData_PID.begin());
            gl_3_MotionPIDStruct.m_SampledData_PID.erase(gl_3_MotionPIDStruct.m_SampledData_PID.begin());

            gl_3_MotionPIDStruct.m_PIDout=gl_Algorithm.PID(gl_3_MotionPIDStruct.m_Kp,
                                                           gl_3_MotionPIDStruct.m_Ki,
                                                           gl_3_MotionPIDStruct.m_Kd,
                                                           gl_3_MotionPIDStruct.MaxPIDoutput,
                                                           gl_3_MotionPIDStruct.MinPIDoutput,
                                                           gl_3_MotionPIDStruct.m_curerror,
                                                           gl_3_MotionPIDStruct.m_lasterror,
                                                           gl_3_MotionPIDStruct.m_preerror,
                                                           gl_3_MotionPIDStruct.m_SampledData_PID.back());
            gl_3_MotionPIDStruct.m_preerror=gl_3_MotionPIDStruct.m_lasterror;
            gl_3_MotionPIDStruct.m_lasterror=gl_3_MotionPIDStruct.m_curerror;

            PID_Dynamic[3]=gl_3_MotionPIDStruct.m_PIDout;
            gl_Algorithm.NewtonEulerian(PID_Dynamic,PID_Torque);
            DataResolveSend(NO_1_motorID,PID_Torque[3]);

        }

    }

    else
        { Transmit_USBCANdevice2(NO_3_motorID);}

    if(gl_4_MotionPIDStruct.m_Enable==true)
    {
        if(!gl_4_MotionPIDStruct.m_DesiredData_PID.empty() && !gl_4_MotionPIDStruct.m_SampledData_PID.empty())
        {
            gl_4_MotionPIDStruct.m_curerror=gl_4_MotionPIDStruct.m_DesiredData_PID.back()- gl_4_MotionPIDStruct.m_SampledData_PID.back();
            gl_4_MotionPIDStruct.m_DesiredData_PID.erase(gl_4_MotionPIDStruct.m_DesiredData_PID.begin());
            gl_4_MotionPIDStruct.m_SampledData_PID.erase(gl_4_MotionPIDStruct.m_SampledData_PID.begin());

            gl_4_MotionPIDStruct.m_PIDout=gl_Algorithm.PID(gl_4_MotionPIDStruct.m_Kp,
                                                           gl_4_MotionPIDStruct.m_Ki,
                                                           gl_4_MotionPIDStruct.m_Kd,
                                                           gl_4_MotionPIDStruct.MaxPIDoutput,
                                                           gl_4_MotionPIDStruct.MinPIDoutput,
                                                           gl_4_MotionPIDStruct.m_curerror,
                                                           gl_4_MotionPIDStruct.m_lasterror,
                                                           gl_4_MotionPIDStruct.m_preerror,
                                                           gl_4_MotionPIDStruct.m_SampledData_PID.back());
            gl_4_MotionPIDStruct.m_preerror=gl_4_MotionPIDStruct.m_lasterror;
            gl_4_MotionPIDStruct.m_lasterror=gl_4_MotionPIDStruct.m_curerror;

            PID_Dynamic[4]=gl_4_MotionPIDStruct.m_PIDout;
            gl_Algorithm.NewtonEulerian(PID_Dynamic,PID_Torque);
            DataResolveSend(NO_1_motorID,PID_Torque[4]);
            qDebug()<<gl_4_MotionPIDStruct.m_SampledData_PID.back();

        }
    }
    else
        { Transmit_USBCANdevice2(NO_4_motorID);}

    if(gl_5_MotionPIDStruct.m_Enable==true)
    {
        if(!gl_5_MotionPIDStruct.m_DesiredData_PID.empty() && !gl_5_MotionPIDStruct.m_SampledData_PID.empty())
        {
            gl_5_MotionPIDStruct.m_curerror=gl_5_MotionPIDStruct.m_DesiredData_PID.back()- gl_5_MotionPIDStruct.m_SampledData_PID.back();
            gl_5_MotionPIDStruct.m_DesiredData_PID.erase(gl_5_MotionPIDStruct.m_DesiredData_PID.begin());
            gl_5_MotionPIDStruct.m_SampledData_PID.erase(gl_5_MotionPIDStruct.m_SampledData_PID.begin());

            gl_5_MotionPIDStruct.m_PIDout=gl_Algorithm.PID(gl_5_MotionPIDStruct.m_Kp,
                                                           gl_5_MotionPIDStruct.m_Ki,
                                                           gl_5_MotionPIDStruct.m_Kd,
                                                           gl_5_MotionPIDStruct.MaxPIDoutput,
                                                           gl_5_MotionPIDStruct.MinPIDoutput,
                                                           gl_5_MotionPIDStruct.m_curerror,
                                                           gl_5_MotionPIDStruct.m_lasterror,
                                                           gl_5_MotionPIDStruct.m_preerror,
                                                           gl_5_MotionPIDStruct.m_SampledData_PID.back());
            gl_5_MotionPIDStruct.m_preerror=gl_5_MotionPIDStruct.m_lasterror;
            gl_5_MotionPIDStruct.m_lasterror=gl_5_MotionPIDStruct.m_curerror;

            PID_Dynamic[5]=gl_5_MotionPIDStruct.m_PIDout;
            gl_Algorithm.NewtonEulerian(PID_Dynamic,PID_Torque);
            DataResolveSend(NO_1_motorID,PID_Torque[5]);
        }
    }
    else
        { Transmit_USBCANdevice2(NO_5_motorID);}

    if(gl_6_MotionPIDStruct.m_Enable==true)
    {
        if(!gl_6_MotionPIDStruct.m_DesiredData_PID.empty() && !gl_6_MotionPIDStruct.m_SampledData_PID.empty())
        {
            gl_6_MotionPIDStruct.m_curerror=gl_6_MotionPIDStruct.m_DesiredData_PID.back()- gl_6_MotionPIDStruct.m_SampledData_PID.back();
            gl_6_MotionPIDStruct.m_DesiredData_PID.erase(gl_6_MotionPIDStruct.m_DesiredData_PID.begin());
            gl_6_MotionPIDStruct.m_SampledData_PID.erase(gl_6_MotionPIDStruct.m_SampledData_PID.begin());

            gl_6_MotionPIDStruct.m_PIDout=gl_Algorithm.PID(gl_6_MotionPIDStruct.m_Kp,
                                                           gl_6_MotionPIDStruct.m_Ki,
                                                           gl_6_MotionPIDStruct.m_Kd,
                                                           gl_6_MotionPIDStruct.MaxPIDoutput,
                                                           gl_6_MotionPIDStruct.MinPIDoutput,
                                                           gl_6_MotionPIDStruct.m_curerror,
                                                           gl_6_MotionPIDStruct.m_lasterror,
                                                           gl_6_MotionPIDStruct.m_preerror,
                                                           gl_6_MotionPIDStruct.m_SampledData_PID.back());
            gl_6_MotionPIDStruct.m_preerror=gl_6_MotionPIDStruct.m_lasterror;
            gl_6_MotionPIDStruct.m_lasterror=gl_6_MotionPIDStruct.m_curerror;

            PID_Dynamic[6]=gl_6_MotionPIDStruct.m_PIDout;
            gl_Algorithm.NewtonEulerian(PID_Dynamic,PID_Torque);
            DataResolveSend(NO_1_motorID,PID_Torque[6]);
        }
    }
    else
        { Transmit_USBCANdevice2(NO_6_motorID);}




}

void MyThread2::run()
{
    LARGE_INTEGER m_nFreq;
    LARGE_INTEGER m_nBeginTime;
    LARGE_INTEGER m_nEndTime;
    double frequency=50.0;
    double timepast=0.0;

    double tempPosition[12];//临时保存各个关节的期望位移和实际位移，共6个关节，每关节位移包括期望值和实际值
    double tempTime;


    long len=0;

    QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
    QueryPerformanceFrequency(&m_nFreq);

    while(stopFlag==false)
    {
        AngleReadOrder();//角度读取指令
        len = Receive_USBCANdevice();
        if(len!= 0xFFFFFFFF && len>0 )
        {
            QueryPerformanceCounter(&m_nEndTime);
            timepast = (double)(m_nEndTime.QuadPart-m_nBeginTime.QuadPart)/((double)m_nFreq.QuadPart);// s 级别
            gl_Time.push_back(timepast);

            for(int i=0; i<len; i++)
            {
                gl_mutex1.lock();
                gl_mutex2.lock();
                AngleDataResove(&gl_ReceiveData_USBCAN[i]);//解析角度值，获取当前实际位移（角度）
                CalculateDesiredPosition(&gl_ReceiveData_USBCAN[i]);//实时计算期望达到的位移（角度）
                gl_mutex2.unlock();
                gl_mutex1.unlock();

                ClearBuffer_USBCANdevice();//清空缓存帧
                PIDControlSend();//pid控制器，力矩模式

                long len2=0;
                len2 = Receive_USBCANdevice();
                if(len2!= 0xFFFFFFFF && len2>0 )
                {

                    for(int i=0; i<len2; i++)
                    {
                        gl_mutex1.lock();
                        TorqueDataResove(&gl_ReceiveData_USBCAN[i]);
                        gl_mutex1.unlock();
                    }
                }


            }

         gl_Time.erase(gl_Time.begin());
         gl_1_MotionPIDStruct.m_time.clear();
         gl_1_MotionPIDStruct.m_SampledData_PID.clear();
         gl_1_MotionPIDStruct.m_DesiredData_PID.clear();
         gl_2_MotionPIDStruct.m_time.clear();
         gl_2_MotionPIDStruct.m_SampledData_PID.clear();
         gl_2_MotionPIDStruct.m_DesiredData_PID.clear();
         gl_3_MotionPIDStruct.m_time.clear();
         gl_3_MotionPIDStruct.m_SampledData_PID.clear();
         gl_3_MotionPIDStruct.m_DesiredData_PID.clear();
         gl_4_MotionPIDStruct.m_time.clear();
         gl_4_MotionPIDStruct.m_SampledData_PID.clear();
         gl_4_MotionPIDStruct.m_DesiredData_PID.clear();
         gl_5_MotionPIDStruct.m_time.clear();
         gl_5_MotionPIDStruct.m_SampledData_PID.clear();
         gl_5_MotionPIDStruct.m_DesiredData_PID.clear();
         gl_6_MotionPIDStruct.m_time.clear();
         gl_6_MotionPIDStruct.m_SampledData_PID.clear();
         gl_6_MotionPIDStruct.m_DesiredData_PID.clear();


        }

        

    }












}

void MyThread2::M_sleep(unsigned int msec)//定时器
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }


}
