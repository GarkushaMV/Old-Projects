#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QGraphicsView>
#include <QPaintEvent>
#include <QBuffer>
#include <QFile>

namespace Ui {
    class QPaintWidget;
}

class QPaintWidget : public QWidget
{
    Q_OBJECT
public:
    QPaintWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    char conmat[100][100];
    int vertex;
public slots:
    void saveToFile(const QString& filePath);
};

#endif // QPAINTWIDGET_H
