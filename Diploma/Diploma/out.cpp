#include "out.h"
#include "ui_out.h"

out::out(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::out)
{
    ui->setupUi(this);
}

out::~out()
{
    delete ui;
}

void out::on_comboBox_currentIndexChanged(int index)
{

}

void out::on_spinBox_valueChanged(int arg1)
{

}

void out::on_tableWidget_doubleClicked(const QModelIndex &index)
{

}

void out::on_pushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Вы действительно хотите создать заказ?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)
    {

    }
}
