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

private:
    Ui::out *ui;
};

#endif // OUT_H
