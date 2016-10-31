#ifndef EXPLORER_H
#define EXPLORER_H

#include <QMainWindow>

namespace Ui {
class Explorer;
}

class Explorer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Explorer(QWidget *parent = 0);
    ~Explorer();

private:
    Ui::Explorer *ui;
};

#endif // EXPLORER_H
