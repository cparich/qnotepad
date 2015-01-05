#ifndef PENWIDGET_H
#define PENWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <unordered_map>

class PenWidget : public QWidget
{
	Q_OBJECT

	std::unordered_map<int,std::tuple<int,int,int,int>> input_map;

	bool useTouch = false;

	QPixmap *pixmap;

	void TouchBegin(QEvent *e);
	void TouchUpdate(QEvent *e);
	void TouchEnd(QEvent* e);
	void TouchCancel(QEvent *e);

public:
	explicit PenWidget(QWidget *parent = 0);
	~PenWidget();

	bool AcceptTouch(bool touch);

	void DrawSegment(int x1, int y1, int x2, int y2, qreal pressure = 1);

	void clearImage();

signals:

public slots:
	void update();

	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);

	void tabletEvent(QTabletEvent *event);

	bool event(QEvent *_event);
};

#endif // PENWIDGET_H
