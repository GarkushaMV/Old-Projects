#ifndef OUT_H
#define OUT_H

#include <QMainWindow>

namespace Ui {
class out;
}

class out : public QMainWindow
{
    Q_OBJECT

public:
    explicit out(QWidget *parent = 0);
    ~out();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_spinBox_valueChanged(int arg1);

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::out *ui;
};

#endif // OUT_H
