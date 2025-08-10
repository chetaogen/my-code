#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"mythread.h"
#include"mythread2.h"
#include"mythread3.h"
#include"ControlCAN.h"
#include"drawAngleCurve.h"
#include"drawtorquecurve.h"
#include"cansetting.h"
#include"parameterset.h"
#include <QTime>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_btnCanStart_clicked();



    void on_btnAngleImage_clicked();

    void on_btnMotorStop_clicked();

    void on_btnZeroDrag_clicked();

    void on_btnMomentImage_clicked();

    void on_btnThread_clicked();


    void on_pushButton_clicked();

    void on_ClearBtn_clicked();

    void on_quitBtn_clicked();


    void on_btnImpedance_clicked();

    void on_buttonPress_pressed();

    void on_buttonPress_released();

    void on_button2_pressed();

    void on_button2_released();

    void excelWrite();
    void on_SaveBtn_clicked();


    void on_ParamentSetBtn_clicked();

    void on_PIDBtn_clicked();

    void on_buttonPress_clicked();



    void on_btnSend_clicked();

private:
    Ui::MainWindow *ui;

    MyThread *ZeroDrag;
    MyThread2 *Trajectory;
    mythread3 *ImpedanceControl;
    DrawAngleCurve *m_angleCurve;
    DrawTorqueCurve *m_torqueCurve;
    CANsetting *cansetting;

    QTimer excelTimer;

    ParameterSet m_dialog;




protected:
    virtual void keyPressEvent(QKeyEvent *ev);
    virtual void keyReleaseEvent(QKeyEvent *ev);

signals:
    void starting();
    void stop();



};

#endif // MAINWINDOW_H
