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
	CouchbaseLibManager::Get();

	///TimeLine
	//	connect(timelineUI::Get(), SIGNAL(btnLoadPressed()), this, SLOT(onBtnLoadClicked()));
	//	connect(timelineUI::Get(), SIGNAL(btnRunPressed()), this, SLOT(onBtnRunClicked()));

	//Worker* worker = new Worker();

	//	QObject::connect(this,SIGNAL(queryDatabase(QString)),Database::Get(),SLOT(query(QString)),Qt::QueuedConnection);


	//	QObject::connect(Database::Get(),SIGNAL(saved(QString)),this,SIGNAL(saved(QString)));

}






void Controller::showDisplay()
{


	AccessController::Get()->logout();
	AccessController::Get()->login("merplyroot","LilyMichael");
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
		Prsistance::init();
	//QObject::connect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showDisplayDataReturned(QJsonDocument)));
	//Database::Get()->getDoc("ViewStructure::5");

	//QJsonDocument d =Database::Get()->getDocument();
	//ViewGroups* vgs= new ViewGroups(0,"Contact",d.object(),d.object());
	//layout->addWidget(vgs);

	QObject::connect(navigationUI::Get(),SIGNAL(subNavPressed(QJsonObject)),this,SLOT(subNavPressed(QJsonObject)));


	initNavigation();
}


void Controller::showDisplayDataReturned(QJsonDocument document)
{

	//	QObject::disconnect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showDisplayDataReturned(QJsonDocument)));
	StructureViewGroupsUI::ShowUI(document.object());
}

void Controller::loadNavigationData(QJsonDocument document)
{
	//	QObject::disconnect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(loadNavigationData(QJsonDocument)));
	//qDebug() << "load";
	navigationUI::Get()->loadMainNavigation(document);
}

void Controller::subNavPressed(QJsonObject view)
{
	//qDebug() << __FILE__ << __LINE__  << view;
	if(AccessController::Get()->hasReadAccess(view))
		if(view.value("Type").toString().contains("Entity") && !view.value("Card").toString().isEmpty()){
			if(view.value("Select").toString().contains("Index")){
				QString card = view.value("Card").toString();
				//qDebug() << __FILE__ << __LINE__  <<"Cards"<< card;
				//queryIndexView(card);
				IndexUI::ShowUI(card,QVector<QJsonDocument>());
				}
			else{
				Database* database  = Database::Gett();
				QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(subNavPressedData(QJsonDocument)));
				//qDebug() << __FILE__ << __LINE__  <<"getDocument"<< view.value("Card").toString();
				database->getDoc(view.value("Card").toString());

				}
			}
		else {if(view.value("Type").toString().contains("Page")){
				//qDebug() << __FILE__ << __LINE__  <<"PAgee"<< view.value("Card").toString();
				Database* database  = Database::Gett();
				QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(subNavPressedPageData(QJsonDocument)));
				database->getDoc(view.value("Card").toString());
				}
			}
	else IndexUI::ShowUI("ViewStructure::91",QVector<QJsonDocument>());
}

void Controller::queryIndexView(QString vStrctKey)
{
	indexDocument_id = vStrctKey;
	//qDebug() << __FILE__ << __LINE__<< indexDocument_id;
	QString card = vStrctKey.replace("ViewStructure::","");
	card.append("::%");
	QString query = QString("SELECT `"+QString(DATABASE)+"`.*,meta("+QString(DATABASE)+").id AS `document_id` FROM `"+QString(DATABASE)+"` WHERE meta("+QString(DATABASE)+").id LIKE '"+card+"' LIMIT 400");
	//qDebug() << __FILE__ << __LINE__ <<"QINDEX : " << query;

	Database* database  = Database::Gett();
	QObject::connect(database,SIGNAL(gotDocuments(QVector<QJsonDocument>)),this,SLOT(subNavPressedIndexData(QVector<QJsonDocument>)));
	database->query(query);
}

