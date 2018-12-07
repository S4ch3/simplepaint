#include "rectangle.h"
#include "ishape.h"
Rectangle::Rectangle()
{
    m_borderColor = Qt::red;
    m_fillColor = Qt::cyan;
     m_type = 1;
}

void Rectangle::draw(QPainter &painter)
{


    painter.drawRect(m_rect);

   m_polygon << QPoint(0,85) << QPoint(75,75)
            << QPoint(100,10)<< QPoint(125,75);

QPointF points[3] = {m_rect.topLeft(), m_rect.bottomRight()};
QPointF points1[3] = {m_rect.center(), m_rect.topRight()};
    painter.drawPolygon(points, 3);
    painter.drawPolygon(points1, 3);
    painter.restore();
    //drawBoundings(painter);
//   m_polygon << QPoint(0,85) << QPoint(75,75)
//            << QPoint(100,10)<< QPoint(125,75);

//QPointF points[3] = {m_rect.topLeft(), (m_rect.bottomLeft() + m_rect.bottomRight())/2 , m_rect.topRight()};
//    painter.drawPolygon(points, 3);
//    painter.restore();

}

bool Rectangle::contains(const QPoint &p)
{
    return m_rect.contains(p);
}
