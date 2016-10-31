
#include "PaintWidget.h"
#include "PaintWindow.h"

#include <QMouseEvent>
#include <QPoint>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QTimer>
#include <QString>

#include <cstdio>
using std::fwrite;
#include <cmath>
using std::abs;
using std::pow;
using std::sqrt;
using std::atan2;
using std::sin;
using std::cos;
#include <cstdlib>
using std::srand;
using std::rand;
#include <cstring>
using std::memset;
#include <ctime>

#include <GL/glu.h>

#define PIX_COMPONENTS 3

typedef struct bmpInfoHeader{
    unsigned long infoHeaderSize; 		//40
    long width; 						//500
    long height; 						//500
    unsigned short nPlanes; 			//1
    unsigned short colorDepth; 			//24
    unsigned long compressionMethod; 	//0
    unsigned long imageSize; 			//500 * 500 * 3
    long hResolution;					//0
    long vResolution;					//0
    unsigned long nColors;				//0
    unsigned long nImportantColors;		//0
}bmpInfoHeader;

typedef struct bmpHeader{
    short signature;
    int fileSize;
    int reservedField;
    int offset;
}bmpHeader;

typedef struct PixelInfo{
    unsigned char info[PIX_COMPONENTS];

    bool operator==( PixelInfo& p ){
        return ( info[0] == p.info[0] && info[1] == p.info[1] && info[2] == p.info[2] );
    }

    bool operator!=( PixelInfo& p ){
        return !( *this == p );
    }

}PixelInfo;

PaintWidget::PaintWidget( QWidget* parent ) : QGLWidget( parent ), clickPoint( 0, 0 ), curPoint( 0, 0 ), lowPoint( 0, 0 ),
    color( 0, 0, 0 ), bgColor( 255, 255, 255 ){

    width_ = PaintWindow::width();
    height_ = PaintWindow::height();
    rowSize_ = width_ * 3;
    rWidth = 0;
    rHeight = 0;
    while( rowSize_ % 4 != 0 ){
        rowSize_++;
    }
    setMinimumSize( width_, height_ );
    srand( std::time( 0 ) );
    firstDone = false;
    pencilActive = false;
    eraserActive = false;
    sprayActive = false;
    correctClick = false;
    recentlyCleared = false;
    nClicks = 0;
    polygonAngle = 0.0;
    selectedTool_ = PaintWindow::Line;
    pixelInfo = new PixelInfo[ width_ * height_ ];
    tempInfo = 0;
    bufferInfo = 0;
    splinePoints = new QPoint[4];
    timer = new QTimer( this );
    connect( timer, SIGNAL( timeout() ), this, SLOT( updateGL() ) );
}

PaintWidget::~PaintWidget(){
    if( pixelInfo != 0 ){
        delete[] pixelInfo;
    }
    if( splinePoints != 0 ){
        delete[] splinePoints;
    }
    if( tempInfo != 0 ){
        delete[] tempInfo;
    }
}

int PaintWidget::selectedTool() const{
    return selectedTool_;
}

void PaintWidget::setSelectedTool( int t ){
    selectedTool_ = t;
    nClicks = 0;
}

int PaintWidget::nSides() const{
    return nSides_;
}

void PaintWidget::setNSides( int n ){
    nSides_ = n;
}

int PaintWidget::width() const{
    return width_;
}

int PaintWidget::height() const{
    return height_;
}

int PaintWidget::rowSize() const{
    return rowSize_;
}

void PaintWidget::setWidth( int w ){
    width_ = w;
}

void PaintWidget::setHeight( int h ){
    height_ = h;
}

void PaintWidget::setRowSize( int r ){
    rowSize_ = r;
    while( rowSize_ % 4 != 0 ){
        rowSize_++;
    }
}

void PaintWidget::setColor( const QColor& c ){
    color = c;
}

void PaintWidget::putPixel( int x, int y, const QColor& c ){
    glColor3f( c.red() / 255.0, c.green() / 255.0, c.blue() / 255.0 );
    glBegin( GL_POINTS );
    glVertex2i( x, y );
    glEnd();
}

