/**************************************************************************
** File: model.cpp
** Created on: 15.04.2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/

#include "model.h"
#include "prsistance.h"

#include "controller.h"
#include "database.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QProcess>





//QString Model::xmlDir = QString("%1%2xml%2").arg(QDir::currentPath()).arg(QDir::separator());




Model::Model(){
	this->showWarning = true;
	subNavigation =  QMap<int, QList<QTreeWidgetItem *> >();
	pages =  QMap<int, QJsonObject >();
	Database::Get();
}

bool Model::getShowWarning() const
{
	return showWarning;
}

void Model::addSubNavigation(int key, QList<QTreeWidgetItem *> subNav)
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

void Model::addMainNavigation(int key, QString mainNav)
{
	mainNavigation.insert(key,mainNav);
}

QString Model::getMainNavigation(int key)
{
	return mainNavigation.value(key);
}

bool Model::removeMainNavigation(int key)
{
	return mainNavigation.remove(key);
}

void Model::clearMainNavigation()
{
	mainNavigation.clear();
}


QList<QTreeWidgetItem *> Model::getSubNavigation(int key)
{
	return subNavigation.value(key);
}

QMap<int, QList<QTreeWidgetItem*> > Model::getSubNavigationModel()
{
	return subNavigation;
}

QMap<int, QString> Model::getMainNavigationModel()
{
	return mainNavigation;
}
bool Model::removeSubNavigation(int key)
{
	return subNavigation.remove(key);
}

void Model::addPage(int key, QJsonObject page)
{
	pages.insert(key, page);
}
QJsonObject Model::getPage(int key)
{
	return pages.value(key);
}
bool Model::removePage(int key)
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
