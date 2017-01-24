#ifndef DATABASE_H
#define DATABASE_H

#include <cstdio>
#include <cstdlib>
#include <string.h>


#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

#include <libcouchbase/couchbase.h>
#include <libcouchbase/n1ql.h>

//#define DATABASE "default"
#define DATABASE "AM"
#define ORDERBY "رقم"

class Database: public QObject
{

	Q_OBJECT
public:
	Database();

	static Database* Get();
	static void storage_callback(lcb_t, const void *, lcb_storage_t, lcb_error_t, const lcb_store_resp_t *resp);
	static void get_callback(lcb_t instance, const void *cookie, lcb_error_t err,
							 const lcb_get_resp_t *resp);
	static void on_stored_status (lcb_t instance, const void *, lcb_storage_t,
								  lcb_error_t err, const lcb_store_resp_t *resp);
	static void on_removed(lcb_t instance, const void *, lcb_error_t err, const lcb_remove_resp_t *resp);
	static void arithmatic_callback(lcb_t instance, const void*, lcb_error_t error, const lcb_arithmetic_resp_t*);
	bool storeDoc(QString key,QJsonDocument document);
	bool updateDoc(QJsonDocument document);
	bool deleteDoc(QString documentid);
	static bool IncrementKey(QString key);
	static int GetKey(QString key);
	static lcb_t InitDatabase(QString connStr = "");
	static bool KillDatabase(lcb_t instance);
	static void got_document(lcb_t instance, const void *, lcb_error_t err,
							 const lcb_get_resp_t *resp);
	static bool getDoc(QString key);

	//QJsonDocument getDocument() const;
	static void rowCallback(lcb_t, int, const lcb_RESPN1QL *resp);

	static lcb_t instance;



	QVector<QJsonDocument> getArray() const;

	QString getValue() const;
	QString LastKeyID;
	QString getLastKeyID() const;

	void query(QString query, bool cached = true);

private:
	static Database* p_instance;
	//QJsonDocument document;
	QString lastQuery;
	QJsonDocument documentToArray;
	QVector<QJsonDocument> array;
	bool connIssue;
	QMap<QString,QJsonDocument> cachedDocuments;
	QMap<QString,QVector<QJsonDocument> > cachedArrayDocuments;

	//	QString value;

public slots :

signals:
	void gotDocument(QJsonDocument document);
	void gotDocuments(QVector<QJsonDocument> array);
	void gotValue(QString value);
	void gotLastKey(QString LastKeyID);
	void saved(QString document_id);
};

#endif // DATABASE_H
