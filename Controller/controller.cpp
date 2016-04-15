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
#include "prsistance.h"

#include "structureviewgroupsui.h"
#include "createeditui.h"
#include "pageui.h"




Controller::Controller(QObject *parent) :
	QObject(parent)
{


	///TimeLine
	//	connect(timelineUI::Get(), SIGNAL(btnLoadPressed()), this, SLOT(onBtnLoadClicked()));
	//	connect(timelineUI::Get(), SIGNAL(btnRunPressed()), this, SLOT(onBtnRunClicked()));



}




void Controller::showDisplay()
{

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

	//Prsistance::init();

	QObject::connect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showDisplayDataReturned(QJsonDocument)));
	Database::Get()->getDoc("ViewStructure::1");

	//QJsonDocument d =Database::Get()->getDocument();
	//ViewGroups* vgs= new ViewGroups(0,"Contact",d.object(),d.object());
	//layout->addWidget(vgs);

	QObject::connect(navigationUI::Get(),SIGNAL(subNavPressed(QJsonObject)),this,SLOT(subNavPressed(QJsonObject)));

	QObject::connect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(loadNavigationData(QJsonDocument)));
	Database::Get()->getDoc("NavigationUI::1");

}

void Controller::showDisplayDataReturned(QJsonDocument document)
{
	StructureViewGroupsUI::ShowUI(document.object());
	QObject::disconnect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(showDisplayDataReturned(QJsonDocument)));
}

void Controller::loadNavigationData(QJsonDocument document)
{
	QObject::disconnect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(loadNavigationData(QJsonDocument)));
	navigationUI::Get()->loadMainNavigation(document);
}






void Controller::subNavPressed(QJsonObject view)
{
	//qDebug() << view;
	if(view.value("Type").toString().contains("Entity")){

		//QObject::connect(Database::Get(),SIGNAL(Database::Get()->gotDocument(QJsonDocument)),this,SLOT(subNavPressed(QJsonObject)));

		//	Database::Get()->getDoc("ViewStructure::"+QString(view.value("EntityId").toString()));
		QObject::connect(Database::Get(),SIGNAL(gotDocuments(QList<QJsonDocument>)),this,SLOT(subNavPressedData(QList<QJsonDocument>)));
		QString query = QString("SELECT `"+QString(DATABASE)+"`.*,meta("+QString(DATABASE)+").id AS `document_id` FROM `"+QString(DATABASE)+"` WHERE "+QString(DATABASE)+".Title = '"+view.value("Card").toString()+"'");
		//qDebug()<<"Q : " << query;
		Database::Get()->query(query);
		}
	else if(view.value("Type").toString().contains("Page")){
		PageUI::ShowUI(view);
		}
}
void Controller::subNavPressedData(QList<QJsonDocument> documents)
{
//	qDebug() << "SubPreseed" << documents;
	QObject::disconnect(Database::Get(),SIGNAL(gotDocuments(QList<QJsonDocument>)),this,SLOT(subNavPressedData(QList<QJsonDocument>)));
	if(documents.count() > 0)
		CreateEditUI::ShowUI(documents.first().object(),QJsonObject());

}

/**
 * @author Michael Bishara
 * @brief Controller::Get
 * @return
 */
Controller* Controller::p_instance = 0;
Controller* Controller::Get()
{
	if (p_instance == 0)
		p_instance = new Controller();

	return p_instance;
}

int Controller::Count(const QString table)
{
	return Prsistance::Count(table);
}

void Controller::getDoc(QString key)
{
	//QObject::connect(Database::Get(),SIGNAL(Database::Get()->gotDocument(QJsonDocument)),this,SLOT(subNavPressed(QJsonObject)));

	QObject::connect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(getDocData(QJsonDocument)));
	Database::getDoc(key);
}
void Controller::getDocData(QJsonDocument document)
{
	QObject::disconnect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(getDocData(QJsonDocument)));
	emit gotDocument(document);
}
QList<QString> Controller::getListItems(QString table, QString select,QString condition)
{
	return Prsistance::ComboxList(table,select,condition);
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

QList<QJsonDocument> Controller::getAll(const QString entity, const QString condition)
{
	return Prsistance::GetALL(entity,condition);
}

QString Controller::toString(QJsonArray array)
{
	QString data;
	for(int j = 0; j < array.count(); j++){
		if(array.at(j).isArray())
			data += toString(array.at(j).toArray());
		else data += array.at(j).toString();
		data += ",";
		}
	return data;
}

bool Controller::documentInList(QList<QJsonDocument> all, QString key)
{
	foreach(QJsonDocument d,all){
		if(d.object().value("document_id").toString().compare(key) == 0)
			return true;
		}
	return false;
}

QList<QJsonDocument> Controller::getEnities()
{
	return Prsistance::GetALL("ViewStructure","default.Type =\"Entity\"");
}

void Controller::getFields(QString Title)
{
	QObject::connect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(getFieldsData(QJsonDocument)));

	Database::Get()->query("SELECT array_star(default.Viewgroups[*].Viewgroup).Fields FROM  `default` WHERE META(`default`).id LIKE 'ViewStructure::%' AND default.Title ='"+Title+"'");

}

