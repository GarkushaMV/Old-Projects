#include "qpaintwidget.h"
#include "dialog.h"
#include <iostream>
#include <cmath>
#include <set>
#include <time.h>

QPaintWidget::QPaintWidget(QWidget * parent) : QWidget(parent)
{
    vertex = 0;
    for(int i=0; i < 100; i++)
        for(int j=0; j<100; j++)
            conmat[i][j] = 0;
}

/*void QPaintWidget::paintLineLeft(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(QPen(Qt::red,1,Qt::SolidLine));
    p.drawLine(0,0,width(),height());
}*/

void QPaintWidget::paintEvent(QPaintEvent * )
{
    QPainter p(this);
    qsrand (10);
    p.fillRect(0,0,width(), height(), Qt::white);
    p.setPen(QPen(QPen(QBrush(Qt::black, Qt::SolidPattern), 12, Qt::SolidLine, Qt::RoundCap)));
    if(vertex == 1)
    {
        p.drawPoint(width()/2, height()/2);
    }
    else if (vertex > 1)
    {
        int dots[vertex][2];
        for(int i = 0; i < vertex; i++)
        {
            dots[i][0] = (width() - 12) * (1 + std::sin(2* M_PI * i/vertex)) /2 + 6;
            dots[i][1] = (height() - 12) * (1 + std::cos(2* M_PI * i/vertex)) /2 + 6;
        }
       for(int i = 0; i < vertex; i++)
           p.drawPoint(dots[i][0], dots[i][1]);
        p.setPen(QPen(QPen(QBrush(Qt::black, Qt::SolidPattern), 1, Qt::SolidLine, Qt::RoundCap)));
        for(int h = 0, i = 0; i < 1000; i ++)
        {
            h = abs(std::rand())%vertex;
            std::srand(time(NULL));
            std::swap(dots[h], dots[0]);
        }
        for(int i = 0; i < vertex; i++)
            for(int j = i + 1; j< vertex; j++)
                if(conmat[i][j]!=0)
                    p.drawLine(dots[i][0], dots[i][1], dots[j][0], dots[j][1]);
    }

    p.end();
}

void QPaintWidget::saveToFile(const QString& filePath)
{
    QPixmap pixmap(size());
    render(&pixmap);
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::ReadWrite);
    pixmap.save(&buffer, "PNG");
    QFile file(filePath);
    file.resize(buffer.size());
    std::cout<<file.size();
    file.open(QIODevice::WriteOnly);
    file.write(bytes);
    file.close();
}
