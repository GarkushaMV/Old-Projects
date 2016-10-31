#include <QApplication>

#include "PaintWindow.h"

int main(int argc, char* argv[] ){
    QApplication app( argc, argv );
    PaintWindow window;

    window.setAttribute( Qt::WA_QuitOnClose );
    window.setFixedSize(window.width(), window.height());
    window.show();

    return app.exec();
}
