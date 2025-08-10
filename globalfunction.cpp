#include "globalfunction.h"
#include"globalvars.h"
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
/**********************************************************
 *
 * 这部分为USNB-CAN设备的操作函数
 *
 * ********************************************************/
bool Open_USBCANdevice()
{

    unsigned long dwRel;
   dwRel = VCI_OpenDevice(gl_nDeviceType, gl_nDeviceInd, gl_nReserved);

    if (dwRel != STATUS_OK)
    {
     QMessageBox::critical(0, QObject::tr("打开设备失败!"),
     "打开设备失败!！ ", QMessageBox::Ok);
    return false;
    }
    return true;
}


bool Close_USBCANdevice()
{
    BOOL bRel;

    bRel =  VCI_CloseDevice(gl_nDeviceType, gl_nDeviceInd);
    return bRel;

}


bool Init_USBCANdevice()
{
    VCI_INIT_CONFIG init_config;
    init_config.AccCode = 0x80000008;
    init_config.AccMask =0xFFFFFFFF;//全部接收
    init_config.Filter = 1;
    DWORD dwRel;
    int nCANInd = 0;
    unsigned int gBand = 0x1400;//波特率1000K
    init_config.Timing0 = gBand&0xff;
    init_config.Timing1 = gBand >> 8;
    init_config.Mode = 0;// 0-正常模式，1-只听模式，2-自发自收模式

    dwRel = VCI_InitCAN(gl_nDeviceType, gl_nDeviceInd, gl_nCANInd[0],&init_config);//只初始化通道0

    if (dwRel != STATUS_OK)
    {
        QMessageBox::critical(0, QObject::tr("初始化失败!"),
                              "初始化失败!！ ", QMessageBox::Cancel);
        return false;
    }

    return true;

}
bool Init_USBCANdevice2()
{
    VCI_INIT_CONFIG init_config;
    init_config.AccCode = 0x80000008;
    init_config.AccMask =0xFFFFFFFF;//全部接收
    init_config.Filter = 1;
    DWORD dwRel2;
    int nCANInd = 0;
    unsigned int gBand = 0x1400;//波特率1000K
    init_config.Timing0 = gBand&0xff;
    init_config.Timing1 = gBand >> 8;
    init_config.Mode = 0;// 0-正常模式，1-只听模式，2-自发自收模式

    dwRel2=VCI_InitCAN(gl_nDeviceType, gl_nDeviceInd, gl_nCANInd[1],&init_config);//只初始化通道0
    if (dwRel2 != STATUS_OK)
    {
        QMessageBox::critical(0, QObject::tr("初始化失败!"),
                              "初始化失败!！ ", QMessageBox::Cancel);
            return false;
    }

    return true;

}

bool Start_USBCANdevice()
{
    DWORD dwRel;
    dwRel = VCI_StartCAN(gl_nDeviceType, gl_nDeviceInd, gl_nCANInd[0]);
    if (dwRel == STATUS_ERR)
    {
        QMessageBox::critical(0, QObject::tr("启动设备失败!"),
        "启动设备失败!！ ", QMessageBox::Cancel);
       return false;

    }

    return true;
}


long Receive_USBCANdevice( )
{

  DWORD dwRel;
  VCI_CAN_OBJ vco[100];
  Q_UNUSED(vco);

  gl_mutex.lock();
  dwRel = VCI_Receive(gl_nDeviceType, gl_nDeviceInd, gl_nCANInd[0], gl_ReceiveData_USBCAN, 1000, 0);
  gl_mutex.unlock();

  return dwRel;

}



long  GetReceiveNum_USBCANdevice()
{
    //此函数用以获取指定接收缓冲区中接收到但尚未被读取的帧数量
    return   VCI_GetReceiveNum(gl_nDeviceType, gl_nDeviceInd, gl_nCANInd[0]);

}

bool ClearBuffer_USBCANdevice()
{
    //此函数用以清空指定CAN通道的缓冲区。
    return VCI_ClearBuffer(gl_nDeviceType, gl_nDeviceInd, gl_nCANInd[0]);
}


