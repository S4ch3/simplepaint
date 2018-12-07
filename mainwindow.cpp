#include <QPaintEvent>
#include <QPainter>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shapes/rectangle.h"
#include "shapes/ellipse.h"
#include "shapes/triangle.h"
#include "shapes/ishape.h"
#include "QDebug"
#include <QFileDialog>
#include <QFile>
#include <QDataStream>
#include <iostream>
#include <QColorDialog>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    m_curShape(NULL)

{
    ui->setupUi(this);
    connect(ui->m_btnSave, SIGNAL(clicked()), this, SLOT(onBtnSaveClicked()));
    connect(ui->m_btnRestore, SIGNAL(clicked()), this, SLOT(onBtnRestoreClicked()));

    connect(ui->m_btnBorderColor, SIGNAL(clicked()), this, SLOT(onBtnBorderColorClicked()));
    connect(ui->m_btnFillColor, SIGNAL(clicked()), this, SLOT(onBtnFillColorClicked()));

    connect(ui->m_penWidth, SIGNAL(editingFinished()), this, SLOT(onPenWEditingFinished()));

    connect(ui->m_btnDelete, SIGNAL(clicked()), this, SLOT(onBtnDeleteClicked()));

    //    IShape* ptr = new Rectangle;
    //    ptr->setRect (QRect(150,15,25,50));
    //    m_shapes.append(ptr);

    //    ptr = new Ellipse();
    //    ptr->setRect(QRect(70, 80,100,200));
    //    m_shapes.append(ptr);


    //    ptr = new Triangle();
    //    ptr->setRect(QRect(20,30,100,200));
    //    m_shapes.append(ptr);

}

MainWindow::~MainWindow()
{
    delete ui;
    qDeleteAll(m_shapes);
}

void MainWindow::paintEvent(QPaintEvent *e)
{

    QPainter painter(this);
    // IShape* shape = NULL;
    painter.setPen(Qt::white);
    painter.fillRect(e->rect(), (Qt::white));

    for(int i =0; i<m_shapes.size(); ++i)
        m_shapes.at(i)->drawShape(painter);
    if(m_curShape != NULL)
        m_curShape->drawShape(painter);


    // painter.drawRect(m_rect);

    QWidget::paintEvent(e);
}

