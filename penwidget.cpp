#include "penwidget.h"
#include <QDebug>
#include <QPainter>
#include <algorithm>
#include <QTabletEvent>

PenWidget::PenWidget(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_AcceptTouchEvents, true);

    old_x = xpos = old_y = ypos = 0;

    pixmap = new QPixmap(size());
    pixmap->fill(qRgb(255,255,255));
}

PenWidget::~PenWidget()
{
    delete pixmap;
}

void PenWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), *pixmap);
}

void PenWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void PenWidget::mousePressEvent(QMouseEvent *event)
{
}

void PenWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //    old_x = 0;
    //    old_y = 0;
    //    repaint();
}

void PenWidget::resizeEvent(QResizeEvent *event)
{
    auto pm = new QPixmap(event->size());
    pm->fill(qRgb(255,255,255));
    QPainter painter(pm);
    painter.drawPixmap(pixmap->rect(), *pixmap, pixmap->rect());
    delete pixmap;
    pixmap = pm;
}

void PenWidget::tabletEvent(QTabletEvent *event)
{
    xpos = event->x();
    ypos = event->y();

    if(event->type() == QEvent::TabletPress) {
        old_x = xpos;
        old_y = ypos;
    }

//    if(old_x==0)
//        old_x = xpos;
//    if(old_y==0)
//        old_y = ypos;

    QPainter painter (pixmap);
    QPen pen (Qt::black);
    pen.setWidthF(event->pressure()*10);
    painter.setPen(pen);
    painter.drawLine(old_x, old_y, xpos, ypos);

    old_x = xpos;
    old_y = ypos;

    repaint();
}

bool PenWidget::event(QEvent *_event)
{
    switch(_event->type())
    {
    case QEvent::TouchBegin:
        _event->accept();
    case QEvent::TouchUpdate:
    case QEvent::TouchCancel:
    case QEvent::TouchEnd:
        qDebug() << "Touch Event";
        return true;
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
        qDebug() << "Mouse Event";
        break;
    case QEvent::TabletMove:
    case QEvent::TabletPress:
    case QEvent::TabletRelease:
        qDebug() << "Tablet Event";

    }
    return QWidget::event(_event);
}
