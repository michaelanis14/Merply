/**************************************************************************
** File: Controller.h
** Created on: 06.03.2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/

#ifndef Controller_H
#define Controller_H

#include "accesscontroller.h"

#include <structureviewseditui.h>

#include <QObject>
#include <QString>
#include <QMap>
#include <QTreeWidgetItem>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

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
	bool showWarning(QString warning);
	static bool ShowQuestion(QString question);
	void static Log(QStringList log);

	bool deleteDocument(QString id);
	static bool Compare(QJsonObject first,QJsonObject second);

	QStringList getModelDocumentsNameByType(const QString& modelType);

	int Count(const QString table);
	void getDoc(QString key);
	void getJsonList(QString table, QString select,QString condition = "");
	void getJsonEntityFieldsList(QString table, QString select,QString condition = "");
	void getLastKey();
	void getValue(QString key);
	QString getDatabaseName();

	QList<QString> select(const QString query);
	QList<QJsonDocument> getAll(const QString entity, const QString condition);
	QString toString(QJsonArray array);
	bool documentInList(QList<QJsonDocument> all, QString key);
	QList<QJsonDocument> getEnities();
	void getFields(QString Title);
	void updateLayoutViewGroups(QString entityName, QList<StructureViewsEditUI*> sVEUIs);
	QStringList getLayoutViewGroups(QString entity);
	bool storeDoc(QString key,QJsonDocument document);
	static bool UpdateDoc(QJsonDocument document);

	void showCreateEditeStrUI(QString str);
	void showCreateEditeValueUI(QString key);
	void queryIndexView(QString vStrctKey);

	void editControllerCancelPressed();
	SubFieldUI* getFirstSubField(QString feildName);
	//Model Interface
	//Navigation
	void initNavigation();
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

	bool saveNavigation();
	bool saveNavigationPages();
	QJsonObject saveSubNavigation(QTreeWidgetItem* item);

	//Model Defines
	int static GetWindowWidth();
	int static GetWindowHeight();
	int static GetTimeLineWidth();
	int static GetNavigationWidth();
	int static GetNavigationSettingsBarHeight();
	int static GetNavigationMainHeight();
	int static GetNavigationSubHeight();
	static QString getLastKeyID();
	//Access Control



private:
	explicit Controller(QObject * parent = 0);
	static Controller* p_instance;
	QMap<QString,QStringList> layoutViewGroups;
	QString indexDocument_id;
public slots:
	void subNavPressed(QJsonObject view);
	void linkPressed(QJsonObject link);
	void editControllerCancelDataPressed(QJsonDocument document);

	void showDisplayDataReturned(QJsonDocument document);
	void loadNavigationData(QJsonDocument document);
	void subNavPressedData(QList<QJsonDocument> documents);
	void subNavPressedIndexData(QList<QJsonDocument> documents);
	void subNavPressedPageData(QList<QJsonDocument> documents);
	void getFieldsData(QList<QJsonDocument> documents);
	void linkPressedData(QJsonDocument document);
	void getDocData(QJsonDocument document);
	void GetJsonListData(QList<QJsonDocument> items);
	void getValueData(QString value);

	void getLastKeyData(QString key);


	void showCreateEditeStrUIData(QJsonDocument str);
	void showCreateEditeValueUIData(QJsonDocument value);

signals:
	void getDocDataReturned(QJsonDocument document);
	void gotFieldsData(QList<QString> fields);

	void gotDocument(QJsonDocument docuemnt);
	void gotDocuments(QList<QJsonDocument> array);
	void gotValue(QString value);
	void gotLastKey(QString LastKeyID);
	void gotJsonListData(QList<QJsonDocument> items);


};

#endif // Controller_H
