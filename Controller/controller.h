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

	//Model Interface
		 //Navigation
	static void AddSubNavigation(double key, QList<QTreeWidgetItem*> subNav);
	static QList<QTreeWidgetItem*> GetSubNavigation(double key);
	static bool RemoveSubNavigation(double key);
	static void ClearSubNavigation();

	static void AddPage(double key, QJsonObject page);
	static QJsonObject GetPage(double key);
	static bool RemovePage(double key);
	static void ClearPages();

	static void AddMainNavigation(double key, QString mainNav);
	static QString GetMainNavigation(double key);
	static bool RemoveMainNavigation(double key);
	static void ClearMainNavigation();

	static bool SaveNavigation();
	static QJsonObject SaveSubNavigation(QTreeWidgetItem* item);

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
	void login(QString username,QString password);
	bool hasRootGroupAccess();
	bool hasAdminGroupAccess();
	bool hasAccess(QString group);


private:
	explicit Controller(QObject * parent = 0);
	static Controller* p_instance;
	QMap<QString,QStringList> layoutViewGroups;
	bool hasReadAccess(QJsonObject permissions);
	bool hasWriteAccess(QJsonObject permissions);
	QString indexDocument_id;
public slots:
	void subNavPressed(QJsonObject view);
	void linkPressed(QJsonObject link);
	void editControllerCancelDataPressed(QJsonDocument document);

	void showDisplayDataReturned(QJsonDocument document);
	void loadNavigationData(QJsonDocument document);
	void subNavPressedData(QList<QJsonDocument> documents);
	void subNavPressedIndexData(QList<QJsonDocument> documents);
	void getFieldsData(QList<QJsonDocument> documents);
	void linkPressedData(QJsonDocument document);
	void getDocData(QJsonDocument document);
	void GetJsonListData(QList<QJsonDocument> items);


	void getLastKeyData(QString key);
	void loginData(QList<QJsonDocument> user);

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
