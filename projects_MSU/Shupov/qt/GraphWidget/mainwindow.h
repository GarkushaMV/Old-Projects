#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <vector>
#include "qpaintwidget.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_NewGrathButton_clicked();

    void on_SaveGrathButton_clicked();

private:
    Ui::MainWindow *ui;
signals:
    void sendSaveFilePath( const QString& );
};

#endif // MAINWINDOW_H
