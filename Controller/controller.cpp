/**************************************************************************
** File: Controller.cpp
** Created on: 06.03.2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/

#include "controller.h"

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QPushButton>
#include <QTextBrowser>
#include <QCloseEvent>
#include <QDir>
#include <QSettings>
#include <QtDebug>
#include <QDesktopServices>
#include <QMessageBox>
#include <QScopedPointer>
#include <QProcess>


#include "model.h"
#include "timelineui.h"
#include "navigationui.h"
#include "navigationeditui.h"
#include "prsistance.h"

#include "structureviewgroupsui.h"
#include "createeditui.h"
#include "pageui.h"
#include "indexui.h"

#include "couchbaselibmanager.h"




Controller::Controller(QObject *parent) :
	QObject(parent)
{
	//	CouchbaseLibManager::Get();

	///TimeLine
	//	connect(timelineUI::Get(), SIGNAL(btnLoadPressed()), this, SLOT(onBtnLoadClicked()));
	//	connect(timelineUI::Get(), SIGNAL(btnRunPressed()), this, SLOT(onBtnRunClicked()));

	//Worker* worker = new Worker();

	//	QObject::connect(this,SIGNAL(queryDatabase(QString)),new Database(),SLOT(query(QString)),Qt::QueuedConnection);


	//	QObject::connect(new Database(),SIGNAL(saved(QString)),this,SIGNAL(saved(QString)));
	QObject::connect(Prsistance::Get(),SIGNAL(count(int)),this,SIGNAL(CountData(int)));


}






void Controller::showDisplay()
{

	QObject::connect(AccessController::Get(),SIGNAL(successLogin()),this,SLOT(successLogin()));

	//AccessController::Get()->logout();
	AccessController::Get()->login("root","root");
	//navigationUI::Get();
	///Tabs
	QStringList tabList = QStringList();
	//Model::Get()->getTabsList();
	if(!tabList.isEmpty())
		foreach (QString tabName, tabList)
			{
			/*
//			EntitiesUI* p = new EntitiesUI();
//			navigationUI::Get()->addTab(p,tabName);
	//		QStringList TabGroupNames = Model::Get()->getTabGroupNames(tabName);
			//HNavigationUI::Get()->clearTabs();
			foreach (QString groupName, TabGroupNames)
				{
				p->addGroup(groupName);

				HNavigationUI::Get()->addTab(p,groupName);
				}
			p->ShowUI();
*/
			}
	//navigationUI::Get()->tabChanged(navigationUI::Get()->getTabs().at(0));
	//	navigationUI::Get()->setCurrentIndex(1);
	//	navigationUI::Get()->setParent(MainWindow::GetMainDisplay());

	//
	//
	//QObject::connect(new Database(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showDisplayDataReturned(QJsonDocument)));
	//new Database()->getDoc("ViewStructure::5");

	//QJsonDocument d =new Database()->getDocument();
	//ViewGroups* vgs= new ViewGroups(0,"Contact",d.object(),d.object());
	//layout->addWidget(vgs);


	getViewStructures(); //preLoading the createEdit UI

	//getPageStructures(); //preLoading the createEdit UI

}

void Controller::successLogin()
{
	qDebug() << "SucessLogin";
	QObject::connect(navigationUI::Get(),SIGNAL(subNavPressed(QJsonObject)),this,SLOT(subNavPressed(QJsonObject)));
	initNavigation();
}

void Controller::reBuildViewStructures()
{
	QMapIterator<QString, QJsonObject> i(Model::Get()->cachedViewStructures);
	while (i.hasNext()) {
		i.next();

		StructureViewGroupsUI* strct = new StructureViewGroupsUI(0,i.value(),QStringList(),false);

		QJsonObject savedObj = strct->save();
		//	qDebug()<< __FILE__ << __LINE__ << savedObj;
		//qDebug() << __FILE__ << __LINE__  <<"SAVE: editControllerSavePressed"<< savedObj;
	//	Controller::Get()->updateJson(savedObj.value("document_id").toString(),"ViewStructure",QJsonDocument(savedObj));

		}

}

void Controller::showDisplayDataReturned(QJsonDocument document)
{

	//	QObject::disconnect(new Database(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showDisplayDataReturned(QJsonDocument)));
	StructureViewGroupsUI::ShowUI(document.object());
}

void Controller::loadNavigationData(QJsonDocument document)
{
	//	QObject::disconnect(new Database(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(loadNavigationData(QJsonDocument)));
	//qDebug() << "load";
	navigationUI::Get()->loadMainNavigation(document);
}

void Controller::subNavPressed(QJsonObject view)
{
	qDebug() << __FILE__ << __LINE__  << view;

	if(AccessController::Get()->hasReadAccess(view))
		if(view.value("Type").toString().contains("Entity") && view.value("Card") != QJsonValue::Undefined ){
			if(view.value("Select").toString().contains("Index")){
				int card = view.value("Card").toInt();
				qDebug() << __FILE__ << __LINE__  <<"Cards"<< card;
				//queryIndexView(card);
				IndexUI::ShowUI(card);

				}
			else{
				//	Database* database  = new Database();
				//	QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(subNavPressedData(QJsonDocument)));
				//qDebug() << __FILE__ << __LINE__  <<"getDocument"<< view.value("Card").toString();
				//	database->getDoc(view.value("Card").toString());
				Controller::Get()->showCreateEditeStrUI(QString::number(view.value("Card").toInt()),false);

				}
			}
		else {if(view.value("Type").toString().contains("Page")){
				//qDebug() << __FILE__ << __LINE__  <<"PAgee"<< view.value("Card").toString();
				//				Database* database  = new Database();
				//QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(subNavPressedPageData(QJsonDocument)));
				qDebug() << __FILE__ << __LINE__ << __func__ ; ///DATABASEER					database->getDoc(view.value("Card").toString());
				}
			}
	else IndexUI::ShowUI(1);
}

void Controller::queryIndexView(QString vStrctKey)
{
	indexDocument_id = vStrctKey;
	//qDebug() << __FILE__ << __LINE__<< indexDocument_id;
	QString card = vStrctKey.replace("ViewStructure::","");
	card.append("::%");
	QString query = QString("SELECT `"+QString(DATABASE)+"`.*,meta("+QString(DATABASE)+").id AS `document_id` FROM `"+QString(DATABASE)+"` WHERE meta("+QString(DATABASE)+").id LIKE '"+card+"' LIMIT 400");
	//qDebug() << __FILE__ << __LINE__ <<"QINDEX : " << query;

	Database* database  = new Database();
	QObject::connect(database,SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(subNavPressedIndexData(QVector<QSqlRecord>)));
	database->query(query);
}

void Controller::editControllerCancelPressed()
{
	navigationUI::Get()->setHidden(false);
	navigationUI::Get()->setParent(MainForm::Get());
	Database* database  = new Database();
	QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(editControllerCancelDataPressed(QJsonDocument)));

	database->getJson("viewstructure","Navigation","","1");

}

SubFieldUI*Controller::getFirstSubField(QString strID,QString feildName)
{
	QString key = strID.split("::").count() > 1?strID.split("::")[1]:strID;

	//	QString key = strID.split("::")[1];
	//	if(getCachedViewStructure(key).value())

	if(isCachedCreateEditUI(key)){
		if(((CreateEditUI*)getCachedCreateEditUI(key))->getFieldsgroups().find(feildName.trimmed()) != ((CreateEditUI*)getCachedCreateEditUI(key))->getFieldsgroups().end()
				&&((CreateEditUI*)getCachedCreateEditUI(key))->getFieldsgroups().value(feildName.trimmed()))
			return ((CreateEditUI*)getCachedCreateEditUI(key))->getFieldsgroups().value(feildName.trimmed())->subFields.first();

		/*	else if(((PageUI*)getCachedPageUI(key))->getFieldsgroups().find(feildName.trimmed()) != ((PageUI*)getCachedPageUI(key))->getFieldsgroups().end()
			&&((PageUI*)getCachedPageUI(key))->getFieldsgroups().value(feildName.trimmed())){
		qDebug() << "PAGEEEEEEEEEEEEEEEEEEEEEEEEEE";
		return ((PageUI*)getCachedPageUI(key))->getFieldsgroups().value(feildName.trimmed())->subFields.first();
		}
*/
		}
	return new SubFieldUI();
}

