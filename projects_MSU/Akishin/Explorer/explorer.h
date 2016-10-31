#ifndef EXPLORER_H
#define EXPLORER_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QDir>
#include <QFileIconProvider>
#include <QIcon>
#include <QFile>
#include <QLabel>
#include <QString>
#include <iostream>
#include <QMessageBox>

namespace Ui {
class Explorer;
}

class Explorer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Explorer(QWidget *parent = 0);
    ~Explorer();
    QString CopyBuff;
    QString CopyFileName;
    QFileInfo* FInf;
    QIcon* Ic;
    QFileIconProvider* provider;
    QDir direct;

private slots:
    void on_BackButton_clicked();

    void on_Dir_itemDoubleClicked(QListWidgetItem *item);

    void on_Loc_returnPressed();

    void CopyAction();

    void PasteAction();

    void DeleteAction();
private:
    Ui::Explorer *ui;
};

#endif // EXPLORER_H
