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
#include <QDebug>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPalette>
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
	void loadMainNavigation(QList<QJsonDocument> navDocs);
	QList<QTreeWidgetItem*> loadSubNavigation(QJsonArray subNav);
	void save();
	explicit navigationUI(QWidget *parent = 0);


	static navigationUI* p_instance;
	QVBoxLayout* layout;


	QTreeWidget *subNavigation;
	QTreeWidget *mainNavigation;
	void paintEvent(QPaintEvent *);
	bool editMode;

public slots:
	void mainNavPressed(QTreeWidgetItem* item, int column);
	void subNavPressed(QTreeWidgetItem* item, int column);
	void btn_Clicked(QString btn);

signals:
	void subNavPressed(QJsonObject view);

};

#endif // NAVIGATIONUI_H
