#include "database.h"

//#include "model.h"

#include "accesscontroller.h"
#include "couchbaselibmanager.h"
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <QThread>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>


void Database::storage_callback(lcb_t, const void *, lcb_storage_t,
								lcb_error_t , const lcb_store_resp_t *resp)
{

	qDebug("Stored %.*s\n", (int)resp->v.v0.nkey, resp->v.v0.key) ;
}

void Database::get_callback(lcb_t , const void *, lcb_error_t ,
							const lcb_get_resp_t *resp)
{
	qDebug("Retrieved key %.*s\n", (int)resp->v.v0.nkey, resp->v.v0.key);
	qDebug("Value is %.*s\n", (int)resp->v.v0.nbytes, resp->v.v0.bytes);
}

void Database::on_stored_status (lcb_t instance, const void *, lcb_storage_t ,
								 lcb_error_t err, const lcb_store_resp_t * resp)
{
	if (err != LCB_SUCCESS) {
		qDebug("Couldn’t store item to cluster: %s\n", lcb_strerror(instance, err));
		}
	else {
		QByteArray keyByte((char*) resp->v.v0.key,(int)resp->v.v0.nkey);
		p_instance->LastKeyID = QString(keyByte);
		emit p_instance->gotLastKey(QString(keyByte));
		qDebug("Stored Key_on_stored_status:  %.*s\n",(int)resp->v.v0.nkey,resp->v.v0.key);


		QString card = p_instance->LastKeyID.split("::")[0];
		card.append("::%");
		QString query = QString("SELECT `"+QString(DATABASE)+"`.*,meta("+QString(DATABASE)+").id AS `document_id` FROM `"+QString(DATABASE)+"` WHERE meta("+QString(DATABASE)+").id LIKE \""+card+"\"");

		//if(p_instance->cachedArrayDocuments.contains(query)){
		//	p_instance->cachedArrayDocuments.remove(query);
		//	}

		p_instance->emit saved(p_instance->LastKeyID);
		}
}

void  Database::arithmatic_callback(lcb_t instance, const void *,
									lcb_error_t error,
									const lcb_arithmetic_resp_t *)
{
	if (error == LCB_SUCCESS) {
		// qDebug("Stored Key_arithmatic_callback:  %.*s\n",(int)resp->v.v0.nkey,resp->v.v0.key);
		} else {
		fprintf(stderr, "Couldn’t schedule operation: %s\n", lcb_strerror(instance, error));
		}
}


bool Database::updateDoc(QJsonDocument document)
{
	if(p_instance->cachedDocuments.contains(document.object().value("document_id").toString())){
		//	qDebug() << "contains update Document" << document.object().value("document_id").toString();
		p_instance->cachedDocuments.remove(document.object().value("document_id").toString());
		}
	lcb_t instance = Database::InitDatabase();
	//qDebug() << __FILE__ << __LINE__  << "UPDATE DOC" << document ;
	//qDebug()  << document.object().value("document_id").toString().toLatin1();

	//lcb_set_store_callback(instance, on_stored_status);

	QJsonObject objWithKey = document.object();
	//objWithKey.insert("document_id",key);
	objWithKey.insert("ed",QDateTime::currentDateTime().currentMSecsSinceEpoch());
	objWithKey.insert("edited_at",QDateTime::currentDateTime().toString(Qt::ISODate));
	objWithKey.insert("edited_byID",AccessController::Get()->getUserID());
	objWithKey.insert("edited_byName",AccessController::Get()->getUserName());
	document = QJsonDocument(objWithKey);

	struct lcb_store_cmd_st cmd;// = { 0 };
	lcb_store_cmd_t *cmdlist = &cmd;
	QByteArray bKey = document.object().value("document_id").toString().toLatin1();
	const char *docbKey = bKey.data();
	document.object().remove("document_id");
	QByteArray ba =  document.toJson(QJsonDocument::Compact) ;
	const char *doc = ba.data();
	//qDebug() << __FILE__ << __LINE__  <<"Prsistance UpdateDOC"<< document.object().value("document_id").toString() << strJson;
	cmd.v.v0.key = docbKey;
	cmd.v.v0.nkey = strlen(docbKey);
	cmd.v.v0.bytes = doc;
	cmd.v.v0.nbytes = strlen(doc);
	cmd.v.v0.operation = LCB_REPLACE;
	//qDebug() << __FILE__ << __LINE__  <<document.object().value("cas_value").toString().toLongLong();
	cmd.v.v0.cas =  document.object().value("cas_value").toString().toLongLong();
	lcb_set_store_callback(instance, on_stored_status);
	lcb_set_get_callback(instance, get_callback);


	lcb_error_t err = lcb_store(instance, NULL, 1, &cmdlist);
	if (err == LCB_SUCCESS) {
		//lcb_wait(instance);
		} else {
		fprintf(stderr, "Couldn’t schedule operation: %s\n", lcb_strerror(instance, err));
		qDebug() << __FILE__ << __LINE__ << __FILE__ << __LINE__ << "ERRLOG" << document;
		}


	return Database::KillDatabase(instance);
}