void Controller::getFieldsData(QJsonDocument document)
{
	//CreateEditUI::ShowUI(document.object(),QJsonObject());
	QObject::disconnect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(getFieldsData(QJsonDocument)));
	QStringList fieldsName;
	foreach(QJsonValue fv,document.object().value("Fields").toArray()){
		foreach(QJsonValue fvvapn,fv.toArray()){
			fieldsName << fvvapn.toObject().value("Label").toString();
			}
		}
	emit getFieldsData( fieldsName);
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
	//qDebug() << layoutViewGroups;
	}
}

QStringList Controller::getLayoutViewGroups(QString entity)
{
	return layoutViewGroups.value(entity);
}

bool Controller::storeDoc(QString key, QJsonDocument document)
{
	return Database::Get()->storeDoc(key,document);
}

bool Controller::UpdateDoc(QJsonDocument document)
{
	return Database::Get()->updateDoc(document);
}

void Controller::linkPressed(QJsonObject link)
{
	qDebug() << link;

	if(link.value("Type").toString().contains("Link")){
		//	Database::Get()->getDoc("ViewStructure::"+QString(view.value("EntityId").toString()));
		QObject::connect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(linkPressedData(QJsonDocument)));
		QString query = QString("SELECT `"+QString(DATABASE)+"`.*,meta("+QString(DATABASE)+").id AS `document_id` FROM `"+QString(DATABASE)+"` WHERE "+QString(DATABASE)+".Title = '"+link.value("Source").toString()+"'");
		//qDebug()<<"Q : " << query;
		Database::Get()->query(query);
		//qDebug() << view.value("Card").toString() << d;
		}

}
void Controller::linkPressedData(QJsonDocument document)
{
	QObject::disconnect(Database::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(linkPressedData(QJsonDocument)));

	CreateEditUI::ShowUI(document.object(),QJsonObject());
}




void Controller::AddSubNavigation(int key, QList<QTreeWidgetItem*> subNav)
{
	Model::Get()->addSubNavigation(key,subNav);
}

QList<QTreeWidgetItem*> Controller::GetSubNavigation(int key)
{
	return Model::Get()->getSubNavigation(key);
}

bool Controller::RemoveSubNavigation(int key)
{
	return Model::Get()->removeSubNavigation(key);
}

void Controller::ClearSubNavigation()
{
	Model::Get()->clearSubNavigation();
}

void Controller::AddPage(int key, QJsonObject page)
{
	Model::Get()->addPage(key,page);
}

QJsonObject Controller::GetPage(int key)
{
	return Model::Get()->getPage(key);
}

bool Controller::RemovePage(int key)
{
	return Model::Get()->removePage(key);
}

void Controller::ClearPages()
{
	Model::Get()->clearPages();
}

void Controller::AddMainNavigation(int key, QString mainNav)
{
	Model::Get()->addMainNavigation(key,mainNav);
}

QString Controller::GetMainNavigation(int key)
{
	return Model::Get()->getMainNavigation(key);
}

bool Controller::RemoveMainNavigation(int key)
{
	return Model::Get()->removeMainNavigation(key);
}

void Controller::ClearMainNavigation()
{
	Model::Get()->clearMainNavigation();
}


//Navigation
//void Controller::addMainNavigation(int key, QList<QTreeWidgetItem *> subNav)
//{
//	Model::Get()->addMainNavigation(key,subNav);
//}








bool Controller::SaveNavigation()
{


	QMapIterator<int, QString > i(Model::Get()->getMainNavigationModel());
	//QList<QJsonDocument> mainNavs;
	QJsonObject navigation;
	QJsonArray mainNavs;
	while (i.hasNext()) {
		i.next();
		QJsonObject mainNav;
		mainNav.insert("Title",i.value());
		mainNav.insert("ID",i.key());
		QJsonArray items;
		foreach(QTreeWidgetItem * tab,GetSubNavigation(i.key())){
			items.append(SaveSubNavigation(tab));
			}
		mainNav.insert("Items",items);
		//	qDebug() << mainNav;
		//mainNavs.append(QJsonDocument(mainNav));
		mainNavs << mainNav;
		}

	navigation.insert("MainNavigations",mainNavs);
	navigation.insert("document_id","NavigationUI::1");
	return Controller::UpdateDoc(QJsonDocument(navigation));

}
QJsonObject Controller::SaveSubNavigation(QTreeWidgetItem * item)
{

	QJsonObject itemTab = QJsonObject();
	itemTab.insert("Title",item->text(0));
	itemTab.insert("ID",item->text(1).toInt());
	itemTab.insert("Page",GetPage(item->text(1).toInt()));
	if(item->childCount() > 0){
		QJsonArray items = QJsonArray();
		for(int i = 0; i < item->childCount();i++)
			items << SaveSubNavigation(item->child(i));
		itemTab.insert("Items",items);
		}
	return itemTab;
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
	  qDebug() << "Yes was clicked";
	 // QApplication::quit();
	} else {
	  qDebug() << "Yes was *not* clicked";
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
	return Database::Get()->deleteDoc(id);
}

bool Controller::Compare(QJsonObject first, QJsonObject second)
{
	//	qDebug() << "COMPAREEEEEEEEEEE";
	//	qDebug() << first;
	//	qDebug() << second;
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



