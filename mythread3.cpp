//力矩控制，实现阻抗效果
//点击界面按钮1、2（已绑定键盘左右方向键），实现自由拖动与阻抗效果的切换
#include "mythread3.h"
#include<QDebug>
#include"ControlCAN.h"
#include<globalvars.h>
#include<QApplication>
#include<globalfunction.h>
#include<QTimer>

mythread3::mythread3(QThread *parent) : QThread(parent)
{
    stopFlag=false;
    button1=false;
    button2=false;

}

void mythread3::stop()
{
    stopFlag=true;
}

void mythread3::AngleReadOrder()
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
}



void mythread3::AngleDataResove(VCI_CAN_OBJ *ReceiveData_USBCAN)
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
        gl_1_ImpedanceStruct.m_ok=true;

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
            gl_2_ImpedanceStruct.m_ok=true;
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
            gl_3_ImpedanceStruct.m_ok=true;
            qDebug()<<"angle 3:"<<angleOutput[3];
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
            gl_4_ImpedanceStruct.m_ok=true;
        }
        else
         qDebug()<<"angle4_wrong:"<<desirevalue<<endl;
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
            gl_5_ImpedanceStruct.m_ok=true;
        }
        else
         qDebug()<<"angle6_wrong:"<<desirevalue<<endl;
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
       gl_6_ImpedanceStruct.m_ok=true;
        break;
    default:
        break;
    }
}

void mythread3::TorqueCalulat_Transmit( double *TransTorque)
{
    int  Tao[7]{};
    BYTE ControlData4[6]{};
    BYTE ControlData5[6]{};
    double desiredTorque[7]{};
    for(int i=1;i<=6;i++)
    {
        desiredTorque[i]=fabs(TransTorque[i]);
        chart_e_Torque[i]=desiredTorque[i];
        //chart_e_Torque[i]=TransTorque[i];
    }

    Tao[1]=desiredTorque[1]/1.80*(2000.0/32);     //将力矩数值转化为控制数值
    Tao[2]=desiredTorque[2]/1.80*(2000.0/32);//3.85

    Tao[3]=desiredTorque[3]/0.86*100;//*(2000.0/32);//0.88

    Tao[4]=desiredTorque[4]*(2000.0/24);//0.28
    Tao[5]=desiredTorque[5]*(2000.0/24);
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


}

