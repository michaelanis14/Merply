/*************************************
**   Created on:  12/4/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/

#ifndef MERPLYTABELVIEW_H
#define MERPLYTABELVIEW_H


#include "merplyreporttablemodel.h"
#include "mtabelcombobox.h"
#include "qtrpt.h"

#include "hcontrollers.h"
#include "merplyqueryui.h"

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
	void indexTable(const int document_id, const QVector<QJsonDocument> items);
	QVector<QJsonDocument> items;
	QJsonObject save();
	MerplyReportTableModel* model;
	MerplyReportTableModel* getModel() const;
	QModelIndex getIndexAt(QPoint position);
	QTableView* getTableView() const;
	void generateQuery(int limit);
private:
	QVBoxLayout* layout;
	QHBoxLayout* lblLayout;
	QLabel* print;
	QTableView* tableView;
	MerplyQueryUI* queryUI;

	HControllers* controllers ;
	QString currenctPrintID;
	QtRPT *report;
	bool add;
	bool edit;
	void initHController(QJsonObject columns);
	void initDelegateClmns(QJsonObject columns);
	QVector<MTabelCombobox *> delegateItems;
	QString indexDocument_id;
	//QStandardItemModel *model;
	//QStringList headerLabels;
signals:
	void updateModel(QVector<QJsonDocument> documents);


public slots:
	void printTabel();
	void printEntity(const QString&id);
	void gotReportData(QVector<QJsonDocument> documents);
	void updateHeaderData(QList<QString> headerItems);
	void setValue(const int, const QString paramName, QVariant &paramValue, const int);
	void modelFinished();
	void controller_Clicked(QString nameAction);
	void selectionChanged(const QItemSelection &, const QItemSelection &);
	void resizeTabelToContets();
};

#endif // merplyTabelView_H
