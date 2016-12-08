/**************************************************************************
** File: model.h
** Created on: 15.04.2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/

#ifndef MODEL_H
#define MODEL_H

#include "controller.h"
#include "user.h"


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

#include  <View/createeditui.h>

class Model:public QObject
{
	Q_OBJECT

public:
	static Model* Get();
	bool Log(const QStringList& log);
	void setDataModel(QList<QStringList> *value);
	void setShowWarning(bool value);
	bool getShowWarning() const;


	//lazyloading
	QMap< QString,QWidget* > cachedCreateEditUI;

	//Navigation
	void addSubNavigation(double key, QList<QTreeWidgetItem*> subNav);
	QList<QTreeWidgetItem*> getSubNavigation(double key);
	bool removeSubNavigation(double key);
	void clearSubNavigation();



	void addPage(double key, QJsonObject page);
	QJsonObject getPage(double key);
	bool removePage(double key);
	void clearPages();

	void addMainNavigation(double key, QString mainNav);
	QString getMainNavigation(double key);
	bool removeMainNavigation(double key);
	void clearMainNavigation();




	QMap<double, QList<QTreeWidgetItem*> > getSubNavigationModel();
	QMap<double, QString > getMainNavigationModel();

	void login(QString uid,QString username,QString name);
	void logout();
	QString getUserID();
	QString getUserName();
	QString getUserUsername();

	QMap<double, QJsonObject> getPages() const;

	QString getDefaulConnStrg() const;
	void setDefaulConnStrg(const QString& value);

private:
	explicit Model();
	///Flags///
	bool showWarning;
	bool isNameExistInList(QStringList &list, QString &name) ;
	static Model* p_instance;
	QMap<double, QList<QTreeWidgetItem *> > subNavigation;
	QMap<double, QJsonObject > pages;
	QMap<double, QString > mainNavigation;
	User* loggedUser;
	//Defaults
	QString defaulConnStrg;
};

#endif // MODEL_H
