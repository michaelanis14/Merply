/**************************************************************************
** File: model.cpp
** Created on: 15.04.2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/

#include "model.h"

#include "controller.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QProcess>





//QString Model::xmlDir = QString("%1%2xml%2").arg(QDir::currentPath()).arg(QDir::separator());




Model::Model():QObject()
{
	this->showWarning = true;
	subNavigation =  QMap<double, QList<QTreeWidgetItem *> >();
	pages =  QMap<double, QJsonObject >();
	loggedUser = 0;
	this->defaulConnStrg = "couchbase://localhost/default";
}

bool Model::getShowWarning() const
{
	return showWarning;
}

void Model::addSubNavigation(double key, QList<QTreeWidgetItem *> subNav)
{
	subNavigation.insert(key, subNav);
}

void Model::clearSubNavigation()
{
	subNavigation.clear();
}

void Model::clearPages()
{
	pages.clear();
}

void Model::addMainNavigation(double key, QString mainNav)
{
	mainNavigation.insert(key,mainNav);
}

QString Model::getMainNavigation(double key)
{
	return mainNavigation.value(key);
}

bool Model::removeMainNavigation(double key)
{
	return mainNavigation.remove(key);
}

void Model::clearMainNavigation()
{
	mainNavigation.clear();
}


QList<QTreeWidgetItem *> Model::getSubNavigation(double key)
{
	return subNavigation.value(key);
}

QMap<double, QList<QTreeWidgetItem*> > Model::getSubNavigationModel()
{
	return subNavigation;
}

QMap<double, QString> Model::getMainNavigationModel()
{
	return mainNavigation;
}

void Model::login(QString uid, QString username, QString name)
{
	loggedUser = new User(uid,username,name);
}

void Model::logout()
{
	loggedUser = 0;
}

QString Model::getUserID()
{
	if(loggedUser){
		return loggedUser->getId();
		}
	return "";
}

QString Model::getUserName()
{
	if(loggedUser){
		return loggedUser->getName();
		}
	return "";
}

QString Model::getUserUsername()
{
	if(loggedUser){
		return loggedUser->getUsername();
		}
	return "";
}
bool Model::removeSubNavigation(double key)
{
	return subNavigation.remove(key);
}

void Model::addPage(double key, QJsonObject page)
{
	pages.insert(key, page);
}
QJsonObject Model::getPage(double key)
{
	return pages.value(key);
}
bool Model::removePage(double key)
{
	return pages.remove(key);
}




Model* Model::p_instance = 0;
Model* Model::Get()
{
	if (p_instance == 0)
		p_instance = new Model();

	return p_instance;
}

void Model::setShowWarning(bool value)
{
	showWarning = value;
}

bool Model::isNameExistInList(QStringList &list, QString &name) {
	for(QStringList::Iterator it = list.begin(); it != list.end(); ++it ) {
		if(name == *it) {
			return true;
			}
		}
	return false;
}

QString Model::getDefaulConnStrg() const
{
	return defaulConnStrg;
}

void Model::setDefaulConnStrg(const QString& value)
{
	defaulConnStrg = value;
}

QMap<double, QJsonObject> Model::getPages() const
{
	return pages;
}

bool Model::Log(const QStringList& log)
{
	QString fileName = "log";

	if(!QFile::exists(fileName)){
#ifndef Q_OS_WIN32
#ifndef Q_OS_IOS
		QFile file(fileName);
		QTextStream out(&file);
		if(!file.open(QFile::Append | QFile::Text))
			{
			return false;
			}
		QProcess p;
		p.start("lscpu");
		p.waitForFinished();
		QString cpu = QString(p.readAllStandardOutput());
		p.close();

		out << "-----------------------"+QApplication::applicationName()+"-------------------------------- \n";
		out << "System Information \n";
		out << cpu;
		out.flush();
		file.close();
#endif
#endif
		}

	QFile file(fileName);
	if(!file.open(QFile::Append | QFile::Text))
		{
		return false;
		}

	QTextStream out(&file);

	foreach(QString event,log){
		out << event.trimmed();
		out << "\t";
		out.flush(); // write immediately to ensure correct order of items in output fil
		}
	out << "\n";
	file.close();
	return true;
}