long  Transmit_USBCANdevice( )
{
    DWORD dwRel;

    gl_TransmitData_USBCAN.SendType= 0; //正常发送
    gl_TransmitData_USBCAN.RemoteFlag= 0; //数据帧
    gl_TransmitData_USBCAN.ExternFlag= 0;//标准帧
    gl_TransmitData_USBCAN.DataLen = 8; //要发送的数据长度
    gl_TransmitData_USBCAN.Data[0]=0XA1;
    gl_TransmitData_USBCAN.Data[1]=0;
    gl_TransmitData_USBCAN.Data[2]=0;
    gl_TransmitData_USBCAN.Data[3]=0;
    gl_TransmitData_USBCAN.Data[6]=0;
    gl_TransmitData_USBCAN.Data[7]=0;

    gl_mutex.lock();
    dwRel =  VCI_Transmit(gl_nDeviceType, gl_nDeviceInd, gl_nCANInd[0], &gl_TransmitData_USBCAN, 1);
    gl_mutex.unlock();
    return dwRel;
}

long  Array_Transmit_USBCANdevice( )
{
    DWORD dwRel;
   for(int i=0;i<7;i++)
   {
    a_TransmitData_USBCAN[i].ID=IDNum[i];
    a_TransmitData_USBCAN[i].SendType= 0; //正常发送
    a_TransmitData_USBCAN[i].RemoteFlag= 0; //数据帧
    a_TransmitData_USBCAN[i].ExternFlag= 0;//标准帧
    a_TransmitData_USBCAN[i].DataLen = 8; //要发送的数据长度

    gl_mutex.lock();
    dwRel =  VCI_Transmit(gl_nDeviceType, gl_nDeviceInd, gl_nCANInd[0], &a_TransmitData_USBCAN[i], 1);
    gl_mutex.unlock();
   }
    return dwRel;
}

long Transmit_to_Slave(unsigned int ID,  double value)
{

    int s_value=value;

    BYTE ControlData5;
    BYTE ControlData6;
    ControlData6=BYTE(s_value>>8);
    ControlData5=BYTE(s_value&(0xFF));


    DWORD dwRel;

    for(int i=0;i<7;i++)
    {
    S_TransmitData_USBCAN.ID=ID;
    S_TransmitData_USBCAN.SendType= 0; //正常发送
    S_TransmitData_USBCAN.RemoteFlag= 0; //数据帧
    S_TransmitData_USBCAN.ExternFlag= 0;//标准帧
    S_TransmitData_USBCAN.DataLen = 8; //要发送的数据长度
    S_TransmitData_USBCAN.Data[0]=0;
    S_TransmitData_USBCAN.Data[1]=0;
    S_TransmitData_USBCAN.Data[2]=0;
    S_TransmitData_USBCAN.Data[3]=0;
    S_TransmitData_USBCAN.Data[4]=0;
    S_TransmitData_USBCAN.Data[5]=ControlData5;
    S_TransmitData_USBCAN.Data[6]=ControlData6;
    S_TransmitData_USBCAN.Data[7]=0;

    gl_mutex.lock();
    dwRel =  VCI_Transmit(gl_nDeviceType, gl_nDeviceInd, gl_nCANInd[1], &S_TransmitData_USBCAN, 1);
    gl_mutex.unlock();
    }
    return dwRel;
}



long Transmit_USBCANdevice2(int motor_Id)
{
    DWORD dwRel;
    switch (motor_Id)
    {
    case NO_1_motorID:
        gl_TransmitData_USBCAN.ID=IDNum[0];
        break;
    case NO_2_motorID:
        gl_TransmitData_USBCAN.ID=IDNum[1];
        break;
    case NO_3_motorID:
        gl_TransmitData_USBCAN.ID=IDNum[2];
        break;
    case NO_4_motorID:
        gl_TransmitData_USBCAN.ID=IDNum[3];
        break;
    case NO_5_motorID:
        gl_TransmitData_USBCAN.ID=IDNum[4];
        break;
    case NO_6_motorID:
        gl_TransmitData_USBCAN.ID=IDNum[5];
        break;

    default:
        break;
    }

    gl_TransmitData_USBCAN.SendType= 0; //正常发送
    gl_TransmitData_USBCAN.RemoteFlag= 0; //数据帧
    gl_TransmitData_USBCAN.ExternFlag= 0;//标准帧
    gl_TransmitData_USBCAN.DataLen = 8; //要发送的数据长度
    gl_TransmitData_USBCAN.Data[0]=0XA2;
    gl_TransmitData_USBCAN.Data[1]=0;
    gl_TransmitData_USBCAN.Data[2]=0;
    gl_TransmitData_USBCAN.Data[3]=0;
    gl_TransmitData_USBCAN.Data[4]=0;
    gl_TransmitData_USBCAN.Data[5]=0;
    gl_TransmitData_USBCAN.Data[6]=0;
    gl_TransmitData_USBCAN.Data[7]=0;

    gl_mutex.lock();
    dwRel =  VCI_Transmit(gl_nDeviceType, gl_nDeviceInd, gl_nCANInd[0], &gl_TransmitData_USBCAN, 1);
    gl_mutex.unlock();
    return dwRel;
}
/*******************************************
 * 对电机操作
 * ****************************************/
