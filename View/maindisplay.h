/**************************************************************************
** File: maindisplay.h
** Created on: Wed Feb 18 2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/

#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H


#include <QWidget>
//#include "QPaintEvent"
//#include <QStyleOption>
class QScrollArea;

class MainDisplay : public QWidget
{
	Q_OBJECT
public:
	explicit MainDisplay(QWidget* parent);
	QScrollArea *scrollAreaFormPanel;
	QWidget *formPanel;
	void paintEvent(QPaintEvent *);

signals:

public slots:

};

#endif // MAINDISPLAY_H
