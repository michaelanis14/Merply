#ifndef COUCHBASELIBMANAGER_H
#define COUCHBASELIBMANAGER_H


#include <QObject>
#include<QStack>
#include <libcouchbase/couchbase.h>


class CouchbaseLibManager : public QObject
{
	Q_OBJECT
public:
	explicit CouchbaseLibManager(QObject *parent = 0, int poolCount = 10, QString connStr = "");
	static  CouchbaseLibManager* Get(int poolCount = 10,QString connStr = "");
	lcb_t popConnection();
	void pushConnection(lcb_t instance);

private:
	static CouchbaseLibManager* p_instance;
	QStack<lcb_t> couchbaseConnectPool;
	void init(int poolCount,QString connStr);
	QString connStr;
	int poolCount;

signals:

public slots:
};

#endif // COUCHBASELIBMANAGER_H
