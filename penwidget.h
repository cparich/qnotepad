#ifndef PENWIDGET_H
#define PENWIDGET_H

#include <QWidget>
#include <QMouseEvent>

class PenWidget : public QWidget
{
    Q_OBJECT

    int old_x, old_y;
    int xpos, ypos;

    QPixmap *pixmap;

public:
    explicit PenWidget(QWidget *parent = 0);
    ~PenWidget();

signals:

public slots:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

    void tabletEvent(QTabletEvent *event);

    bool event(QEvent *_event);
};

#endif // PENWIDGET_H
