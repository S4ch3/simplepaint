#include "triangle.h"
#include "ishape.h"

Triangle::Triangle()
{
    m_borderColor = Qt::green;
    m_fillColor = Qt::red;
    m_type = 2;
}

void Triangle::draw(QPainter &painter)
{
    painter.save();
    initPainter(painter);
    //drawBoundings(painter);
//   m_polygon << QPoint(0,85) << QPoint(75,75)
//            << QPoint(100,10)<< QPoint(125,75);

//QPointF points[3] = {m_rect.topLeft(), (m_rect.bottomLeft() + m_rect.bottomRight())/2 , m_rect.topRight()};
//    painter.drawPolygon(points, 3);
//    painter.restore();
    painter.drawPolygon(getPolygon());
    painter.restore();
}
QPolygon Triangle::getPolygon() const
{
    QPolygon polygon;
    QPoint top;
   top.setY(m_rect.top());
   top.setX(m_rect.center().x());
   polygon << m_rect.bottomLeft()<<m_rect.bottomRight()<<top;
        return polygon;
}

bool Triangle::contains(const QPoint& p)
{

    return getPolygon().containsPoint(p, Qt::OddEvenFill);
}
