#ifndef CALCULATION_H
#define CALCULATION_H

#include <QMainWindow>

namespace Ui {
class Calculation;
}

class Calculation : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculation(QWidget *parent = 0);
    ~Calculation();

private slots:

    void calc();

    void on_K1_valueChanged(double arg1);

    void on_K2_valueChanged(double arg1);

    void on_K3_valueChanged(double arg1);

    void on_H_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_A0_valueChanged(double arg1);

    void on_C0_valueChanged(double arg1);

    void on_B0_valueChanged(double arg1);

    void on_D0_valueChanged(double arg1);

    void on_T_valueChanged(double arg1);

    void on_t_max_valueChanged(double arg1);

    void on_graph_clicked();

private:
    Ui::Calculation *ui;
};

#endif // CALCULATION_H
