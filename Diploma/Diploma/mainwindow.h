#include <QtCore>
#include <QtGui>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QLabel>
#include <QMainWindow>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QListWidgetItem>
#include <QLocale>
#include <QSqlTableModel>
#include <QTableView>
#include <QTextCodec>
#include <QChar>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <windows.h>
#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


namespace Ui {
class MainWindow;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_Layout_cellDoubleClicked(int row, int column);

    void on_CreateZAKAZ_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

public slots:
    void Galocka(QListWidgetItem  * item);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
