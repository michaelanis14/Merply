/**************************************************************************
** File: maindisplay.cpp
** Created on: Wed Feb 18 2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/



#include <QScrollArea>
#include <QResizeEvent>
#include "maindisplay.h"
#include "mainform.h"

/**
* @author Michael Bishara
* @date   18 February, 2015
* @brief  Displays parent class.
*
* the parent display for the application, other displays inherit all its properties
*/


/**
* @author Michael Bishara
* @date   18 February, 2015
* @brief  constructor.
*
* Constructs the display widget inheriting from QWidget,
* setting all default parameters for displays.
*/
MainDisplay::MainDisplay(QWidget* parent) :
	QWidget(parent)

{

	this->setContentsMargins(0,0,0,0);
	setMouseTracking( true );


	scrollAreaFormPanel = new QScrollArea(this);
	scrollAreaFormPanel->setObjectName("scrollAreaFormPanel");
	scrollAreaFormPanel->setContentsMargins(0,0,0,0);
	scrollAreaFormPanel->setFrameStyle(QFrame::NoFrame);
	//scrollAreaFormPanel->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//scrollAreaFormPanel->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//scrollAreaFormPanel->setGeometry(0,0,WINDOW_WIDTH - TIMELINE_WIDTH,WINDOW_HEIGHT - NAVIGATION_HEIGHT);

	//formPanel = new QWidget(scrollAreaFormPanel);
	formPanel = new QWidget(this);
	//	formPanel->setFixedWidth();
	formPanel->setContentsMargins(0,0,0,0);
	formPanel->setObjectName("formPanel");

	//	formPanel->setFont(font3);
	scrollAreaFormPanel->setWidget(this->formPanel);
	scrollAreaFormPanel->setWidgetResizable(true);


	this->setStyleSheet("formPanel{ border: 1px solid gray;}");



}

void MainDisplay::keyPressEvent(QKeyEvent* event)
{
	qDebug() << "keyyyy";
	if (event->key() == Qt::Key_Return)
	{
	focusNextPrevChild(true);
	}
}
void MainDisplay::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

