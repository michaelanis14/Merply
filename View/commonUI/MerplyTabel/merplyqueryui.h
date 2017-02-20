#ifndef MERPLYQUERYUI_H
#define MERPLYQUERYUI_H

#include "erpcombobox.h"
#include "merplyquerysubfield.h"

#include <QHBoxLayout>
#include <QObject>
#include <QWidget>
#include <QPushButton>

class MerplyQueryUI : public QWidget
{
	Q_OBJECT
public:
	explicit MerplyQueryUI(QWidget *parent = 0, bool btnFilter = false);
	void fill(QJsonObject strct);
	void fillEntityQuery(QJsonObject strct);
	void fillDocumentID(QString document_id);
	void fillAddtoTable(QJsonArray clmns);
	QString getFields(QString entity);
private:
	bool btnFilterFlag;
	QPushButton* btnFilter;
	QHBoxLayout *layout;
	QVector<MerplyQuerySubField*> fields;
	QString document_id;
	QJsonObject strct;
	bool clmnsFlag;
	//QJsonArray clmns;
	QString selectClmnsQuery;
	void clear();
signals:
	void queryResults(QVector<QJsonDocument> items);
public slots:
	void fillData(QJsonDocument strct);
	void generateQuery();
	void gotData(QVector<QJsonDocument> items);
	void disablebutton();

};

#endif // MERPLYQUERYUI_H

