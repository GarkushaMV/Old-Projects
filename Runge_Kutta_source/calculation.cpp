#include "calculation.h"
#include "ui_calculation.h"
#include "limits"
#include <QDebug>
long double k1 = 0, k2 = 0, k3 = 0, H  = 0;
long double a0 = 0, b0 = 0, c0 = 0, d0 = 0;
long double a = a0, b = b0, c = c0, d = d0;
long double t0 = 0, t_max = 1;
int n = 20;

Calculation::Calculation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculation)
{
    ui->setupUi(this);
}

Calculation::~Calculation()
{
    delete ui;
}

void Calculation::on_K1_valueChanged(double arg1)
{
    k1 = arg1;
}

void Calculation::on_K2_valueChanged(double arg1)
{
    k2 = arg1;
}

void Calculation::on_K3_valueChanged(double arg1)
{
    k3 = arg1;
}

void Calculation::on_H_valueChanged(int arg1)
{
    n = arg1;
    if((arg1 > (0.00000001)) || (arg1 < (-0.00000001)))
        H = t0/((long double)arg1);
    else
        qDebug() << "Division by zero";
}

void Calculation::on_A0_valueChanged(double arg1)
{
    a0 = arg1;
}

void Calculation::on_B0_valueChanged(double arg1)
{
    b0 = arg1;
}

void Calculation::on_C0_valueChanged(double arg1)
{
    c0 = arg1;
}

void Calculation::on_D0_valueChanged(double arg1)
{
    d0 = arg1;
}

void Calculation::on_T_valueChanged(double arg1)
{
    t0 = arg1;
    H  = t0/((long double)n);
}



long double f_a(long double cor1, long double cor2, long double cor3, long double cor4)
{
    return ((a+cor1)*(- k1*(c+cor3) - k3*(b+cor2)));
}

long double f_b(long double cor1, long double cor2, long double cor3, long double cor4)
{
    return (k1*(a+cor1)*(c+cor3) + 2*k3*(a+cor1)*(b+cor2) - k2*(d+cor4)*(c+cor3));
}

long double f_c(long double cor1, long double cor2, long double cor3, long double cor4)
{
    return (k2*(d+cor4)*(c+cor3) - k3*(a+cor1)*(b+cor2));
}

long double f_d(long double cor1, long double cor2, long double cor3, long double cor4)
{
    return (- k1*(a+cor1)*(c+cor3) - k2*(d+cor4)*(c+cor3));
}


void Calculation::calc()
{
    long double cor[4][4];
    a = a0;
    b = b0;
    c = c0;
    d = d0;
    for(int i=0; i < n; i++)
    {
        cor[0][0] = f_a(0, 0, 0, 0);
        cor[0][1] = f_b(0, 0, 0, 0);
        cor[0][2] = f_c(0, 0, 0, 0);
        cor[0][3] = f_d(0, 0, 0, 0);

        cor[1][0] = f_a(H*cor[0][0]/2, H*cor[0][1]/2, H*cor[0][2]/2, H*cor[0][3]/2);
        cor[1][1] = f_b(H*cor[0][0]/2, H*cor[0][1]/2, H*cor[0][2]/2, H*cor[0][3]/2);
        cor[1][2] = f_c(H*cor[0][0]/2, H*cor[0][1]/2, H*cor[0][2]/2, H*cor[0][3]/2);
        cor[1][3] = f_d(H*cor[0][0]/2, H*cor[0][1]/2, H*cor[0][2]/2, H*cor[0][3]/2);

        cor[2][0] = f_a(H*cor[1][0]/2, H*cor[1][1]/2, H*cor[1][2]/2, H*cor[1][3]/2);
        cor[2][1] = f_b(H*cor[1][0]/2, H*cor[1][1]/2, H*cor[1][2]/2, H*cor[1][3]/2);
        cor[2][2] = f_c(H*cor[1][0]/2, H*cor[1][1]/2, H*cor[1][2]/2, H*cor[1][3]/2);
        cor[2][3] = f_d(H*cor[1][0]/2, H*cor[1][1]/2, H*cor[1][2]/2, H*cor[1][3]/2);

        cor[3][0] = f_a(H*cor[2][0], H*cor[2][1], H*cor[2][2], H*cor[2][3]);
        cor[3][1] = f_b(H*cor[2][0], H*cor[2][1], H*cor[2][2], H*cor[2][3]);
        cor[3][2] = f_c(H*cor[2][0], H*cor[2][1], H*cor[2][2], H*cor[2][3]);
        cor[3][3] = f_d(H*cor[2][0], H*cor[2][1], H*cor[2][2], H*cor[2][3]);

        a += H*(cor[0][0] + 2*cor[1][0] + 2*cor[2][0] + cor[3][0])/6;
        b += H*(cor[0][1] + 2*cor[1][1] + 2*cor[2][1] + cor[3][1])/6;
        c += H*(cor[0][2] + 2*cor[1][2] + 2*cor[2][2] + cor[3][2])/6;
        d += H*(cor[0][3] + 2*cor[1][3] + 2*cor[2][3] + cor[3][3])/6;
    }
}

