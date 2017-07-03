#ifndef PRINTCONTROLLER_H
#define PRINTCONTROLLER_H

#include "qtrpt.h"
#include<QJsonDocument>
#include <QJsonArray>
#include <QObject>

class PrintController : public QObject
{
	Q_OBJECT
public:
	explicit PrintController(QObject *parent = 0);
	static PrintController* Get();
	void printEntity(int id);
private:
	static PrintController* p_instance;
	QtRPT *report;
	QJsonDocument printDocumnet;
	QJsonDocument printStrct;
	QMap <QString,QString> fieldsValues;
	QJsonArray reportData;
	void getFieldstoValueMap(QJsonObject entity);
	bool showDialog;
signals:

public slots:
	void gotPrintEntity(QJsonDocument document, bool showDialog = true);
	void gotPrintStrct(QJsonDocument strct);
	void setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage);
};

#endif // PRINTCONTROLLER_H