void PaintWidget::drawLine( int x1, int y1, int x2, int y2 ){
    int dx = abs( x2 - x1 );
    int dy = abs( y2 - y1 );
    int p;
    int x, y;
    int addX = ( x1 < x2 )? 1 : ( x1 > x2 )? -1 : 0;
    int addY = ( y1 < y2 )? 1 : ( y1 > y2 )? -1 : 0;

    x = x1;
    y = y1;
    if( dx >= dy ){
        p = 2 * dy - dx;
        putPixel( x, y, color );
        while( x != x2 ){
            x += addX;
            if( p < 0 ){
                p += 2 * dy;
            }
            else{
                y += addY;
                p += 2 * ( dy - dx );
            }
            putPixel( x, y, color );
        }
    }
    else{
        p = 2 * dx - dy;
        putPixel( x, y, color );
        while( y != y2 ){
            y += addY;
            if( p < 0 ){
                p += 2 * dx;
            }
            else{
                x += addX;
                p += 2 * ( dx - dy );
            }
            putPixel( x, y, color );
        }
    }
}

void PaintWidget::drawEllipse( int xC, int yC, int rX, int rY ){
    long long x, y;
    long long rX2 = ( rX * rX );
    long long rY2 = ( rY * rY );
    long long p = ceil( rY2 - rX2 * rY + rX2 * 0.25 );
    long long auxX, auxY;

    x = 0;
    y = rY;
    putEllipsePixels( x, y, xC, yC );
    auxX = 0;
    auxY = 2 * rX2 * y;
    while( auxX < auxY ){
        x++;
        auxX = 2 * rY2 * x;
        if( p < 0 ){
            p += auxX + rY2;
        }
        else{
            y--;
            auxY = 2 * rX2 * y;
            p += auxX - auxY + rY2;
        }
        putEllipsePixels( x, y, xC, yC );
    }

    p = ceil( rY2 * ( ( x + 0.5 ) * ( x + 0.5 ) ) + rX2 * ( ( y - 1 ) * ( y - 1 ) ) - rX2 * rY2 );
    while( y > 0 ){
        y--;
        auxY = 2 * rX2 * y;
        if( p > 0 ){
            p += -auxY + rX2;
        }
        else{
            x++;
            auxX = 2 * rY2 * x;
            p += auxX - auxY + rX2;
        }
        putEllipsePixels( x, y, xC, yC );
    }
}

void PaintWidget::clear(){
    glClearColor( 1, 1, 1, 0.0 );
    glClear( GL_COLOR_BUFFER_BIT );
    glReadPixels( 0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, pixelInfo );
    emit resetFilePath();
    recentlyCleared = true;
    updateGL();
}

void PaintWidget::saveToFile( const QString& filePath ){
    FILE* file;
    bmpHeader h1;
    bmpInfoHeader h2;
    PixelInfo* bitmap;

    file = fopen( filePath.toStdString().c_str(), "wb" );
    if( file != NULL ){
        bitmap = new PixelInfo[ rowSize_ * height_ ];
        glPixelStorei( GL_PACK_ALIGNMENT, 4 );
        glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
        glReadPixels( 0, 0, width_, height_, GL_BGR, GL_UNSIGNED_BYTE, bitmap );
        glPixelStorei( GL_PACK_ALIGNMENT, 1 );
        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

        h2.infoHeaderSize = sizeof(bmpInfoHeader);
        h2.width = width_;
        h2.height = height_;
        h2.nPlanes = 1;
        h2.colorDepth = 24;
        h2.compressionMethod = 0;
        h2.imageSize = width_ * 3;
        h2.imageSize *= height_;
        while( h2.imageSize % 4 != 0 ){
            h2.imageSize++;
        }
        h2.hResolution = 0;
        h2.vResolution = 0;
        h2.nColors = 0;
        h2.nImportantColors = 0;

        h1.signature = 0x4D42;
        h1.fileSize = sizeof(bmpHeader) + sizeof( bmpInfoHeader ) + h2.imageSize;
        h1.reservedField = 0;
        h1.offset = sizeof(bmpHeader) + sizeof( bmpInfoHeader );

        fwrite( &h1.signature, sizeof( short ), 1, file );
        fwrite( &h1.fileSize, sizeof( int ), 1, file );
        fwrite( &h1.reservedField, sizeof( int ), 1, file );
        fwrite( &h1.offset, sizeof( int ), 1, file );
        fwrite( &h2, sizeof( bmpInfoHeader ), 1, file );
        fwrite( bitmap, h2.imageSize, 1, file );

        fclose( file );
        delete bitmap;
    }
}

