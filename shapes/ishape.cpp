

#include <QDebug>
#include "ishape.h"


IShape::IShape() :
    m_penW(2),
    m_isSelected(false),
    m_fillColor(Qt::transparent),
    m_borderColor(Qt::blue),
    m_angle(0.0),
    m_scaleF(1.0)
{
}

IShape::~IShape()
{
}
void IShape::drawShape(QPainter &painter)
{
    painter.save();
    initPainter(painter);
    transformPainter(painter);
    QRect r = m_rect;
    m_rect.moveCenter(QPoint(0,0));

    draw(painter);
    m_rect = r;
    painter.restore();
}

void IShape::initPainter(QPainter & painter)
{
    if(m_isSelected)
    {
        painter.setBrush(Qt::transparent);
        painter.setPen(QPen(Qt::black, m_penW, Qt::DashDotLine ));
    }
    else
    {
    painter.setBrush(m_fillColor);
    painter.setPen(QPen(m_borderColor, m_penW));
    }
}

void IShape::transformPainter(QPainter& painter)
{

   painter.translate(m_rect.center());
   painter.rotate(m_angle);
   painter.scale(m_scaleF, m_scaleF);
}
