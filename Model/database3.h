#ifndef DATABASE3_H
#define DATABASE3_H

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

class Database3 : public QObject
{
	Q_OBJECT
public:
	explicit Database3(QObject *parent = 0);
	/*
	static void
	bootstrap_callback(lcb_t instance, lcb_error_t err);
	static void get_callback(lcb_t instance, int cbtype, const lcb_RESPBASE *rb);
	static void store_callback(lcb_t instance, int cbtype, const lcb_RESPBASE *rb);
	static lcb_io_opt_t
	create_libevent_io_ops(struct event_base *evbase);
	static lcb_t
	create_libcouchbase_handle(lcb_io_opt_t ioops);
*/
signals:

public slots:
};

#endif // DATABASE3_H
