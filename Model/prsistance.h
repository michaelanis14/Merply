#ifndef PRSISTANCE_H
#define PRSISTANCE_H

#define DATABASE "default"

#include "database.h"

#include <QString>
#include <QStringList>




class Prsistance : public QObject
{
	Q_OBJECT
public:
	explicit Prsistance(QObject *parent = 0);
	static Prsistance* Get();
	static bool write(QString table, QList<QString> lines,bool update);
	static void write(QString table, QString line);

	static QJsonArray table(QString line);
	static bool init();
	static QString initCountries();
	static QString initCities();
	static void GetJsonList(QString table, QString select,QString condition = "");
	static void GetJsonEntityFields(QString table, QString select,QString condition = "");

	static int Count(const QString table);
	static QList<QJsonDocument> GetALL(const QString entity,const QString condition);
	static bool Select(const QString query);
	static QString GetDatabaseName();
private:
	static Prsistance* p_instance;
signals:
	void GotJsonSelectList(QList<QJsonDocument> items);
public slots:
	void GetJsonListData(QList<QJsonDocument> items);
};

#endif // PRSISTANCE_H
