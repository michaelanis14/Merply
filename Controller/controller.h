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
#include <QWidget>
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
	void ShowError(QString message);
	static bool ShowQuestion(QString question);
	void static Log(QStringList log);

	bool deleteDocument(QString id);
	static bool Compare(QJsonObject first,QJsonObject second);

	QStringList getModelDocumentsNameByType(const QString& modelType);

	int Count(const QString table);
	int countIndex(const QString index);
	void getDoc(QString key);
	void getJsonList(QString table, QString select,QString condition = "");
	void getJsonEntityFieldsList(QString table, QString select,QString condition = "");
	void getLastKey();
	void getValue(QString key);
	QString getDatabaseName();

	QList<QString> select(const QString query);
	QVector<QJsonDocument> getAll(const QString entity, const QString condition);
	QString toString(QString key = "",QJsonValue value = QJsonValue());
	bool documentInList(QVector<QJsonDocument> all, QString key);
	QVector<QJsonDocument> getEnities();
	void getFields(QString Title);
	void getIndexHeader(QString title);
	void getViewStructures();
	void updateLayoutViewGroups(QString entityName, QList<StructureViewsEditUI*> sVEUIs);
	QStringList getLayoutViewGroups(QString entity);
	bool storeDoc(QString key,QJsonDocument document);
	static bool UpdateDoc(QJsonDocument document);

	void showCreateEditeStrUI(QString str, bool create);
	void showCreateEditeValueUI(QString key);
	void queryIndexView(QString vStrctKey);

	void editControllerCancelPressed();
	SubFieldUI* getFirstSubField(QString feildName);

	void createIndexes(QJsonObject viewStrct);
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

	void getReport(QJsonObject clmns, QString filter="");
	QString getLocalSourceReport(QJsonObject clmn, int index, QString filter);
	void insertCachedCreateEditUI(QString key, QWidget* instance);
	QWidget* getCachedCreateEditUI(QString key);
	bool isCachedCreateEditUI(QString key);
	QWidget* getStructure(QString key);

	//build
	void buildStructure();

	//
	void getReportTableData(QJsonObject strct);

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


	bool runQRPTDesingerapp();

	void query(QString query,bool cached);

	bool createEditStore(QJsonObject document);
	bool createEditRemoveRowItems(QJsonArray rowsItems);
	QVector<QJsonObject> creatEditeItems;
	void deleteEntity(QString documentID);
	void saveRefrenceStructures(QJsonObject mainStrct,QJsonObject data);

	//preLoading feature
	QMap<QString,QJsonObject> structNames;
	//QMap<QString,QWidget*> structCreateEditUI;
	QMap<QString,QWidget*> createEditUIWidget;
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
	void subNavPressedData(QJsonDocument documents);
	void subNavPressedIndexData(QVector<QJsonDocument> documents);
	void subNavPressedPageData(QJsonDocument document);
	void getFieldsData(QVector<QJsonDocument> documents);
	void getIndexHeaderData(QVector<QJsonDocument> documents);
	void getViewStructuresData(QVector<QJsonDocument> documents);
	void linkPressedData(QJsonDocument document);
	void getDocData(QJsonDocument document);
	void GetJsonListData(QVector<QJsonDocument> items);
	void getValueData(QString value);

	void getReportData(QVector<QJsonDocument> documents);
	void getLastKeyData(QString key);

	void showCreateEditeStrUICreateTrueData(QJsonDocument str);
	void showCreateEditeStrUIData(QJsonDocument str);
	void showCreateEditeValueUIData(QJsonDocument value);
	void queryData(QVector<QJsonDocument> items);

	void createEditStoreItems(QString key);
	void getTabelsData(QString entity,QStringList tbls);
	void deleteEntityData(QVector<QJsonDocument> items);

	void successLogin();
signals:
	void getDocDataReturned(QJsonDocument document);
	void gotFieldsData(QList<QString> fields);
	void gotStructsData(QMap<QString,QJsonObject> structsName);
	void gotReportData(QVector<QJsonDocument> documents);
	void gotDocument(QJsonDocument docuemnt);
	void gotDocuments(QVector<QJsonDocument> array);
	void gotValue(QString value);
	void gotLastKey(QString LastKeyID);
	void gotJsonListData(QVector<QJsonDocument> items);
	void queryDatabase(QString q);
	void saved(QString document_id);
	void savedItems(QString document_id);
	void savedQJson(QJsonDocument savedDocument);

};

#endif // Controller_H
