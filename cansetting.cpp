#include "cansetting.h"
#include "ui_cansetting.h"

CANsetting::CANsetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CANsetting)
{
    ui->setupUi(this);
    this->setWindowTitle("CAN卡参数设置");
}

CANsetting::~CANsetting()
{
    delete ui;
}

void CANsetting::on_YesBtn_clicked()
{
    CANtype = ui->cantype->currentIndex();
    index = ui->index->currentIndex();
    baundRate = (int)ui->baundRate->currentText().remove("Kbps").toFloat();
    devicCOM = ui->CanCom->currentIndex();
    this->hide();

}

void CANsetting::on_cancelBtn_clicked()
{
      this->hide();
}