void Database::on_removed(lcb_t instance, const void *, lcb_error_t err,
						  const lcb_remove_resp_t *resp) {

	if (err != LCB_SUCCESS) {
		fprintf(stderr, "Failed to remove item: %s\n", lcb_strerror(instance, err));
		}
	else qDebug("Removed %.*s\n", (int)resp->v.v0.nkey, resp->v.v0.key) ;

}

bool Database::deleteDoc(QString documentid)
{
	lcb_t instance = Database::InitDatabase();
	if(instance == NULL){
		qDebug() << __FILE__ << __LINE__<< "Failed to INIT Database @ Increment";
		return false;
		}
	lcb_set_remove_callback(instance, on_removed);
	lcb_remove_cmd_t cmd ;//= { 0 };
	const lcb_remove_cmd_t *cmdlist = &cmd;
	QByteArray bKey = documentid.toLatin1();
	const char *docbKey = bKey.data();
	cmd.v.v0.key = docbKey;
	cmd.v.v0.nkey = strlen(docbKey);
	lcb_error_t err = lcb_remove(instance, NULL, 1, &cmdlist);
	if (err != LCB_SUCCESS) {
		printf("Couldn't schedule remove operation: %s\n", lcb_strerror(instance, err));
		return false;
		} else {
		//lcb_wait(instance);
		Database::KillDatabase(instance);
		return true;
		}
	return true;
}

lcb_t Database::InitDatabase(QString connStr)
{
	// initializing
	//p_instance->document = QJsonDocument();
	connStr = "couchbase://localhost/"+QString(DATABASE);
	//	this->instance;

	return CouchbaseLibManager::Get()->popConnection();
	//if(p_instance->instance){
	//qDebug() << "static";
	//return p_instance->instance;
	//	}

	//connStr = "couchbase://ec2-35-166-198-84.us-west-2.compute.amazonaws.com/"+QString(DATABASE);


	//connStr = "couchbase://139.59.149.28/"+QString(DATABASE);



	//p_instance->array.clear();

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
		return  NULL;
		}

	// connecting

	lcb_connect(instance);
	lcb_wait(instance);
	if ( (err = lcb_get_bootstrap_status(instance)) != LCB_SUCCESS ) {
		qDebug() << __FILE__ << __LINE__ << "Couldn't bootstrap! " << lcb_strerror(instance, err);
		return NULL;
		}
	p_instance->instance = instance;
	return instance;
}

bool Database::KillDatabase(lcb_t instance,bool wait)
{
	//lcb_tick_nowait(instance);
	if(wait)
		lcb_wait3(instance,LCB_WAIT_NOCHECK);
	CouchbaseLibManager::Get()->pushConnection(instance);
	//lcb_destroy(instance);
	return true;
}

bool Database::IncrementKey(QString key)
{
	//p_instance->value = QString::number(-1);
	p_instance->LastKeyID = "-1";
	lcb_t instance = Database::InitDatabase();
	if(instance == NULL){
		qDebug() << __FILE__ << __LINE__<< "Failed to INIT Database @ Increment";
		return false;
		}

	//lcb_set_store_callback(instance, on_stored_status);
	//lcb_set_get_callback(instance, get_callback);
	lcb_arithmetic_cmd_t cmdd ;//= { 0 };
	const lcb_arithmetic_cmd_t *cmdlistt = &cmdd;
	QByteArray bKey = key.toLatin1();
	const char *docbKey = bKey.data();
	cmdd.v.v0.key = docbKey;
	cmdd.v.v0.nkey = strlen(docbKey);
	cmdd.v.v0.delta = 1; // Increment by one
	cmdd.v.v0.initial = 0; // Set to 1 if it does not exist
	cmdd.v.v0.create = 1; // Create item if it does not exist
	lcb_arithmetic(instance, NULL, 1, &cmdlistt);
	lcb_set_arithmetic_callback(instance, arithmatic_callback);
	lcb_wait(instance); // get_callback is invoked here
	return Database::KillDatabase(instance);

}