void Controller::createIndexes(QJsonObject viewStrct)
{
	QString key;
	if(viewStrct.value("document_id") != QJsonValue::Undefined)
		key = viewStrct.value("document_id").toString();
	else key = viewStrct.value("Title").toString();

	//qDebug() << __FILE__ << __LINE__  << viewStrct;
	int i = 0;
	foreach(QJsonValue vg,viewStrct.value("Viewgroups").toArray()){
		//	qDebug() << __FILE__ << __LINE__  << vg;

		foreach(QJsonValue fv,vg.toObject().value("Viewgroup").toObject().value("Fields").toArray()){
			//	qDebug() << __FILE__ << __LINE__  << fv;
			//	qDebug() << __FILE__ << __LINE__  << fvvapn;
			if(fv.toObject().value("IndexField") != QJsonValue::Undefined){
				QString lbl = fv.toObject().value("Label").toString().toLatin1();
				if(lbl.contains("?"))
					lbl = QString(key.at(0)).append(QString::number(i));

				QString indexname = QString(DATABASE).append("_").append(key).append(lbl).append("_idx");
				int indexCount = Controller::Get()->countIndex(indexname);
				if(indexCount > 0)
					continue;
				QString query;
				if(fv.toObject().value("SubFields").toArray().count() > 0){
					if(fv.toObject().value("SubFields").toArray().first().toObject().value("Type").toString().compare("Table") == 0){
						query = "CREATE INDEX `"+indexname+"` ON `AM`(`"+key+"`) WHERE META(`"+QString(DATABASE)+"`).id Like '"+key+":"+lbl+"::%'  AND `"+key+"` LIKE '"+key+"::%' AND `"+key+"` IS NOT MISSING USING GSI";

						}
					else {
						query = "CREATE INDEX `"+indexname+"` ON `AM`(`"+fv.toObject().value("Label").toString()+"`) WHERE META(`"+QString(DATABASE)+"`).id Like '"+key+"::%'  USING GSI";
						}
					}
				//	Database* database  = new Database();
				//database->query(query);
				qDebug() << __FILE__ << __LINE__ <<"Creating Index :" << indexname;
				//qDebug() << __FILE__ << __LINE__  << query;

				while (Prsistance::CountIndexes(indexname) < 1) {
					QThread::sleep(1);
					}
				}
			}
		i++;
		}
}



void Controller::createEditSqlTabel(QJsonObject viewStrct)
{
	QString key;
	if(viewStrct.value("document_id") != QJsonValue::Undefined)
		key = viewStrct.value("document_id").toString();

	//QString tabel = getCachedViewStructure(key).value("Title").toString();

	qDebug() << viewStrct;

	QString query;
	query = "CREATE TABLE `"+key+"` ( `id` mediumint NOT NULL auto_increment, `pagestructure` json DEFAULT NULL, PRIMARY KEY (`id`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;";


}



void Controller::initNavigation()
{
	Database* database  = new Database();
	QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(loadNavigationData(QJsonDocument)));
	qDebug() << __FILE__ << __LINE__ << __func__ ; ///DATABASEER
	database->getJson("viewstructure","Navigation","Default","1");

}

void Controller::editControllerCancelDataPressed(QJsonDocument document)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(editControllerCancelDataPressed(QJsonDocument)));
	navigationUI::Get()->loadMainNavigation(document);
	NavigationEditUI::Get()->setHidden(true);
}

void Controller::subNavPressedData(QJsonDocument documents)
{
	//	qDebug() << __FILE__ << __LINE__  << "SubPreseed" << documents;
	//QObject::disconnect(new Database(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(subNavPressedData(QJsonDocument)));
	QString key = documents.object().value("document_id").toString().split("::")[1];
	if(isCachedCreateEditUI(key)){
		//((CreateEditUI*)getCachedCreateEditUI(key))->fill(QJsonObject(),);
		MainForm::Get()->ShowDisplay(((CreateEditUI*)getCachedCreateEditUI(key)));
		}
	//CreateEditUI::ShowUI(documents.object(),QJsonObject(),false);
	//if()
}
/**
 * @brief Controller::subNavPressedIndexData
 * @param documents
 * @return
 */
void Controller::subNavPressedIndexData(QVector<QSqlRecord> documents)
{
	//QObject::disconnect(new Database(),SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(subNavPressedIndexData(QVector<QSqlRecord>));
	qDebug() << __FILE__ << __LINE__ << __func__  << documents; ///DATABASEER
	//if(!indexDocument_id.isEmpty())
	//	IndexUI::ShowUI(this->indexDocument_id,documents);

	this->indexDocument_id = "";
}

void Controller::subNavPressedPageData(QJsonDocument document)
{
	//QObject::disconnect(new Database(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(subNavPressedPageData(QJsonDocument)));
	//qDebug() << __FILE__ << __LINE__<< document;
	PageUI::ShowUI(document.object());
}
/**
 * @author Michael Bishara
 */
Controller* Controller::p_instance = 0;
Controller* Controller::Get()
{
	if (p_instance == 0){
		//	QThread* thread = new QThread;
		p_instance = new Controller();
		//	p_instance->moveToThread(thread);
		//	thread->start();
		}


	return p_instance;
}

void Controller::Count(const QString table)
{
	Prsistance::Get()->count(table);
}

int Controller::countIndex(const QString index)
{
	return Prsistance::CountIndexes(index);
}

void Controller::getDoc(const QString& select, const QString &tabel, const QString &key, const QString &id)
{
	Database* database  = new Database();
	QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(getDocData(QJsonDocument)));
	qDebug() << __FILE__ << __LINE__ << __func__ ; ///DATABASEER
	//database->getJson("viewstructure","ViewStructure",key);
	database->getJson(select,tabel,key,id);

}
void Controller::getDocData(QJsonDocument document)
{
	//QObject::disconnect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(getDocData(QJsonDocument)));
	emit gotDocument(document);
}
void Controller::getSelectList(QString table, QString select,QString condition)
{

	QObject::connect(Prsistance::Get(),SIGNAL(GotSelectList(QVector<QSqlRecord>)),Controller::Get(),SLOT(GetSelectListData(QVector<QSqlRecord>)));
	Prsistance::GetSelectList(table,select,condition);
}
void Controller::getJsonEntityFieldsList(QString table, QString select,QString condition)
{

	//	QObject::connect(Prsistance::Get(),SIGNAL(GotJsonSelectList(QVector<QSqlRecord>)),Controller::Get(),SLOT(GetJsonListData(QVector<QSqlRecord>)));
	Prsistance::GetSelectList(table,select,condition);
}

void Controller::GetSelectListData(QVector<QSqlRecord> items)
{

	QObject::disconnect(Prsistance::Get(),SIGNAL(GotSelectList(QVector<QSqlRecord>)),Controller::Get(),SLOT(GetSelectListData(QVector<QSqlRecord>)));
	emit gotSelectListData(items);
}



void Controller::getLastKey()
{
	//	Database* database  = new Database();
	qDebug() <<  __FILE__ << __LINE__ <<"GOTTTTLASTTTTKEYYY CONTROLLER" ;
	//QObject::connect(new Database(),SIGNAL(gotLastKey(QString)),Controller::Get(),SLOT(getLastKeyData(QString)));
}

/*
void Controller::getValue(QString key)
{
	Database* database  = new Database();
	QObject::connect(database,SIGNAL(gotValue(QString)),this,SLOT(getValueData(QString)));
	database->getDoc(key);
}

void Controller::getValueData(QString value)
{
	//	QObject::disconnect(new Database(),SIGNAL(gotValue(QString)),this,SLOT(getValueData(QString)));
	emit gotValue(value);
}

*/
void Controller::getLastKeyData(QString key)
{
	//qDebug() << __FILE__ << __LINE__ <<"GOTTTTLASTTTTKEYYY CONTROLLER" << key;
	//QObject::disconnect(new Database(),SIGNAL(gotLastKey(QString)),Controller::Get(),SLOT(getLastKeyData(QString)));
	emit Controller::Get()->gotLastKey(key);
}



QString Controller::getDatabaseName()
{
	return Prsistance::GetDatabaseName();
}

QList<QString> Controller::select(const QString query)
{
	query.count();
	//TODO
	return QList<QString>();
}

QVector<QJsonDocument> Controller::getAll(const QString entity, const QString condition)
{
	return Prsistance::GetALL(entity,condition);
}

QString Controller::toString(QString key, QJsonValue value)
{
	QString data;

	QString dtoCompare = QString::fromUtf8("تاريخ");
	if(key.compare(dtoCompare) == 0 || key.contains("Date")){
		QDateTimeEdit *date = new QDateTimeEdit;
		date->setHidden(true);
		date->setDateTime(QDateTime::fromString(value.toString(),Qt::ISODate));
		data  =  date->dateTime().toString("dd/MM/yyyy");
		}

	else if(value.isArray()){
		QJsonArray array = value.toArray();
		for(int j = 0; j < array.count(); j++){
			if(array.at(j).isArray())
				data += toString("",array.at(j).toArray());
			else if(array.at(j).isObject()){
				//	qDebug() << __FILE__ << __LINE__ <<"Obj" << array.at(j).toObject();
				if(array.at(j).toObject().value("Value") != QJsonValue::Undefined)
					data += array.at(j).toObject().value("Value").toString();
				else if(array.at(j).toObject().value("merplyTabel") != QJsonValue::Undefined){
					qDebug() << __FILE__ << __LINE__  << "TODO:"<<"printValues of table";
					}
				}
			else data += array.at(j).toString();

			if(j < array.count()-1)
				data += ",";
			}
		}else if(value.isString())
		data = value.toString();
	else if(value.isObject()){
		if(value.toObject().value("Value") != QJsonValue::Undefined)
			data += value.toObject().value("Value").toString();
		}
	else if(value.isDouble()){
		data += QString::number(value.toDouble());
		}
	else {
		//	qDebug()<< __FILE__ << __LINE__ << "toString  ERROR TYPE IS NOT DEFIENED" << value;
		}

	return data;
}