void Calculation::on_pushButton_clicked()
{
    calc();
    ui ->Layout_a ->setText("<html><head/><body><p><span style=\" font-size:12pt; color:#640000;\">I</span><span style=\" font-size:12pt; color:#640000; vertical-align:super;\">+</span><span style=\" font-size:12pt; color:#640000;\">(t) = " + QString::number((double) a) + "</span></p></body></html>");
    ui ->Layout_b ->setText("<html><head/><body><p><span style=\" font-size:12pt; color:#006400;\">I</span><span style=\" font-size:12pt; color:#006400; vertical-align:super;\">-</span><span style=\" font-size:12pt; color:#006400;\">(t) = " + QString::number((double) b) + "</span></p></body></html>");
    ui ->Layout_c ->setText("<html><head/><body><p><span style=\" font-size:12pt; color:#000064;\">e</span><span style=\" font-size:12pt; color:#000064; vertical-align:super;\">-</span><span style=\" font-size:12pt; color:#000064;\">(t) = " + QString::number((double) c) + "</span></p></body></html>");
    ui ->Layout_d ->setText("<html><head/><body><p><span style=\" font-size:12pt; color:#646400;\"> N(t) = " + QString::number((double) d) + "</span></p></body></html>");
}



void Calculation::on_t_max_valueChanged(double arg1)
{
    t_max = arg1;
}

void Calculation::on_graph_clicked()
{
    QVector<double> x(1000), y1(1000), y2(1000), y3(1000), y4(1000);
    long double ymax = 1.0;
    long double old_t = t0;
    long double old_h = H;
    for (int i=0; i<1000; ++i)
    {
        x[i] = i * t_max/1000.0;
        t0 = x[i];
        H  = t0/((double)n);
        calc();
        y1[i] = a;
        y2[i] = b;
        y3[i] = c;
        y4[i] = d;
        if (y1[i] > ymax)
            ymax = y1[i];
        if (y2[i] > ymax)
            ymax = y2[i];
        if (y3[i] > ymax)
            ymax = y3[i];
        if (y4[i] > ymax)
            ymax = y4[i];
    }
    t0 = old_t;
    H = old_h;
    // create graph and assign data to it:
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y1);
    ui->widget->graph(0)->setPen(QPen(QColor(100, 0, 0)));
    ui->widget->addGraph();
    ui->widget->graph(1)->setData(x, y2);
    ui->widget->graph(1)->setPen(QPen(QColor(0, 100, 0)));
    ui->widget->addGraph();
    ui->widget->graph(2)->setData(x, y3);
    ui->widget->graph(2)->setPen(QPen(QColor(0, 0, 100)));
    ui->widget->addGraph();
    ui->widget->graph(3)->setData(x, y4);
    ui->widget->graph(3)->setPen(QPen(QColor(100, 100, 0)));
    // give the axes some labels:
    ui->widget->xAxis->setLabel("t");
    // set axes ranges, so we see all data:
    ui->widget->xAxis->setRange(0, t_max);
    ui->widget->yAxis->setRange(0, ymax);
    ui->widget->replot();
}