int Database::GetKey(QString key)
{

	if(getDoc(key))
		return p_instance->LastKeyID.toInt();
	return -1;
}

void Database::got_document(lcb_t instance, const void *, lcb_error_t err,
							const lcb_get_resp_t *resp)
{
	if (err == LCB_SUCCESS) {
		QJsonParseError parserError;
		QByteArray byteArray((char*) resp->v.v0.bytes,(int)resp->v.v0.nbytes);
		QJsonDocument documentWithoutCAS =  QJsonDocument::fromJson(byteArray , &parserError);

		if(parserError.error == QJsonParseError::NoError){
			QJsonObject objectwithCAS = documentWithoutCAS.object();
			objectwithCAS.insert("cas_value",QString::number(resp->v.v0.cas));
			QByteArray keyByte((char*) resp->v.v0.key,(int)resp->v.v0.nkey);
			objectwithCAS.insert("document_id",QString(keyByte));
			emit (p_instance->gotDocument(QJsonDocument(objectwithCAS)));
			//	p_instance->cachedDocuments.insert(QString(keyByte),QJsonDocument(objectwithCAS));
			}
		else{
			emit p_instance->gotValue(QString(byteArray));
			p_instance->LastKeyID = QString(byteArray);
			qDebug() << __FILE__ << __LINE__  << "ERR @Database 219" << parserError.errorString() << QString(byteArray);
			//qDebug() << __FILE__ << __LINE__  <<"Last Keyy"<< p_instance->LastKeyID;
			}
		} else {
		QByteArray keyByte((char*) resp->v.v0.key,(int)resp->v.v0.nkey);
		//qDebug() << __FILE__ << __LINE__  << QString(keyByte);
		fprintf(stderr, "Couldn’t retrieve item: %s %s %d\n", lcb_strerror(instance, err),resp->v.v0.key,(int)resp->v.v0.nkey);
		}
}

bool Database::getDoc(QString key) {
	//Query("SELECT * from QString(DATABASE)  WHERE  \"id = Contact::* \"");
	//qDebug() << __FILE__ << __LINE__  << "hello";
	//qDebug() << __FILE__ << __LINE__  <<"Key:"<< key;
	if(p_instance->cachedDocuments.contains(key)){
		//	qDebug() << "cached" << key;
		emit (p_instance->gotDocument(p_instance->cachedDocuments.value(key)));
		return true;
		}
	p_instance->LastKeyID = "-1";

	lcb_t instance = Database::InitDatabase();
	if(instance == NULL){
		qDebug() << __FILE__ << __LINE__<< "Failed to INIT Database @ Increment";
		return false;
		}
	lcb_set_get_callback(instance, got_document);

	lcb_get_cmd_t cmd ;//= { 0 };
	const lcb_get_cmd_t *cmdlist[] = { &cmd };
	QByteArray bKey = key.toLatin1();
	const char *docbKey = bKey.data();
	cmd.v.v0.key = docbKey;
	cmd.v.v0.nkey = key.size();

	lcb_error_t err = lcb_get(instance, NULL, 1, cmdlist);
	if (err == LCB_SUCCESS) {
		//lcb_wait(instance);
		Database::KillDatabase(instance);
		return true;
		}
	else {
		fprintf(stderr, "Couldn’t schedule get operation: %s\n", lcb_strerror(instance, err));
		Database::KillDatabase(instance);
		return false;
		}


}

