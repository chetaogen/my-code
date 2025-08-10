#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QThread"
#include<QDebug>
#include<globalfunction.h>
#include<globalvars.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("遥操作控制平台");

    ZeroDrag=new MyThread();
    Trajectory=new MyThread2();
    ImpedanceControl=new mythread3();
    m_angleCurve=new DrawAngleCurve();
    m_torqueCurve=new DrawTorqueCurve();
    cansetting=new CANsetting();


    setStyleSheet(  "QMainWindow{background-color:rgb(138, 138, 138)}");
   // QWidget *parent_widget= new QWidget();
    ui->widget_2->setObjectName("parent_widget");
    ui->widget_2->setStyleSheet("#parent_widget{border-image:url(:/robot.png)}");

    connect(&excelTimer,SIGNAL(timeout()),this,SLOT(excelWrite()));




    connect(ZeroDrag,&MyThread::emitSignal,this,[=](){
        ui->lineEdit_1_A->setText(QString::number(angleOutput[1]));
        ui->lineEdit_2_A->setText(QString::number(angleOutput[2]));
        ui->lineEdit_3_A->setText(QString::number(angleOutput[3]));
        ui->lineEdit_4_A->setText(QString::number(angleOutput[4]));
        ui->lineEdit_5_A->setText(QString::number(angleOutput[5]));
        ui->lineEdit_6_A->setText(QString::number(angleOutput[6]));


        ui->lineEdit_1_T->setText(QString::number(chart_e_Torque[1]));
        ui->lineEdit_2_T->setText(QString::number(chart_e_Torque[2]));
        ui->lineEdit_3_T->setText(QString::number(chart_e_Torque[3]));
        ui->lineEdit_4_T->setText(QString::number(chart_e_Torque[4]));
        ui->lineEdit_5_T->setText(QString::number(chart_e_Torque[5]));
        ui->lineEdit_6_T->setText(QString::number(chart_e_Torque[6]));

        ui->lineEdit_1_T_1->setText(QString::number(chart_r_Torque[1]));
        ui->lineEdit_2_T_2->setText(QString::number(chart_r_Torque[2]));
        ui->lineEdit_3_T_3->setText(QString::number(chart_r_Torque[3]));
        ui->lineEdit_4_T_4->setText(QString::number(chart_r_Torque[4]));
        ui->lineEdit_5_T_5->setText(QString::number(chart_r_Torque[5]));
        ui->lineEdit_6_T_6->setText(QString::number(chart_r_Torque[6]));


        ui->lineEdit_X->setText(QString::number(coordinates[0]));
        ui->lineEdit_Y->setText(QString::number(coordinates[1]));
        ui->lineEdit_Z->setText(QString::number(coordinates[2]));



        ui->lineEdit_1_A_2->setText(QString::number(3.2*angleOutput[1]));
        ui->lineEdit_2_A_2->setText(QString::number(3.2*angleOutput[2]));
        ui->lineEdit_3_A_2->setText(QString::number(3.2*angleOutput[3]));
        ui->lineEdit_4_A_2->setText(QString::number(3.2*angleOutput[4]));
        ui->lineEdit_5_A_2->setText(QString::number(3.2*angleOutput[5]));
        ui->lineEdit_6_A_2->setText(QString::number(3.2*angleOutput[6]));
        ui->lineEdit_X_2->setText(QString::number(3.2*coordinates[0]));
        ui->lineEdit_Y_2->setText(QString::number(3.2*coordinates[1]));
        ui->lineEdit_Z_2->setText(QString::number(3.2*coordinates[2]));




    });

    connect(ImpedanceControl,&mythread3::emitSignal,this,[=]()
    {
        ui->lineEdit_1_A->setText(QString::number(angleOutput[1]));
        ui->lineEdit_2_A->setText(QString::number(angleOutput[2]));
        ui->lineEdit_3_A->setText(QString::number(angleOutput[3]));
        ui->lineEdit_4_A->setText(QString::number(angleOutput[4]));
        ui->lineEdit_5_A->setText(QString::number(angleOutput[5]));
        ui->lineEdit_6_A->setText(QString::number(angleOutput[6]));


        ui->lineEdit_1_T->setText(QString::number(chart_e_Torque[1]));
        ui->lineEdit_2_T->setText(QString::number(chart_e_Torque[2]));
        ui->lineEdit_3_T->setText(QString::number(chart_e_Torque[3]));
        ui->lineEdit_4_T->setText(QString::number(chart_e_Torque[4]));
        ui->lineEdit_5_T->setText(QString::number(chart_e_Torque[5]));
        ui->lineEdit_6_T->setText(QString::number(chart_e_Torque[6]));


        ui->lineEdit_1_T_1->setText(QString::number(chart_r_Torque[1]));
        ui->lineEdit_2_T_2->setText(QString::number(chart_r_Torque[2]));
        ui->lineEdit_3_T_3->setText(QString::number(chart_r_Torque[3]));
        ui->lineEdit_4_T_4->setText(QString::number(chart_r_Torque[4]));
        ui->lineEdit_5_T_5->setText(QString::number(chart_r_Torque[5]));
        ui->lineEdit_6_T_6->setText(QString::number(chart_r_Torque[6]));


        ui->lineEdit_X->setText(QString::number(coordinates[0]));
        ui->lineEdit_Y->setText(QString::number(coordinates[1]));
        ui->lineEdit_Z->setText(QString::number(coordinates[2]));
    });



}
MainWindow::~MainWindow()
{
    delete ui;

}




