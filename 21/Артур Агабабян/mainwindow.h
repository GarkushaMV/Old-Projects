#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QSlider>
#include <QApplication>
#include "mylabel.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyLabel *imageLabel;
    QWidget *allPanels;
    QLayout *layout;
    QLabel *rightPanel;
    QSlider *slider;
};

#endif // MAINWINDOW_H