void Controller::editControllerCancelPressed()
{
	navigationUI::Get()->setHidden(false);
	navigationUI::Get()->setParent(MainForm::Get());
	QObject::connect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(editControllerCancelDataPressed(QJsonDocument)));
	Controller::Get()->getDoc("NavigationUI::1");
}

SubFieldUI*Controller::getFirstSubField(QString feildName)
{
	if(ViewGroups::Fieldsgroups.find(feildName.trimmed()) != ViewGroups::Fieldsgroups.end() )
		return ViewGroups::Fieldsgroups.value(feildName.trimmed())->subFields.first();
	return new SubFieldUI();
}

void Controller::createIndexes(QJsonObject viewStrct)
{
	QString key;
	if(viewStrct.value("document_id") != QJsonValue::Undefined)
		key = viewStrct.value("document_id").toString().split("::")[1];
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
				//	qDebug() << lbl;
				QString indexname = QString(DATABASE).append("-").append(key.toLower()).append(lbl).append("-index");
				int indexCount = Controller::Get()->countIndex(indexname);
				if(indexCount == 0){
					Database* database  = Database::Gett();
					QString query = "CREATE INDEX `"+indexname+"` ON `AM`(`"+fv.toObject().value("Label").toString()+"`) WHERE META(`"+QString(DATABASE)+"`).id Like '"+key+"::%'  USING GSI";
					database->query(query);
					//qDebug() << __FILE__ << __LINE__  << indexname;
					//qDebug() << __FILE__ << __LINE__  << query;
					}
				}
			i++;
			}
		}
}

void Controller::initNavigation()
{
	Database* database  = Database::Gett();
	QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(loadNavigationData(QJsonDocument)));
	database->getDoc("NavigationUI::1");

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
	//QObject::disconnect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(subNavPressedData(QJsonDocument)));
	CreateEditUI::ShowUI(documents.object(),QJsonObject(),false);
}

void Controller::subNavPressedIndexData(QVector<QJsonDocument> documents)
{
	//QObject::disconnect(Database::Get(),SIGNAL(gotDocuments(QVector<QJsonDocument>)),this,SLOT(subNavPressedIndexData(QVector<QJsonDocument>)));
	if(!indexDocument_id.isEmpty())
		IndexUI::ShowUI(this->indexDocument_id,documents);

	this->indexDocument_id = "";
}

void Controller::subNavPressedPageData(QJsonDocument document)
{
	//QObject::disconnect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(subNavPressedPageData(QJsonDocument)));
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

int Controller::Count(const QString table)
{
	return Prsistance::Count(table);
}

int Controller::countIndex(const QString index)
{
	return Prsistance::CountIndexes(index);
}

void Controller::getDoc(QString key)
{
	//QObject::connect(Database::Get(),SIGNAL(Database::Get()->gotDocument(QJsonDocument)),this,SLOT(subNavPressed(QJsonObject)));
	Database* database  = Database::Gett();
	QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(getDocData(QJsonDocument)));
	database->getDoc(key);
}
void Controller::getDocData(QJsonDocument document)
{
	//QObject::disconnect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(getDocData(QJsonDocument)));
	emit gotDocument(document);
}
void Controller::getJsonList(QString table, QString select,QString condition)
{

	QObject::connect(Prsistance::Get(),SIGNAL(GotJsonSelectList(QVector<QJsonDocument>)),Controller::Get(),SLOT(GetJsonListData(QVector<QJsonDocument>)));
	Prsistance::GetJsonList(table,select,condition);
}
void Controller::getJsonEntityFieldsList(QString table, QString select,QString condition)
{

	QObject::connect(Prsistance::Get(),SIGNAL(GotJsonSelectList(QVector<QJsonDocument>)),Controller::Get(),SLOT(GetJsonListData(QVector<QJsonDocument>)));
	Prsistance::GetJsonEntityFields(table,select,condition);
}

