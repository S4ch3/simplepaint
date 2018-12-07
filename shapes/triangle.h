#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "ishape.h"
#include <QPolygon>
class Triangle : public IShape
{
public:
    Triangle();

    virtual void draw(QPainter& painter);
    virtual bool contains(const QPoint& p);
    QPolygon getPolygon()const;
private:

};

#endif // TRIANGLE_H
