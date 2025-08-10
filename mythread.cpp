//实现基于动力学的零力拖动，力矩控制
#include "mythread.h"
#include<QDebug>
#include"ControlCAN.h"
#include<globalvars.h>
#include<QApplication>
#include<globalfunction.h>
MyThread::MyThread(QThread *parent) : QThread(parent)
{
    stopFlag=false;
}

void MyThread::stop()
{
    stopFlag=true;
}

void MyThread::AngleReadOrder()//电机角度读取指令
{

    for(int i=0;i<6;i++)
    {
        a_TransmitData_USBCAN[i].Data[0]=0x92;
        for(int j=1;j<7;j++)
        {
            a_TransmitData_USBCAN[i].Data[j]=0x00;
        }       
    }
    Array_Transmit_USBCANdevice();

    long len=0;
    len = Receive_USBCANdevice();


    if(len!= 0xFFFFFFFF && len>0 )
    {

        for(int i=0; i<len; i++)
        {
            gl_mutex1.lock();
            AngleDataResove(&gl_ReceiveData_USBCAN[i]);
            gl_mutex1.unlock();

        }

    }
    ClearBuffer_USBCANdevice();//清空数据帧

}


void MyThread::AngleDataResove(VCI_CAN_OBJ *ReceiveData_USBCAN)//对角度信息进行解析
{
    VCI_CAN_OBJ RecvData = *ReceiveData_USBCAN;
    double value;
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
        gl_1_zeroDrag.m_ok=true;
        angleOutput[1]=desirevalue;
        //Transmit_to_Slave(IDNum[0],angleOutput[1]);
        qDebug()<<"发送成功:"<<endl;
        break;

    case NO_2_motorID:
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

            angleOutput[2]=desirevalue;
            gl_2_zeroDrag.m_ok=true;
            //Transmit_to_Slave(IDNum[1],angleOutput[2]);

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

            angleOutput[3]=desirevalue;
            gl_3_zeroDrag.m_ok=true;
            //Transmit_to_Slave(IDNum[2],angleOutput[3]);

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

            angleOutput[4]=desirevalue;
            gl_4_zeroDrag.m_ok=true;
            //Transmit_to_Slave(IDNum[3],angleOutput[4]);

        break;

    case NO_5_motorID:
        if(data7==0)
        {
            value=RecvData.Data[1]+RecvData.Data[2]*256.0;
            desirevalue=value*0.01-90;
        }
        else if(data7 == 255)
        {
            value=(255-RecvData.Data[1])+(255-RecvData.Data[2])*256.0;
            desirevalue=-value*0.01-90;
        }

            angleOutput[5]=desirevalue;
            gl_5_zeroDrag.m_ok=true;
            //Transmit_to_Slave(IDNum[4],angleOutput[5]);

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
        gl_6_zeroDrag.m_ok=true;
        //Transmit_to_Slave(IDNum[5],angleOutput[6]);
        break;
    default:
        break;
    }

}


void MyThread::TorqueCalulat_Transmit(double *TransTorque)//电机输出力矩的转换与发送
{

    int  Tao[7]{};
    BYTE ControlData4[7]{};
    BYTE ControlData5[7]{};
    double desiredTorque[7]{};
    for(int i=1;i<=6;i++)
    {
        desiredTorque[i]=abs(TransTorque[i]);
        chart_e_Torque[i]=desiredTorque[i];
        //chart_e_Torque[i]=TransTorque[i];
    }
    desiredTorque[5]=abs(desiredTorque[5]-0.01);

    Tao[1]=desiredTorque[1]/1.80*(2000.0/32);     //将力矩数值转化为控制数值
    Tao[2]=desiredTorque[2]/1.80*(2000.0/32)*1.15;//*1.15+20

    Tao[3]=desiredTorque[3]/0.86*100*1.1;//*(2000.0/32);//*1.2

    Tao[4]=desiredTorque[4]*(2000.0/24)*2.0;//*2.2
    Tao[5]=desiredTorque[5]*(2000.0/24)*30;//*60
    Tao[6]=desiredTorque[6]*(2000.0/24);

     ControlData5[0]=BYTE(Tao[1]>>8);
     ControlData4[0]=BYTE(Tao[1]&(0xFF));

     ControlData5[1]=BYTE(Tao[2]>>8);
     ControlData4[1]=BYTE(Tao[2]&(0xFF));

     ControlData5[2]=0xFF-BYTE(Tao[3]>>8);
     ControlData4[2]=0XFF-BYTE(Tao[3]&(0xFF));

     if(TransTorque[4]<0)
     {
         ControlData5[3]=BYTE(Tao[4]>>8);
         ControlData4[3]=BYTE(Tao[4]&(0xFF));
     }
     else if( TransTorque[4]>0)
     {
            ControlData5[3]=0xFF-BYTE(Tao[4]>>8);
            ControlData4[3]=0XFF-BYTE(Tao[4]&(0xFF));
     }


     if(angleOutput[5]>-90)
    {
        ControlData5[4]=BYTE(Tao[5]>>8);
        ControlData4[4]=BYTE(Tao[5]&(0xFF));
    }
     else if( angleOutput[5]<-90)
    {
        ControlData5[4]=0xFF-BYTE(Tao[5]>>8);
        ControlData4[4]=0XFF-BYTE(Tao[5]&(0xFF));
    }


        ControlData5[5]=BYTE(Tao[6]>>8);
        ControlData4[5]=BYTE(Tao[6]&(0xFF));





    for(int i=0;i<6;i++)
    {

        a_TransmitData_USBCAN[i].Data[0]=0xA1;
        a_TransmitData_USBCAN[i].Data[1]=0x00;
        a_TransmitData_USBCAN[i].Data[2]=0x00;
        a_TransmitData_USBCAN[i].Data[3]=0x00;
        a_TransmitData_USBCAN[i].Data[4]=ControlData4[i];
        a_TransmitData_USBCAN[i].Data[5]=ControlData5[i];
        a_TransmitData_USBCAN[i].Data[6]=0x00;
        a_TransmitData_USBCAN[i].Data[7]=0x00;

    }
    Array_Transmit_USBCANdevice();

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
    ClearBuffer_USBCANdevice();

}

