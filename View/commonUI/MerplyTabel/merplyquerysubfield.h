#ifndef MERPLYQUERYSUBFIELD_H
#define MERPLYQUERYSUBFIELD_H

#include <QObject>
#include <QWidget>
#include <QFormLayout>
#include "erpcombobox.h"

class MerplyQuerySubField : public QWidget
{
	Q_OBJECT
public:
	explicit MerplyQuerySubField(QJsonObject strct,QWidget *parent = 0);
	QString getValue(QString entity);
	int getLayoutCount();
private:
	QFormLayout * layout;
	ERPComboBox* combox;
	QWidget* field;
	QJsonObject strct;
	QString label;
	QString clmnNumber;

signals:

public slots:
	void refrenceData(QVector<QJsonDocument> items);
};

#endif // MERPLYQUERYSUBFIELD_H
