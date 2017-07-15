#ifndef PRSISTANCE_H
#define PRSISTANCE_H



#include "database.h"

#include <QString>
#include <QStringList>
#include <QMap>



class Prsistance : public QObject
{
	Q_OBJECT
public:
	explicit Prsistance(QObject *parent = 0);
	static Prsistance* Get();
	static bool init();
	static QString readFile(QString path);
	static QStringList readCSVFile(QString path);

	static void GetSelectList(QString table, QString select,QString condition = "");
	static void GetJsonEntityFields(QString table, QString select,QString condition = "");



	void count(const QString &table);
	void countTabel(const QString &table);
	static int CountIndexes(const QString index);
	static QVector<QJsonDocument> GetALL(const QString entity,const QString condition);
	static bool Select(const QString query);
	static QString GetDatabaseName();
	static bool CreateViewStructureTabels();

	QString getTableNumber(QString table);

	int countRecords(QString table);
	QStringList getColumnsNumber(const QString table);
	void insertIntoTable(QString tableName, QString fileName, int startingRow, QStringList dataIndex);
private:
	static Prsistance* p_instance;
	bool ready;
	Database* database;
signals:
	void GotSelectList(QVector<QSqlRecord> items);
	void count(int count);
public slots:
	void GetSelectListData(QVector<QSqlRecord> items);
	void gotCount(QString value);
	void readyToQuery(bool ready = true);
};

#endif // PRSISTANCE_H