bool Controller::documentInList(QVector<QJsonDocument> all, QString key)
{
	foreach(QJsonDocument d,all){
		if(d.object().value("document_id").toString().compare(key) == 0)
			return true;
		}
	return false;
}

QVector<QJsonDocument> Controller::getEnities()
{
	return Prsistance::GetALL("ViewStructure",QString(DATABASE).append(".Type =\"Entity\""));
}

/*
void Controller::getFields(QString Title, int)
{
	if(!Title.isEmpty() && Title.compare("_") != 0){
		Database* database  = new Database();
		QObject::connect(database,SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(getFieldsData(QVector<QJsonDocument>)));
		QString query = "SELECT array_star("+QString(DATABASE)+".Viewgroups[*].Viewgroup).Fields FROM  `"+QString(DATABASE)+"` WHERE META(`"+QString(DATABASE)+"`).id = '"+Title+"'";
		//	qDebug() << __FILE__ << __LINE__  << "getFields"<<query;
		qDebug() << __FILE__ << __LINE__ << __func__ ; ///DATABASEER
		database->query(query);
		}
}



void Controller::getFieldsData(QVector<QJsonDocument> documents)
{
	//CreateEditUI::ShowUI(document.object(),QJsonObject());
	//	QObject::disconnect(new Database(),SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(getFieldsData(QVector<QSqlRecord>));

	if(!documents.isEmpty() ){
		QStringList fieldsName;
		foreach(QJsonValue fv,documents.first().object().value("Fields").toArray()){
			foreach(QJsonValue fvvapn,fv.toArray()){
				fieldsName << fvvapn.toObject().value("Label").toString();
				foreach(QJsonValue subFld,fvvapn.toObject().value("SubFields").toArray()){
					if(subFld.toObject().value("Type").toString().compare("Table") == 0){
						QString tableName= fieldsName.count() > 0?fieldsName.at(fieldsName.count()-1):"";
						fieldsName.removeLast();
						foreach(QJsonValue clmn,subFld.toObject().value("Columns").toArray()){
							fieldsName <<clmn.toObject().value("Header").toString().append("$").append(tableName);
							}
						}
					}
				}
			}
		//qDebug() << __FILE__ << __LINE__  <<"Fieldss"<<fieldsName;
		emit gotFieldsData( fieldsName);
		}
}



void Controller::getIndexHeader(QString title)
{
	if(!title.isEmpty() && title.compare("_") != 0){
		Database* database  = new Database();
		QObject::connect(database,SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(getIndexHeaderData(QVector<QJsonDocument>)));
		QString query = "SELECT array_star("+QString(DATABASE)+".Viewgroups[*].Viewgroup).Fields FROM  `"+QString(DATABASE)+"` WHERE META(`"+QString(DATABASE)+"`).id = '"+title+"'";
		//qDebug() << __FILE__ << __LINE__  << "getFields"<<query;
		qDebug() << __FILE__ << __LINE__ << __func__ ; ///DATABASEER
		database->query(query);
		}
}

void Controller::getIndexHeaderData(QVector<QJsonDocument> documents){
	//	QObject::disconnect(new Database(),SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(getIndexHeaderData(QVector<QSqlRecord>));
	if(!documents.isEmpty() ){
		QStringList fieldsName;
		foreach(QJsonValue fv,documents.first().object().value("Fields").toArray()){
			foreach(QJsonValue fvvapn,fv.toArray()){
				if(fvvapn.toObject().value("ShowInIndex") == QJsonValue::Undefined)
					continue;
				fieldsName << fvvapn.toObject().value("Label").toString();
				foreach(QJsonValue subFld,fvvapn.toObject().value("SubFields").toArray()){
					if(subFld.toObject().value("Type").toString().compare("Table") == 0){
						//QString tableName= fieldsName.count() > 0?fieldsName.at(fieldsName.count()-1):"";
						fieldsName.removeLast();
						foreach(QJsonValue clmn,subFld.toObject().value("Columns").toArray()){
							fieldsName <<clmn.toObject().value("Header").toString();
							}
						}
					}
				}
			}
		//qDebug() << __FILE__ << __LINE__  <<"Fieldss"<<fieldsName;
		emit gotFieldsData(fieldsName);
		}

	//qDebug() << __FILE__ << __LINE__  <<"Fieldss"<<documents;
}
*/
void Controller::getViewStructures()
{
	Database* database  = new Database();
	QObject::connect(database,SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(getViewStructuresData(QVector<QSqlRecord>)));
	QString query = " SELECT `id` AS strctKey,`key` AS strctName, `viewstructure` AS viewstructure FROM ViewStructure ";
	//qDebug() << __FILE__ << __LINE__ << __func__ ; ///DATABASEER
	database->query(query);

}

void Controller::getViewStructuresData(QVector<QSqlRecord> documents){

	foreach(QSqlRecord stct,documents){
		QVariant structKey = stct.value("strctKey");
		QVariant structName = stct.value("strctName");
		QVariant structValue = stct.value("viewstructure");
		QJsonObject strctObj = QJsonDocument::fromJson(structValue.toString().toUtf8()).object();
		strctObj.insert("document_id",structKey.toString());
		strctObj.insert("document_Name",structName.toString());

		//	qDebug() << __FILE__ << __LINE__ << "document_id" <<strctObj.value("document_id").toString();
		insertCachedViewStructure(QString::number(structKey.toInt()),strctObj);
		buildViewStructureIndexFieldsNamesList(strctObj);

		}
	buildCachedCreateEditUI();
	//buildCachedIndexUI();

	//reBuildViewStructures(); // OneTime Run for the migration to MySQL

	//Prsistance::Get()->CreateViewStructureTabels(); //OneTime Run for the migration to MySQL
}
void Controller::getPageStructures()
{
	Database* database  = new Database();
	QObject::connect(database,SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(getPageStructuresData(QVector<QSqlRecord>)));
	QString query = " SELECT id , pagestructure AS pagestructure FROM PageStructure ";

	database->query(query);
}

void Controller::getPageStructuresData(QVector<QSqlRecord> documents){

	foreach(QSqlRecord stct,documents){
		QVariant structKey = stct.value("id");
		QVariant structValue = stct.value("pagestructure");
		insertCachedPageStructure(structKey.toInt(),QJsonValue::fromVariant(structValue).toObject());
		}
	buildCachedPageUI();
}
void Controller::buildCachedCreateEditUI()
{
	foreach (QString structName, getCachedViewStructures().keys()) {
		CreateEditUI* createEditUI =  new CreateEditUI(0,getCachedViewStructure(structName), QJsonObject());
		insertCachedCreateEditUI(structName,createEditUI);
		createEditUI->fill(getCachedViewStructure(structName), QJsonObject());
		//qDebug() << structName;
		}
}

void Controller::buildCachedIndexUI()
{
	foreach (QString structName, getCachedViewStructures().keys()) {
		IndexUI* indexUI =  new IndexUI(0);
		insertCachedCreateEditUI(structName,indexUI);
		indexUI->fill(getCachedViewStructure(structName).value("document_id").toString().toInt());
		//qDebug() << structName;
		}
}

void Controller::buildCachedPageUI()
{
	foreach (int structName, getCachedPageStructures().keys()) {
		PageUI* pageUI =  new PageUI(0,getCachedPageStructure(structName));
		insertCachedPageUI(structName,pageUI);
		pageUI->fill(getCachedPageStructure(structName));
		//qDebug() << structName;
		}
}


void Controller::updateLayoutViewGroups(QString entityName,QList<StructureViewsEditUI*> sVEUIs)
{
	QStringList groups;
	foreach(StructureViewsEditUI* viewgroup,sVEUIs){
		if(viewgroup->Style->currentText().contains("horizontail"))
			if(!viewgroup->joinCheck->isChecked())
				if(!groups.contains(viewgroup->groupName->text()))
					groups << viewgroup->groupName->text();
		}
	//if(!groups.isEmpty())
	{

	layoutViewGroups.insert(entityName,groups);
	if(groups.isEmpty()){
		groups << "default";
		layoutViewGroups.insert(entityName,groups);
		}
	//qDebug() << __FILE__ << __LINE__  << layoutViewGroups;
	}
}

