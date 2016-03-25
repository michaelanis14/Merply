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

	Database::Get()->getDoc("ViewStructure::1");
	QJsonDocument d =Database::Get()->getDocument();
	//ViewGroups* vgs= new ViewGroups(0,"Contact",d.object(),d.object());
	StructureViewGroupsUI::ShowUI(d.object());
	//layout->addWidget(vgs);

	QObject::connect(navigationUI::Get(),SIGNAL(subNavPressed(QJsonObject)),this,SLOT(subNavPressed(QJsonObject)));


	navigationUI::Get()->loadMainNavigation(getAll("NavigationUI",""));
	//navigationUI::Get()->addTab(StructureViewGroupsUI::GetUI(),"Contact");
}
void Controller::subNavPressed(QJsonObject view)
{
	if(view.value("Type").toString().contains("Entity")){
		Database::Get()->getDoc("ViewStructure::"+QString(view.value("EntityId").toString()));
		QJsonDocument d =Database::Get()->getDocument();
		qDebug() << view.value("EntityId").toString();
		CreateEditUI::ShowUI(d.object(),QJsonObject());
		}
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

bool Controller::getDoc(QString key)
{
	return Database::getDoc(key);
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

QList<QString> Controller::getFields(QString Entity)
{
	QStringList fieldsName;
	Database::Get()->query("SELECT array_star(default.Viewgroups[*].Viewgroup).Fields FROM  `default` WHERE META(`default`).id = \"ViewStructure::"+Entity+"\"");
	foreach(QJsonValue fv,Database::Get()->getDocument().object().value("Fields").toArray()){
		foreach(QJsonValue fvvapn,fv.toArray()){
			fieldsName << fvvapn.toObject().value("Label").toString();
			}
		}
	return fieldsName;
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
	QJsonObject mainNav;
	while (i.hasNext()) {
		i.next();
		mainNav.insert("Title",i.value());
		mainNav.insert("ID",i.key());
		QJsonArray items;
		foreach(QTreeWidgetItem * tab,GetSubNavigation(i.key())){
			//QJsonObject item;
			//item.insert("Title",tab->text());
			items.append(GetPage(tab->text(1).toInt()));
			}
		mainNav.insert("Items",items);

	//	qDebug() << mainNav;
		//mainNavs.append(QJsonDocument(mainNav));
		}
	mainNav.insert("document_id","NavigationUI::1");
	return Controller::UpdateDoc(QJsonDocument(mainNav));

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



void Controller::showWarning(QString warning){
	//QMessageBox::StandardButton reply;
	//reply = QMessageBox::question(0, "Test", warning,QMessageBox::Ok|QMessageBox::No);
	//reply =

	if(Model::Get()->getShowWarning())
		QMessageBox::critical(0,"Warning",warning,QMessageBox::Ok);
	else{
		fprintf (stderr, "%s", warning.toLatin1().constData());
		}
	/*
	if (reply == QMessageBox::Ok) {
	  qDebug() << "Yes was clicked";
	 // QApplication::quit();
	} else {
	  qDebug() << "Yes was *not* clicked";
	}
	*/
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



