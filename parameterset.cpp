#include "parameterset.h"
#include "ui_parameterset.h"
#include"globalvars.h"
ParameterSet::ParameterSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParameterSet)
{
    ui->setupUi(this);
    this->setWindowTitle("运动轨迹参数设置");
}

ParameterSet::~ParameterSet()
{
    delete ui;
}

void ParameterSet::accept()
{
    if(ui->checkBox_1->isChecked())
    {
      gl_1_MotionPIDStruct.m_Kp=ui->PID_P->value();
      gl_1_MotionPIDStruct.m_Ki=ui->PID_I->value();
      gl_1_MotionPIDStruct.m_Kd=ui->PID_D->value();
      gl_1_MotionPIDStruct.m_q0=ui->q_1->value();
      gl_1_MotionPIDStruct.m_wf=ui->Wf_1->value();
      gl_1_MotionPIDStruct.m_a[0]=ui->a_1_1->value();
      gl_1_MotionPIDStruct.m_a[1]=ui->a_1_2->value();
      gl_1_MotionPIDStruct.m_a[2]=ui->a_1_3->value();
      gl_1_MotionPIDStruct.m_a[3]=ui->a_1_4->value();
      gl_1_MotionPIDStruct.m_a[4]=ui->a_1_5->value();
      gl_1_MotionPIDStruct.m_b[0]=ui->b_1_1->value();
      gl_1_MotionPIDStruct.m_b[1]=ui->b_1_2->value();
      gl_1_MotionPIDStruct.m_b[2]=ui->b_1_3->value();
      gl_1_MotionPIDStruct.m_b[3]=ui->b_1_4->value();
      gl_1_MotionPIDStruct.m_b[4]=ui->b_1_5->value();
    }

    if(ui->checkBox_2->isChecked())
    {
      gl_2_MotionPIDStruct.m_Kp=ui->PID_P_2->value();
      gl_2_MotionPIDStruct.m_Ki=ui->PID_I_2->value();
      gl_2_MotionPIDStruct.m_Kd=ui->PID_D_2->value();
      gl_2_MotionPIDStruct.m_q0=ui->q_2->value();
      gl_2_MotionPIDStruct.m_wf=ui->Wf_2->value();
      gl_2_MotionPIDStruct.m_a[0]=ui->a_2_1->value();
      gl_2_MotionPIDStruct.m_a[1]=ui->a_2_2->value();
      gl_2_MotionPIDStruct.m_a[2]=ui->a_2_3->value();
      gl_2_MotionPIDStruct.m_a[3]=ui->a_2_4->value();
      gl_2_MotionPIDStruct.m_a[4]=ui->a_2_5->value();
      gl_2_MotionPIDStruct.m_b[0]=ui->b_2_1->value();
      gl_2_MotionPIDStruct.m_b[1]=ui->b_2_2->value();
      gl_2_MotionPIDStruct.m_b[2]=ui->b_2_3->value();
      gl_2_MotionPIDStruct.m_b[3]=ui->b_2_4->value();
      gl_2_MotionPIDStruct.m_b[4]=ui->b_2_5->value();
     }

    if(ui->checkBox_3->isChecked())
    {
      gl_3_MotionPIDStruct.m_Kp=ui->PID_P_3->value();
      gl_3_MotionPIDStruct.m_Ki=ui->PID_I_3->value();
      gl_3_MotionPIDStruct.m_Kd=ui->PID_D_3->value();
      gl_3_MotionPIDStruct.m_q0=ui->q_3->value();
      gl_3_MotionPIDStruct.m_wf=ui->Wf_3->value();
      gl_3_MotionPIDStruct.m_a[0]=ui->a_3_1->value();
      gl_3_MotionPIDStruct.m_a[1]=ui->a_3_2->value();
      gl_3_MotionPIDStruct.m_a[2]=ui->a_3_3->value();
      gl_3_MotionPIDStruct.m_a[3]=ui->a_3_4->value();
      gl_3_MotionPIDStruct.m_a[4]=ui->a_3_5->value();
      gl_3_MotionPIDStruct.m_b[0]=ui->b_3_1->value();
      gl_3_MotionPIDStruct.m_b[1]=ui->b_3_2->value();
      gl_3_MotionPIDStruct.m_b[2]=ui->b_3_3->value();
      gl_3_MotionPIDStruct.m_b[3]=ui->b_3_4->value();
      gl_3_MotionPIDStruct.m_b[4]=ui->b_3_5->value();
    }

    if(ui->checkBox_4->isChecked())
    {
      gl_4_MotionPIDStruct.m_Kp=ui->PID_P_4->value();
      gl_4_MotionPIDStruct.m_Ki=ui->PID_I_4->value();
      gl_4_MotionPIDStruct.m_Kd=ui->PID_D_4->value();
      gl_4_MotionPIDStruct.m_q0=ui->q_4->value();
      gl_4_MotionPIDStruct.m_wf=ui->Wf_4->value();
      gl_4_MotionPIDStruct.m_a[0]=ui->a_4_1->value();
      gl_4_MotionPIDStruct.m_a[1]=ui->a_4_2->value();
      gl_4_MotionPIDStruct.m_a[2]=ui->a_4_3->value();
      gl_4_MotionPIDStruct.m_a[3]=ui->a_4_4->value();
      gl_4_MotionPIDStruct.m_a[4]=ui->a_4_5->value();
      gl_4_MotionPIDStruct.m_b[0]=ui->b_4_1->value();
      gl_4_MotionPIDStruct.m_b[1]=ui->b_4_2->value();
      gl_4_MotionPIDStruct.m_b[2]=ui->b_4_3->value();
      gl_4_MotionPIDStruct.m_b[3]=ui->b_4_4->value();
      gl_4_MotionPIDStruct.m_b[4]=ui->b_4_5->value();
    }

    if(ui->checkBox_5->isChecked())
    {
      gl_5_MotionPIDStruct.m_Kp=ui->PID_P_5->value();
      gl_5_MotionPIDStruct.m_Ki=ui->PID_I_5->value();
      gl_5_MotionPIDStruct.m_Kd=ui->PID_D_5->value();
      gl_5_MotionPIDStruct.m_q0=ui->q_5->value();
      gl_5_MotionPIDStruct.m_wf=ui->Wf_5->value();
      gl_5_MotionPIDStruct.m_a[0]=ui->a_5_1->value();
      gl_5_MotionPIDStruct.m_a[1]=ui->a_5_2->value();
      gl_5_MotionPIDStruct.m_a[2]=ui->a_5_3->value();
      gl_5_MotionPIDStruct.m_a[3]=ui->a_5_4->value();
      gl_5_MotionPIDStruct.m_a[4]=ui->a_5_5->value();
      gl_5_MotionPIDStruct.m_b[0]=ui->b_5_1->value();
      gl_5_MotionPIDStruct.m_b[1]=ui->b_5_2->value();
      gl_5_MotionPIDStruct.m_b[2]=ui->b_5_3->value();
      gl_5_MotionPIDStruct.m_b[3]=ui->b_5_4->value();
      gl_5_MotionPIDStruct.m_b[4]=ui->b_5_5->value();
    }

    if(ui->checkBox_6->isChecked())
    {
      gl_6_MotionPIDStruct.m_Kp=ui->PID_P_6->value();
      gl_6_MotionPIDStruct.m_Ki=ui->PID_I_6->value();
      gl_6_MotionPIDStruct.m_Kd=ui->PID_D_6->value();
      gl_6_MotionPIDStruct.m_q0=ui->q_6->value();
      gl_6_MotionPIDStruct.m_wf=ui->Wf_6->value();
      gl_6_MotionPIDStruct.m_a[0]=ui->a_6_1->value();
      gl_6_MotionPIDStruct.m_a[1]=ui->a_6_2->value();
      gl_6_MotionPIDStruct.m_a[2]=ui->a_6_3->value();
      gl_6_MotionPIDStruct.m_a[3]=ui->a_6_4->value();
      gl_6_MotionPIDStruct.m_a[4]=ui->a_6_5->value();
      gl_6_MotionPIDStruct.m_b[0]=ui->b_6_1->value();
      gl_6_MotionPIDStruct.m_b[1]=ui->b_6_2->value();
      gl_6_MotionPIDStruct.m_b[2]=ui->b_6_3->value();
      gl_6_MotionPIDStruct.m_b[3]=ui->b_6_4->value();
      gl_6_MotionPIDStruct.m_b[4]=ui->b_6_5->value();
     }





    QDialog::accept();

}

