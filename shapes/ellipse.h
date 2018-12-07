#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "ishape.h"

class Ellipse : public IShape
{
public:
    Ellipse();


    virtual void draw(QPainter &painter);
    virtual bool contains(const QPoint& p);

};

#endif // ELLIPSE_H
