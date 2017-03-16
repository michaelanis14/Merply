#include "couchbaselibmanager.h"
#include "model.h"

CouchbaseLibManager::CouchbaseLibManager(QObject *parent,int poolCount,QString connStr) : QObject(parent)
{
	this->connStr = connStr;
	this->poolCount = poolCount;
	init(poolCount,connStr);
}




 CouchbaseLibManager* CouchbaseLibManager::Get(int poolCount,QString connStr)
{
	if ( p_instance == 0){
		p_instance = new CouchbaseLibManager(0,poolCount,connStr);
		}
	return p_instance;
}

lcb_t CouchbaseLibManager::popConnection()
{
	//qDebug() << __FILE__ << __LINE__ <<"Pool POP";
	if(couchbaseConnectPool.count() == 0) {
		qDebug() << __FILE__ << __LINE__ <<"Pool is Empty reInit";
		init(poolCount,connStr);
		}
	return couchbaseConnectPool.pop();
}

void CouchbaseLibManager::pushConnection(lcb_t instance)
{
	//qDebug() << __FILE__ << __LINE__ <<"Pool PUSH";
	couchbaseConnectPool.push(instance);
}

void CouchbaseLibManager::init(int poolCount,QString connStr)
{
	for(int i = 0; i < poolCount; i++){
	//	qDebug() << __FILE__ << __LINE__  << "init";
		connStr = "couchbase://localhost/"+QString(DATABASE);
		//connStr = "couchbase://192.168.1.135,139.59.149.28,193.171.44.206/"+QString(DATABASE);
		//connStr = "couchbase://193.171.44.206/"+QString(DATABASE);

		struct lcb_create_st cropts;// = { 0 };
		cropts.version = 3;
		QByteArray databaseByte = connStr.toLatin1();
		const char *databseCharK = databaseByte.data();
		cropts.v.v3.connstr = databseCharK;
		//cropts.v.v3.passwd ="2019066";
		//cropts.v.v3.username="admin";

		//qDebug() << cropts.v.v3.connstr<<cropts.v.v3.passwd <<cropts.v.v3.username;
		lcb_error_t err;
		lcb_t instance;
		err = lcb_create(&instance, &cropts);
		if (err != LCB_SUCCESS) {
			qDebug("Couldn't create instance!\n");
			qDebug() <<  lcb_strerror(instance, err);
			}

		// connecting

		lcb_connect(instance);
		lcb_wait(instance);
		if ( (err = lcb_get_bootstrap_status(instance)) != LCB_SUCCESS ) {
			qDebug() << __FILE__ << __LINE__ << "Couldn't bootstrap! " << lcb_strerror(instance, err);
			}
		couchbaseConnectPool.push(instance);
		}
}





CouchbaseLibManager* CouchbaseLibManager::p_instance = 0;