void Controller::GetJsonListData(QVector<QJsonDocument> items)
{

	QObject::disconnect(Prsistance::Get(),SIGNAL(GotJsonSelectList(QVector<QJsonDocument>)),Controller::Get(),SLOT(GetJsonListData(QVector<QJsonDocument>)));
	emit gotJsonListData(items);
}



void Controller::getLastKey()
{
	//	Database* database  = Database::Gett();
	qDebug() <<  __FILE__ << __LINE__ <<"GOTTTTLASTTTTKEYYY CONTROLLER" ;
	//QObject::connect(Database::Get(),SIGNAL(gotLastKey(QString)),Controller::Get(),SLOT(getLastKeyData(QString)));
}

void Controller::getValue(QString key)
{
	Database* database  = Database::Gett();
	QObject::connect(database,SIGNAL(gotValue(QString)),this,SLOT(getValueData(QString)));
	database->getDoc(key);
}
void Controller::getValueData(QString value)
{
	//	QObject::disconnect(Database::Get(),SIGNAL(gotValue(QString)),this,SLOT(getValueData(QString)));
	emit gotValue(value);
}


void Controller::getLastKeyData(QString key)
{
	//qDebug() << __FILE__ << __LINE__ <<"GOTTTTLASTTTTKEYYY CONTROLLER" << key;
	//QObject::disconnect(Database::Get(),SIGNAL(gotLastKey(QString)),Controller::Get(),SLOT(getLastKeyData(QString)));
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

QString Controller::toString(QJsonValue value)
{
	QString data;
	if(value.isArray()){
		QJsonArray array = value.toArray();
		for(int j = 0; j < array.count(); j++){
			if(array.at(j).isArray())
				data += toString(array.at(j).toArray());
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
		qDebug()<< __FILE__ << __LINE__ << "toString  ERROR TYPE IS NOT DEFIENED" << value;
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

void Controller::getFields(QString Title)
{
	if(!Title.isEmpty() && Title.compare("_") != 0){
		Database* database  = Database::Gett();
		QObject::connect(database,SIGNAL(gotDocuments(QVector<QJsonDocument>)),this,SLOT(getFieldsData(QVector<QJsonDocument>)));
		QString query = "SELECT array_star("+QString(DATABASE)+".Viewgroups[*].Viewgroup).Fields FROM  `"+QString(DATABASE)+"` WHERE META(`"+QString(DATABASE)+"`).id = '"+Title+"'";
		//	qDebug() << __FILE__ << __LINE__  << "getFields"<<query;
		database->query(query);
		}
}



void Controller::getFieldsData(QVector<QJsonDocument> documents)
{
	//CreateEditUI::ShowUI(document.object(),QJsonObject());
	//	QObject::disconnect(Database::Get(),SIGNAL(gotDocuments(QVector<QJsonDocument>)),this,SLOT(getFieldsData(QVector<QJsonDocument>)));
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
		Database* database  = Database::Gett();
		QObject::connect(database,SIGNAL(gotDocuments(QVector<QJsonDocument>)),this,SLOT(getIndexHeaderData(QVector<QJsonDocument>)));
		QString query = "SELECT array_star("+QString(DATABASE)+".Viewgroups[*].Viewgroup).Fields FROM  `"+QString(DATABASE)+"` WHERE META(`"+QString(DATABASE)+"`).id = '"+title+"'";
		//qDebug() << __FILE__ << __LINE__  << "getFields"<<query;
		database->query(query);
		}
}
void Controller::getIndexHeaderData(QVector<QJsonDocument> documents){
	//	QObject::disconnect(Database::Get(),SIGNAL(gotDocuments(QVector<QJsonDocument>)),this,SLOT(getIndexHeaderData(QVector<QJsonDocument>)));
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
		emit gotFieldsData( fieldsName);
		}

	//qDebug() << __FILE__ << __LINE__  <<"Fieldss"<<documents;
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
bool Controller::storeDoc(QString key, QJsonDocument document)
{
	Database* database  = Database::Gett();
	QObject::connect(database,SIGNAL(saved(QString)),this,SIGNAL(saved(QString)));
	return database->storeDoc(key,document);
}

bool Controller::UpdateDoc(QJsonDocument document)
{
	Database* database  = Database::Gett();
	return database->updateDoc(document);
}

void Controller::showCreateEditeStrUI(QString str,bool create)
{
	//qDebug() << __FILE__ << __LINE__  << str.split("::")[1] <<"Check cached";
	QString key = str.split("::").count() > 1?str.split("::")[1]:"";
	if(create){
		Database* database  = Database::Gett();
		QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showCreateEditeStrUICreateTrueData(QJsonDocument)));
		database->getDoc(str);
		}
	else if(!key.isEmpty() && Model::Get()->cachedCreateEditUI.contains(key)){
		//	qDebug() << __FILE__ << __LINE__  << key <<"Cached" ;
		MainForm::Get()->ShowDisplay((CreateEditUI*)Model::Get()->cachedCreateEditUI.value(key));
		}
	else{
		//	qDebug() << __FILE__ << __LINE__  << key <<"NOT Cached";
		Database* database  = Database::Gett();
		QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showCreateEditeStrUIData(QJsonDocument)));
		database->getDoc(str);
		}

}
void Controller::showCreateEditeStrUIData(QJsonDocument str)
{
	//	QObject::disconnect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showCreateEditeStrUIData(QJsonDocument)));
	CreateEditUI::ShowUI(str.object(),QJsonObject(),false);
}
void Controller::showCreateEditeStrUICreateTrueData(QJsonDocument str)
{
	//	QObject::disconnect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showCreateEditeStrUICreateTrueData(QJsonDocument)));
	CreateEditUI::ShowUI(str.object(),QJsonObject(),true);
}
void Controller::showCreateEditeValueUI(QString key)
{
	Database* database  = Database::Gett();
	QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showCreateEditeValueUIData(QJsonDocument)));
	database->getDoc(key);
}

