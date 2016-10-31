#ifndef FUNCTION_H
#define FUNCTION_H

#include <QString>
#include <QPoint>
#include <cmath>

double f_func(double x, double y, double t)
{
    //here is x' = f(x, y, t), you may change f(x, y, t) as you wish (in return .......;)
    return sin(t * 0.1) * t * 0.1;
}

double g_func(double x, double y, double t)
{
    //here is x' = g(x, y, t), you may change g(x, y, t) as you wish (in return .......;)
    return cos(t * 0.1) * t * 0.1;
}

#endif // FUNCTION_H

