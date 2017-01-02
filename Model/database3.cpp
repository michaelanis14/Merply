#include "database3.h"

#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <QThread>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QMessageBox>

Database3::Database3(QObject *parent) : QObject(parent)
{

}
/*

void Database3::bootstrap_callback(lcb_t instance, lcb_error_t err)
{
	lcb_CMDSTORE cmd = { 0 };
	LCB_CMD_SET_KEY(&cmd, "foo", 3);
	LCB_CMD_SET_VALUE(&cmd, "bar", 3);
	cmd.operation = LCB_SET;
	err = lcb_store3(instance, NULL, &cmd);
}

void Database3::get_callback(lcb_t instance, int cbtype, const lcb_RESPBASE *rb)
{
	const lcb_RESPGET *rg = (const lcb_RESPGET *)rb;
	fprintf(stdout, "I stored and retrieved the key 'foo'. Value: %.*s.\n", (int)rg->nvalue, rg->value);
	event_base_loopbreak((void *)lcb_get_cookie(instance));
}

void Database3::store_callback(lcb_t instance, int cbtype, const lcb_RESPBASE *rb)
{
	lcb_error_t rc;
	lcb_CMDGET gcmd =  { 0 };
	LCB_CMD_SET_KEY(&gcmd, rb->key, rb->nkey);
	rc = lcb_get3(instance, NULL, &gcmd);
}

lcb_io_opt_t
Database3::create_libevent_io_ops(struct event_base *evbase)
{
	struct lcb_create_io_ops_st ciops;
	lcb_io_opt_t ioops;
	lcb_error_t error;

	memset(&ciops, 0, sizeof(ciops));
	ciops.v.v0.type = LCB_IO_OPS_LIBEVENT;
	ciops.v.v0.cookie = evbase;

	error = lcb_create_io_ops(&ioops, &ciops);
	if (error != LCB_SUCCESS) {
		fprintf(stderr, "Failed to create an IOOPS structure for libevent: %s\n", lcb_strerror(NULL, error));
		exit(EXIT_FAILURE);
	}

	return ioops;
}

lcb_t
Database3::create_libcouchbase_handle(lcb_io_opt_t ioops)
{
	lcb_t instance;
	lcb_error_t error;
	struct lcb_create_st copts;

	memset(&copts, 0, sizeof(copts));

	// If NULL, will default to localhost
	copts.version = 3;
	copts.v.v3.connstr = "couchbase://localhost/default";
	copts.v.v0.io = ioops;
	error = lcb_create(&instance, &copts);

	// Set up the callbacks
	lcb_set_bootstrap_callback(instance, bootstrap_callback);
	lcb_install_callback3(instance, LCB_CALLBACK_GET, get_callback);
	lcb_install_callback3(instance, LCB_CALLBACK_STORE, store_callback);
	lcb_connect(instance);
	return instance;
}

// This example shows how we can hook ourself into an external event loop.
// You may find more information in the blogpost: http://goo.gl/fCTrX

int main(void)
{
	struct event_base *evbase = event_base_new();
	lcb_io_opt_t ioops = create_libevent_io_ops(evbase);
	lcb_t instance = create_libcouchbase_handle(ioops);

	//Store the event base as the user cookie in our instance so that
	 // we may terminate the program when we're done//
	lcb_set_cookie(instance, evbase);

	// Run the event loop//
	event_base_loop(evbase, 0);

	// Cleanup//
	event_base_free(evbase);
	lcb_destroy(instance);
	exit(EXIT_SUCCESS);
}
*/
