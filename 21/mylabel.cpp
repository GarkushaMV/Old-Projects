#include "mylabel.h"
#include "function.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>

MyLabel::MyLabel(QWidget *parent) :
    QLabel(parent)
{
    startPoint = QPoint(width()/2, height()/2);
    maxTime = 1;
}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
    startPoint = event->pos();
    update();
}

void MyLabel::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::white);
    painter.setBrush(QBrush(QColor(255, 255, 255)));
    painter.drawRect(0, 0, width(), height());

    painter.setPen(QPen(QBrush(QColor(128, 0, 0)), 1));
    painter.setBrush(QBrush(QColor(128, 0, 0)));
    painter.drawEllipse(startPoint, 5, 5);

    QPointF last, cur;
    last = startPoint;

    painter.setPen(QPen(QBrush(QColor(0, 128, 0)), 1));

    for(int t = 0; t < maxTime; t++)
    {
        cur = last + QPointF((f_func(last.x(), last.y(), t)), (g_func(last.x(), last.y(), t)) );
        painter.drawLine(last, cur);
        last = cur;
    }
}

void MyLabel::setMaxTime(int t)
{
    maxTime = t;
    update();
}