void Controller::showCreateEditeValueUIData(QJsonDocument value)
{
	//	QObject::disconnect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showCreateEditeValueUIData(QJsonDocument)));
	QString key  = value.object().value("document_id").toString().split("::")[0];
	if(!key.isEmpty() && Model::Get()->cachedCreateEditUI.contains(key)){
		//qDebug() << __FILE__ << __LINE__  << key <<"is Cached Value";
		((CreateEditUI*)Model::Get()->cachedCreateEditUI.value(key))->ShowUI(QJsonObject(),value.object(),false);
		//((CreateEditUI*)MainForm::Get()->GetCurrentDisplay())->ShowUI(QJsonObject(),value.object());
		//MainForm::Get()->ShowDisplay();
		}
	else{
		//qDebug() << __FILE__ << __LINE__  << key <<"Not Cached Value";
		CreateEditUI::ShowUI(QJsonObject(),value.object(),false);
		}

}




void Controller::linkPressed(QJsonObject link)
{
	qDebug() << __FILE__ << __LINE__  << link;

	if(link.value("Type").toString().contains("Link")){
		//	Database::Get()->getDoc("ViewStructure::"+QString(view.value("EntityId").toString()));
		Database* database  = Database::Gett();
		QObject::connect(database,SIGNAL(gotDocument(QJsonDocument)),this,SLOT(linkPressedData(QJsonDocument)));
		QString query = QString("SELECT `"+QString(DATABASE)+"`.*,meta("+QString(DATABASE)+").id AS `document_id` FROM `"+QString(DATABASE)+"` WHERE "+QString(DATABASE)+".Title = '"+link.value("Source").toString()+"'");
		//qDebug() << __FILE__ << __LINE__ <<"Q : " << query;
		database->query(query);
		//qDebug() << __FILE__ << __LINE__  << view.value("Card").toString() << d;
		}

}
void Controller::linkPressedData(QJsonDocument document)
{
	//QObject::disconnect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(linkPressedData(QJsonDocument)));

	CreateEditUI::ShowUI(document.object(),QJsonObject(),false);
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
	return Controller::UpdateDoc(QJsonDocument(navigation));

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
				savedPages = savedPages & Controller::UpdateDoc(QJsonDocument(cardData));

				}else{
				if(page.value("Type").toString().compare("Page")){
					Controller::Get()->storeDoc("Page",QJsonDocument(cardData));
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
		Database* database  = Database::Gett();
		QObject::connect(database,SIGNAL(gotDocuments(QVector<QJsonDocument>)),this,SLOT(getReportData(QVector<QJsonDocument>)),Qt::QueuedConnection);

		database->query(clmns.value("QueryUI").toObject().value("Query").toString().replace("#QUERYMERPLY",""),false); //TODO: CACHED FLAGG
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
			//QObject::connect(Database::Get(),SIGNAL(gotDocuments(QVector<QJsonDocument>)),this,SLOT(getReportData(QVector<QJsonDocument>)),Qt::QueuedConnection);
			//Database::Get()->query(query);
			//	emit queryDatabase(query);
			}
		else emit gotReportData(QVector<QJsonDocument>());


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
	return (Model::Get()->cachedCreateEditUI.value(key));

}
bool Controller::isCachedCreateEditUI(QString key)
{
	//qDebug() << __FILE__ << __LINE__  << "insert"<<key<< instance;
	return Model::Get()->cachedCreateEditUI.contains(key);
}

