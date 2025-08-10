#include "globalvars.h"


int gl_nDeviceType = 4; /* USBCAN-II */
int gl_nDeviceInd = 1; //设备索引号，比如当只有一个设备时，索引号为0，有两个时可以为0或1
int gl_nReserved = 0;
int gl_nCANInd[2]={0,1};//第几路CAN。即对应卡的CAN通道号， CAN0为0， CAN1为1。

VCI_CAN_OBJ gl_TransmitData_USBCAN;
VCI_CAN_OBJ a_TransmitData_USBCAN[6];
VCI_CAN_OBJ S_TransmitData_USBCAN;
VCI_CAN_OBJ gl_ReceiveData_USBCAN[1000];
UINT  IDNum[6]={0x00000141,0x00000142,0x00000144,0x00000145,0x00000146,0x00000147};

Eigen::Matrix4d gl_T06;

QSemaphore  gl_sem(0);// 定义一个信号量
QMutex gl_mutex;
QMutex gl_mutex1;
QMutex gl_mutex2;

Angle_TorqueStruct gl_1_Struct;
Angle_TorqueStruct gl_2_Struct;
Angle_TorqueStruct gl_3_Struct;
Angle_TorqueStruct gl_4_Struct;
Angle_TorqueStruct gl_5_Struct;
Angle_TorqueStruct gl_6_Struct;

floatByteUnion gl_floatByte;

zeroDragStruct gl_1_zeroDrag;
zeroDragStruct gl_2_zeroDrag;
zeroDragStruct gl_3_zeroDrag;
zeroDragStruct gl_4_zeroDrag;
zeroDragStruct gl_5_zeroDrag;
zeroDragStruct gl_6_zeroDrag;

bool SendFlag=false;

ImpedanceStruct gl_1_ImpedanceStruct;
ImpedanceStruct gl_2_ImpedanceStruct;
ImpedanceStruct gl_3_ImpedanceStruct;
ImpedanceStruct gl_4_ImpedanceStruct;
ImpedanceStruct gl_5_ImpedanceStruct;
ImpedanceStruct gl_6_ImpedanceStruct;


PIDMotionParameterStruct gl_1_MotionPIDStruct;
PIDMotionParameterStruct gl_2_MotionPIDStruct;
PIDMotionParameterStruct gl_3_MotionPIDStruct;
PIDMotionParameterStruct gl_4_MotionPIDStruct;
PIDMotionParameterStruct gl_5_MotionPIDStruct;
PIDMotionParameterStruct gl_6_MotionPIDStruct;


std::vector<double>  gl_Time;
std::vector<double>  gl_Time2;

QXlsx::Document *gl_xlsx;
QString gl_xlsxname;
long gl_xlsxRow;
//float angleOutput[8]{};
double angleOutput[7]{};
double chart_r_Torque[7]{};
double chart_e_Torque[7]{};
double coordinates[3]{};
 double angleOutput_2[7];
 double Torque_2[7];
 double coordinates_2[3];
Algorithm gl_Algorithm;

