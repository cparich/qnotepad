#-------------------------------------------------
#
# Project created by QtCreator 2014-09-11T14:02:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = draw-test
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
		mainwindow.cpp \
	penwidget.cpp

HEADERS  += mainwindow.h \
	penwidget.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY =

