#ifndef DATABASE_H
#define DATABASE_H


#include "databaseworker.h"

#include <QList>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

//#define DATABASE "default"
class DatabaseWorker; // forw decl

class Database : public QThread
{
	Q_OBJECT
public:
	 Database(QObject *parent = 0);
	 ~Database();
	//static Database* Get();
//	QList<QSqlRecord> query(const QString &query, const QVariantMap &arguments);
	void query(const QString &query);
	void getJson(const QString& select, const QString &tabel, const QString& key, const QString &id);
	void deletRow(const QString &tabel, const QString &id);
	void insert(QString query);
	void execute( const QString& query );

private :
	DatabaseWorker* m_worker;

	QString connectionName;
	QString connectionNameMain;
	QVector<QSqlRecord> threadedSql(const QSqlDatabase &db, const QString &query) ;
	bool treadedInsert(const QSqlDatabase &db,const QString &query);


public slots:
	void gotQueryResutls(const QVector<QSqlRecord> results);
	void gotJson(const QVector<QSqlRecord> results);




signals:
  void progress( const QString& msg );
  void ready(bool);
  void readyToQuery();
  void results( const QList<QSqlRecord>& records );

  void queryResults(QVector<QSqlRecord> results);
  void gotDocument(QJsonDocument document);
  void gotDocuments(QVector<QJsonDocument> documents);
  void gotValue(QString value);
  //void gotLastKey(QString LastKeyID);
  void saved(QString document_id);
  void savedQJson(QJsonDocument savedDocument);


protected:
  void run();

signals:
  void executefwd( const QString& query );




};

#endif // DATABASE_H
