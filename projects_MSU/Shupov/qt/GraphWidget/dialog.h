#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>






namespace Ui {
     class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT
public:
    Dialog(Dialog *parent = 0);
    ~Dialog();
    int VertexNumber;
    int EdgesNumber;
    int ComponentNumber;
    int MaxDegreeNumber;
    int MinDegreeNumber;
private slots:
    void on_VertexNumberBox_valueChanged(int arg1);

    void on_EdgesNumberbox_valueChanged(int arg1);

    void on_ComponentNumberBox_valueChanged(int arg1);

    void on_MaxDegreeNumberBox_valueChanged(int arg1);

    void on_MinDegreeNumberBox_valueChanged(int arg1);

private:
    Ui::Dialog *Dui;
};

#endif // DIALOG_H