void Controller::getReportData(QVector<QJsonDocument> documents)
{
	//qDebug() << __FILE__ << __LINE__  << "GotReport Data" << documents;
	//QObject::disconnect(Database::Get(),SIGNAL(gotDocuments(QVector<QJsonDocument>)),this,SLOT(getReportData(QVector<QJsonDocument>)));
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
	//	Database* database  = Database::Gett();
	qDebug() << __FILE__ << __LINE__ <<"getLastKeyID NO DATA";
	return "Database::Get()->getLastKeyID()";
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

void Controller::query(QString query, bool cached)
{
	Database* database  = Database::Gett();
	QObject::connect(database,SIGNAL(gotDocuments(QVector<QJsonDocument>)),this,SLOT(queryData(QVector<QJsonDocument>)));
	database->query(query,cached);
}

bool Controller::createEditStore(QJsonObject document)
{
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
		Database* database  = Database::Gett();
		QObject::connect(database,SIGNAL(saved(QString)),this,SIGNAL(saved(QString)));
		database->updateDoc(QJsonDocument(document));
		}
	else{
		Database* database  = Database::Gett();
		QObject::connect(database,SIGNAL(saved(QString)),this,SIGNAL(saved(QString)));
		database->storeDoc(document.value("document_id").toString(),QJsonDocument(document));
		}
	QObject::disconnect(this,SIGNAL(saved(QString)),this,SIGNAL(savedItems(QString)));

	return true;
}

bool Controller::createEditRemoveRowItems(QJsonArray rowsItems)
{
	bool success = true;
	foreach (QJsonValue row, rowsItems) {
		if(row.toObject().value("documentID") != QJsonValue::Undefined)
			success = deleteDocument(row.toObject().value("documentID").toString());
		}
	return success;
}

void Controller::deleteEntity(QString documentID)
{
	if(Controller::Get()->deleteDocument(documentID))
		{
		QString strctKey = documentID.split("::")[0];
		QString query = "SELECT (SELECT META(`"+QString(DATABASE)+"`).id AS DocumentID FROM `AM` WHERE META(`"+QString(DATABASE)+"`).id LIKE '"+strctKey+"%' AND  "+strctKey+" LIKE '"+documentID+"') AS ITEMSLIST";
		Database* database  = Database::Gett();
		QObject::connect(database,SIGNAL(gotDocuments(QVector<QJsonDocument>)),this,SLOT(deleteEntityData(QVector<QJsonDocument>)));
		//	qDebug() << __FILE__ << __LINE__<< query;
		database->query(query);
		}

	//	"SELECT array_star("+QString(DATABASE)+".Viewgroups[*].Viewgroup).Fields FROM  `"+QString(DATABASE)+"` WHERE META(`"+QString(DATABASE)+"`).id = '"+Title+"'";
	//	qDebug() << __FILE__ << __LINE__  << "getFields"<<query;


}

