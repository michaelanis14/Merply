/**************************************************************************
** File: model.h
** Created on: 15.04.2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/

#ifndef MODEL_H
#define MODEL_H

#include "controller.h"
#include <QList>
#include <QStringList>
#include <QMap>
#include <QTreeWidgetItem>


//DEFINES
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600
#define TIMELINE_WIDTH 180
#define NAVIGATION_WIDTH 200
#define NAVIGATION_HEIGHT 50
#define NAVIGATION_CONTROL_HEIGHT 25
#define NAVIGATION_MAIN_HEIGHT 150
#define NAVIGATION_SUB_HEIGHT 100


class Model:public QObject
{
	Q_OBJECT

public:
	static Model* Get();
	bool Log(const QStringList& log);
	void setDataModel(QList<QStringList> *value);
	void setShowWarning(bool value);
	bool getShowWarning() const;

	//Navigation
	void addSubNavigation(int key, QList<QTreeWidgetItem*> subNav);
	QList<QTreeWidgetItem*> getSubNavigation(int key);
	bool removeSubNavigation(int key);
	void clearSubNavigation();

	void addPage(int key, QJsonObject page);
	QJsonObject getPage(int key);
	bool removePage(int key);
	void clearPages();

	void addMainNavigation(int key, QString mainNav);
	QString getMainNavigation(int key);
	bool removeMainNavigation(int key);
	void clearMainNavigation();




	QMap<int, QList<QTreeWidgetItem*> > getSubNavigationModel();
	QMap<int, QString > getMainNavigationModel();

private:
	explicit Model();
	///Flags///
	bool showWarning;
	bool isNameExistInList(QStringList &list, QString &name) ;
	static Model* p_instance;
	QMap<int, QList<QTreeWidgetItem *> > subNavigation;
	QMap<int, QJsonObject > pages;
	QMap<int, QString > mainNavigation;

};

#endif // MODEL_H
