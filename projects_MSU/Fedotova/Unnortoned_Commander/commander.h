#ifndef COMMANDER_H
#define COMMANDER_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QDir>
#include <QFileIconProvider>
#include <QIcon>
#include <QFile>
#include <iostream>
#include <QMessageBox>


namespace Ui {
class Commander;
}

class Commander : public QMainWindow
{
    Q_OBJECT

public:
    explicit Commander(QWidget *parent = 0);
    ~Commander();
    char activity;
    QFileInfo* FInf;
    QIcon* Ic;
    QFileIconProvider* provider;
    QDir direct_1;
    QDir direct_2;

private slots:

    void on_CopyButton_clicked();

    void on_DeleteButton_clicked();

    void on_Loc_1_returnPressed();

    void on_Loc_2_returnPressed();

    void on_Dir_1_itemDoubleClicked(QListWidgetItem *item);

    void on_Dir_2_itemDoubleClicked(QListWidgetItem *item);

    void on_Dir_1_activated(const QModelIndex &index);

    void on_Dir_2_activated(const QModelIndex &index);

    void on_Dir_1_itemClicked(QListWidgetItem *item);

    void on_Dir_2_itemClicked(QListWidgetItem *item);

private:
    Ui::Commander *ui;
};

#endif // COMMANDER_H