void MotorClose()
{
    for (int i=0;i < 7; i++)
    {

        a_TransmitData_USBCAN[i].Data[0]=0x80;
        a_TransmitData_USBCAN[i].Data[1]=0x00;
        a_TransmitData_USBCAN[i].Data[2]=0x00;
        a_TransmitData_USBCAN[i].Data[3]=0x00;
        a_TransmitData_USBCAN[i].Data[4]=0x00;
        a_TransmitData_USBCAN[i].Data[5]=0x00;
        a_TransmitData_USBCAN[i].Data[6]=0x00;
        a_TransmitData_USBCAN[i].Data[7]=0x00;
    }
    Array_Transmit_USBCANdevice();

}

void MotorClock()
{

    for (int i=0;i < 7; i++)
    {

        a_TransmitData_USBCAN[i].Data[0]=0xA2;
        a_TransmitData_USBCAN[i].Data[1]=0x00;
        a_TransmitData_USBCAN[i].Data[2]=0x00;
        a_TransmitData_USBCAN[i].Data[3]=0x00;
        a_TransmitData_USBCAN[i].Data[4]=0x00;
        a_TransmitData_USBCAN[i].Data[5]=0x00;
        a_TransmitData_USBCAN[i].Data[6]=0x00;
        a_TransmitData_USBCAN[i].Data[7]=0x00;
    }
    Array_Transmit_USBCANdevice();
}


/*******************************************
 *为QXlsx操作模式下的 excel文件的操作函数
 * ****************************************/