void MainWindow::on_btnCanStart_clicked()                    //启动USBCAN
{
    if(ui->btnCanStart->text() == tr("CAN启动"))
    {
        ui->btnCanStart->setText(tr("CAN关闭"));
        Open_USBCANdevice();
        Init_USBCANdevice();
        Init_USBCANdevice2();
        Start_USBCANdevice();

        ui->btnZeroDrag->setEnabled(true);


    }
    else if(ui->btnCanStart->text() == tr("CAN关闭"))
    {
        ui->btnCanStart->setText(tr("CAN启动"));
        Close_USBCANdevice();


    }


}

void MainWindow::on_btnZeroDrag_clicked()           //零力拖动的线程
{

    ZeroDrag->start();
    m_angleCurve->dataTimer.start(0);
    m_torqueCurve->dataTimer.start(0);

    if(ZeroDrag->isRunning())
    {
        ImpedanceControl->stop();
        ui->btnImpedance->setEnabled(false);
    }


}



void MainWindow::on_btnAngleImage_clicked()                    //绘制角度图像
{
    if(ui->btnAngleImage->text() == tr("角度图像"))
    {
        ui->btnAngleImage->setText(tr("关闭角度图像"));
        m_angleCurve->show();

    }

    else if(ui->btnAngleImage->text() == tr("关闭角度图像"))
    {
        ui->btnAngleImage->setText(tr("角度图像"));
        m_angleCurve->close();

    }

}

void MainWindow::on_btnMotorStop_clicked()
{
    MotorClose();
    if(ZeroDrag->isRunning())
    {
        ZeroDrag->stop();
    }


    if(ImpedanceControl->isRunning())
    {
        ImpedanceControl->stop();
    }
    MotorClose();
}





void MainWindow::on_btnMomentImage_clicked()
{
    if(ui->btnMomentImage->text() == tr("力矩图像"))
    {
        ui->btnMomentImage->setText(tr("关闭力矩图像"));
        m_torqueCurve->show();

    }
    else if(ui->btnMomentImage->text() == tr("关闭力矩图像"))
    {
        ui->btnMomentImage->setText(tr("力矩图像"));
        m_torqueCurve->close();

    }
}

void MainWindow::on_btnThread_clicked()
{


     if(ZeroDrag->isRunning())
    {
        ZeroDrag->stop();
//        ZeroDrag->quit();
//        ZeroDrag->wait();
//        ZeroDrag->deleteLater();

        ui->btnImpedance->setEnabled(true);
    }

     if(ImpedanceControl->isRunning())
     {
          ImpedanceControl->stop();
          ImpedanceControl->quit();
          ImpedanceControl->wait();

          ui->btnZeroDrag->setEnabled(true);
     }

     m_angleCurve->dataTimer.stop();
     m_torqueCurve->dataTimer.stop();
}


void MainWindow::on_pushButton_clicked()
{
    cansetting->show();
}

void MainWindow::on_ClearBtn_clicked()
{
    ui->lineEdit_1_A->clear();  ui->lineEdit_1_T->clear();   ui->lineEdit_1_T_1->clear();   ui->lineEdit_X->clear();
    ui->lineEdit_2_A->clear();  ui->lineEdit_2_T->clear();   ui->lineEdit_2_T_2->clear();
    ui->lineEdit_3_A->clear();  ui->lineEdit_3_T->clear();   ui->lineEdit_3_T_3->clear();   ui->lineEdit_Y->clear();
    ui->lineEdit_4_A->clear();  ui->lineEdit_4_T->clear();   ui->lineEdit_4_T_4->clear();   ui->lineEdit_Z->clear();
    ui->lineEdit_5_A->clear();  ui->lineEdit_5_T->clear();   ui->lineEdit_5_T_5->clear();
    ui->lineEdit_6_A->clear();  ui->lineEdit_6_T->clear();   ui->lineEdit_6_T_6->clear();


}

void MainWindow::on_quitBtn_clicked()
{
    MotorClose();
    if(ZeroDrag->isRunning())
    {
        ZeroDrag->stop();
    }


    if(ImpedanceControl->isRunning())
    {
        ImpedanceControl->stop();
    }

    if(Trajectory->isRunning())
    {
        Trajectory->stop();
    }
    this->hide();

}


