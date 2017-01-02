#ifndef PRSISTANCE_H
#define PRSISTANCE_H



#include "database.h"

#include <QString>
#include <QStringList>




class Prsistance : public QObject
{
	Q_OBJECT
public:
	explicit Prsistance(QObject *parent = 0);
	static Prsistance* Get();
	static bool init();
	static QString readFile(QString path);
	static QStringList readCSVFile(QString path);

	static void GetJsonList(QString table, QString select,QString condition = "");
	static void GetJsonEntityFields(QString table, QString select,QString condition = "");

	static int Count(const QString table);
	static int CountIndexes(const QString index);
	static QVector<QJsonDocument> GetALL(const QString entity,const QString condition);
	static bool Select(const QString query);
	static QString GetDatabaseName();
private:
	static Prsistance* p_instance;
signals:
	void GotJsonSelectList(QVector<QJsonDocument> items);
public slots:
	void GetJsonListData(QVector<QJsonDocument> items);
};

#endif // PRSISTANCE_H
