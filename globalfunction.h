#ifndef GLOBALFUNCTION_H
#define GLOBALFUNCTION_H
#endif // GLOBALFUNCTION_H

#include<windows.h>
#include "ControlCAN.h"

/*******************************************
 * CAN通讯指令
 * ****************************************/
bool Open_USBCANdevice();
bool Close_USBCANdevice();
bool Init_USBCANdevice();
bool Init_USBCANdevice2();
bool Start_USBCANdevice();
long Receive_USBCANdevice( );
long GetReceiveNum_USBCANdevice();
bool ClearBuffer_USBCANdevice();
long Transmit_USBCANdevice();
long Transmit_USBCANdevice2(int motor_Id);
long Array_Transmit_USBCANdevice();
long Transmit_to_Slave(unsigned int ID, double value);

/*******************************************
 * 对Excel表操作
 * ****************************************/
void SetupExcel();
void WriteExcel();

/*******************************************
 * 对电机操作
 * ****************************************/
void MotorClose();
void MotorClock();

void DataResolution(int motor_Id,double Message);
