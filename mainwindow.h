#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	bool useTouch = false;

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_actionPen_triggered();

	void on_actionEraser_triggered();

	void on_actionTouchToggle_triggered();

	void on_pushButton_3_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
