#include "qgraphwidget.h"
#include "graphwindow.h"

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


QGraphWidget::QGraphWidget(QWidget *parent) : QGLWidget( parent )
{

}

