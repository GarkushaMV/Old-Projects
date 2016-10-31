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