void ParameterSet::setvalue(double *K_1, double *D_1, double *K_2, double *D_2, double *K_3, double *D_3, double *K_4, double *D_4, double *K_5, double *D_5, double *K_6, double *D_6)
{
//    ui->K_1->setValue(*K_1);
//    ui->D_1->setValue(*D_1);

//    ui->K_2->setValue(*K_2);
//    ui->D_2->setValue(*D_2);

//    ui->K_3->setValue(*K_3);
//    ui->D_3->setValue(*D_3);

//    ui->K_4->setValue(*K_4);
//    ui->D_4->setValue(*D_4);

//    ui->K_5->setValue(*K_5);
//    ui->D_5->setValue(*D_5);

//    ui->K_6->setValue(*K_6);
//    ui->D_6->setValue(*D_6);

//    ui->K_7->setValue(*K_7);
//    ui->D_7->setValue(*D_7);
}

void ParameterSet::on_checkBox_1_clicked(bool checked)
{

    if(checked)
        gl_1_MotionPIDStruct.m_Enable=true;
    else
        gl_1_MotionPIDStruct.m_Enable=false;
}

void ParameterSet::on_checkBox_2_clicked(bool checked)
{
    if(checked)
        gl_2_MotionPIDStruct.m_Enable=true;
    else
        gl_2_MotionPIDStruct.m_Enable=false;
}

void ParameterSet::on_checkBox_3_clicked(bool checked)
{
    if(checked)
        gl_3_MotionPIDStruct.m_Enable=true;
    else
        gl_3_MotionPIDStruct.m_Enable=false;
}

void ParameterSet::on_checkBox_4_clicked(bool checked)
{
    if(checked)
        gl_4_MotionPIDStruct.m_Enable=true;
    else
        gl_4_MotionPIDStruct.m_Enable=false;
}

void ParameterSet::on_checkBox_5_clicked(bool checked)
{
    if(checked)
        gl_5_MotionPIDStruct.m_Enable=true;
    else
        gl_5_MotionPIDStruct.m_Enable=false;
}

void ParameterSet::on_checkBox_6_clicked(bool checked)
{
    if(checked)
        gl_6_MotionPIDStruct.m_Enable=true;
    else
        gl_6_MotionPIDStruct.m_Enable=false;
}