QStringList Controller::getLayoutViewGroups(QString entity)
{
	return layoutViewGroups.value(entity);

}
void Controller::storeJson(const QString& key, const QString& tabel, QJsonDocument document)
{
	//Fields array
	//	qDebug() << Prsistance::GenetrateCreateTabelQuery(document);
	//	return;

	Database* database  = new Database();
	QObject::connect(database,SIGNAL(saved(QString)),this,SIGNAL(saved(QString)));

	QString strJson(document.toJson(QJsonDocument::Compact));
	QString query;
	if(key.isEmpty())
		query = "INSERT INTO `"+tabel+"` (`viewstructure`)"
									  " VALUES ('"+strJson+"') ;";
	else
		query = "INSERT INTO `"+tabel+"` (`key`,`viewstructure`)"
									  " VALUES ('"+key+"','"+strJson+"') ;";
	database->insert(query);
}

void Controller::updateJson(const QString& id,const QString& tabel,QJsonDocument document)
{
	//	qDebug() << Prsistance::GenetrateCreateTabelQuery(document);
	//	return;

	Database* database  = new Database();
	QObject::connect(database,SIGNAL(saved(QString)),this,SIGNAL(saved(QString)));
	QString strJson(document.toJson(QJsonDocument::Compact));
	QString query;
	query = "UPDATE `"+tabel+"` SET `viewstructure` =  '"+strJson+"' WHERE id = LAST_INSERT_ID('"+id+"') ;";
	database->insert(query);
}

void Controller::showCreateEditeStrUI(QString str,bool create)
{
	//qDebug() << __FILE__ << __LINE__  << str.split("::")[1] <<"Check cached";
	QString key = str.split("::").count() > 1?str.split("::")[1]:str;
	if(create){
		Database* database  = new Database();
		QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showCreateEditeStrUICreateTrueData(QJsonDocument)));
		database->getJson("viewstructure","ViewStructure",key,"");
		//database->getDoc(str);
		}
	else if(!key.isEmpty() && isCachedCreateEditUI(key)){
		qDebug() << __FILE__ << __LINE__  << key <<"Cached" ;
		//MainForm::Get()->ShowDisplay(->getP_instance());
		//qDebug() << ((CreateEditUI*)(Controller::Get()->getStructure(key)))->getViewStructure();
		//((CreateEditUI*)(Controller::Get()->getStructure(key)))->ShowUI(structNames.value(key),QJsonObject(),false);
		MainForm::Get()->ShowDisplay(((CreateEditUI*)(getCachedCreateEditUI(key))));
		}
	else{
		qDebug() << __FILE__ << __LINE__  << key <<"NOT Cached";
		Database* database  = new Database();
		QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showCreateEditeStrUIData(QJsonDocument)));
		database->getJson("viewstructure","ViewStructure","",key);
		}

}
void Controller::showCreateEditeStrUIData(QJsonDocument str)
{
	//	QObject::disconnect(new Database(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showCreateEditeStrUIData(QJsonDocument)));
	//CreateEditUI::ShowUI(str.object(),QJsonObject(),true);
	QString key = str.object().value("document_id").toString().split("::").count() > 1?str.object().value("document_id").toString().split("::")[1]:str.object().value("document_id").toString();

	if(isCachedCreateEditUI(key)){
		//((CreateEditUI*)getCachedCreateEditUI(key))->fill(QJsonObject(),);
		MainForm::Get()->ShowDisplay(((CreateEditUI*)getCachedCreateEditUI(key)));
		}
	else {
		qDebug() << __FILE__ << __LINE__  << key <<"NOT Cached" << key;
		//new CreateEditUI
		}
}
void Controller::showCreateEditeStrUICreateTrueData(QJsonDocument str)
{
	//	QObject::disconnect(new Database(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showCreateEditeStrUICreateTrueData(QJsonDocument)));
	QString key = str.object().value("document_id").toString().split("::")[1];
	if(isCachedCreateEditUI(key)){
		//((CreateEditUI*)getCachedCreateEditUI(key))->fill(QJsonObject(),);
		MainForm::Get()->ShowDisplay(((CreateEditUI*)getCachedCreateEditUI(key)));
		}
}
void Controller::showCreateEditeValueUI(QString key)
{
	if(key.split("::").count() > 1){
		Database* database  = new Database();
		QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showCreateEditeValueUIData(QJsonDocument)));
		database->getJson("viewstructure","ViewStructure",key.split("::")[1],"");
		}
}

void Controller::showCreateEditeValueUIData(QJsonDocument value)
{
	//	QObject::disconnect(new Database(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showCreateEditeValueUIData(QJsonDocument)));
	QString key  = value.object().value("document_id").toString().split("::")[0];
	if(!key.isEmpty()){
		//qDebug() << __FILE__ << __LINE__  << key <<"is Cached Value";
		//((CreateEditUI*)Model::Get()->cachedCreateEditUI.value(key))->ShowUI(QJsonObject(),value.object(),false);
		//((CreateEditUI*)MainForm::Get()->GetCurrentDisplay())->ShowUI(QJsonObject(),value.object());
		//MainForm::Get()->ShowDisplay();



		if(isCachedCreateEditUI(key)){
			((CreateEditUI*)getCachedCreateEditUI(key))->fillData(value.object());
			MainForm::Get()->ShowDisplay(((CreateEditUI*)getCachedCreateEditUI(key)));
			}
		}


}

void Controller::linkPressed(QJsonObject link)
{
	qDebug() << __FILE__ << __LINE__  << link;

	if(link.value("Type").toString().contains("Link")){
		//	new Database()->getDoc("ViewStructure::"+QString(view.value("EntityId").toString()));
		Database* database  = new Database();
		QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(linkPressedData(QJsonDocument)));
		QString query = QString("SELECT `"+QString(DATABASE)+"`.*,meta("+QString(DATABASE)+").id AS `document_id` FROM `"+QString(DATABASE)+"` WHERE "+QString(DATABASE)+".Title = '"+link.value("Source").toString()+"'");
		//qDebug() << __FILE__ << __LINE__ <<"Q : " << query;
		database->query(query);
		//qDebug() << __FILE__ << __LINE__  << view.value("Card").toString() << d;
		}

}
void Controller::linkPressedData(QJsonDocument document)
{
	//QObject::disconnect(new Database(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(linkPressedData(QJsonDocument)));
	QString key = document.object().value("document_id").toString();
	if(isCachedCreateEditUI(key))
		MainForm::Get()->ShowDisplay(((CreateEditUI*)getCachedCreateEditUI(key)));
	//CreateEditUI::ShowUI(document.object(),QJsonObject(),false);
}

void Controller::addSubNavigation(double key, QList<QTreeWidgetItem*> subNav)
{
	Model::Get()->addSubNavigation(key,subNav);
}

QList<QTreeWidgetItem*> Controller::getSubNavigation(double key)
{
	return Model::Get()->getSubNavigation(key);
}

bool Controller::removeSubNavigation(double key)
{
	return Model::Get()->removeSubNavigation(key);
}

void Controller::clearSubNavigation()
{
	Model::Get()->clearSubNavigation();
}

void Controller::addPage(double key, QJsonObject page)
{
	Model::Get()->addPage(key,page);
}

QJsonObject Controller::getPage(double key)
{
	return Model::Get()->getPage(key);
}

bool Controller::removePage(double key)
{
	return Model::Get()->removePage(key);
}

void Controller::clearPages()
{
	Model::Get()->clearPages();
}

void Controller::addMainNavigation(double key, QString mainNav)
{
	Model::Get()->addMainNavigation(key,mainNav);
}

QString Controller::getMainNavigation(double key)
{
	return Model::Get()->getMainNavigation(key);
}

bool Controller::removeMainNavigation(double key)
{
	return Model::Get()->removeMainNavigation(key);
}

void Controller::clearMainNavigation()
{
	Model::Get()->clearMainNavigation();
}
bool Controller::saveNavigation()
{

	saveNavigationPages();
	QMapIterator<double, QString > i(Model::Get()->getMainNavigationModel());
	//QVector<QJsonDocument> mainNavs;
	QJsonObject navigation;
	QJsonArray mainNavs;
	while (i.hasNext()) {
		i.next();
		QJsonObject mainNav;
		mainNav.insert("Title",i.value());
		mainNav.insert("ID",i.key());
		QJsonArray items;
		//qDebug() << __FILE__ << __LINE__  << i.key();
		foreach(QTreeWidgetItem * tab,getSubNavigation(i.key())){
			items.append(saveSubNavigation(tab));
			}
		mainNav.insert("Items",items);
		//	qDebug() << __FILE__ << __LINE__  << mainNav;
		//mainNavs.append(QJsonDocument(mainNav));
		mainNavs << mainNav;
		}

	navigation.insert("MainNavigations",mainNavs);
	navigation.insert("document_id","NavigationUI::1");
	Controller::Get()->updateJson("1","Navigation",QJsonDocument(navigation));
	return true;

}

