/**************************************************************************
** File: timelineui.cpp
** Created on: 20.04.2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/

#include "timelineui.h"

timelineUI::timelineUI(QWidget *parent) :
	QWidget(parent)
{
	layout = new QHBoxLayout(this);
	layout->setContentsMargins(2,2,2,2);
	this->setContentsMargins(2,2,2,2);
	this->setObjectName("timelineUI");
//	this->setMaximumWidth(80);
	this->setAutoFillBackground(true);
	btnLoad = new QLabel(this);
	btnLoad->setFixedHeight(10);
	btnLoad->setObjectName("Load");
	btnLoad->setText("Load");

	btnRun = new QLabel(this);
	btnRun->setObjectName("Run");
	btnRun->setText("Run");

	layout->addWidget(btnLoad);
	layout->addWidget(btnRun);
	addTimeInstance("new");
}

timelineUI* timelineUI::p_instance = 0;
timelineUI* timelineUI::Get(){

	if (p_instance == 0)
		p_instance = new timelineUI();

	return p_instance;
}
void timelineUI::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void timelineUI::addTimeInstance(QString title){
	QLabel * timeInstance = new QLabel(title);
	timeInstance->setObjectName("navigationTab");
	timeInstance->setMinimumWidth(50);
	timeInstance->setMinimumHeight(40);
	layout->addWidget(timeInstance);
}

void timelineUI::mousePressEvent(QMouseEvent *event){

	QLabel *child=  static_cast<QLabel *>(childAt(event->pos()));
	if  (!child)
		return;
	else {
		if( child->objectName().compare("Load") == 0){
			emit btnLoadPressed();
		}
		else if( child->objectName().compare("Run") == 0){
			qDebug() << "run";
			emit btnRunPressed();
		}

	}
	event->accept();


}
