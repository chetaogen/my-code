#ifndef PARAMETERSET_H
#define PARAMETERSET_H

#include <QDialog>

namespace Ui {
class ParameterSet;
}

class ParameterSet : public QDialog
{
    Q_OBJECT

public:
    explicit ParameterSet(QWidget *parent = 0);
    ~ParameterSet();

    void accept() override;

    double m_K_1;
    double m_D_1;
    double m_K_2;
    double m_D_2;
    double m_K_3;
    double m_D_3;
    double m_K_4;
    double m_D_4;
    double m_K_5;
    double m_D_5;
    double m_K_6;
    double m_D_6;
    double m_K_7;
    double m_D_7;

    void setvalue(double *K_1,double *D_1,double *K_2,double *D_2,double *K_3,double *D_3,double *K_4,double *D_4,double *K_5,double *D_5,double *K_6,double *D_6);

private slots:


    void on_checkBox_1_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_3_clicked(bool checked);

    void on_checkBox_4_clicked(bool checked);

    void on_checkBox_5_clicked(bool checked);

    void on_checkBox_6_clicked(bool checked);

    void on_checkBox_7_clicked(bool checked);

private:
    Ui::ParameterSet *ui;
};

#endif // PARAMETERSET_H