bool Controller::saveNavigationPages()
{
	//	qDebug() << __FILE__ << __LINE__  << "SaveN";
	bool savedPages = true;
	QMapIterator<double, QJsonObject > i(Model::Get()->getPages());
	while (i.hasNext()) {
		i.next();
		QJsonObject page = i.value();
		if(page.value("CardData") != QJsonValue::Undefined){
			QJsonObject cardData = page.value("CardData").toObject();
			if(page.value("Card") != QJsonValue::Undefined && page.value("Card").toString().compare("-1") != 0){
				cardData.insert("document_id",page.value("Card").toString());
				//savedPages = savedPages ;
				Controller::Get()->updateJson(page.value("Card").toString(),"Page",QJsonDocument(cardData));

				}else{
				if(page.value("Type").toString().compare("Page")){
					Controller::Get()->storeJson("","Page",QJsonDocument(cardData));
					}

				qDebug() << __FILE__ << __LINE__ <<"withoutID" << page;
				}
			page.remove("CardData");
			addPage(i.key(),page);
			}
		}
	return savedPages;
}
QJsonObject Controller::saveSubNavigation(QTreeWidgetItem * item)
{

	QJsonObject itemTab = QJsonObject();
	itemTab.insert("Title",item->text(0));
	itemTab.insert("ID",item->text(1).toDouble());
	itemTab.insert("Page",getPage(item->text(1).toDouble()));
	itemTab.insert("TabPermissions",getPage(item->text(1).toDouble()).value("TabPermissions"));

	//qDebug() << __FILE__ << __LINE__  << item->text(1).toDouble() << getPage(item->text(1).toDouble());
	if(item->childCount() > 0){
		QJsonArray items = QJsonArray();
		for(int i = 0; i < item->childCount();i++)
			items << saveSubNavigation(item->child(i));
		itemTab.insert("Items",items);
		}
	return itemTab;
}

void Controller::getReport(QJsonObject clmns,QString filter)
{
	bool addedSelectItems = false;

	if(clmns.value("QueryUI") != QJsonValue::Undefined){
		qRegisterMetaType<QVector<QJsonDocument> >("MyStruct");
		Database* database  = new Database();
		QObject::connect(database,SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(getReportData(QVector<QSqlRecord>)));
		database->query(clmns.value("QueryUI").toObject().value("Query").toString().replace("#QUERYMERPLY","")); //TODO: CACHED FLAGG
		//	qDebug() << __FILE__ << __LINE__<<"getReport Querii"  << clmns;
		}
	else if(clmns.value("Columns").isArray()){
		//QJsonArray arr = (columns.value("Columns").toArray());
		int i = 0;
		QString query;
		QString orderby;
		orderby += " ORDER BY ";
		bool hasSelectQuery = false;
		foreach(QJsonValue clmn,clmns.value("Columns").toArray()){
			QJsonObject clmnObj = clmn.toObject();

			if(clmn.toObject().value("Type").toString().compare("Text") == 0){
				//qDebug() << __FILE__ << __LINE__  <<"Text"<< clmn;
				}
			else if(clmn.toObject().value("LocalSource")!= QJsonValue::Undefined){
				if(hasSelectQuery && i > 0 && i < clmns.value("Columns").toArray().count()){
					query+= " UNION ALL ";
					orderby += ",";
					}
				QString source = clmnObj.value("Source").toString().split("::")[1];
				addedSelectItems = true;
				hasSelectQuery = true;
				query+= getLocalSourceReport(clmn.toObject(),i,filter);
				orderby += "`"+source+QString::number(i)+"Key`";
				}
			else if(clmnObj.value("Source").toString().split("::").count() > 1
					&&	!clmnObj.value("Select").toString().isEmpty())
				{
				addedSelectItems = true;
				QString source = clmnObj.value("Source").toString().split("::")[1];

				QString selectStr = clmnObj.value("Select").toString();
				QString uniqueRef = QString(source.toLatin1().at(0)).append(QString(selectStr.toLatin1().at(0))).append(QString::number(i)) ;

				if(hasSelectQuery && i > 0 && i < clmns.value("Columns").toArray().count()){
					query+= " UNION ALL ";
					orderby += ",";
					}
				hasSelectQuery = true;
				query += "SELECT ";
				query += "`"+selectStr+"` AS `"+clmnObj.value("Header").toString()+"`";
				query += " , META(`"+uniqueRef+"d`).id AS `"+source+QString::number(i)+"Key`";

				orderby += "`"+source+QString::number(i)+"Key`";
				//	qDebug() << __FILE__ << __LINE__  << clmnObj.value("LocalFilter").toString() << clmnObj.value("LocalFilter").toString().split("::").count() <<clmnObj.value("Source").toString() <<clmnObj.value("Source").toString().split("::").count();
				if(clmnObj.value("LocalFilter") != QJsonValue::Undefined
						&&	clmnObj.value("Source").toString().split("::").count() > 1
						&&	clmnObj.value("LocalFilter").toString().split("::").count() > 1)
					{

					QString localFilter = clmnObj.value("LocalFilter").toString().split("::")[1];
					QString entityFilter = clmnObj.value("EntityFilter").toString();




					query += " , META(`"+uniqueRef+"a`).id AS `"+localFilter+QString::number(i)+"Key`";
					query += " , META(`"+uniqueRef+"d`).id AS `Join"+localFilter+QString::number(i)+"Key`";
					query += "FROM ";
					query += QString(DATABASE) +" "+uniqueRef+"d UNNEST `"+uniqueRef+"d`.Fields "+uniqueRef+"ff UNNEST "+uniqueRef+"d.Fields "+uniqueRef+"f UNNEST (Array item.`"+entityFilter+"`[0] FOR item IN "+uniqueRef+"f END)[0] "+uniqueRef+"fk  INNER JOIN "+QString(DATABASE) +"  "+uniqueRef+"a ON KEYS "+uniqueRef+"fk.`Key`";
					query += "UNNEST "+uniqueRef+"a  af UNNEST af.Fields `"+uniqueRef+"aff` UNNEST (Array item.Name[0] FOR item IN "+uniqueRef+"aff END) "+uniqueRef+"afs "; //UNNEST (Array item.Salutation[0] FOR item IN "+uniqueRef+"ff END) IC2fkrk";
					query += "WHERE ";
					query += "META("+uniqueRef+"d).id LIKE '"+source+"::%'";
					query += QString(" AND ") + QString("(Array item.`"+selectStr+"`[0] FOR item IN `"+uniqueRef+"ff` END)[0] ");
					query += QString(" AND ")+ QString("META(`"+uniqueRef+"a`).id LIKE '"+localFilter+"::%' ");


					}
				else {
					query += "FROM ";
					query += QString(DATABASE) +" `"+uniqueRef+"d` ";
					query += "WHERE ";
					query += "META(`"+uniqueRef+"d`).id LIKE '"+source+"::%'";
					//query += QString(" AND ") + QString("(Array item.`"+selectStr+"`[0] FOR item IN "+uniqueRef+"ff END)[0] ");
					}
				if(clmnObj.value("LocalSource") != QJsonValue::Undefined){
					//	qDebug() << __FILE__ << __LINE__  <<"clmnObj.value().toString()";
					}

				//qDebug() << __FILE__ << __LINE__  << i << (clmns.value("Columns").toArray().count() - 1) << query;

				}
			i++;
			}
		query+= orderby;
		//qDebug() << __FILE__ << __LINE__ <<"getReport" << query;
		/*
		QString query;
		query += "SELECT ";
		int iS = 0;
		foreach(QString s, select){
			iS++;
			query+= s;
			if(iS < select.count())
				query += ", ";

			}
		query += "FROM ";
		int iF = 0;
		foreach(QString f, from){
			iF++;
			query+= f;
			if(iF < from.count())
				query += "INNER JOIN ";

			}
		query += "WHERE ";
		int iW = 0;
		foreach(QString w, where){
			iW++;
			query+= w;
			if(iW < where.count())
				query += "AND ";

			}


		qDebug() << __FILE__ << __LINE__  << query;
		*/
		//qDebug() << __FILE__ << __LINE__  << "Before Query";

		if(addedSelectItems){
			//qDebug() << __FILE__ << __LINE__  <<"Report Q:"<< query;
			//qRegisterMetaType<QVector<QJsonDocument> >("MyStruct");
			//QObject::connect(new Database(),SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(getReportData(QVector<QSqlRecord>),Qt::QueuedConnection);
			//new Database()->query(query);
			//	emit queryDatabase(query);
			}
		else emit gotReportData(QVector<QSqlRecord>());


		}



}

