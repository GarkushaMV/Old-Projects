#ifndef PAINT_WIDGET_H
#define PAINT_WIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include <QPoint>
#include <QColor>
#include <QPainter>
#include <QTimer>
#include <QString>

class PaintWindow;
struct PixelInfo;

class PaintWidget : public QGLWidget{
    Q_OBJECT

    public:
        PaintWidget( QWidget* parent = 0 );
        ~PaintWidget();
        int selectedTool() const;
        int nSides() const;
        int width() const;
        int height() const;
        int rowSize() const;
        void setWidth( int w );
        void setHeight( int h );
        void setRowSize( int r );
        void putPixel( int x, int y, const QColor& c );
        void drawLine( int x1, int y1, int x2, int y2 );
        void drawEllipse( int xC, int yC, int rX, int rY );

    public slots:
        void setSelectedTool( int t );
        void setNSides( int n );
        void setColor( const QColor& c );
        void clear();
        void saveToFile( const QString& filePath );

    protected:
        void initializeGL();
        void paintGL();
        void mousePressEvent( QMouseEvent* event );
        void mouseReleaseEvent( QMouseEvent* event );
        void mouseMoveEvent( QMouseEvent* event );
        void paintEvent( QPaintEvent* event );

    private:
        int selectedTool_;
        int nSides_;
        int width_;
        int height_;
        int rowSize_;
        int rWidth;
        int rHeight;
        int radius;
        int rx;
        int ry;
        int nClicks;
        double polygonAngle;
        bool firstDone;
        bool pencilActive;
        bool eraserActive;
        bool sprayActive;
        bool clicked;
        bool correctClick;
        bool recentlyCleared;
        PixelInfo* pixelInfo;
        PixelInfo* tempInfo;
        PixelInfo* bufferInfo;
        QPoint clickPoint;
        QPoint curPoint;
        QPoint lowPoint;
        QPoint* splinePoints;
        QColor color;
        QColor bgColor;
        QPainter painter;
        QTimer* timer;

        void putEllipsePixels( int x, int y, int xC, int yC );
        bool checkPoint( int x, int y, int x1, int y1, int x2, int y2 );

        void glWindowPos4fMESAemulate( GLfloat x, GLfloat y, GLfloat z, GLfloat w );
        void glWindowPos2fMESAemulate( GLfloat x, GLfloat y );

    signals:
        void resetFilePath();
};

#endif //PAINT_WIDGET_H
