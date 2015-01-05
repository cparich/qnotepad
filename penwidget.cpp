#include "penwidget.h"
#include <QDebug>
#include <QPainter>
#include <algorithm>
#include <QTabletEvent>

#include <tuple>

void PenWidget::TouchBegin(QEvent* e)
{
	if(!useTouch)
		return;

	auto asTouch = (QTouchEvent*)e;
	for(QTouchEvent::TouchPoint point : asTouch->touchPoints())
	{
		int x = point.pos().toPoint().x();
		int y = point.pos().toPoint().y();
		input_map[point.id()] = std::make_tuple(x, y, x, y);
	}

	e->accept();
}

void PenWidget::TouchUpdate(QEvent *e)
{
	auto asTouch = (QTouchEvent*)e;
	for(QTouchEvent::TouchPoint point : asTouch->touchPoints())
	{
		int old_x;
		int old_y;
		int x = point.pos().toPoint().x();
		int y = point.pos().toPoint().y();
		// did touchbegin fail to fire?
		if(input_map.find(point.id()) == input_map.end())
		{
			old_x = x;
			old_y = y;
		}
		else
		{
			old_x = std::get<2>(input_map[point.id()]);
			old_y = std::get<3>(input_map[point.id()]);
		}

		input_map[point.id()] = std::make_tuple(old_x, old_y, x, y);

		if(useTouch)
			DrawSegment(old_x,old_y,x,y);
	}
	e->accept();
}

void PenWidget::TouchEnd(QEvent *e)
{
	auto asTouch = (QTouchEvent*)e;
	for(QTouchEvent::TouchPoint point : asTouch->touchPoints())
	{
		int old_x = std::get<2>(input_map[point.id()]);
		int old_y = std::get<3>(input_map[point.id()]);
		int x = point.pos().toPoint().x();
		int y = point.pos().toPoint().y();

		if(useTouch)
			DrawSegment(old_x,old_y,x,y);

		input_map.erase(input_map.find(point.id()));
	}
	e->accept();
}

void PenWidget::TouchCancel(QEvent *e)
{
	auto asTouch = (QTouchEvent*)e;
	for(QTouchEvent::TouchPoint point : asTouch->touchPoints())
	{
		input_map.erase(input_map.find(point.id()));
	}
	e->accept();
}

PenWidget::PenWidget(QWidget *parent) :
	QWidget(parent)
{
	setAttribute(Qt::WA_AcceptTouchEvents, true);

	pixmap = new QPixmap(size());
	pixmap->fill(qRgb(255,255,255));
}

PenWidget::~PenWidget()
{
	delete pixmap;
}

bool PenWidget::AcceptTouch(bool touch)
{
	useTouch = touch;
}

void PenWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), *pixmap);
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

void PenWidget::DrawSegment(int x1, int y1, int x2, int y2, qreal pressure)
{
	QPainter painter (pixmap);
	painter.setRenderHint(QPainter::Antialiasing);
	QPen pen (Qt::black);
	pen.setWidthF(pressure);
	painter.setPen(pen);
	painter.drawLine(x1, y1, x2, y2);
}

void PenWidget::clearImage()
{
	pixmap->fill(qRgb(255,255,255));
	repaint();
}

void PenWidget::update()
{
	repaint();
}

void PenWidget::tabletEvent(QTabletEvent *event)
{
	int x, y, old_x, old_y;
	x = event->x();
	y = event->y();
	old_x = x;
	old_y = y;

	switch(event->type())
	{
	case QEvent::TabletPress:
		input_map[-1] = std::make_tuple(old_x,old_y,x,y);
		break;
	case QEvent::TabletMove:
		old_x = std::get<2>(input_map[-1]);
		old_y = std::get<3>(input_map[-1]);
		input_map[-1] = std::make_tuple(old_x,old_y,x,y);
		break;
	case QEvent::TabletRelease:
		old_x = std::get<2>(input_map[-1]);
		old_y = std::get<3>(input_map[-1]);
		input_map.erase(input_map.find(-1));
		break;
	}

	DrawSegment(old_x, old_y, x, y, event->pressure()*10);
}

bool PenWidget::event(QEvent *_event)
{
	switch(_event->type())
	{
	case QEvent::TouchBegin:
		TouchBegin(_event);
		return true;
	case QEvent::TouchUpdate:
		TouchUpdate(_event);
		return true;
	case QEvent::TouchCancel:
		TouchCancel(_event);
		return true;
	case QEvent::TouchEnd:
		TouchEnd(_event);
		return true;
	}
	return QWidget::event(_event);
}