QString Controller::getLocalSourceReport(QJsonObject clmn,int index,QString filter)
{
	QStringList selectField = clmn.value("Select").toString().split("$");
	QString select = selectField.count() > 1?selectField[0]:clmn.value("Select").toString();
	QString field = selectField.count() > 1?selectField[1]:clmn.value("Select").toString();

	QString source = clmn.value("Source").toString().split("::")[1];
	//	QString sourceEFilter = clmn.value("SourceEntityFilter").toString();
	//	QString sourceLFilter = clmn.value("SourceLocalFilter").toString();
	QString uniqueRef = QString(source.at(0)).append(QString(select.at(0))).append(QString::number(rand())) ;


	QString query;
	query = "SELECT (Array itemw.`"+select+"` FOR itemw IN ((Array item.`"+field+"`[0].`merplyTabel` FOR item IN "+uniqueRef+"f END)[0])END) AS `"+clmn.value("Header").toString()+"` , META("+uniqueRef+"d).id AS `"+source+QString::number(index)+"Key`"
																																																													"FROM default "+uniqueRef+"d UNNEST "+uniqueRef+"d.Fields "+uniqueRef+"f WHERE META("+uniqueRef+"d).id = '"+filter+"' "
																																																																																									   "AND (Array item.`"+field+"`[0].`merplyTabel` FOR item IN "+uniqueRef+"f END)";
	//qDebug() << __FILE__ << __LINE__  << "LocalSorce Q: " << query;
	return query;
}

void Controller::insertCachedCreateEditUI(QString key, QWidget* instance)
{
	//qDebug() << __FILE__ << __LINE__  << "insert"<<key<< instance;
	Model::Get()->cachedCreateEditUI.insert(key,instance);
}

QWidget* Controller::getCachedCreateEditUI(QString key)
{
	//qDebug() << __FILE__ << __LINE__ <<"getCachedCreateEditUI"<< key;
	return (Model::Get()->cachedCreateEditUI.value(key));

}

bool Controller::isCachedCreateEditUI(QString key)
{
	//qDebug() << __FILE__ << __LINE__  << "insert"<<key<< instance;
	return Model::Get()->cachedCreateEditUI.contains(key);

}

void Controller::insertCachedViewStructure(QString key, QJsonObject viewStrct)
{
	Model::Get()->cachedViewStructures.insert(key,viewStrct);
}

QJsonObject Controller::getCachedViewStructure(QString key)
{
	return Model::Get()->cachedViewStructures.value(key);
}

QMap<QString, QJsonObject> Controller::getCachedViewStructures() const
{
	return Model::Get()->getCachedViewStructures();
}

void Controller::insertCachedPageStructure(int key, QJsonObject viewStrct)
{
	Model::Get()->cachedPageStructures.insert(key,viewStrct);
}

QJsonObject Controller::getCachedPageStructure(int key)
{
	return Model::Get()->cachedPageStructures.value(key);
}

QMap<int, QJsonObject> Controller::getCachedPageStructures() const
{
	return Model::Get()->getCachedPageStructures();
}

void Controller::insertCachedIndexUI(QString key, QWidget* instance)
{
	Model::Get()->cachedIndexUI.insert(key,instance);
}

QWidget*Controller::getCachedIndexUI(QString key)
{
	return (Model::Get()->cachedIndexUI.value(key));
}

bool Controller::isCachedIndexUI(QString key)
{
	return Model::Get()->cachedIndexUI.contains(key);
}

void Controller::insertCachedPageUI(int key, QWidget* instance)
{
	Model::Get()->cachedPageUI.insert(key,instance);
}

QWidget*Controller::getCachedPageUI(int key)
{
	return (Model::Get()->cachedPageUI.value(key));
}

bool Controller::isCachedPageUI(int key)
{
	return Model::Get()->cachedPageUI.contains(key);
}

void Controller::insertCachedViewStructureFieldsNames(int id, QStringList fieldsNames)
{
	Model::Get()->cachedViewStructureFieldsNames.insert(id,fieldsNames);
}

QStringList Controller::getCachedViewStructureFieldsNames(int id)
{
	return (Model::Get()->cachedViewStructureFieldsNames.value(id));
}

void Controller::insertCachedViewStructureIndexFieldsNames(int id, QStringList fieldsNames)
{
	Model::Get()->cachedViewStructureIndexFieldsNames.insert(id,fieldsNames);

}

QStringList Controller::getCachedViewStructureIndexFieldsNames(int id)
{
	return (Model::Get()->cachedViewStructureIndexFieldsNames.value(id));
}

void Controller::insertCachedViewStructureNames(QString name, int id)
{
	Model::Get()->cachedViewStructureNames.insert(name,id);
}

int Controller::getCachedViewStructureNames(QString name)
{
	return (Model::Get()->cachedViewStructureNames.value(name));
}

QStringList Controller::getCachedViewStructureNames()
{
	return (Model::Get()->cachedViewStructureNames.keys());
}

QMap<int,QJsonObject> Controller::getCachedViewStructureSubFields(int id)
{
	return (Model::Get()->cachedViewStructureSubFields.value(id));
}

void Controller::insertCachedViewStructureSubFields(int id, QMap<int,QJsonObject> subFields)
{
	Model::Get()->cachedViewStructureSubFields.insert(id,subFields);
}

void Controller::insertCachedViewStructureTabelFields(int key, QVector<QJsonObject> tabelFields)
{
	Model::Get()->cachedViewStructureTabelFields.insert(key,tabelFields);
}

QVector<QJsonObject> Controller::getCachedViewStructureTabelFields(int key)
{
	return Model::Get()->cachedViewStructureTabelFields.value(key);
}

QMap<int, QVector<QJsonObject> > Controller::getCachedViewStructureTabelFields() const
{
	return Model::Get()->getCachedViewStructureTabelFields();
}



int Controller::getCachedSubFieldsClmnRef(int strctID)
{
	if(subFieldsCounter.contains(strctID)){
		subFieldsCounter.insert(strctID,subFieldsCounter.value(strctID)+1);
		return subFieldsCounter.value(strctID);
		}
	else{

		subFieldsCounter.insert(strctID,0);
		return 0;
		}
}


void Controller::getReportData(QVector<QSqlRecord> documents)
{
	//qDebug() << __FILE__ << __LINE__  << "GotReport Data" << documents;
	//QObject::disconnect(new Database(),SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(getReportData(QVector<QSqlRecord>));
	emit gotReportData(documents);

}


void Controller::getReportTableData(QJsonObject strct)
{
	foreach(QJsonValue clmn, strct.value("Columns").toArray()){
		if(clmn.toObject().value("Type").toString().compare("Database") == 0){
			//	qDebug() << __FILE__ << __LINE__  << clmn.toObject().value("Select").toString() << clmn.toObject().value("Source").toString();
			}
		}
}

int Controller::GetWindowWidth()
{
	return WINDOW_WIDTH;
}

int Controller::GetWindowHeight()
{
	return WINDOW_HEIGHT;
}

int Controller::GetTimeLineWidth()
{
	return TIMELINE_WIDTH;
}

int Controller::GetNavigationWidth()
{
	return NAVIGATION_WIDTH;
}

int Controller::GetNavigationSettingsBarHeight()
{
	return NAVIGATION_CONTROL_HEIGHT;
}

int Controller::GetNavigationMainHeight()
{
	return NAVIGATION_MAIN_HEIGHT;
}

int Controller::GetNavigationSubHeight()
{
	return NAVIGATION_SUB_HEIGHT;
}

QString Controller::getLastKeyID()
{
	//	Database* database  = new Database();
	qDebug() << __FILE__ << __LINE__ <<"getLastKeyID NO DATA";
	return "new Database()->getLastKeyID()";
}

bool Controller::runQRPTDesingerapp()
{
	QProcess *p = new QProcess(this);
	QString programPath;
	programPath= QDir::currentPath()+"/../RPTD/debug/QtRptDesigner" ;
	//qDebug() << __FILE__ << __LINE__  << programPath;
	p->start(programPath);
	return true;
}

void Controller::query(QString query)
{
	Database* database  = new Database();
	QObject::connect(database,SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(queryData(QVector<QSqlRecord>)));
	database->query(query);
}