void MyThread::TorqueDataResove(VCI_CAN_OBJ *ReceiveData_USBCAN)//输出力矩的信息解析
{
    VCI_CAN_OBJ RecvData = *ReceiveData_USBCAN;
    double value;
    double desirevalue;
    switch (RecvData.ID)
    {
    case NO_1_motorID:
        if( angleOutput[1]>0)
        {
           value=RecvData.Data[2]+RecvData.Data[3]*256.0;
        }
        else
        {
            value=0;
        }

        //desirevalue=value*(33.0/2048.0)*1.80;                                  //根据电流换算扭矩
        desirevalue=value*(33.0/2048.0);
        chart_r_Torque[1]=desirevalue;
        //qDebug()<<"chart_r_Torque[1]:"<<chart_r_Torque[1]<<endl;
        break;

    case NO_2_motorID:
        value=RecvData.Data[2]+RecvData.Data[3]*256.0;
        //desirevalue=value*(33.0/2048.0)*1.80/1.15;
        desirevalue=value*(33.0/2048.0);
         chart_r_Torque[2]=desirevalue;
         // qDebug()<<"chart_r_Torque[2]:"<<chart_r_Torque[2]<<endl;
        break;

    case NO_3_motorID:
        value=255-RecvData.Data[2]+(255-RecvData.Data[3])*256.0;
        //desirevalue=value/120*0.86;
        desirevalue=value/100;
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
        chart_r_Torque[6]=0;
       // qDebug()<<"chart_r_Torque[7]:"<<chart_r_Torque[7]<<endl;
        break;

    default:
        break;
    }


}

