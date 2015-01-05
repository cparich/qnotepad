#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setAttribute(Qt::WA_AcceptTouchEvents, true);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionPen_triggered()
{

}

void MainWindow::on_actionEraser_triggered()
{

}

void MainWindow::on_actionTouchToggle_triggered()
{
	useTouch = !useTouch;
	ui->widget->AcceptTouch(useTouch);
}

void MainWindow::on_pushButton_3_clicked()
{
	ui->widget->clearImage();
}