void Database::rowCallback(lcb_t , int , const lcb_RESPN1QL *resp) {

	//qDebug() << "rowCallback" << (resp->rflags & LCB_RESP_F_FINAL);
	if (! (resp->rflags & LCB_RESP_F_FINAL)) {
		QJsonParseError parserError;
		QByteArray byteArray(resp->row,resp->nrow);
		//	QJsonDocument documentToArray =  QJsonDocument();
		//documentToArray=  QJsonDocument::fromJson(byteArray , &parserError);
		QJsonDocument::fromJson(byteArray , &parserError);
		if(parserError.error == QJsonParseError::NoError){
			//	documentToArray.toJson(QJsonDocument::Compact);
			p_instance->array.append(QJsonDocument::fromJson(byteArray , &parserError));
			}
		else{
			qDebug() << __FILE__ << __LINE__  << parserError.errorString() << "emitting Value";
			p_instance->emit gotValue(QString(byteArray));
			//	qDebug() << __FILE__ << __LINE__  << p_instance->value;
			}

		} else {
		//	qDebug() << __FILE__ << __LINE__  << p_instance->array;

		//p_instance->document = QJsonDocument(p_instance->array);
		//		p_instance->cachedArrayDocuments.insert(p_instance->lastQuery,p_instance->array);

		p_instance->emit gotDocuments(p_instance->array);

		//	qDebug() << __FILE__ << __LINE__ <<p_instance->lastQuery << p_instance->array;
		//.toJson(QJsonDocument::Compact);
		//	qDebug("Got metadata: %.*s\n", (int)resp->nrow, resp->row);
		}

}
void Database::query(QString query,bool cached)
{

	//if(cached && p_instance->cachedArrayDocuments.contains(query)){
	//	qDebug() << "cachedQ:" << query;
	//	emit (gotDocuments(p_instance->cachedArrayDocuments.value(query)));
	//	return;
	//	}
	//
	qDebug() << __FILE__ << __LINE__ <<"Query:: " << query;
	this->lastQuery = query;
	lcb_t instance = Database::InitDatabase();
	p_instance->array.clear();
	if(instance == NULL){
		qDebug() << __FILE__ << __LINE__<< "Failed to INIT Database @ Increment";
		return;
		}

	// Error checking omitted for brevity

	// The command structure
	lcb_CMDN1QL cmd = {0,0,0,0,0,0,0};
	// Allocate the parameter object
	lcb_N1QLPARAMS *nparams = lcb_n1p_new();

	lcb_n1p_setstmtz(nparams,query.toUtf8().constData());
	lcb_n1p_mkcmd(nparams, &cmd);
	cmd.callback = rowCallback;
	lcb_error_t rc = lcb_n1ql_query(instance, NULL, &cmd);
	if(rc == LCB_SUCCESS){
		lcb_n1p_free(nparams);
		//lcb_wait(instance);

		//qDebug() << __FILE__ << __LINE__  << "sucess q" << query;
		Database::KillDatabase(instance);
		return ;

		}
	else{
		qDebug() << __FILE__ << __LINE__  << "FAIL query" << query;
		lcb_n1p_free(nparams);
		//lcb_wait(instance);
		Database::KillDatabase(instance);
		//return false;
		}
	// We can release the params object now..


}

QVector<QJsonDocument> Database::getArray() const
{
	//qDebug() << __FILE__ << __LINE__  << array <<"--------";
	return array;
}

QString Database::getValue() const
{
	return "-1";
}

QString Database::getLastKeyID() const
{
	return LastKeyID;
}


/**
 * @brief Database::storeDoc
 * @param key
 * @param document
 * @return
 */
