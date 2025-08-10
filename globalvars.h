#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#endif // GLOBALVARS_H

#include<QMutex>
#include"ControlCAN.h"
#include<QMessageBox>
#include<QDebug>
#include"Eigen/Core"
#include<Algorithm.h>
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxcellrange.h"
#include "xlsxworksheet.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSemaphore>

#define PI acos(-1.0)
#define rad(x)  (x*PI/180)  //角度转化为弧度
#define angle(x) (x*180/PI) //弧度转化为角度

extern int gl_nDeviceType; /* USBCAN-II */
extern int gl_nDeviceInd;
extern int gl_nReserved;
extern int gl_nCANInd[2];
extern VCI_CAN_OBJ gl_TransmitData_USBCAN;
extern VCI_CAN_OBJ a_TransmitData_USBCAN[6];
extern VCI_CAN_OBJ S_TransmitData_USBCAN;
extern VCI_CAN_OBJ gl_ReceiveData_USBCAN[1000];
extern UINT  IDNum[6];

//定义联合体，该联合体用以CAN总线处理浮点型数据，根据IEEE标准，一个浮点型数据用4个字节进行表示
typedef union _floatByte
{
    float float_data;
    unsigned char byte_data[4];
}floatByteUnion, *floatByte;

extern floatByteUnion gl_floatByte;
extern QSemaphore  gl_sem;// 定义一个信号量
extern QMutex gl_mutex;
extern QMutex gl_mutex1;
extern QMutex gl_mutex2;
const int  DATACOUNT=2000;
const int NO_1_motorID=321;
const int NO_2_motorID=322;
const int NO_3_motorID=580;
const int NO_4_motorID=325;
const int NO_5_motorID=326;
const int NO_6_motorID=327;

extern Eigen::Matrix4d gl_T06;


typedef struct Collection_Data//结构体定义
{
    std::vector<double>	m_Time_Save;	// 时间，保存数据用
    std::vector<double>	m_Angle_Save;
    std::vector<double>	m_SampledTorque_Save;
    std::vector<double>	m_DesiredTorque_Save;
} Angle_TorqueStruct;


extern Angle_TorqueStruct gl_1_Struct;
extern Angle_TorqueStruct gl_2_Struct;
extern Angle_TorqueStruct gl_3_Struct;
extern Angle_TorqueStruct gl_4_Struct;
extern Angle_TorqueStruct gl_5_Struct;
extern Angle_TorqueStruct gl_6_Struct;


extern std::vector<double>  gl_Time;//double类型的动态数组变量，用于存储时间，写入excel用
extern std::vector<double>  gl_Time2;

extern QXlsx::Document *gl_xlsx;
extern QString gl_xlsxname;
extern long gl_xlsxRow;

extern  double angleOutput[7];
extern  double chart_e_Torque[7];
extern  double chart_r_Torque[7];
extern  double coordinates[3];

extern  double angleOutput_2[7];
extern  double Torque_2[7];
extern  double coordinates_2[3];

extern  bool SendFlag;

typedef struct zeroParammters
{
    bool m_ok;
    double m_putOut;

}zeroDragStruct;
extern zeroDragStruct gl_1_zeroDrag;
extern zeroDragStruct gl_2_zeroDrag;
extern zeroDragStruct gl_3_zeroDrag;
extern zeroDragStruct gl_4_zeroDrag;
extern zeroDragStruct gl_5_zeroDrag;
extern zeroDragStruct gl_6_zeroDrag;





typedef struct ImpedanceParammters
{
    //double m_M;
    double m_K;
    double m_D;
    double m_delta_q;
    std::vector<double> m_q;
    bool  m_ok;
    double m_limit;
    double m_putOut;
    std::vector<double> m_torque;

}ImpedanceStruct;

extern ImpedanceStruct gl_1_ImpedanceStruct;
extern ImpedanceStruct gl_2_ImpedanceStruct;
extern ImpedanceStruct gl_3_ImpedanceStruct;
extern ImpedanceStruct gl_4_ImpedanceStruct;
extern ImpedanceStruct gl_5_ImpedanceStruct;
extern ImpedanceStruct gl_6_ImpedanceStruct;


extern Algorithm gl_Algorithm;

typedef struct _PIDMotionParameters // 结构体的定义
{
    bool	m_Enable;			// 使能标志位
    double	m_Kp;				// kp
    double	m_Ki;			// ki
    double  m_Kd;				// kd
    std::vector<double>  m_time;
    double  m_curerror;//当前误差
    double  m_lasterror;//上次误差
    double  m_preerror;//上上次误差
    int     m_PIDout;
    int  MaxPIDoutput;
    int  MinPIDoutput;
    std::vector<double>	m_SampledData_PID;//PID运算用
    std::vector<double>	m_DesiredData_PID;//PID运算用
    double  m_wf;				// 角频率
    double  m_q0;
    double m_a[5];            //sin函数幅值
    double m_b[5];            //cos函数幅值

} PIDMotionParameterStruct;
extern  PIDMotionParameterStruct gl_1_MotionPIDStruct;
extern  PIDMotionParameterStruct gl_2_MotionPIDStruct;
extern  PIDMotionParameterStruct gl_3_MotionPIDStruct;
extern  PIDMotionParameterStruct gl_4_MotionPIDStruct;
extern  PIDMotionParameterStruct gl_5_MotionPIDStruct;
extern  PIDMotionParameterStruct gl_6_MotionPIDStruct;

