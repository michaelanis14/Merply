/**************************************************************************
** File: timelineui.h
** Created on: 20.04.2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/

#ifndef TIMELINEUI_H
#define TIMELINEUI_H
#include "qpainter.h"

#include <QWidget>
#include <QLabel>
//#include <QPaintEvent>
#include <QVBoxLayout>
//#include <QPaintEvent>
//#include <QStyleOption>


class timelineUI : public QWidget
{
	Q_OBJECT
public:

	void addTimeInstance(QString title);
	static timelineUI* Get();
private:
	explicit timelineUI(QWidget *parent = 0);
	QHBoxLayout * layout;
	QLabel * btnLoad;
	QLabel * btnRun;
	static timelineUI* p_instance;
	void paintEvent(QPaintEvent *);
protected:
	void mousePressEvent(QMouseEvent *event);

signals:
	void btnLoadPressed();
	void btnRunPressed();
public slots:

};

#endif // TIMELINEUI_H