void MainWindow::on_btnImpedance_clicked()
{
    ImpedanceControl->InitParmeter();
    ImpedanceControl->start();
    m_angleCurve->dataTimer.start(0);
    m_torqueCurve->dataTimer.start(0);
    if(ImpedanceControl->isRunning())
    {

        ZeroDrag->stop();
        ui->btnZeroDrag->setEnabled(false);
    }



}

void MainWindow::on_buttonPress_pressed()
{
  // ImpedanceControl->button1=true;
}

void MainWindow::on_buttonPress_released()
{
   //ImpedanceControl->button1=false;

}

void MainWindow::on_button2_pressed()
{
    ImpedanceControl->button2=true;

}

void MainWindow::on_button2_released()
{
    ImpedanceControl->button2=false;

}

void MainWindow::excelWrite()
{
    WriteExcel();
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    this->grabKeyboard();
    switch(ev->key()){
    case Qt::Key_Left:
        if(!ev->isAutoRepeat())
        {
            ImpedanceControl->button1=true;
            ui->buttonPress->setStyleSheet("border-color:rgb(148,0,0);");
        }
        break;
    case Qt::Key_Right:
        if(!ev->isAutoRepeat())
        {
            ImpedanceControl->button2=true;
             ui->button2->setStyleSheet("border-color:rgb(148,0,0);");
        }
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{
    this->grabKeyboard();
    switch(ev->key()){
    case Qt::Key_Left:
        if(!ev->isAutoRepeat())
        {
            ImpedanceControl->button1=false;
            ui->buttonPress->setStyleSheet("border-color:rgb(255,255,255);");

        }
        break;
    case Qt::Key_Right:
        if(!ev->isAutoRepeat())
        {
            ImpedanceControl->button2=false;
            ui->button2->setStyleSheet("border-color:rgb(255,255,255);");
        }
        break;
    }
}

void MainWindow::on_SaveBtn_clicked()
{
    if(ui->SaveBtn->text() == tr("保存"))
    {
        ui->SaveBtn->setText(tr("停止"));
        SetupExcel();
        this->excelTimer.start(50);

    }

    else if(ui->SaveBtn->text() == tr("停止"))
    {
        ui->SaveBtn->setText(tr("保存"));
        this->excelTimer.stop();

    }

}


void MainWindow::on_ParamentSetBtn_clicked()
{

        //对话框初始显示时的KD参数值
            m_dialog.setvalue(&gl_1_ImpedanceStruct.m_K,
                              &gl_1_ImpedanceStruct.m_D,
                              &gl_2_ImpedanceStruct.m_K,
                              &gl_2_ImpedanceStruct.m_D,
                              &gl_3_ImpedanceStruct.m_K,
                              &gl_3_ImpedanceStruct.m_D,
                              &gl_4_ImpedanceStruct.m_K,
                              &gl_4_ImpedanceStruct.m_D,
                              &gl_5_ImpedanceStruct.m_K,
                              &gl_5_ImpedanceStruct.m_D,
                              &gl_6_ImpedanceStruct.m_K,
                              &gl_6_ImpedanceStruct.m_D);
        //保存修改后的KD参数值
            if(m_dialog.exec()==QDialog::Accepted)
            {
                m_dialog.accept();
                gl_1_ImpedanceStruct.m_K=m_dialog.m_K_1;
                gl_1_ImpedanceStruct.m_D=m_dialog.m_D_1;
                gl_2_ImpedanceStruct.m_K=m_dialog.m_K_2;
                gl_2_ImpedanceStruct.m_D=m_dialog.m_D_2;
                gl_3_ImpedanceStruct.m_K=m_dialog.m_K_3;
                gl_3_ImpedanceStruct.m_D=m_dialog.m_D_3;
                gl_4_ImpedanceStruct.m_K=m_dialog.m_K_4;
                gl_4_ImpedanceStruct.m_D=m_dialog.m_D_4;
                gl_5_ImpedanceStruct.m_K=m_dialog.m_K_5;
                gl_5_ImpedanceStruct.m_D=m_dialog.m_D_5;
                gl_6_ImpedanceStruct.m_K=m_dialog.m_K_6;
                gl_6_ImpedanceStruct.m_D=m_dialog.m_D_6;

             }


}

void MainWindow::on_PIDBtn_clicked()
{
    Trajectory->start();
    m_angleCurve->dataTimer.start(0);
    m_torqueCurve->dataTimer.start(0);
}

void MainWindow::on_buttonPress_clicked()
{

    MotorClock();
}





void MainWindow::on_btnSend_clicked()
{
    if(ui->btnSend->text() == tr("主从传输"))
    {
                ui->btnSend->setText(tr("传输关闭"));
                SendFlag=true;

    }

    else if(ui->btnSend->text() == tr("传输关闭"))
    {
                ui->btnSend->setText(tr("主从传输"));
                SendFlag=false;

    }
}

