#ifndef InitTabel_H
#define InitTabel_H

#include "prsistance.h"

#include <QObject>

class InitTabel : public QObject
{
	Q_OBJECT
public:
	explicit InitTabel(QObject *parent = 0, QString tblName = "");
	void count(QString tblName);
	QString tblName;
	Prsistance *persistance;
	QString genetrateCreateTabelQuery(QJsonDocument document);
	QString genetrateCreateTabelQueryForTabel(QString parentEntity, QString field, QJsonValue tabel);

public slots:
	void gotCounterT(int tblCount);
	void gotResults(QVector<QSqlRecord> results);
signals:

public slots:
};

#endif // InitTabel_H
