/**************************************************************************
** File: navigationui.cpp
** Created on: 20.11.2015
** Author: Michael Bishara
** Copyright (C) 2015 Michael Bishara
**************************************************************************/

#include"hnavigationui.h"
#include "navigationui.h"
#include "model.h"

HNavigationTab::HNavigationTab(QWidget* parent,QWidget* display,QString title) :
	QWidget(parent)
{
	//this->setContentsMargins(0,0,0,0);
	this->setObjectName("HNavigationTab");
	this->layout = new QHBoxLayout(this);
	this->layout->setContentsMargins(0,0,0,0);
	this->display = display;
	this->tab = new QLabel();
	this->tab->setText(title);
	this->tab->setObjectName("Tab");

	this->layout->addWidget(tab);
	this->layout->setAlignment(tab,Qt::AlignHCenter);
}
QLabel *HNavigationTab::getTab() const
{
	return tab;
}

void HNavigationTab::setTab(QLabel *value)
{
	tab = value;
}
QWidget *HNavigationTab::getDisplay() const
{
	return display;
}

void HNavigationTab::setDisplay(QWidget *value)
{
	display = value;
}


void HNavigationTab::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
HNavigationUI::HNavigationUI(QWidget *parent) :
	QWidget(parent)
{

	this->setContentsMargins(0,0,0,0);
	this->setObjectName("HNavigationUI");
	this->layout = new QHBoxLayout(this);
	this->layout->setContentsMargins(0,0,0,0);
	this->layout->setAlignment(Qt::AlignLeft);
	this->setMinimumHeight(40);
	this->setMaximumHeight(40);

}
QList<HNavigationTab *> HNavigationUI::getTabs() const
{
	return tabs;
}

void HNavigationUI::setTabs(const QList<HNavigationTab *> &value)
{
	tabs = value;
}

HNavigationUI* HNavigationUI::p_instance = 0;
HNavigationUI* HNavigationUI::Get(){
	if (p_instance == 0){
		p_instance = new HNavigationUI();
	}
	return p_instance;
}
void HNavigationUI::addTab(QWidget* widget,QString title){
	HNavigationTab* tab = new HNavigationTab(this,widget,title);
	tab->setMaximumHeight(NAVIGATION_HEIGHT);
	layout->addWidget(tab);
	tabs << tab;
}
QWidget* HNavigationUI::getDisplayByTabName(QString tabName){
	foreach(HNavigationTab * tab, tabs){
		if(tab->getTab()->text().compare(tabName) == 0)
			return tab->getDisplay();
	}
	return new QWidget();
}

void HNavigationUI::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void HNavigationUI::tabChanged(HNavigationTab* selectedTab){
	foreach(HNavigationTab* tab, tabs){
		if(tab != selectedTab)
			tab->getTab()->setObjectName("Tab");
		else {
			tab->getTab()->setObjectName("TabSelected");
//			((EntitiesUI*)tab->getDisplay())->ShowUI();
		}
		tab->getTab()->style()->unpolish(tab->getTab());
		tab->getTab()->style()->polish(tab->getTab());
		tab->getTab()->update();

		}
}

void HNavigationUI::clearTabs()
{
	foreach(HNavigationTab* tab, tabs){
		layout->removeWidget(tab);
		tab->setHidden(true);
		tab->deleteLater();
		}
}

void HNavigationUI::mousePressEvent(QMouseEvent *event){
	QLabel *child=  static_cast<QLabel *>(childAt(event->pos()));
	if  (!child)
		return;
	else {
		if( child->objectName().compare("Tab") == 0){
			tabChanged(((HNavigationTab*)child->parent()));

		}
	}
}

