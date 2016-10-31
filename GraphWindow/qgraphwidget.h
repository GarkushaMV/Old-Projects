#ifndef QGRAPHWIDGET_H
#define QGRAPHWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include <QPoint>
#include <QColor>
#include <QPainter>
#include <QTimer>
#include <QString>


class QGraphWindow;

class QGraphWidget : public QGLWidget
{
public:
    QGraphWidget( QWidget* parent = 0 );
    ~QGraphWidget();
    void putPixel( int x, int y, const QColor& c );
public slots:
    void saveToFile( const QString& filePath );
protected:
    void initializeGL();
    void paintGL();
};

#endif // QGRAPHWIDGET_H
