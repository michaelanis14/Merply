/**************************************************************************
** File: navigationui.h
** Created on: 20.04.2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/

#ifndef NAVIGATIONUI_H
#define NAVIGATIONUI_H



#include <QPainter>

#include <QWidget>
#include <QLabel>
#include <QButtonGroup>

//#include <QPaintEvent>
#include <QHBoxLayout>
//#include <QPaintEvent>

#include <QTreeWidget>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>




class navigationUI : public QWidget
{
	Q_OBJECT
public:
	static navigationUI* Get();
	void loadMainNavigation(QJsonDocument navDoc);
	QList<QTreeWidgetItem*> loadSubNavigation(QJsonArray subNav);
	void save();
	explicit navigationUI(QWidget *parent = 0);


	static navigationUI* p_instance;
	QVBoxLayout* layout;


	QTreeWidget *subNavigation;
	QTreeWidget *mainNavigation;
	void paintEvent(QPaintEvent *);
	bool editMode;
	void resizeEvent(QResizeEvent* event);

public slots:
	void mainNavPressed(QTreeWidgetItem* item, int);
	void subNavPressed(QTreeWidgetItem* item, int);
	void btn_Clicked(QString btn);
	void btn_ClickedDataReturned(QJsonDocument document);

signals:
	void subNavPressed(QJsonObject view);

};

#endif // NAVIGATIONUI_H
