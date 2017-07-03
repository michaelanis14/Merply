/**************************************************************************
** File: Controller.h
** Created on: 06.03.2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/

#ifndef Controller_H
#define Controller_H


#include "model.h"
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


	static Controller* Get();


	//void buildGUI();

	QStringList getListSource(QString source);
	QStringList getNameByGroupName(const QString& groupName);

	void  setShowWarning(bool value);
	bool showWarning(QString warning);
	void ShowError(QString message);
	static bool ShowQuestion(QString question);
	void static Log(QStringList log);

	static bool Compare(QJsonObject first,QJsonObject second);

	QStringList getModelDocumentsNameByType(const QString& modelType);

	void Count(const QString table);
	int countIndex(const QString index);
	void getDoc(const QString& select, const QString &tabel, const QString& key, const QString &id);
	void getSelectList(QString table, QString select,QString condition = "");
	void getJsonEntityFieldsList(QString table, QString select,QString condition = "");
	void getLastKey();
	/*
	void getValue(QString key);
	*/
	QString getDatabaseName();

	QList<QString> select(const QString query);
	QVector<QJsonDocument> getAll(const QString entity, const QString condition);
	QString toString(QString key = "",QJsonValue value = QJsonValue());
	bool documentInList(QVector<QJsonDocument> all, QString key);
	QVector<QJsonDocument> getEnities();
	//void getFields(QString Title,int);
	//void getIndexHeader(QString title);
	void getViewStructures();
	void getPageStructures();
	void updateLayoutViewGroups(QString entityName, QList<StructureViewsEditUI*> sVEUIs);
	QStringList getLayoutViewGroups(QString entity);
	void storeJson(const QString& key,const QString& tabel,QJsonDocument document);
	void updateJson(const QString& id,const QString& tabel,QJsonDocument document);

	//void showCreateEditeStrUI(int structure_id, int data_id);
	//void showCreateEditeValueUI(int id, QString tabel);
	void queryIndexView(QString vStrctKey);

	void editControllerCancelPressed();
	SubFieldUI* getFirstSubField(QString strID, QString feildName);

	void createIndexes(QJsonObject viewStrct);
	void createEditSqlTabel(QJsonObject viewStrct);
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

	//void insertCachedCreateEditUI(int key, QWidget* instance);
	//QWidget* getCachedCreateEditUI(int key);
	//bool isCachedCreateEditUI(int key);

	void insertCachedViewStructure(int key, QJsonObject viewStrct);
	QJsonObject getCachedViewStructure(int key);
	QMap<int, QJsonObject> getCachedViewStructures() const;

	void insertCachedPageStructure(int key, QJsonObject viewStrct);
	QJsonObject getCachedPageStructure(int key);
	QMap<int, QJsonObject> getCachedPageStructures() const;

	void insertCachedIndexUI(int key, QWidget* instance);
	QWidget* getCachedIndexUI(int key);
	bool isCachedIndexUI(int key);

	void insertCachedPageUI(int key, QWidget* instance);
	QWidget* getCachedPageUI(int key);
	bool isCachedPageUI(int key);

	void insertCachedViewStructureFieldsNames(int id, QStringList fieldsNames);
	QStringList getCachedViewStructureFieldsNames(int id);

	void insertCachedViewStructureIndexFieldsNames(int id, QStringList fieldsNames);
	QStringList getCachedViewStructureIndexFieldsNames(int id);

	void insertCachedViewStructureNames(QString name, int id);
	int getCachedViewStructureNames(QString name);
	QStringList getCachedViewStructureNames();

	QMap<int, QJsonObject> getCachedViewStructureSubFields(int id);
	void insertCachedViewStructureSubFields(int id, QMap<int, QJsonObject> subFields);

	void insertCachedViewStructureTabelFields(int key, QVector<QJsonObject> tabelFields);
	QVector<QJsonObject> getCachedViewStructureTabelFields(int key);
	QMap<int, QVector<QJsonObject> > getCachedViewStructureTabelFields() const;


	int getCachedSubFieldsClmnRef(int strctID);
	QMap<int,int> subFieldsCounter;

	//buildCachedUI s
	void buildCachedCreateEditUI();
	void buildCachedIndexUI();
	void buildCachedPageUI();

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

	void query(QString query);

	bool createEditStore(QJsonObject document);
	bool createEditRemoveRowItems(QJsonArray rowsItems);
	QVector<QJsonObject> creatEditeItems;
	void deleteEntity(const QString& tabel, const QString& id);
	void saveRefrenceStructures(QJsonObject mainStrct,QJsonObject data);

	//Database Interface
	void insertUpdateRow(QString query);

	//preLoading feature
	//QMap<QString,QJsonObject> structNames;
	//QMap<QString,QWidget*> createEditUIWidget;
	//bool accessed = false;

	Database* getDatabase() const;

private:
	explicit Controller(QObject * parent = 0);
	static Controller* p_instance;
	QMap<QString,QStringList> layoutViewGroups;
	QString indexDocument_id;
	Database* database;
public slots:
	void showDisplay();


	void subNavPressed(QJsonObject view);
	void linkPressed(QJsonObject link);
	void editControllerCancelDataPressed(QJsonDocument document);

	void showDisplayDataReturned(QJsonDocument document);
	void loadNavigationData(QJsonDocument document);
	//void subNavPressedData(QJsonDocument documents);
	void subNavPressedIndexData(QVector<QSqlRecord> documents);
	void subNavPressedPageData(QJsonDocument document);
	//void getFieldsData(QVector<QJsonDocument> documents);
	//void getIndexHeaderData(QVector<QJsonDocument> documents);
	void getViewStructuresData(QVector<QSqlRecord> documents);
	void getPageStructuresData(QVector<QSqlRecord> documents);
	void linkPressedData(QJsonDocument document);
	void getDocData(QJsonDocument document);
	void GetSelectListData(QVector<QSqlRecord> items);
	//void getValueData(QString value);

	void getReportData(QVector<QSqlRecord> documents);
	void getLastKeyData(QString key);

	void deleteDocument(const QString& tabel, const QString& id);
	void deleteEntity(const int& tabel, const int& id);

	//void showCreateEditeStrUICreateTrueData(QJsonDocument str);
	//void showCreateEditeStrUIData(QJsonDocument str);
	//void showCreateEditeValueUIData(QVector<QSqlRecord> data);
	void queryData(QVector<QSqlRecord> items);

	void createEditStoreItems(QString key);
	void getTabelsData(QString entity,QStringList tbls);
	//void deleteEntityData(QVector<QJsonDocument> items);

	void buildViewStructureIndexFieldsNamesList(QJsonObject viewstrct); //

	void successLogin();
	void reBuildViewStructures();
signals:
	void getDocDataReturned(QJsonDocument document);
//	void gotFieldsData(QList<QString> fields);
//	void gotStructsData(QMap<QString,QJsonObject> structsName);
	void gotReportData(QVector<QSqlRecord> documents);
	void gotDocument(QJsonDocument docuemnt);
	void gotDocuments(QVector<QJsonDocument> array);
	//void gotValue(QString value);
	void gotLastKey(QString LastKeyID);
	void gotSelectListData(QVector<QSqlRecord> items);
	void queryDatabase(QString q);
	void saved(QString document_id);
	void savedItems(QString document_id);
	void savedQJson(QJsonDocument savedDocument);
	void CountData(int count);

};

#endif // Controller_H