void Controller::saveRefrenceStructures(QJsonObject mainStrct, QJsonObject data)
{
	//qDebug() << mainStrct;

	if(mainStrct.value("Viewgroups").isArray()){
		//	QJsonArray dataVGs =data.value("Fields").toArray();

		foreach (QJsonValue item, mainStrct.value("Viewgroups").toArray()) {
			QJsonObject viewGroupObject = item.toObject().value("Viewgroup").toObject();
			if(viewGroupObject.value("RefrenceFields") != QJsonValue::Undefined){

				foreach(QJsonValue refrenceFields,viewGroupObject.value("RefrenceFields").toArray()){
					QJsonObject newData;
					foreach(QJsonValue refrenceSubFields,refrenceFields.toObject().value("RefrenceSubFields").toArray()){
						//qDebug()<< __FILE__ << __LINE__ << refrenceSubFields.toObject();
						//qDebug() << data
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

								///ELSE not Table
								}

							}
						else {
							if(refrenceSubFields.toObject().value("Field").toString().contains("$"))
								newData.insert(refrenceSubFields.toObject().value("Field").toString(),data.value(refrenceSubFields.toObject().value("RefrenceValue").toString()));
							}

						}

					if(!newData.isEmpty()){
						//qDebug()<< __FILE__ << __LINE__ << refrenceFields.toObject().value("Source");
						newData.insert("document_id",refrenceFields.toObject().value("Source").toString());
						Controller::Get()->createEditStore(newData);
						}
					}


				}

			}
		}

}
void Controller::createEditStoreItems(QString key)
{
	QObject::disconnect(this,SIGNAL(saved(QString)),this,SLOT(createEditStoreItems(QString)));
	bool success = true;
	foreach(QJsonObject tbl,creatEditeItems){
		QString id = QString(key.split("::")[0]).append(":").append(tbl.value("FieldKey").toString());
		//qDebug() << __FILE__ << __LINE__ << id << key;
		foreach(QJsonValue v,tbl.value("merplyTabel").toArray()){
			QJsonObject row = v.toObject();
			if(row.value(QString(key.split("::")[0])) == QJsonValue::Undefined){
				row.insert(QString(key.split("::")[0]),key);
				//qDebug() << __FILE__ << __LINE__ << "New Row" << row;
				success = Controller::Get()->storeDoc(id,QJsonDocument(row));
				}
			else {
				//qDebug() << __FILE__ << __LINE__ << "Update Row" << row;
				success = Controller::Get()->UpdateDoc(QJsonDocument(row));
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
																																  "FROM `"+QString(DATABASE)+"`  USE INDEX("+strctID+""+tbl+"_idx) "
																																															"WHERE Meta(`"+QString(DATABASE)+"`).id LIKE '"+strctID+":"+tbl+"::%' AND  `"+strctID+"` LIKE '"+entity+"' AND `"+strctID+"` IS NOT MISSING) AS `"+tbl+"` ";
		query += subQuery;
		i++;
		}
	//qDebug() << __FILE__ << __LINE__<< query;
	Database* database  = Database::Gett();
	QObject::connect(database,SIGNAL(gotDocuments(QVector<QJsonDocument>)),this,SLOT(queryData(QVector<QJsonDocument>)));
	database->query(query,false);
}

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

void Controller::queryData(QVector<QJsonDocument> items)
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
bool Controller::deleteDocument(QString id)
{
	Database* database  = Database::Gett();
	return database->deleteDoc(id);
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