void PaintWidget::initializeGL(){
    if( !firstDone ){
        glClearColor( 1, 1, 1, 0.0 );
        glMatrixMode( GL_PROJECTION );
        glClear( GL_COLOR_BUFFER_BIT );
        glPixelStorei( GL_PACK_ALIGNMENT, 1 );
        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    }
    else{
        glDrawPixels( width_, height_, GL_RGB, GL_UNSIGNED_BYTE, pixelInfo );
    }
}

void PaintWidget::paintGL(){
    if( firstDone ){
        if( !pencilActive && !eraserActive && !sprayActive ){
            painter.begin( this );
            painter.beginNativePainting();
            glDrawPixels( width_, height_, GL_RGB, GL_UNSIGNED_BYTE, pixelInfo );
        }
        if( !recentlyCleared ){
            switch( selectedTool_ ){
                case PaintWindow::Line:
                    drawLine( clickPoint.x(), clickPoint.y(), curPoint.x(), curPoint.y() );
                    break;
                case PaintWindow::Ellipse:
                    drawEllipse( clickPoint.x(), clickPoint.y(), rx, ry );
                    break;
                case PaintWindow::Pencil:
                    drawLine( clickPoint.x(), clickPoint.y(), curPoint.x(), curPoint.y() );
                    clickPoint.setX( curPoint.x() );
                    clickPoint.setY( curPoint.y() );
                    pencilActive = true;
                    break;
            }
        }
        else{
            recentlyCleared = false;
        }
        if( !pencilActive && !eraserActive && !sprayActive ){
            glFlush();
            painter.endNativePainting();
            painter.end();
        }
    }
}

void PaintWidget::mousePressEvent( QMouseEvent* event ){
    if( event -> button() == Qt::LeftButton ){
        clicked = true;
        firstDone = true;
        clickPoint.setX( event -> x() );
        clickPoint.setY( event -> y() );
        switch( selectedTool_ ){
            case PaintWindow::Pencil:
                glReadPixels( 0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, pixelInfo );
                curPoint.setX( event -> x() );
                curPoint.setY( event -> y() );
                updateGL();
                break;
            default:
                glReadPixels( 0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, pixelInfo );
                break;
        }
    }
}

void PaintWidget::mouseReleaseEvent( QMouseEvent* event ){
    if( event -> button() == Qt::LeftButton ){
        clicked = false;
        switch( selectedTool_ ){
            case PaintWindow::Pencil:
                pencilActive = false;
                glFlush();
                painter.endNativePainting();
                painter.end();
                glReadPixels( 0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, pixelInfo );
                break;
            default:
                glReadPixels( 0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, pixelInfo );
                break;
        }
    }
}

void PaintWidget::mouseMoveEvent( QMouseEvent* event ){
    curPoint.setX( event -> x() );
    curPoint.setY( event -> y() );
    switch( selectedTool_ ){
        case PaintWindow::Ellipse:
            rx = abs( clickPoint.x() - curPoint.x() );
            ry = abs( clickPoint.y() - curPoint.y() );
            break;
    }
    updateGL();
}

void PaintWidget::paintEvent( QPaintEvent*  ){
    painter.begin( this );
    painter.beginNativePainting();
    glInit();
    painter.endNativePainting();
    painter.end();
}

void PaintWidget::putEllipsePixels( int x, int y, int xC, int yC ){
    putPixel( x + xC, y + yC, color );
    putPixel( x + xC, -y + yC, color );
    putPixel( -x + xC, -y + yC, color );
    putPixel( -x + xC, y + yC, color );
}


bool PaintWidget::checkPoint( int x, int y, int lx1, int ly1, int lx2, int ly2 ){
    return ( x > lx1 && x < lx2 && y > ly2 && y < ly1 );
}

void PaintWidget::glWindowPos4fMESAemulate( GLfloat x, GLfloat y, GLfloat z, GLfloat w ){
    GLfloat fx, fy;
    glPushAttrib( GL_TRANSFORM_BIT | GL_VIEWPORT_BIT );
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
    glDepthRange( z, z );
    glViewport( (int)x - 1, (int)y - 1, 2, 2);
    fx = x - (int) x;
    fy = y - (int) y;
    glRasterPos4f(fx, fy, 0.0, w);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

void PaintWidget::glWindowPos2fMESAemulate( GLfloat x, GLfloat y ){
    glWindowPos4fMESAemulate(x, y, 0, 1);
}
