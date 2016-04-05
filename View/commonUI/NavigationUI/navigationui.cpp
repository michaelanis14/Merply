/**************************************************************************
** File: navigationui.cpp
** Created on: 30.04.3015
** Author: Michael Bishara
** Copyright (C) 3015 Merply - Michael Bishara e.U.
**************************************************************************/
#include "controller.h"
#include <QDebug>
#include "navigationui.h"
#include "navigationbtn.h"

#include "navigationeditui.h"
#include "mainform.h"
#include <QHeaderView>



navigationUI::navigationUI(QWidget *parent) :
	QWidget(parent){
	this->setContentsMargins(0,0,0,0);
	this->setObjectName("navigationUI");
	this->layout = new QVBoxLayout(this);
	this->layout->setContentsMargins(0,0,0,0);
	this->layout->setAlignment(Qt::AlignLeft);
	this->setFixedWidth(Controller::GetNavigationWidth());
	this->setFixedHeight(Controller::GetWindowHeight());

	SettingsCtrlsUI* sctrlUI = new SettingsCtrlsUI();
	sctrlUI->setFixedHeight(Controller::GetNavigationSettingsBarHeight());
	sctrlUI->addbtn("Settings",":/resources/icons/settings.png","settings");
	QObject::connect(sctrlUI, SIGNAL(btnClicked(QString)),this, SLOT(btn_Clicked(QString)));
	layout->addWidget(sctrlUI);



	subNavigation = new QTreeWidget();
	subNavigation->setColumnCount(2);
	subNavigation->setFixedWidth(Controller::GetNavigationWidth());
	subNavigation->setFixedHeight(Controller::GetWindowHeight()-(Controller::GetNavigationSettingsBarHeight() +15)-Controller::GetNavigationMainHeight());

	subNavigation->header()->close();
	QObject::connect(subNavigation, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(subNavPressed(QTreeWidgetItem*,int)));
	subNavigation->hideColumn(1);


	mainNavigation = new QTreeWidget();
	mainNavigation->setColumnCount(3);
	mainNavigation->setFixedWidth(Controller::GetNavigationWidth());
	mainNavigation->setFixedHeight(Controller::GetNavigationMainHeight());
	mainNavigation->header()->close();
	QObject::connect(mainNavigation, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(mainNavPressed(QTreeWidgetItem*,int)));
	mainNavigation->hideColumn(0);
	mainNavigation->hideColumn(2);




	this->layout->addWidget(subNavigation,1);
	this->layout->addWidget(mainNavigation,1);
	this->editMode = false;

}

void navigationUI::loadMainNavigation(QList<QJsonDocument> navDocs)
{
	mainNavigation->clear();
	subNavigation->clear();
	Controller::ClearMainNavigation();
	Controller::ClearSubNavigation();
	Controller::ClearPages();
	foreach(QJsonDocument doc,navDocs){
		int key = doc.object().value("ID").toInt();
		QString title = doc.object().value("Title").toString();
		QJsonArray items = doc.object().value("Items").isArray()?doc.object().value("Items").toArray():QJsonArray();
		//qDebug() << title << items;
		if(!title.isEmpty() && !items.isEmpty()){
			QTreeWidgetItem* maintab = new QTreeWidgetItem();
			maintab->setText(2,QString::number(key));
			maintab->setText(1,title);
			mainNavigation->insertTopLevelItem(0,maintab);
			}
		mainNavigation->resizeColumnToContents(0);

		Controller::AddMainNavigation(key,title);
		Controller::AddSubNavigation(key,loadSubNavigation(items));
		}
	if(mainNavigation->topLevelItemCount() > 0){
		mainNavigation->selectionModel()->select(mainNavigation->model()->index(0,0,QModelIndex()),QItemSelectionModel::Select| QItemSelectionModel::Rows);
		mainNavPressed(mainNavigation->topLevelItem(0),0);
		}

}

QList<QTreeWidgetItem *> navigationUI::loadSubNavigation(QJsonArray subNav)
{
	QList<QTreeWidgetItem *> items;
	foreach(QJsonValue tab,subNav){
		int key = tab.toObject().value("ID").toInt();
		QString title = tab.toObject().value("Title").toString();
		if(key!=0 && !title.isEmpty())
			Controller::AddPage(key,tab.toObject().value("Page").toObject());
		QTreeWidgetItem*  item = new QTreeWidgetItem();
		item->setText(1,QString::number(key));
		item->setText(0,title);
		if(tab.toObject().value("Items").isArray())
			item->addChildren(loadSubNavigation(tab.toObject().value("Items").toArray()));
		items.append(item);
		}
	return  items;
}

void navigationUI::save()
{
	Controller::SaveNavigation();
}


navigationUI* navigationUI::p_instance = 0;
navigationUI* navigationUI::Get(){
	if (p_instance == 0){
		p_instance = new navigationUI();
		}
	return p_instance;
}




void navigationUI::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void navigationUI::mainNavPressed(QTreeWidgetItem* item, int column)
{
	//qDebug() <<item->text(0)  << column;

	//item->setText(0,"Pressedd");
	if(column == 0)
		subNavigation->insertTopLevelItems(0,Controller::GetSubNavigation(item->text(2).toInt()));
	else qDebug() << item->text(column) << column;
	subNavigation->clearFocus();
}

void navigationUI::subNavPressed(QTreeWidgetItem* item, int column)
{
	if(column == 0)
		emit subNavPressed(Controller::GetPage(item->text(1).toInt()));
	else qDebug() << item->text(column) << column;
	//save();
}

void navigationUI::btn_Clicked(QString btn)
{
	//qDebug() << btn;
	if(btn.contains("settings")){
		navigationUI::Get()->setHidden(true);
		NavigationEditUI::Get()->setParent(MainForm::Get());
		NavigationEditUI::Get()->loadMainNavigation(Controller::Get()->getAll("NavigationUI",""));
		NavigationEditUI::Get()->setHidden(false);

		}
}