bool Controller::createEditStore(QJsonObject document)
{
	emit savedQJson(QJsonDocument(document));
	if(!creatEditeItems.isEmpty())
		creatEditeItems.clear();

	QStringList keys = document.keys();
	foreach(QString key,keys){
		if(document.value(key).isObject()){
			if(document.value(key).toObject().value("RemovedRows") != QJsonValue::Undefined){
				createEditRemoveRowItems(document.value(key).toObject().value("RemovedRows").toArray());
				document.value(key).toObject().remove("RemovedRows");
				}
			if(document.value(key).toObject().value("merplyTabel") != QJsonValue::Undefined){
				QJsonObject tbl  = document.value(key).toObject();
				tbl.insert("FieldKey",key);
				creatEditeItems.append(tbl);
				document.remove(key);
				}
			}
		}
	if(creatEditeItems.count() >  0){
		QObject::disconnect(this,SIGNAL(saved(QString)),this,SLOT(createEditStoreItems(QString)));
		QObject::connect(this,SIGNAL(saved(QString)),this,SLOT(createEditStoreItems(QString)));

		//Controller::Get()->storeDoc(key,QJsonDocument(vgsSave));
		}
	else {
		QObject::connect(this,SIGNAL(saved(QString)),this,SIGNAL(savedItems(QString)));
		}

	//qDebug() << __FILE__ << __LINE__ <<document.value("document_id").toString()<< document;

	if(document.value("cas_value") != QJsonValue::Undefined){
		Database* database  = new Database();
		QObject::connect(database,SIGNAL(saved(QString)),this,SIGNAL(saved(QString)));
		//QObject::connect(database,SIGNAL(savedQJson(QJsonDocument)),this,SIGNAL(savedQJson(QJsonDocument)));
		qDebug() << __FILE__ << __LINE__ << __func__ ; ///DATABASEER
		//	database->updateDoc(QJsonDocument(document));
		}
	else{
		Database* database  = new Database();
		QObject::connect(database,SIGNAL(saved(QString)),this,SIGNAL(saved(QString)));
		//	QObject::connect(database,SIGNAL(savedQJson(QJsonDocument)),this,SIGNAL(savedQJson(QJsonDocument)));
		qDebug() << __FILE__ << __LINE__ << __func__ ; ///DATABASEER
		//	database->storeDoc(document.value("document_id").toString(),QJsonDocument(document));
		}
	QObject::disconnect(this,SIGNAL(saved(QString)),this,SIGNAL(savedItems(QString)));

	return true;
}

bool Controller::createEditRemoveRowItems(QJsonArray rowsItems)
{
	bool success = true;
	foreach (QJsonValue row, rowsItems) {
		if(row.toObject().value("documentID") != QJsonValue::Undefined){
			//success =
			deleteDocument(row.toObject().value("documentID").toString().split("::")[0],row.toObject().value("documentID").toString().split("::")[1]);
			qDebug() << __FILE__ << __LINE__ << __func__ ; ///DATABASEER
			}
		}
	return success;
}

void Controller::deleteEntity(const QString& tabel, const QString& id)
{
	qDebug() << __FILE__ << __LINE__ << __func__ ; ///DATABASEER
	Controller::Get()->deleteDocument(tabel,id);
	/*
	if()
		{
		QString strctKey = documentID.split("::")[0];
		QString query = "SELECT (SELECT META(`"+QString(DATABASE)+"`).id AS DocumentID FROM `AM` WHERE META(`"+QString(DATABASE)+"`).id LIKE '"+strctKey+"%' AND  "+strctKey+" LIKE '"+documentID+"') AS ITEMSLIST";
		Database* database  = new Database();
		QObject::connect(database,SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(deleteEntityData(QVector<QSqlRecord>)));
		//	qDebug() << __FILE__ << __LINE__<< query;
		database->query(query);
		}

	//	"SELECT array_star("+QString(DATABASE)+".Viewgroups[*].Viewgroup).Fields FROM  `"+QString(DATABASE)+"` WHERE META(`"+QString(DATABASE)+"`).id = '"+Title+"'";
	//	qDebug() << __FILE__ << __LINE__  << "getFields"<<query;

*/
}

void Controller::saveRefrenceStructures(QJsonObject mainStrct, QJsonObject data)
{
	//qDebug()<< __FILE__ << __LINE__ <<  mainStrct;
	//qDebug()<< __FILE__ << __LINE__ <<  data;
	if(mainStrct.value("Viewgroups").isArray()){
		//	QJsonArray dataVGs =data.value("Fields").toArray();

		foreach (QJsonValue item, mainStrct.value("Viewgroups").toArray()) {
			QJsonObject viewGroupObject = item.toObject().value("Viewgroup").toObject();
			if(viewGroupObject.value("RefrenceFields") != QJsonValue::Undefined){

				foreach(QJsonValue refrenceFields,viewGroupObject.value("RefrenceFields").toArray()){
					QJsonObject newData;
					foreach(QJsonValue refrenceSubFields,refrenceFields.toObject().value("RefrenceSubFields").toArray()){
						//	qDebug()<< __FILE__ << __LINE__ << refrenceSubFields.toObject();
						//qDebug() << data;
						if(refrenceSubFields.toObject().value("RefrenceValue").toString().contains("$")){
							QStringList refrencTblHeader = refrenceSubFields.toObject().value("RefrenceValue").toString().split("$");
							QStringList fieldTblHeader = refrenceSubFields.toObject().value("Field").toString().split("$");

							if(refrencTblHeader.count() > 1 && fieldTblHeader.count() > 1){
								QString dataKey = refrencTblHeader.at(1);
								QString newDataFieldKey = fieldTblHeader.at(0);
								if(data.value(dataKey).toObject().value("merplyTabel") != QJsonValue::Undefined){
									QJsonObject tbl;
									QJsonArray newDataRows;
									QJsonArray oldDataRows;
									bool appendFlag = false;
									if(newData.value(fieldTblHeader.at(1)) != QJsonValue::Undefined){
										oldDataRows = newData.value(fieldTblHeader.at(1)).toObject().value("merplyTabel").toArray();
										appendFlag = true;
										}
									int i = 0;
									foreach(QJsonValue row,data.value(dataKey).toObject().value("merplyTabel").toArray()){
										QJsonObject newDataRow;
										if(appendFlag){
											newDataRow = oldDataRows.at(i).toObject();
											//newDataRows.takeAt(0);
											}
										newDataRow.insert(newDataFieldKey,row.toObject().value(refrencTblHeader.at(0)).toString());

										//newDataRows.insert(i,newDataRow);
										newDataRows << newDataRow;
										//qDebug()<< __FILE__ << __LINE__ << row.toObject().value(refrencTblHeader.at(0));
										i++;
										}

									tbl.insert("merplyTabel",newDataRows);
									newData.insert(fieldTblHeader.at(1),tbl);
									}
								else{
									qDebug() << __FILE__ << __LINE__ <<"NOTATABLE"<< Controller::toString("",data.value(dataKey).toObject());
									}
								///ELSE not Table
								}
							else if(refrencTblHeader.count() > 1){
								QString dataKey = refrencTblHeader.at(1);
								QString newDataFieldKey = fieldTblHeader.at(0);
								if(data.value(dataKey).toObject().value("merplyTabel") != QJsonValue::Undefined){
									QString textTableRow;
									foreach(QJsonValue row,data.value(dataKey).toObject().value("merplyTabel").toArray()){
										textTableRow.append(row.toObject().value(refrencTblHeader.at(0)).toString());
										textTableRow.append("\n");
										}
									if(!textTableRow.isEmpty())
										newData.insert(newDataFieldKey,textTableRow);
									}
								}
							}
						else {
							if(!refrenceSubFields.toObject().value("Field").toString().contains("$"))
								newData.insert(refrenceSubFields.toObject().value("Field").toString(),data.value(refrenceSubFields.toObject().value("RefrenceValue").toString()));
							}

						}

					if(!newData.isEmpty()){
						//	qDebug()<< __FILE__ << __LINE__ << refrenceFields.toObject().value("Source");
						qDebug()<< __FILE__ << __LINE__ << newData;
						newData.insert("document_id",refrenceFields.toObject().value("Source").toString().split("::")[1]);
						Controller::Get()->createEditStore(newData);
						}
					}


				}

			}
		}

}

void Controller::insertUpdateRow(QString query)
{
	Database* database  = new Database();
	QObject::disconnect(database,SIGNAL(saved(QString)),this,SIGNAL(saved(QString)));
	QObject::connect(database,SIGNAL(saved(QString)),this,SIGNAL(saved(QString)));
	database->insert(query);

}

