#include "out.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    out w;
    w.show();

    return a.exec();
}
