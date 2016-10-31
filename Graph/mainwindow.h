#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QButtonGroup>
#include <QMenu>
#include <QMenuBar>
#include <QString>
#include <QColor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_SavingGraph_clicked();

    void on_RefreshGraph_clicked();

    void on_graphicsView_sendSaveFilePath(const QString &);

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