void SetupExcel()
{
    gl_xlsxRow=0;

    QDateTime time;
    time = QDateTime::currentDateTime();//获取系统现在的时间
    gl_xlsxname = time.toString("yyyy年-MM月-dd日 hh时-mm分-ss秒 ddd"); //设置显示格式
    //QDir  gl_direction;
    //gl_direction.setPath("D:/qtwork"); //设置文件夹变量的路径
   // str = gl_direction.absolutePath() +"/"+  str + ".xlsx"; // 可以含有路径，作为文件的存放路径

    gl_xlsxname = gl_xlsxname + ".xlsx";
    QXlsx::Document xlsx;
    xlsx.saveAs(gl_xlsxname);

    gl_xlsx= new QXlsx::Document(gl_xlsxname);

 //Create the first sheet (Otherwise, default "Sheet1" will be created)
//    gl_xlsx->addSheet("ManipulatorData");//增加一页，命名为 ManipulatorData,此页为当前页，操作都是针对此页进行的
    //gl_xlsx->setColumnWidth(2, 20); //Column B
    //gl_xlsx->setColumnWidth(8, 12); //Column H
//    gl_xlsx->renameSheet("Sheet1","底座数据");
//    gl_xlsx->selectSheet("底座数据");
    gl_xlsx->currentWorksheet()->setGridLinesVisible(false);

    gl_xlsx->write(1,1,"时间[s]");

    gl_xlsx->write(1,3,"关节1角度[°]");
    gl_xlsx->write(1,4,"关节1期望位移力矩[N*m]");
    gl_xlsx->write(1,5,"关节1实际力矩[N*m]");

    gl_xlsx->write(1,7,"关节2角度[°]");
    gl_xlsx->write(1,8,"关节2期望位移力矩[N*m]");
    gl_xlsx->write(1,9,"关节2实际力矩[N*m]");

    gl_xlsx->write(1,11,"关节3角度[°]");
    gl_xlsx->write(1,12,"关节3期望位移力矩[N*m]");
    gl_xlsx->write(1,13,"关节3实际力矩[N*m]");

    gl_xlsx->write(1,15,"关节4角度[°]");
    gl_xlsx->write(1,16,"关节4期望位移力矩[N*m]");
    gl_xlsx->write(1,17,"关节4实际力矩[N*m]");

    gl_xlsx->write(1,19,"关节5角度[°]");
    gl_xlsx->write(1,20,"关节5期望位移力矩[N*m]");
    gl_xlsx->write(1,21,"关节5实际力矩[N*m]");

    gl_xlsx->write(1,23,"关节6角度[°]");
    gl_xlsx->write(1,24,"关节6期望位移力矩[N*m]");
    gl_xlsx->write(1,25,"关节6实际力矩[N*m]");



    gl_xlsx->write(1,28,"x坐标[mm]");
    gl_xlsx->write(1,29,"y坐标[mm]");
    gl_xlsx->write(1,30,"z坐标[mm]");


    gl_xlsx->save();
    delete gl_xlsx;

}
void WriteExcel()
{

    gl_xlsx= new QXlsx::Document(gl_xlsxname);
    int lastrow=gl_xlsx->dimension().lastRow();
   // bool  i=false;

  // for(long count=1; count<= DATACOUNT; count++)//DATACOUNT
   // {
long count=1;

//       if(gl_1_ImpedanceStruct.m_ok==true && gl_2_ImpedanceStruct.m_ok==true && gl_3_ImpedanceStruct.m_ok==true && gl_4_ImpedanceStruct.m_ok==true
//               && gl_5_ImpedanceStruct.m_ok==true && gl_6_ImpedanceStruct.m_ok==true && gl_7_ImpedanceStruct.m_ok==true && !gl_Time.empty())
     if(gl_1_zeroDrag.m_ok==true && gl_2_zeroDrag.m_ok==true && gl_3_zeroDrag.m_ok==true
        && gl_4_zeroDrag.m_ok==true && gl_5_zeroDrag.m_ok==true && gl_6_zeroDrag.m_ok==true  )
       {

       //    gl_xlsx->write(lastrow+count,1,lastrow+count);
           gl_xlsx->write(lastrow+count,3,angleOutput[1]);
           gl_xlsx->write(lastrow+count,4,chart_e_Torque[1]);
           gl_xlsx->write(lastrow+count,5,chart_r_Torque[1]);

           gl_xlsx->write(lastrow+count,7,angleOutput[2]);
           gl_xlsx->write(lastrow+count,8,chart_e_Torque[2]);
           gl_xlsx->write(lastrow+count,9,chart_r_Torque[2]);

           gl_xlsx->write(lastrow+count,11,angleOutput[3]);
           gl_xlsx->write(lastrow+count,12,chart_e_Torque[3]);
           gl_xlsx->write(lastrow+count,13,chart_r_Torque[3]);

           gl_xlsx->write(lastrow+count,15,angleOutput[4]);
           gl_xlsx->write(lastrow+count,16,chart_e_Torque[4]);
           gl_xlsx->write(lastrow+count,17,chart_r_Torque[4]);

           gl_xlsx->write(lastrow+count,19,angleOutput[5]);
           gl_xlsx->write(lastrow+count,20,chart_e_Torque[5]);
           gl_xlsx->write(lastrow+count,21,chart_r_Torque[5]);

           gl_xlsx->write(lastrow+count,23,angleOutput[6]);
           gl_xlsx->write(lastrow+count,24,chart_e_Torque[6]);
           gl_xlsx->write(lastrow+count,25,chart_r_Torque[6]);



           gl_xlsx->write(lastrow+count,28,coordinates[0]);
           gl_xlsx->write(lastrow+count,29,coordinates[1]);
           gl_xlsx->write(lastrow+count,30,coordinates[2]);

       }



   //}
     gl_xlsx->save();
     delete gl_xlsx;
     gl_xlsx=NULL;

}


