#ifndef MERPLYQUERYUI_H
#define MERPLYQUERYUI_H

#include "erpcombobox.h"

#include <QHBoxLayout>
#include <QObject>
#include <QWidget>

class MerplyQueryUI : public QWidget
{
	Q_OBJECT
public:
	explicit MerplyQueryUI(QWidget *parent = 0);
	void fill(QJsonObject strct);
	void fillEntityQuery(QJsonObject strct);
	void fillDocumentID(QString document_id);
private:
	QHBoxLayout *layout;
	QVector<QWidget*> fields;
	QString document_id;
	QJsonObject strct;
	void clear();
signals:
	void queryResults(QVector<QJsonDocument> items);
public slots:
	void fillData(QJsonDocument strct);
	void generateQuery();
	void gotData(QVector<QJsonDocument> items);

};

#endif // MERPLYQUERYUI_H