bool Database::storeDoc(QString key,QJsonDocument document) {
	//	qDebug() << __FILE__ << __LINE__  <<key << key.split("::").count() << key << document ;
	if(key.split("::").count() <  2){
		Database::IncrementKey(key);
		int keyID = Database::GetKey(key);
		if(keyID == -1){
			qDebug() << __FILE__ << __LINE__  << "Error Key Value is -1, Database StoreDoc Line:354 Key:" <<key;
			return false;
			}

		key = QString(key)+QString("::")+ QString::number(keyID);
		}
	//qDebug ()<<"key" << key;
	QJsonObject objWithKey = document.object();
	objWithKey.insert("document_id",key);
	objWithKey.insert("cr",QDateTime::currentDateTime().currentMSecsSinceEpoch());
	objWithKey.insert("created_at",QDateTime::currentDateTime().toString(Qt::ISODate));
	objWithKey.insert("created_byID",AccessController::Get()->getUserID());
	objWithKey.insert("created_byName",AccessController::Get()->getUserName());
	document = QJsonDocument(objWithKey);
	lcb_t instance = Database::InitDatabase();
	if(instance == NULL){
		qDebug() << __FILE__ << __LINE__<< "Failed to INIT Database @ Increment";
		return false;
		}
	//lcb_set_store_callback(instance, on_stored_status);
	struct lcb_store_cmd_st cmd;// = { 0 };
	lcb_store_cmd_t *cmdlist = &cmd;

	QByteArray ba =  document.toJson(QJsonDocument::Compact) ;
	const char *doc = ba.data();
	QByteArray bKey = key.toLatin1();
	const char *docbKey = bKey.data();
	cmd.v.v0.key = docbKey;
	cmd.v.v0.nkey = key.size();
	cmd.v.v0.bytes = doc;
	cmd.v.v0.nbytes = strlen(doc);
	cmd.v.v0.operation = LCB_ADD;
	//qDebug() << __FILE__ << __LINE__  <<document.object().value("cas_value").toString().toLongLong();
	cmd.v.v0.cas =  document.object().value("cas_value").toString().toLongLong();

	lcb_set_store_callback(instance, on_stored_status);
	lcb_set_get_callback(instance, get_callback);

	lcb_error_t err = lcb_store(instance, NULL, 1, &cmdlist);
	if (err == LCB_SUCCESS) {
		//lcb_wait(instance);
		return Database::KillDatabase(instance);
		}
	else {
		fprintf(stderr, "Couldn’t schedule operation: %s\n", lcb_strerror(instance, err));
		Database::KillDatabase(instance);
		return  false;
		}



}




Database::Database():
	QObject()
{
	//	this->document =  QJsonDocument();
	//	this->value = QString();
	this->array = QVector<QJsonDocument>();
	this->connIssue = false;
	cachedDocuments =  QMap<QString,QJsonDocument>();
	//cachedArrayDocuments =  QMap<QString,QVector<QJsonDocument> >();
	//IncrementKey("cont");
	/*
	// initializing

	struct lcb_create_st cropts;// = { 0 };
	cropts.version = 3;
	cropts.v.v3.connstr = "couchbase://localhost/default";
	lcb_error_t err;
	lcb_t instance;
	err = lcb_create(&instance, &cropts);
	if (err != LCB_SUCCESS) {
		qDebug("Couldn't create instance!\n");
		exit(1);
		}

	// connecting

	lcb_connect(instance);
	lcb_wait(instance);
	if ( (err = lcb_get_bootstrap_status(instance)) != LCB_SUCCESS ) {
		qDebug("Couldn't bootstrap!\n");
		exit(1);
		}

	// installing callbacks

	lcb_set_store_callback(instance, storage_callback);
	lcb_set_get_callback(instance, get_callback);


	// scheduling operations

	lcb_store_cmd_t scmd;// = { 0 };
	const lcb_store_cmd_t *scmdlist = &scmd;


	scmd.v.v0.key = key.toUtf8().constData();

	scmd.v.v0.nkey = key.size();
	scmd.v.v0.bytes = "Couchbase";
	scmd.v.v0.nbytes = 9;
	scmd.v.v0.operation = LCB_SET;
	err = lcb_store(instance, NULL, 1, &scmdlist);
	if (err != LCB_SUCCESS) {
		qDebug("Couldn't schedule storage operation!\n");
		exit(1);
		}
	lcb_wait(instance); //storage_callback is invoked here

	lcb_get_cmd_t gcmd;// = { 0 };
	const lcb_get_cmd_t *gcmdlist = &gcmd;
	gcmd.v.v0.key = "Hello";
	gcmd.v.v0.nkey = 5;
	err = lcb_get(instance, NULL, 1, &gcmdlist);
	if (err != LCB_SUCCESS) {
		qDebug("Couldn't schedule get operation!\n");
		exit(1);
		}

	lcb_wait(instance); // get_callback is invoked here
*/
}
lcb_t Database::instance = 0;
Database* Database::p_instance = 0;
/**
 * @brief Database::Get
 * Checks if the instance is zero "not inti" then
 * starts a new thread, moving the instace to the new thread
 * finally starting the tread
 * Else if the instance already init, it returns this instance
 * @return p_instance "the static database refrence"
 */
Database* Database::Gett()
{
	//if ( p_instance == 0){

	QThread* thread = new QThread;
	p_instance = new Database();
	p_instance->moveToThread(thread);
	thread->start();
	//	}
	return p_instance;
}
