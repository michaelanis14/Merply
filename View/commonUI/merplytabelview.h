/*************************************
**   Created on:  12/4/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/

#ifndef MERPLYTABELVIEW_H
#define MERPLYTABELVIEW_H


#include "merplyreporttablemodel.h"

#include "qtrpt.h"

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
	merplyTabelView(QWidget *parent = 0, QString propertyName ="");
	QTableWidget* tabel;
	QString save(QString propertyName);
	bool fill(QJsonObject columns);
	void indexTable(const QString document_id, const QList<QJsonDocument> items, const bool, const bool);
	void clear();
	QList<QJsonDocument> items;
private:
	QVBoxLayout* layout;
	QHBoxLayout* lblLayout;
	QLabel* print;
	QString propertyName;
	QTableView* tableView;
	MerplyReportTableModel* model;
	QHash<QString,QJsonObject>indexedTable;
	QString currenctPrintID;
	QtRPT *report;
	//QStandardItemModel *model;
	//QStringList headerLabels;
signals:
	void updateModel(QList<QJsonDocument> documents);
protected:
	void mousePressEvent(QMouseEvent *event);

public slots:
	void printTabel();
	void printEntity(const QString&id);
	void editEntity(const QString&id);
	void deleteEntity(const QString&id);
	void gotReportData(QList<QJsonDocument> documents);
	void updateHeaderData(QList<QString> headerItems);
	void setValue(const int, const QString paramName, QVariant &paramValue, const int);

};

#endif // merplyTabelView_H
