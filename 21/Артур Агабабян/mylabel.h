#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>


class MyLabel : public QLabel
{
    Q_OBJECT

private:
    int maxTime;
    QPoint startPoint;
protected:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
public:
    explicit MyLabel(QWidget *parent = 0);
signals:

public slots:
    void setMaxTime(int t);

};

#endif // MYLABEL_H
