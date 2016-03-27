#include "database.h"

#include <cstdio>
#include <cstdlib>
#include <string.h>


#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>


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
		Database::Get()->setLastKeyID(QString(keyByte));
		qDebug("Stored Key:  %.*s\n",(int)resp->v.v0.nkey,resp->v.v0.key);
		}
}



bool Database::updateDoc(QJsonDocument document)
{
	//Database::IncrementKey(key);

	//	int keyID = Database::GetKey(key);
	//	if(keyID == -1)
	//	return false;

	//key = QString(key)+QString("::")+ QString::number(keyID);
	//qDebug () << key;

	lcb_t instance = Database::InitDatabase();

	//lcb_set_store_callback(instance, on_stored_status);
	struct lcb_store_cmd_st cmd;// = { 0 };
	lcb_store_cmd_t *cmdlist = &cmd;
	QByteArray bKey = document.object().value("document_id").toString().toLatin1();
	const char *docbKey = bKey.data();
	document.object().remove("document_id");
	QString strJson(document.toJson(QJsonDocument::Compact));;
	QByteArray ba = strJson.toLatin1();
	const char *doc = ba.data();
	//qDebug() <<"Prsistance UpdateDOC"<< document.object().value("document_id").toString() << strJson;
	cmd.v.v0.key = docbKey;
	cmd.v.v0.nkey = strlen(docbKey);
	cmd.v.v0.bytes = doc;
	cmd.v.v0.nbytes = strlen(doc);
	cmd.v.v0.operation = LCB_REPLACE;
	//qDebug() <<document.object().value("cas_value").toString().toLongLong();
	cmd.v.v0.cas =  document.object().value("cas_value").toString().toLongLong();

	lcb_error_t err = lcb_store(instance, NULL, 1, &cmdlist);
	if (err == LCB_SUCCESS) {
		lcb_wait(instance);
		} else {
		fprintf(stderr, "Couldn’t schedule operation: %s\n", lcb_strerror(instance, err));
		}
	lcb_set_store_callback(instance, on_stored_status);
	lcb_set_get_callback(instance, get_callback);

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
		lcb_wait(instance);
		Database::KillDatabase(instance);
		return true;
		}
	return true;
}

lcb_t Database::InitDatabase()
{
	// initializing
	Database::Get()->document = QJsonDocument();
	Database::Get()->array.clear();

	struct lcb_create_st cropts;// = { 0 };
	cropts.version = 3;
	cropts.v.v3.connstr = "couchbase://localhost/default";
	lcb_error_t err;
	lcb_t instance;
	err = lcb_create(&instance, &cropts);
	if (err != LCB_SUCCESS) {
		qDebug("Couldn't create instance!\n");
		return  NULL;
		}

	// connecting

	lcb_connect(instance);
	lcb_wait(instance);
	if ( (err = lcb_get_bootstrap_status(instance)) != LCB_SUCCESS ) {
		qDebug("Couldn't bootstrap!\n");
		return NULL;
		}
	return instance;
}

bool Database::KillDatabase(lcb_t instance)
{

	lcb_destroy(instance);
	return true;
}