void MyThread::SingleSend(double *TransTorque)//运行指定关节用
{

    int  Tao[7]{};
    BYTE ControlData4[6]{};
    BYTE ControlData5[6]{};
    double desiredTorque[7]{};
    for(int i=1;i<=6;i++)
    {
        desiredTorque[i]=fabs(TransTorque[i]);
        chart_e_Torque[i]=desiredTorque[i];
    }
    Tao[1]=desiredTorque[1]/1.80*(2000.0/32);     //将力矩数值转化为控制数值
    Tao[2]=desiredTorque[2]/1.80*(2000.0/32)*1.15+20;//3.85

    Tao[3]=desiredTorque[3]/0.86*120;//*(2000.0/32);//0.88
    Tao[4]=desiredTorque[4]*(2000.0/24)*2.2;//0.28
    Tao[5]=desiredTorque[5]*(2000.0/24)*60;
    Tao[6]=desiredTorque[6]*(2000.0/24);

    ControlData5[0]=BYTE(Tao[1]>>8);
    ControlData4[0]=BYTE(Tao[1]&(0xFF));
    ControlData5[1]=BYTE(Tao[2]>>8);
    ControlData4[1]=BYTE(Tao[2]&(0xFF));

    ControlData5[2]=0xFF-BYTE(Tao[3]>>8);
    ControlData4[2]=0XFF-BYTE(Tao[3]&(0xFF));
    ControlData5[3]=BYTE(Tao[4]>>8);
    ControlData4[3]=BYTE(Tao[4]&(0xFF));
    if( TransTorque[5]<0)
    {
        ControlData5[4]=BYTE(Tao[5]>>8);
        ControlData4[4]=BYTE(Tao[5]&(0xFF));
    }
    else if( TransTorque[5]>0)
    {
        ControlData5[4]=0xFF-BYTE(Tao[5]>>8);
        ControlData4[4]=0XFF-BYTE(Tao[5]&(0xFF));
    }

        ControlData5[5]=BYTE(Tao[6]>>8);
        ControlData4[5]=BYTE(Tao[6]&(0xFF));

        if(gl_1_MotionPIDStruct.m_Enable==true)
        {
            gl_TransmitData_USBCAN.ID=IDNum[0];
            gl_TransmitData_USBCAN.Data[4]=ControlData4[0];
            gl_TransmitData_USBCAN.Data[5]=ControlData5[0];
            Transmit_USBCANdevice();

        }
        else
        { Transmit_USBCANdevice2(NO_1_motorID);}


        if(gl_2_MotionPIDStruct.m_Enable==true)
        {
            gl_TransmitData_USBCAN.ID=IDNum[1];
            gl_TransmitData_USBCAN.Data[4]=ControlData4[1];
            gl_TransmitData_USBCAN.Data[5]=ControlData5[1];
            Transmit_USBCANdevice();
        }
        else
        { Transmit_USBCANdevice2(NO_2_motorID);}





        if(gl_3_MotionPIDStruct.m_Enable==true)
        {
            gl_TransmitData_USBCAN.ID=IDNum[2];
            gl_TransmitData_USBCAN.Data[4]=ControlData4[2];
            gl_TransmitData_USBCAN.Data[5]=ControlData5[2];
            Transmit_USBCANdevice();
        }
        else
        { Transmit_USBCANdevice2(NO_3_motorID);}



        if(gl_4_MotionPIDStruct.m_Enable==true)
        {
            gl_TransmitData_USBCAN.ID=IDNum[3];
            gl_TransmitData_USBCAN.Data[4]=ControlData4[3];
            gl_TransmitData_USBCAN.Data[5]=ControlData5[3];
            Transmit_USBCANdevice();
        }
        else
        { Transmit_USBCANdevice2(NO_4_motorID);}



        if(gl_5_MotionPIDStruct.m_Enable==true)
        {
            gl_TransmitData_USBCAN.ID=IDNum[4];
            gl_TransmitData_USBCAN.Data[4]=ControlData4[4];
            gl_TransmitData_USBCAN.Data[5]=ControlData5[4];
            Transmit_USBCANdevice();
        }
        else
        { Transmit_USBCANdevice2(NO_5_motorID);}


        if(gl_6_MotionPIDStruct.m_Enable==true)
        {
            gl_TransmitData_USBCAN.ID=IDNum[5];
            gl_TransmitData_USBCAN.Data[4]=ControlData4[5];
            gl_TransmitData_USBCAN.Data[5]=ControlData5[5];
            Transmit_USBCANdevice();
        }
        else
        { Transmit_USBCANdevice2(NO_6_motorID);}



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







void MyThread::run()
{


    while(!stopFlag)
    {
        AngleReadOrder();
        useAngle[0]=0;
        for(int i=1;i<=6;i++)
        {
            useAngle[i]=rad(angleOutput[i]);
        }

        if(gl_1_zeroDrag.m_ok==true && gl_2_zeroDrag.m_ok==true && gl_3_zeroDrag.m_ok==true
                && gl_4_zeroDrag.m_ok==true && gl_5_zeroDrag.m_ok==true && gl_6_zeroDrag.m_ok==true )
        {

            gl_Algorithm.kinematics(useAngle,&gl_T06);//正运动学计算末端位姿
            //gl_Algorithm.inverse_kinematics(&gl_T06,useAngle[2],inverse_calcu_angle);//由末端位姿逆解得到各关节期望角度
            //gl_Algorithm.NewtonEulerian(inverse_calcu_angle,torqueOut);//调用动力学算法，返回要补偿的力矩数值
            gl_Algorithm.NewtonEulerian(useAngle,torqueOut);
            TorqueCalulat_Transmit(torqueOut);
            //SingleSend(torqueOut);//单关节启用
            if(SendFlag==true)
            {
                for(int j=0;j<6;j++)
                {
                    Transmit_to_Slave(IDNum[j],angleOutput[j+1]);
                }
            }


            emit emitSignal();//界面参数显示

        }



    }
    stopFlag=false;
}







