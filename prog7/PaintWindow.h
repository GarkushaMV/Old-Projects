#ifndef PAINT_WINDOW_H
#define PAINT_WINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QButtonGroup>
#include <QMenu>
#include <QMenuBar>
#include <QString>
#include <QColor>

class PaintWidget;

class PaintWindow : public QMainWindow{
    Q_OBJECT

    public:
        enum ToolNum{
            Line,
            Ellipse,
            Pencil
        };

        PaintWindow();
        static int width();
        static int height();
        static void setWidth( int w );
        static void setHeight( int h );

    public slots:
        void lineSelected();
        void ellipseSelected();
        void pencilSelected();
        void getSaveFilePath();
        void resetFilePath();
        void pickColor();

    private:
        QString lastFile;
        PaintWidget* paintWidget;
        QMenu* fileMenu;
        QMenu* toolMenu;
        QMenu* colorMenu;
        QToolBar* mainToolBar;
        QToolBar* colorToolBar;
        QToolButton* lineToolButton;
        QToolButton* ellipseToolButton;
        QToolButton* pencilToolButton;
        QAction* lineToolAction;
        QAction* ellipseToolAction;
        QAction* pencilToolAction;
        QAction* saveFileAs;
        QAction* pickColorAction;
        QButtonGroup* colorButtonGroup;
        static int width_;
        static int height_;

        void createMainToolBar();
        void createPolygonToolBar();

        void createFileMenu();
        void createToolMenu();
        void createPolygonMenu();

    signals:
        void changeTool( int );
        void changePolygonSides( int );
        void sendSaveFilePath( const QString& );
        void sendOpenFilePath( const QString& );
        void sendColor( const QColor& );
};

#endif //PAINT_WINDOW_H