bool Database::IncrementKey(QString key)
{
	Database::Get()->value = QString::number(-1);

	lcb_t instance = Database::InitDatabase();
	if(instance == NULL){
		qDebug() << "Failed to INIT Database @ Increment";
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
	cmdd.v.v0.initial = 1; // Set to 1 if it does not exist
	cmdd.v.v0.create = 1; // Create item if it does not exist
	lcb_error_t err = lcb_arithmetic(instance, NULL, 1, &cmdlistt);
	if (err == LCB_SUCCESS) {
		lcb_wait(instance);
		//qDebug() << "LCB_SUCCESS_Key";
		//qDebug("Key:  %.*s\n",(int)cmdd.v.v0.nkey,cmdd.v.v0.key);
		} else {
		fprintf(stderr, "Couldn’t schedule operation: %s\n", lcb_strerror(instance, err));
		}

	//lcb_wait(instance); // get_callback is invoked here
	return Database::KillDatabase(instance);

}

int Database::GetKey(QString key)
{
	if(getDoc(key))
		return Database::Get()->value.toInt();
	return -1;
}
void Database::got_document(lcb_t instance, const void *, lcb_error_t err,
							const lcb_get_resp_t *resp)
{
	if (err == LCB_SUCCESS) {
		QJsonParseError parserError;
		QByteArray byteArray((char*) resp->v.v0.bytes,(int)resp->v.v0.nbytes);
		Database::Get()->document = QJsonDocument::fromJson(byteArray , &parserError);
		//qDebug() << resp->v.v0.cas;
		QJsonObject objectwithCAS = Database::Get()->document.object();
		objectwithCAS.insert("cas_value",QString::number(resp->v.v0.cas));

		QByteArray keyByte((char*) resp->v.v0.key,(int)resp->v.v0.nkey);

		//qDebug() <<"Got Doc"<< resp->v.v0.key << keyByte << QString(keyByte);
		objectwithCAS.insert("document_id",QString(keyByte));
		//	qDebug() << objectwithCAS.value("document_id");


		Database::Get()->document = QJsonDocument(objectwithCAS);
		if(parserError.error == QJsonParseError::NoError){
			//QString strJson(Database::Get()->document.toJson(QJsonDocument::Compact));
			//qDebug()<<"NoError" << strJson;
			}
		else{
			//	qDebug() << parserError.errorString();
			Database::Get()->value = QString(byteArray);
			//	qDebug() << Database::Get()->value;
			}

		//	qDebug("Received document: %.*s\n", (int)resp->v.v0.nbytes, resp->v.v0.bytes);
		} else {
		fprintf(stderr, "Couldn’t retrieve item: %s\n", lcb_strerror(instance, err));
		}
}

bool Database::getDoc(QString key) {
	//Query("SELECT * from default WHERE  \"id = Contact::* \"");
	//qDebug() << "hello";
	//qDebug() <<"Key:"<< key;
	lcb_t instance = Database::InitDatabase();
	if(instance == NULL){
		qDebug() << "Failed to INIT Database @ Query";
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
		lcb_wait(instance);
		Database::KillDatabase(instance);
		return true;
		}
	else {
		fprintf(stderr, "Couldn’t schedule get operation: %s\n", lcb_strerror(instance, err));
		Database::KillDatabase(instance);
		return false;
		}


}


QJsonDocument Database::getDocument() const
{
	return document;
}

void Database::rowCallback(lcb_t , int , const lcb_RESPN1QL *resp) {

	if (! (resp->rflags & LCB_RESP_F_FINAL)) {
		QJsonParseError parserError;
		QByteArray byteArray(resp->row,resp->nrow);

		Database::Get()->document = QJsonDocument::fromJson(byteArray , &parserError);
		Database::Get()->document.toJson(QJsonDocument::Compact);
		//qDebug() <<Database::Get()->document.object();
		Database::Get()->array << Database::Get()->document;
		//	QString strJson(Database::Get()->document.toJson(QJsonDocument::Compact));
		//	QJsonValue v(strJson);
		//	Database::Get()->array << v;
		//qDebug() << array;
		if(parserError.error == QJsonParseError::NoError){
			//QString strJson(Database::Get()->document.toJson(QJsonDocument::Compact));
			//qDebug() <<"No Errors"<< strJson;

			}
		else{
			qDebug() << parserError.errorString();
			Database::Get()->value = QString(byteArray);
			//	qDebug() << Database::Get()->value;
			}

		} else {
		//qDebug() << Database::Get()->array;

		//Database::Get()->document = QJsonDocument(Database::Get()->array);
		Database::Get()->document.toJson(QJsonDocument::Compact);
		//qDebug() << Database::Get()->document.array();
		//.toJson(QJsonDocument::Compact);
		//	qDebug("Got metadata: %.*s\n", (int)resp->nrow, resp->row);
		}

}
bool Database::query(QString query)
{
	//qDebug() << query;
	lcb_t instance = Database::InitDatabase();
	Database::Get()->array = QList<QJsonDocument>();
	if(instance == NULL){
		qDebug() << "Failed to INIT Database @ Query";
		return false;
		}

	// Error checking omitted for brevity

	// The command structure
	lcb_CMDN1QL cmd = { 0 };
	// Allocate the parameter object
	lcb_N1QLPARAMS *nparams = lcb_n1p_new();

	lcb_n1p_setstmtz(nparams,query.toUtf8().constData());
	// "SELECT * from default WHERE  \"id = Contact::* \"");

	lcb_n1p_mkcmd(nparams, &cmd);

	cmd.callback = rowCallback;

	lcb_error_t rc = lcb_n1ql_query(instance, NULL, &cmd);
	if(rc == LCB_SUCCESS){
		lcb_n1p_free(nparams);
		lcb_wait(instance);

		//qDebug() << "sucess q" << query;
		Database::KillDatabase(instance);
		return true;

		}
	else{
		lcb_n1p_free(nparams);
		lcb_wait(instance);
		qDebug() << "FAIL query" << query;
		Database::KillDatabase(instance);
		return false;
		}
	// We can release the params object now..

}

QList<QJsonDocument> Database::getArray() const
{
	//qDebug() << array <<"--------";
	return array;
}

QString Database::getValue() const
{
	return value;
}

QString Database::getLastKeyID() const
{
	return LastKeyID;
}

void Database::setLastKeyID(const QString& value)
{
	LastKeyID = value;
}


bool Database::storeDoc(QString key,QJsonDocument document) {
	Database::IncrementKey(key);

	int keyID = Database::GetKey(key);
	if(keyID == -1){
		qDebug() << "Error Key Value is -1, Database StoreDoc Line:373";
		return false;
		}

	key = QString(key)+QString("::")+ QString::number(keyID);
	//	qDebug ()<<"key" << key;
	QJsonObject objWithKey = document.object();
	objWithKey.insert("document_id",key);
	document = QJsonDocument(objWithKey);
	lcb_t instance = Database::InitDatabase();

	//lcb_set_store_callback(instance, on_stored_status);
	struct lcb_store_cmd_st cmd;// = { 0 };
	lcb_store_cmd_t *cmdlist = &cmd;

	QString strJson(document.toJson(QJsonDocument::Compact));;
	QByteArray ba = strJson.toLatin1();
	const char *doc = ba.data();

	QByteArray bKey = key.toLatin1();
	const char *docbKey = bKey.data();
	cmd.v.v0.key = docbKey;
	cmd.v.v0.nkey = key.size();
	cmd.v.v0.bytes = doc;
	cmd.v.v0.nbytes = strlen(doc);
	cmd.v.v0.operation = LCB_ADD;
	//qDebug() <<document.object().value("cas_value").toString().toLongLong();
	cmd.v.v0.cas =  document.object().value("cas_value").toString().toLongLong();

	lcb_set_store_callback(instance, on_stored_status);
	lcb_set_get_callback(instance, get_callback);

	lcb_error_t err = lcb_store(instance, NULL, 1, &cmdlist);
	if (err == LCB_SUCCESS) {
		lcb_wait(instance);
		return Database::KillDatabase(instance);
		}
	else {
		fprintf(stderr, "Couldn’t schedule operation: %s\n", lcb_strerror(instance, err));
		Database::KillDatabase(instance);
		return  false;
		}



}




Database::Database()
{
	this->document =  QJsonDocument();
	this->value = QString();
	this->array = QList<QJsonDocument>();
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
Database* Database::p_instance = 0;
Database* Database::Get()
{
	if (p_instance == 0)
		p_instance = new Database();

	return p_instance;
}