void MainWindow::mousePressEvent (QMouseEvent* e)
{
    m_rect.setTopLeft(e->pos());
    switch(ui->m_shapesType->currentIndex())
    {
    case 0:
    {
        handleSelection(e);
        break;
    }

    case 1:
        m_curShape = new Rectangle;
        break;
    case 2:
        m_curShape = new Triangle;
        break;
    case 3:
        m_curShape = new Ellipse;
        break;

    }

    QWidget::mousePressEvent(e);
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    m_rect.setBottomRight(e->pos());
    if(m_curShape != NULL)
        m_curShape->setRect(m_rect);
    update();
    QWidget::mouseMoveEvent(e);
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_curShape != NULL)
    {

        m_shapes.append(m_curShape);
        m_curShape = NULL;
        QWidget::mouseReleaseEvent(e);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{

    bool isCtrlPressed = (e->modifiers() == Qt::ControlModifier);

    switch(e->key())
    {
    case Qt::Key_Minus:
        if(isCtrlPressed)
            scaleSelected(-0.1);
        break;

    case Qt::Key_Equal:
        if(isCtrlPressed)
            scaleSelected(0.1);
        break;

    case Qt::Key_Z:
        rotateSelected(-5.0);
    break;

    case Qt::Key_X:
        rotateSelected(5.0);
    break;

     case Qt::Key_Left:
        moveSelected(QPoint(-5.0, 0));
    break;

    case Qt::Key_Right:
        moveSelected(QPoint(5.0, 0));
        break;

    case Qt::Key_Up:
        moveSelected(QPoint(0,-5.0));
        break;

    case Qt::Key_Down:
        moveSelected(QPoint(0,5.0));
        break;
    }

    QWidget::keyPressEvent(e);
}

IShape* MainWindow::getShapeUnderCursor(const QPoint& pnt)
{
    IShape* found = NULL;
    for (int i = m_shapes.size() -1; i >=0; --i)
    {
        found = m_shapes[i];
        if(found->contains(pnt))
            return found;
    }
    return NULL;
}

void MainWindow::handleSelection(QMouseEvent *e)
{
    setFocus();
    bool isCtrlPressed = e->modifiers() == Qt::ControlModifier;
    IShape* selected = getShapeUnderCursor(e->pos());
    if(selected == NULL)
    {
        clearSelection();
        update();
        return;
    }
    if(! isCtrlPressed)
    {



        if(! selected->getSelected())
        {
            clearSelection();
            selected->setSelected(true);
            m_selected.append(selected);
        }
        else
        {
            clearSelection();
        }
        update();
    }
    else
    {
        if(! selected->getSelected())
        {
            selected->setSelected(true);
            m_selected.append(selected);
        }
        else
        {
            selected->setSelected(false);
            m_selected.removeAll(selected);
        }
    }
    update();
}
void MainWindow::clearSelection()
{
    for (int i = 0; i < m_selected.size(); ++i)
    {
        m_selected.at(i)->setSelected(false);
    }
    m_selected.clear();
}
void MainWindow::rotateSelected(double step)
{
    IShape* shape = NULL;
    for(int i = 0; i < m_selected.size(); ++i)
    {
        shape = m_selected.at(i);
        shape->setAngle(shape->getAngle() + step);
    }
    update();
}

void MainWindow::moveSelected(const QPoint& offset)
{
    IShape* shape = NULL;

    for(int i = 0; i < m_selected.size(); ++i)
    {
        shape = m_selected.at(i);
        shape->setRect(shape->getRect().translated(offset));
    }
    update();
}

void MainWindow::scaleSelected(double step)
{
    IShape* shape = NULL;

    for(int i = 0; i < m_selected.size(); ++i)
    {
        shape = m_selected.at(i);
        shape->setScaleF(shape->getScaleF() + step);
    }
    update();
}

void MainWindow::onBtnSaveClicked()
{

    QString name = QFileDialog::getSaveFileName();
    QFile file(name);
    if(! file.open(QFile::WriteOnly))
        return;
        QDataStream out (&file);

        IShape* shape = NULL;

    for(int i = 0; i < m_shapes.size(); ++i)
    {

       shape = m_shapes.at(i);
        out << (qint32)shape -> getType();
        out <<shape->getRect();
        out <<shape->getFillColor();
        out <<shape->getBorderColor();
        out <<(qint32)shape->getPenW();
        out <<shape->getSelected();
        out <<(qreal)shape->getAngle();
        out <<(qreal)shape->getScaleF();


        file.write("\n");

//        file.write(QByteArray::number(r.left()));
//        file.write(",");

//        QRect r = shape->getRect();
//        file.write(QByteArray::number(r.right()));
//        file.write(",");

//        file.write(QByteArray::number(r.bottom()));
//        file.write(",");

//        file.write(QByteArray::number(r.right()));
//        file.write(",");

//                // serializaciq - tyrsi To.String;

  }
        file.close();

}

void MainWindow::onBtnRestoreClicked()
{
    QString name = QFileDialog::getOpenFileName();
    QFile file(name);
    if(! file.open(QFile::ReadOnly))
        return;
    IShape* shape = NULL;

    QByteArray fileContents = file.readAll();
    QList <QByteArray> rows = fileContents.split('\n');



    file.close();

    QByteArray item;

    qint32 type = -1;
    QRect rect;
    QColor color;
    qint32 penW = -1;
    bool select = false;
    qreal angle = 0.0;
    qreal scale = 0;

    for(int i=0; i < rows.size(); ++i)
    {
        item = rows.at(i);
        if(item.isEmpty())
            continue;

        QDataStream in (item);

        in >> type;

        switch(type)
        {
        case 1:
            shape = new Rectangle;
            break;
        case 2:
            shape = new Triangle;
            break;
        case 3:
            shape = new Ellipse;
            break;
        }
        in >> rect;
        shape->setRect(rect);

        in >> color;
        shape->setFillColor(color);

        in >> color;
        shape->setBorderColor(color);

        in >> penW;
        shape->setPenW(penW);

        in >> select;
        shape->setSelected(select);

        in >> angle;
        shape->setAngle(angle);

        in >> scale;
        shape->setScaleF(scale);

        m_shapes.append(shape);


    }
    update();
}
void MainWindow::onBtnBorderColorClicked()
{
    QColor color = QColorDialog::getColor();

    if(!color.isValid())
        return;

    IShape* shape = NULL;
    for (int i=0; i < m_selected.size(); ++i)
    {
        shape = m_selected.at(i);
        shape->setBorderColor(color);
    }
    update();
}

void MainWindow::onBtnFillColorClicked()
{
    QColor color = QColorDialog::getColor();

    if(!color.isValid())
        return;
    IShape* shape = NULL;
    for (int i=0; i < m_selected.size(); ++i)
    {
        shape = m_selected.at(i);
        shape->setFillColor(color);
    }
    update();
}

void MainWindow::onPenWEditingFinished()
{
    IShape* shape = NULL;
    int penW = ui->m_penWidth->value();
    for (int i=0; i < m_selected.size(); ++i)
    {
        shape = m_selected.at(i);
        shape->setPenW(penW);
    }
    update();

}

void MainWindow::onBtnDeleteClicked()
{
    IShape* shape = NULL;
    for (int i =0; i < m_selected.size(); ++i)
    {
        shape = m_selected.at(i);
        m_shapes.removeAll(shape);
        delete shape;
    }
    m_selected.clear();
    update();
}
