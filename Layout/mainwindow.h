#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_comboBox_currentIndexChanged(int index);

private slots:
    void on_spinBox_editingFinished();
    
    void on_fontComboBox_currentTextChanged(const QString &arg1);
    
    void on_SwitchText_activated(const QString &arg1);
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
