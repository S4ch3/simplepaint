#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <Qlist>

namespace Ui {
class MainWindow;
}
class IShape;
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent* e);

private:
    IShape* getShapeUnderCursor(const QPoint& pnt);
    Ui::MainWindow *ui;
    QList<IShape*> m_shapes;
    QRect m_rect;
    IShape* m_curShape;
    QList<IShape*> m_selected;
    void handleSelection(QMouseEvent* e);
    void clearSelection();
    void rotateSelected(double step);
    void moveSelected(const QPoint& offset);
    void scaleSelected(double step);

private slots:
    void onBtnSaveClicked();
    void onBtnRestoreClicked();

    void onBtnBorderColorClicked();
    void onBtnFillColorClicked();

    void onPenWEditingFinished();
    void onBtnDeleteClicked();

};

#endif // MAINWINDOW_H
