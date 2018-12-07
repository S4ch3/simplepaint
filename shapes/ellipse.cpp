#include "ellipse.h"
#include <QRegion>
Ellipse::Ellipse()
{
   m_borderColor = Qt::yellow;
   m_fillColor = Qt::green;
    m_type = 1;
}

void Ellipse::draw(QPainter &painter)
{

//    drawBoundings(painter);
    painter.drawEllipse(m_rect);
}

bool Ellipse::contains(const QPoint &p)
{
    QRegion region(m_rect, QRegion::Ellipse);
    return region.contains(p);
}
