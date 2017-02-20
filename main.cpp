/**************************************************************************
** File: main.cpp
** Created on: Wed Feb 18 2015
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/
#include "controller.h"
//#include "mainwindow.h"

#include <QTime>
#include <iostream>
#include <string>
#include <QApplication>
#include <QEvent>
#include <QDebug>
#include <QProcess>
#include <QSysInfo>
#ifdef Q_OS_WIN32
#include <Windows.h>
#endif

#include <QTextCodec>
class Merply_Application : public QApplication {
public:
	Merply_Application(int& argc, char** argv) : QApplication(argc, argv) {}

};



/**
* @brief  the main application function.
*
* calls the first display to be shown
**/

int main(int argc, char *argv[])
{
	Merply_Application a(argc, argv);
	QApplication::setOrganizationName("Merply - Michael Bishara e.U.");
	QApplication::setOrganizationDomain("www.merply.com");
	QApplication::setApplicationName("Merply");
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
//	QTextCodec::s
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

	int id = QFontDatabase::addApplicationFont(":/fonts/artro.ttf");
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
	QFont BDavat(family);


	QApplication::setFont(BDavat);
//	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));


	QApplication::setLayoutDirection(Qt::RightToLeft);

#ifdef Q_OS_WIN32
	MEMORYSTATUSEX memory_status;
	ZeroMemory(&memory_status, sizeof(MEMORYSTATUSEX));
	memory_status.dwLength = sizeof(MEMORYSTATUSEX);
	if (GlobalMemoryStatusEx(&memory_status)) {
		Controller::Log(QStringList() <<	QString("RAM: %1 MB").arg(memory_status.ullTotalPhys / (1024 * 1024)));
		} else {
		Controller::Log(QStringList() << "Unknown RAM");
		}
#endif
#ifndef Q_OS_WIN32
#ifndef Q_OS_IOS
	QProcess p;
	//p.start("awk", QStringList() << "/MemFree/ { print $2 }" << "/proc/meminfo");
	p.start("free -m");
	p.waitForFinished();
	QString memory = p.readAllStandardOutput();
	p.close();


	Controller::Log(QStringList() << "---------------------------------------------------------");
	if(memory.count() > 1)
		Controller::Log(QStringList()<< "System Information :" << memory.split("\n")[1]);
#endif
#endif


	//Controller::Log(QStringList() << QTime::currentTime().toString() << "Application Started");


	Controller::Get()->showDisplay();

	QStringList args = a.arguments();
	if (args.count() == 3)
		{
		Controller::Get()->setShowWarning(false);
		qDebug() << __FILE__ << __LINE__  << "Load File " << args.at(1);
		//Controller::Get()->loadFile(args.at(1));
		qDebug() << __FILE__ << __LINE__  << "Saved at " << args.at(2);
	//	Controller::Get()->save(false);
		return 0;
		}

	return a.exec();
}
