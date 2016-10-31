#include "dialog.h"
#include <QDialog>
#include <cstdlib>
#include "ui_dialog.h"

Dialog::Dialog(Dialog *parent) :
    QDialog(parent), Dui(new Ui::Dialog)
{
    Dui->setupUi(this);
    VertexNumber    = 5;
    EdgesNumber     = 10;
    ComponentNumber = 1;
    MaxDegreeNumber = 4;
    MinDegreeNumber = 4;
}

Dialog::~Dialog()
{
    delete Dui;
}

void Dialog::on_VertexNumberBox_valueChanged(int arg1)
{
    VertexNumber = arg1;
}

void Dialog::on_EdgesNumberbox_valueChanged(int arg1)
{
    EdgesNumber  = arg1;
}

void Dialog::on_ComponentNumberBox_valueChanged(int arg1)
{
    ComponentNumber = arg1;
}

void Dialog::on_MaxDegreeNumberBox_valueChanged(int arg1)
{
    MaxDegreeNumber = arg1;
}

void Dialog::on_MinDegreeNumberBox_valueChanged(int arg1)
{
    MinDegreeNumber = arg1;
}
