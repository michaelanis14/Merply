/**************************************************************************
** File: Controller.h
** Created on: 06.03.2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/

#ifndef Controller_H
#define Controller_H



#include <structureviewseditui.h>

#include <QObject>
#include <QString>
#include <QMap>
#include <QTreeWidgetItem>


class Controller : public QObject
{
	Q_OBJECT
public:
	//    explicit Controller(QObject * parent = 0);
	void showDisplay();
	static Controller* Get();


	//void buildGUI();

	QStringList getListSource(QString source);
	QStringList getNameByGroupName(const QString& groupName);

	void  setShowWarning(bool value);
	void showWarning(QString warning);
	void static Log(QStringList log);

	bool deleteDocument(QString id);

	QStringList getModelDocumentsNameByType(const QString& modelType);

	int Count(const QString table);
	bool getDoc(QString key);
	QList<QString> getListItems(QString table, QString select,QString condition = "");
	QString getDatabaseName();

	QList<QString> select(const QString query);
	QList<QJsonDocument> getAll(const QString entity, const QString condition);
	QString toString(QJsonArray array);
	bool documentInList(QList<QJsonDocument> all, QString key);
	QList<QJsonDocument> getEnities();
	QList<QString> getFields(QString Entity);
	void updateLayoutViewGroups(QString entityName, QList<StructureViewsEditUI*> sVEUIs);
	QStringList getLayoutViewGroups(QString entity);
	bool storeDoc(QString key,QJsonDocument document);
	static bool UpdateDoc(QJsonDocument document);

	//Model Interface
		 //Navigation
	static void AddSubNavigation(int key, QList<QTreeWidgetItem*> subNav);
	static QList<QTreeWidgetItem*> GetSubNavigation(int key);
	static bool RemoveSubNavigation(int key);
	static void ClearSubNavigation();

	static void AddPage(int key, QJsonObject page);
	static QJsonObject GetPage(int key);
	static bool RemovePage(int key);
	static void ClearPages();

	static void AddMainNavigation(int key, QString mainNav);
	static QString GetMainNavigation(int key);
	static bool RemoveMainNavigation(int key);
	static void ClearMainNavigation();

	static bool SaveNavigation();

	//Model Defines
	int static GetWindowWidth();
	int static GetWindowHeight();
	int static GetTimeLineWidth();
	int static GetNavigationWidth();
	int static GetNavigationSettingsBarHeight();
	int static GetNavigationMainHeight();
	int static GetNavigationSubHeight();


private:
	explicit Controller(QObject * parent = 0);
	static Controller* p_instance;
	QMap<QString,QStringList> layoutViewGroups;


public slots:
	void subNavPressed(QJsonObject view);

};

#endif // Controller_H
