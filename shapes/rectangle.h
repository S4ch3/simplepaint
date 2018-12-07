#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "ishape.h"


class Rectangle : public IShape
{
public:
    Rectangle();


    virtual void draw(QPainter &painter);
    virtual bool contains(const QPoint& p);
};

#endif // RECTANGLE_H
