/*************************************
**   Created on:  12/4/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/

#ifndef MERPLYTABELVIEW_H
#define MERPLYTABELVIEW_H


#include "merplyreporttablemodel.h"

#include "qtrpt.h"

#include "hcontrollers.h"

#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>





class merplyTabelView : public QWidget
{
	Q_OBJECT

public:
	merplyTabelView(QWidget *parent = 0,bool add = false,bool edit = false);
	bool fill(QJsonObject columns,QString filter = "");
	bool fillLocalSource(QJsonObject columns,QString filter = "");
	bool fillText(QJsonObject data);
	void indexTable(const QString document_id, const QList<QJsonDocument> items);
	QList<QJsonDocument> items;
	QJsonObject save();
private:
	QVBoxLayout* layout;
	QHBoxLayout* lblLayout;
	QLabel* print;
	QTableView* tableView;
	MerplyReportTableModel* model;
	HControllers* controllers ;
	QString currenctPrintID;
	QtRPT *report;
	bool add;
	bool edit;
	void initHController(QJsonObject columns);
	//QStandardItemModel *model;
	//QStringList headerLabels;
signals:
	void updateModel(QList<QJsonDocument> documents);


public slots:
	void printTabel();
	void printEntity(const QString&id);
	void gotReportData(QList<QJsonDocument> documents);
	void updateHeaderData(QList<QString> headerItems);
	void setValue(const int, const QString paramName, QVariant &paramValue, const int);
	void modelFinished();
	void controller_Clicked(QString nameAction);
	void selectionChanged(const QItemSelection &, const QItemSelection &);
};

#endif // merplyTabelView_H
