#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>
#include <QtConcurrent>
#include <QFuture>
//#define DATABASE "default"


class Database : public QObject
{
	Q_OBJECT
public:
	explicit Database(QObject *parent = 0);
	//static Database* Get();
//	QList<QSqlRecord> query(const QString &query, const QVariantMap &arguments);
	void query(const QString &query);
	void getJson(const QString& select, const QString &tabel, const QString& key, const QString &id);
	void deletRow(const QString &tabel, const QString &id);
	void insert(QString query);
	~Database();
private :


	QString connectionName;
	QString connectionNameMain;
	static Database* p_instance;
	//QVector<QSqlRecord> queryresults;
	QFutureWatcher<QVector<QSqlRecord>> *watcher;
	QFuture<QVector<QSqlRecord> > future;
	//static QAtomicInt no = 0;
	QVector<QSqlRecord> threadedSql(const QSqlDatabase &db, const QString &query) ;
	bool treadedInsert(const QSqlDatabase &db,const QString &query);
signals:
	void queryResults(QVector<QSqlRecord> results);
	void gotDocument(QJsonDocument document);
	void gotDocuments(QVector<QJsonDocument> documents);
	void gotValue(QString value);
	//void gotLastKey(QString LastKeyID);
	void saved(QString document_id);
	void savedQJson(QJsonDocument savedDocument);

public slots:
	void gotQueryResutls();
	void gotJson();


};

#endif // DATABASE_H
