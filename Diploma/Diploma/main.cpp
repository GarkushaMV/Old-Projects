#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{

    QLocale curLocale(QLocale("Russia"));
    QLocale::setDefault(curLocale);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