void mythread3::Torque_Transmit2(int motorID, double TransTorque)
{
        int  Tao;
        BYTE ControlData4;
        BYTE ControlData5;
        switch (motorID)
        {

        case NO_1_motorID:
            Tao=TransTorque/1.80*(2000.0/32);
            ControlData5=BYTE(Tao>>8);
            ControlData4=BYTE(Tao&(0xFF));
            gl_TransmitData_USBCAN.ID=IDNum[0];
            gl_TransmitData_USBCAN.Data[4]=ControlData4;
            gl_TransmitData_USBCAN.Data[5]=ControlData5;
            Transmit_USBCANdevice();
            break;
        case NO_2_motorID:
            Tao=TransTorque/1.80*(2000.0/32);
            ControlData5=BYTE(Tao>>8);
            ControlData4=BYTE(Tao&(0xFF));
            gl_TransmitData_USBCAN.ID=IDNum[1];
            gl_TransmitData_USBCAN.Data[4]=ControlData4;
            gl_TransmitData_USBCAN.Data[5]=ControlData5;
            Transmit_USBCANdevice();
            break;

        case NO_3_motorID:
            Tao=TransTorque/0.86*100;
            ControlData5=0xFF-BYTE(Tao>>8);
            ControlData4=0XFF-BYTE(Tao&(0xFF));
            gl_TransmitData_USBCAN.ID=IDNum[2];
            gl_TransmitData_USBCAN.Data[4]=ControlData4;
            gl_TransmitData_USBCAN.Data[5]=ControlData5;
            Transmit_USBCANdevice();
            break;
        case NO_4_motorID:
            Tao=TransTorque*(2000.0/24);
            ControlData5=BYTE(Tao>>8);
            ControlData4=BYTE(Tao&(0xFF));
            gl_TransmitData_USBCAN.ID=IDNum[3];
            gl_TransmitData_USBCAN.Data[4]=ControlData4;
            gl_TransmitData_USBCAN.Data[5]=ControlData5;
            Transmit_USBCANdevice();
            break;
        case NO_5_motorID:
            Tao=TransTorque*(2000.0/24);
            if( torqueOut[5]<0)
            {
                ControlData5=BYTE(Tao>>8);
                ControlData4=BYTE(Tao&(0xFF));
            }
            else if( torqueOut[5]>0)
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
            //Tao=TransTorque*(2000.0/24);
            Tao=0;
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

void mythread3::TorqueDataResove(VCI_CAN_OBJ *ReceiveData_USBCAN)
{
    VCI_CAN_OBJ RecvData = *ReceiveData_USBCAN;
    double value;
    double desirevalue;
    switch (RecvData.ID)
    {
    case NO_1_motorID: 
        value=255-RecvData.Data[2]+(255-RecvData.Data[3])*256.0;
        desirevalue=-value*(33.0/2048.0)*1.80;                                  //根据电流换算扭矩
        chart_r_Torque[1]=0.0;
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
        chart_r_Torque[6]=0.0;
       // qDebug()<<"chart_r_Torque[7]:"<<chart_r_Torque[7]<<endl;
        break;
    default:
        break;
    }
}

void mythread3::InitParmeter()
{
    gl_1_ImpedanceStruct.m_D=0;
    gl_1_ImpedanceStruct.m_K=0.5;
    gl_1_ImpedanceStruct.m_limit=4;

    gl_2_ImpedanceStruct.m_D=0;
    gl_2_ImpedanceStruct.m_K=0.5;
    gl_2_ImpedanceStruct.m_limit=5;


    gl_3_ImpedanceStruct.m_D=0;
    gl_3_ImpedanceStruct.m_K=0.1;
    gl_3_ImpedanceStruct.m_limit=2;

    gl_4_ImpedanceStruct.m_D=0;
    gl_4_ImpedanceStruct.m_K=0;
    gl_4_ImpedanceStruct.m_limit=0.5;

    gl_5_ImpedanceStruct.m_D=0;
    gl_5_ImpedanceStruct.m_K=0;
    gl_5_ImpedanceStruct.m_limit=0.5;

    gl_6_ImpedanceStruct.m_D=0;
    gl_6_ImpedanceStruct.m_K=0;
    gl_6_ImpedanceStruct.m_limit=0.5;

}

double mythread3::ImpedanceCalculate(double Delta_q, double static_Torque,double K,double D,double Limit)
{
   double MotionOutPut,omega,variation;

   omega=Delta_q/0.5;
   variation=K* Delta_q+D*omega;
   if(variation>Limit)
   {
       variation=Limit;
   }
   if(variation<-Limit)
   {
       variation=-Limit;
   }
   MotionOutPut=static_Torque+variation;
   return MotionOutPut;

}

void mythread3::Judgment_Continue()
{
    if(!gl_1_ImpedanceStruct.m_torque.empty())
    {
       gl_1_ImpedanceStruct.m_putOut=ImpedanceCalculate(gl_1_ImpedanceStruct.m_delta_q,
                                                        *gl_1_ImpedanceStruct.m_torque.begin(),
                                                        gl_1_ImpedanceStruct.m_K,
                                                        gl_1_ImpedanceStruct.m_D,
                                                        gl_1_ImpedanceStruct.m_limit);
       Torque_Transmit2(NO_1_motorID,gl_1_ImpedanceStruct.m_putOut);
       chart_e_Torque[1]=gl_1_ImpedanceStruct.m_putOut;
    }

    if(!gl_2_ImpedanceStruct.m_torque.empty())
    {
       gl_2_ImpedanceStruct.m_putOut=ImpedanceCalculate(gl_2_ImpedanceStruct.m_delta_q,
                                                        *gl_2_ImpedanceStruct.m_torque.begin(),
                                                        gl_2_ImpedanceStruct.m_K,
                                                        gl_2_ImpedanceStruct.m_D,
                                                        gl_2_ImpedanceStruct.m_limit);
       Torque_Transmit2(NO_2_motorID,gl_2_ImpedanceStruct.m_putOut);
       chart_e_Torque[2]=gl_2_ImpedanceStruct.m_putOut;
    }

    if(!gl_3_ImpedanceStruct.m_torque.empty())
    {
       gl_3_ImpedanceStruct.m_putOut=ImpedanceCalculate(gl_3_ImpedanceStruct.m_delta_q,
                                                        *gl_3_ImpedanceStruct.m_torque.begin(),
                                                        gl_3_ImpedanceStruct.m_K,
                                                        gl_3_ImpedanceStruct.m_D,
                                                        gl_3_ImpedanceStruct.m_limit);
       Torque_Transmit2(NO_3_motorID,gl_3_ImpedanceStruct.m_putOut);
       chart_e_Torque[3]=gl_3_ImpedanceStruct.m_putOut;
    }

    if(!gl_4_ImpedanceStruct.m_torque.empty())
    {
       //qDebug()<<"tor_exc_4:"<<*gl_4_ImpedanceStruct.m_torque.begin()<<endl;
       //qDebug()<<"delta_q4:"<<gl_4_ImpedanceStruct.m_delta_q<<endl;
       gl_4_ImpedanceStruct.m_putOut=ImpedanceCalculate(gl_4_ImpedanceStruct.m_delta_q,
                                                        *gl_4_ImpedanceStruct.m_torque.begin(),
                                                        gl_4_ImpedanceStruct.m_K,
                                                        gl_4_ImpedanceStruct.m_D,
                                                        gl_4_ImpedanceStruct.m_limit);
      // qDebug()<<"putout:"<<gl_4_ImpedanceStruct.m_putOut<<endl;
       Torque_Transmit2(NO_4_motorID,gl_4_ImpedanceStruct.m_putOut);
       chart_e_Torque[4]=gl_4_ImpedanceStruct.m_putOut;
    }

    if(!gl_5_ImpedanceStruct.m_torque.empty())
    {
       gl_5_ImpedanceStruct.m_putOut=ImpedanceCalculate(gl_5_ImpedanceStruct.m_delta_q,
                                                        *gl_5_ImpedanceStruct.m_torque.begin(),
                                                        gl_5_ImpedanceStruct.m_K,
                                                        gl_5_ImpedanceStruct.m_D,
                                                        gl_5_ImpedanceStruct.m_limit);
      // Torque_Transmit2(NO_5_motorID,gl_5_ImpedanceStruct.m_putOut);
       Transmit_USBCANdevice2(NO_5_motorID);
       chart_e_Torque[5]=gl_5_ImpedanceStruct.m_putOut;
    }

    if(!gl_6_ImpedanceStruct.m_torque.empty())
    {
       gl_6_ImpedanceStruct.m_putOut=ImpedanceCalculate(gl_6_ImpedanceStruct.m_delta_q,
                                                        *gl_6_ImpedanceStruct.m_torque.begin(),
                                                        gl_6_ImpedanceStruct.m_K,
                                                        gl_6_ImpedanceStruct.m_D,
                                                        gl_6_ImpedanceStruct.m_limit);
       //Torque_Transmit2(NO_6_motorID,gl_6_ImpedanceStruct.m_putOut);
       Transmit_USBCANdevice2(NO_6_motorID);
       chart_e_Torque[6]=gl_6_ImpedanceStruct.m_putOut;
    }

 }

void mythread3::getDelta_Q()
{



    if(!gl_1_ImpedanceStruct.m_q.empty())
    {             
        gl_1_ImpedanceStruct.m_delta_q=angleOutput[1]-*gl_1_ImpedanceStruct.m_q.begin();

    }
    if(!gl_2_ImpedanceStruct.m_q.empty())
    {
        gl_2_ImpedanceStruct.m_delta_q=angleOutput[2]-*gl_2_ImpedanceStruct.m_q.begin();
    }
    if(!gl_3_ImpedanceStruct.m_q.empty())
    {
        gl_3_ImpedanceStruct.m_delta_q=angleOutput[3]-*gl_3_ImpedanceStruct.m_q.begin();
    }
    if(!gl_4_ImpedanceStruct.m_q.empty())
    {
        gl_4_ImpedanceStruct.m_delta_q=angleOutput[4]-*gl_4_ImpedanceStruct.m_q.begin();

    }
    if(!gl_5_ImpedanceStruct.m_q.empty())
    {
        gl_5_ImpedanceStruct.m_delta_q=angleOutput[5]-*gl_5_ImpedanceStruct.m_q.begin();

    }
    if(!gl_6_ImpedanceStruct.m_q.empty())
    {
        gl_6_ImpedanceStruct.m_delta_q=angleOutput[6]-*gl_6_ImpedanceStruct.m_q.begin();
    }

}

void mythread3::getMtorque()
{
    gl_1_ImpedanceStruct.m_torque.push_back(fabs(torqueOut[1]));
    if(gl_1_ImpedanceStruct.m_torque.size()>1)
    {
        gl_1_ImpedanceStruct.m_torque.erase(gl_1_ImpedanceStruct.m_torque.begin());
        gl_1_ImpedanceStruct.m_torque.begin()--;
    }

    gl_2_ImpedanceStruct.m_torque.push_back(fabs(torqueOut[2]));
    if(gl_2_ImpedanceStruct.m_torque.size()>1)
    {
        gl_2_ImpedanceStruct.m_torque.erase(gl_2_ImpedanceStruct.m_torque.begin());
        gl_2_ImpedanceStruct.m_torque.begin()--;
    }

    gl_3_ImpedanceStruct.m_torque.push_back(fabs(torqueOut[3]));
    if(gl_3_ImpedanceStruct.m_torque.size()>1)
    {
        gl_3_ImpedanceStruct.m_torque.erase(gl_3_ImpedanceStruct.m_torque.begin());
        gl_3_ImpedanceStruct.m_torque.begin()--;
    }

    gl_4_ImpedanceStruct.m_torque.push_back(fabs(torqueOut[4]));
    if(gl_4_ImpedanceStruct.m_torque.size()>1)
    {
        gl_4_ImpedanceStruct.m_torque.erase(gl_4_ImpedanceStruct.m_torque.begin());
        gl_4_ImpedanceStruct.m_torque.begin()--;
       // qDebug()<<"tor 4:"<<*gl_4_ImpedanceStruct.m_torque.begin()<<endl;
    }


    gl_5_ImpedanceStruct.m_torque.push_back(fabs(torqueOut[5]));
    if(gl_5_ImpedanceStruct.m_torque.size()>1)
    {
        gl_5_ImpedanceStruct.m_torque.erase(gl_5_ImpedanceStruct.m_torque.begin());
        gl_5_ImpedanceStruct.m_torque.begin()--;
    }

    gl_6_ImpedanceStruct.m_torque.push_back(fabs(torqueOut[6]));
    if(gl_6_ImpedanceStruct.m_torque.size()>1)
    {
        gl_6_ImpedanceStruct.m_torque.erase(gl_6_ImpedanceStruct.m_torque.begin());
        gl_6_ImpedanceStruct.m_torque.begin()--;
    }




    gl_1_ImpedanceStruct.m_q.push_back(angleOutput[1]);
    if(gl_1_ImpedanceStruct.m_q.size()>1)
    {
        gl_1_ImpedanceStruct.m_q.erase(gl_1_ImpedanceStruct.m_q.begin());
        gl_1_ImpedanceStruct.m_q.begin()--;

    }

    gl_2_ImpedanceStruct.m_q.push_back(angleOutput[2]);
    if(gl_2_ImpedanceStruct.m_q.size()>1)
    {
        gl_2_ImpedanceStruct.m_q.erase(gl_2_ImpedanceStruct.m_q.begin());
        gl_2_ImpedanceStruct.m_q.begin()--;
    }

    gl_3_ImpedanceStruct.m_q.push_back(angleOutput[3]);
    if(gl_3_ImpedanceStruct.m_q.size()>1)
    {
        gl_3_ImpedanceStruct.m_q.erase(gl_3_ImpedanceStruct.m_q.begin());
        gl_3_ImpedanceStruct.m_q.begin()--;
    }

    gl_4_ImpedanceStruct.m_q.push_back(angleOutput[4]);
    if(gl_4_ImpedanceStruct.m_q.size()>1)
    {
        gl_4_ImpedanceStruct.m_q.erase(gl_4_ImpedanceStruct.m_q.begin());
        gl_4_ImpedanceStruct.m_q.begin()--;

    }

    gl_5_ImpedanceStruct.m_q.push_back(angleOutput[5]);
    if(gl_5_ImpedanceStruct.m_q.size()>1)
    {
        gl_5_ImpedanceStruct.m_q.erase(gl_5_ImpedanceStruct.m_q.begin());
        gl_5_ImpedanceStruct.m_q.begin()--;

    }

    gl_6_ImpedanceStruct.m_q.push_back(angleOutput[6]);
    if(gl_6_ImpedanceStruct.m_q.size()>1)
    {
        gl_6_ImpedanceStruct.m_q.erase(gl_6_ImpedanceStruct.m_q.begin());
        gl_6_ImpedanceStruct.m_q.begin()--;

    }




}




void mythread3::run()
{

    LARGE_INTEGER m_nFreq;
    LARGE_INTEGER m_nBeginTime;
    LARGE_INTEGER m_nEndTime;
    double frequency=50.0;
    double timepast=0.0;
    QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
    QueryPerformanceFrequency(&m_nFreq);

    //InitParmeter();//初始化各关节阻抗参数
    while(!stopFlag)
    {
        QueryPerformanceCounter(&m_nEndTime);
        timepast = (double)(m_nEndTime.QuadPart-m_nBeginTime.QuadPart)/((double)m_nFreq.QuadPart);// s 级别
        gl_Time.push_back(timepast);
        while(button1==true)
        {
            gl_1_ImpedanceStruct.m_ok=false;
            gl_2_ImpedanceStruct.m_ok=false;
            gl_3_ImpedanceStruct.m_ok=false;
            gl_4_ImpedanceStruct.m_ok=false;
            gl_5_ImpedanceStruct.m_ok=false;
            gl_6_ImpedanceStruct.m_ok=false;

            AngleReadOrder();


            if(gl_1_ImpedanceStruct.m_ok==true && gl_2_ImpedanceStruct.m_ok==true && gl_3_ImpedanceStruct.m_ok==true && gl_4_ImpedanceStruct.m_ok==true
                    && gl_5_ImpedanceStruct.m_ok==true && gl_6_ImpedanceStruct.m_ok==true )
            {

                for(int i=1;i<=6;i++)
                {
                    useAngle[i]=rad(angleOutput[i]);
                }

                //qDebug()<<"按下按钮"<<endl;

                gl_Algorithm.NewtonEulerian(useAngle,torqueOut);//调用动力学算法，返回要补偿的力矩数值
                ClearBuffer_USBCANdevice();
                TorqueCalulat_Transmit(torqueOut);
                getMtorque();
                gl_Algorithm.kinematics(useAngle,&gl_T06);
                emit emitSignal();

            }


        }

/////////////////////////////////////////////////////////////////////////////////////////////////////

        while(button2==true)
        {
            AngleReadOrder();

            for(int i=1;i<=6;i++)
            {
                useAngle[i]=rad(angleOutput[i]);
            }
            gl_Algorithm.kinematics(useAngle,&gl_T06);

            getDelta_Q();

            Judgment_Continue();

            long len3=0;
            len3 = Receive_USBCANdevice();
            if(len3!= 0xFFFFFFFF && len3>0 )
            {

                for(int i=0; i<len3; i++)
                {
                    gl_mutex1.lock();
                    TorqueDataResove(&gl_ReceiveData_USBCAN[i]);
                    gl_mutex1.unlock();
                }

            }
            ClearBuffer_USBCANdevice();
            emit emitSignal();
        }

        Transmit_USBCANdevice2(NO_1_motorID);
        Transmit_USBCANdevice2(NO_2_motorID);
        Transmit_USBCANdevice2(NO_3_motorID);
        Transmit_USBCANdevice2(NO_4_motorID);
        Transmit_USBCANdevice2(NO_5_motorID);
        Transmit_USBCANdevice2(NO_6_motorID);



        gl_Time.erase(gl_Time.begin());

    }
    stopFlag=false;


}

void mythread3::M_sleep(unsigned int msec)
{

    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,500);
    }

}
