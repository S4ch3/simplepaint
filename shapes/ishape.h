#ifndef ISHAPE_H
#define ISHAPE_H
#include <QRect>
#include <QColor>
#include <QPainter>




class IShape
{
public:
    IShape();


    virtual ~IShape();




    virtual bool contains(const QPoint& p) = 0;

    void drawShape(QPainter& painter);

//     void drawBoundings(QPainter& painter)
//    {
//        if( ! m_isSelected)
//            return;
//        painter.save();
//        painter.setPen( QPen( Qt::black, 1, Qt::DashDotLine ) );
//        painter.setBrush(Qt::transparent);
//        painter.drawRect(m_rect);
//        painter.restore();

//    }

    void setRect(const QRect& r);
    void setPolygon(const QPolygon& p);
    void setFillColor(const QColor& c);
    void setBorderColor(const QColor& c);
    void setPenW(int w);
    void setSelected(bool selected);
    void setAngle (double angle);
    double getAngle() const;
    void setScaleF(double f);
    double getScaleF() const;

    QRect getRect() const;
    int getType() const
{
    return m_type;
}

    QColor getFillColor() const;
    QColor getBorderColor()const;

    int getPenW() const;

    bool getSelected()const;

    protected:
        void initPainter(QPainter & painter);
        void transformPainter(QPainter& painter);
        virtual void draw( QPainter& painter) = 0;
//    {
//        if(m_isSelected)
//        {
//            painter.setBrush(Qt::transparent);
//            painter.setPen(QPen(Qt::black, m_penW, Qt::DashDotLine ));
//        }
//        else
//        {
//        painter.setBrush(m_fillColor);
//        painter.setPen(QPen(m_borderColor, m_penW));
//        }
//    }


    QPolygon m_polygon;
    QRect m_rect;
    QColor m_fillColor;
    QColor m_borderColor;
    int m_penW;
    bool m_isSelected;
    int m_type;
    double m_angle;
    double m_scaleF;

};


//QColor IShape::getFillColor() const;
//QColor IShape::getBorderColor()const;
//int IShape::getPenW(int w) const;
//bool IShape::getSelected(bool selected)const;

inline
void IShape::setPolygon(const QPolygon& p)
{
    m_polygon = p;
}

inline
void IShape::setRect(const QRect& r)
{
    m_rect = r;
}
inline
void IShape::setFillColor(const QColor& c)
{
    m_fillColor = c;
}
inline
void IShape::setBorderColor(const QColor& c)
{
    m_borderColor = c;
}
inline
void IShape::setPenW(int w)
{
    m_penW = w;
}
inline
void IShape::setSelected(bool selected)
{
    m_isSelected = selected;
}
inline
bool IShape::getSelected() const
{
    return m_isSelected;
}
inline
QRect IShape::getRect()const
{
    return m_rect;
}
inline
int IShape::getPenW() const
{
    return m_penW;
}
inline
QColor IShape::getFillColor() const
{
    return m_fillColor;
}
inline
QColor IShape::getBorderColor() const
{
    return m_borderColor;
}
inline
void IShape::setAngle (double angle)
{
    m_angle = angle;
}
inline
double IShape::getAngle() const
{
    return m_angle;
}
inline
void IShape::setScaleF(double f)
{
    m_scaleF = f;
}
inline
double IShape::getScaleF() const
{
    return m_scaleF;
}

#endif // ISHAPE_H