void Controller::createEditStoreItems(QString key)
{
	QObject::disconnect(this,SIGNAL(saved(QString)),this,SLOT(createEditStoreItems(QString)));
	//	bool success = true;
	foreach(QJsonObject tbl,creatEditeItems){
		QString id = QString(key.split("::")[0]).append(":").append(tbl.value("FieldKey").toString());
		//qDebug() << __FILE__ << __LINE__ << id << key;
		foreach(QJsonValue v,tbl.value("merplyTabel").toArray()){
			QJsonObject row = v.toObject();
			if(row.value(QString(key.split("::")[0])) == QJsonValue::Undefined){
				row.insert(QString(key.split("::")[0]),key);
				//	qDebug() << __FILE__ << __LINE__ << "New Row" << row;
				//	success = Controller::Get()->storeDoc(id,QJsonDocument(row));
				}
			else {
				//qDebug() << __FILE__ << __LINE__ << "Update Row" << row;
				//
				qDebug() << __FILE__ << __LINE__  << "DATABASE TODO";
				//	Controller::Get()->updateJson(QJsonDocument(row));
				}
			}
		}
	emit savedItems(key);
}

void Controller::getTabelsData(QString entity, QStringList tbls)
{
	int i = 0;
	QString query;
	query += "SELECT ";
	QString strctID = entity.split("::")[0];
	foreach(QString tbl,tbls){
		if(i > 0)
			query += " , ";

		QString subQuery = "(SELECT `"+QString(DATABASE)+"`.*,meta(`"+QString(DATABASE)+"`).cas AS cas ,meta(`"+QString(DATABASE)+"`).id AS documentID "
																																  "FROM `"+QString(DATABASE)+"`  USE INDEX("+QString(DATABASE).append("_").append(strctID).append(tbl)+"_idx) "
																																																									   "WHERE Meta(`"+QString(DATABASE)+"`).id LIKE '"+strctID+":"+tbl+"::%' AND  `"+strctID+"` LIKE '"+entity+"' AND `"+strctID+"` IS NOT MISSING) AS `"+tbl+"` ";
		query += subQuery;
		i++;
		}
	//qDebug() << __FILE__ << __LINE__<< query;
	Database* database  = new Database();
	QObject::connect(database,SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(queryData(QVector<QSqlRecord>)));
	database->query(query);
}

void Controller::buildViewStructureIndexFieldsNamesList(QJsonObject viewstrct)
{

	QStringList fieldsName;
	QStringList indexFieldsName;
	QMap<int,QJsonObject> subfields;
	QVector<QJsonObject> tabelFields;
	//	qDebug() << viewstrct;
	int subFieldCounter = 0;
	int id = viewstrct.value("document_id").toString().toInt();
	foreach(QJsonValue vg,viewstrct.value("Viewgroups").toArray()){
		//	qDebug() << vg.toObject() << vg.toObject().value("Viewgroup");
		foreach(QJsonValue fv,vg.toObject().value("Viewgroup").toObject().value("Fields").toArray()){

			if(fv.toObject().value("ShowInIndex") != QJsonValue::Undefined)
				indexFieldsName << fv.toObject().value("Label").toString();
			fieldsName << fv.toObject().value("Label").toString();

			foreach(QJsonValue subFld,fv.toObject().value("SubFields").toArray()){
				int currentKey = -1;
				subFieldCounter++;
				if(subFld.toObject().value("clmnNumber") == QJsonValue::Undefined || subFld.toObject().value("clmnNumber").toString().compare("0") == 0){

					subfields.insert(subFieldCounter,subFld.toObject());
					currentKey = subFieldCounter;
					}
				else{
					currentKey = subFld.toObject().value("clmnNumber").toString().toInt();
					//	qDebug()  << __FILE__ << __LINE__<< "TABEL:"<<id  << "CURRENT CKEY FOR SUBFIELD"<< currentKey;
					subfields.insert(currentKey,subFld.toObject());
					}
				if(subFld.toObject().value("Type").toString().compare("Table") == 0){

					QString tableName= fieldsName.count() > 0?fieldsName.at(fieldsName.count()-1):"";
					fieldsName.removeLast();
					subfields.remove(currentKey);

					QJsonObject tabel = subFld.toObject();
					tabel.insert("FieldName",tableName);
					tabelFields.append(tabel);

					if(fv.toObject().value("ShowInIndex") != QJsonValue::Undefined)
						indexFieldsName.removeLast();
					foreach(QJsonValue clmn,subFld.toObject().value("Columns").toArray()){
						fieldsName <<clmn.toObject().value("Header").toString().append("$").append(tableName);
						if(fv.toObject().value("ShowInIndex") != QJsonValue::Undefined)
							indexFieldsName <<clmn.toObject().value("Header").toString();
						}
					}
				}
			}
		}


	//	qDebug()  << __FILE__ << __LINE__  <<"FIELDSNAMESS" << id << fieldsName;
	//	qDebug()  << __FILE__ << __LINE__  <<"INDEX NAMES" << id << indexFieldsName;
	insertCachedViewStructureFieldsNames(id,fieldsName);
	insertCachedViewStructureIndexFieldsNames(id,indexFieldsName);
	insertCachedViewStructureNames(viewstrct.value("document_Name").toString(),id);
	insertCachedViewStructureSubFields(id,subfields);
	insertCachedViewStructureTabelFields(id,tabelFields);
}

/*
void Controller::deleteEntityData(QVector<QJsonDocument> items)
{
	//	qDebug()<< __FILE__ << __LINE__;
	foreach(QJsonDocument query,items){
		//TODO: make sure items is removed, otherwise retry
		foreach(QJsonValue item,query.object().value("ITEMSLIST").toArray()){
			Controller::Get()->deleteDocument(item.toObject().value("DocumentID").toString());
			}
		}
}
*/


void Controller::queryData(QVector<QSqlRecord> items)
{
	//qDebug() << items <<"FSFSF";
	emit gotReportData(items);
}

void Controller::setShowWarning(bool value)
{
	Model::Get()->setShowWarning(value);
}

bool Controller::showWarning(QString warning){
	//QMessageBox::StandardButton reply;
	//reply = QMessageBox::question(0, "Test", warning,QMessageBox::Ok|QMessageBox::No);
	//reply =

	if(Model::Get()->getShowWarning())
		QMessageBox::critical(0,"Warning",warning,QMessageBox::Ok);
	else{
		//fprintf (stderr, "%s", warning.toLatin1().constData());
		}
	/*
	if (reply == QMessageBox::Ok) {
	  qDebug() << __FILE__ << __LINE__  << "Yes was clicked";
	 // QApplication::quit();
	} else {
	  qDebug() << __FILE__ << __LINE__  << "Yes was *not* clicked";
	}
	*/
	return true;
}

bool Controller::ShowQuestion(QString question)
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(0, "Test", question,QMessageBox::Ok|QMessageBox::No);
	if (reply == QMessageBox::Ok) {
		return true;
		// QApplication::quit();
		} else {
		return false;
		}
}
void Controller::ShowError(QString message)
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::critical(0, "Error!", message,QMessageBox::Ok);
}



/*
void Controller::showWarning(QString warning)
{

	QString commandGroup = 	Model::Get()->getNode(Model::Get()->getRootNode(node).toDocument(), XMLTags::GetTag(GROUP)).firstChild().nodeValue();
	QString tabName  = Model::Get()->getTabNameByGroupName(commandGroup);
	QString commandName = getName(node);
	showWarning("Tab : "+tabName+"\n"+"Group: "+commandGroup+"\n"+"Entity: "+commandName+"\n"+"\n"+warning);

}*/

void Controller::Log(QStringList log){
	Model::Get()->Log(log);
}
////////Controlling the Model_ Model Functions //////////////////////

/*
bool Controller::save(QList<Entity*> entityGroup,bool update){
	//QString filename = QFileDialog::getSaveFileName(0, QString("Save file"),QString(),QString(),0,0);
	if(entityGroup.count() < 1 &&
			entityGroup.first()->data.value("document_id") != QJsonValue::Undefined )
		return false;
	QString EntityName = getName(entityGroup.first()->xmlNode_);
	QList<QString> lines = QList<QString>();
	foreach(Entity* entity,entityGroup){
		lines.append(entity->save());
		}
	if(update)
		lines.append(QString("cas_value")+"->"+QString(entityGroup.first()->data.value("cas_value").toString()));
	lines.append(QString("document_id")+"->"+QString(entityGroup.first()->data.value("document_id").toString()));

	return Prsistance::write(EntityName,lines,update);

}
*/
void Controller::deleteDocument(const QString& tabel, const QString& id)
{
	Database* database  = new Database();
	database->deletRow(tabel,id);
	//DELETE FROM BankAccount WHERE BankAccountID
}

bool Controller::Compare(QJsonObject first, QJsonObject second)
{
	//	qDebug() << __FILE__ << __LINE__  << "COMPAREEEEEEEEEEE";
	//	qDebug() << __FILE__ << __LINE__  << first;
	//	qDebug() << __FILE__ << __LINE__  << second;
	foreach(QString key,first.keys()){
		if(first[key] != second[key])
			return false;
		}
	foreach(QString key,second.keys()){
		if(first[key] != second[key])
			return false;
		}

	return true;
}


