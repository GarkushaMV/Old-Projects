QT += widgets
QT += opengl

HEADERS = \
    PaintWidget.h \
    PaintWindow.h
SOURCES = \
    PaintWidget.cpp \
    PaintWindow.cpp \
    main.cpp

#install
target.path = /home/immo/prog7
INSTALLS += target

RESOURCES += \
    prog.qrc
