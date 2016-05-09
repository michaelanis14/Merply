/*************************************
**   Created on:  12/4/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/

#ifndef MERPLYTABELVIEW_H
#define MERPLYTABELVIEW_H

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
	bool fill(QJsonObject columns, QJsonObject data);
	void indexTable(const QString document_id, const QList<QJsonDocument> items, const bool edit, const bool remove);
	void clear();
	QList<QJsonDocument> items;
private:
	QVBoxLayout* layout;
	QHBoxLayout* lblLayout;
	QLabel* print;
	QString propertyName;
	//QStandardItemModel *model;
	//QStringList headerLabels;
signals:
protected:
	void mousePressEvent(QMouseEvent *event);

public slots:
	void printTabel();
	void editEntity(const QString&id);
	void deleteEntity(const QString&id);

	void updateHeaderData(QList<QString> headerItems);

};

#endif // merplyTabelView_H
