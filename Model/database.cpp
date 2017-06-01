#include "database.h"
#include "model.h"
#include <QSqlDriver>

Database::Database(QObject *parent) : QObject(parent)
{
	watcher  = new QFutureWatcher<QVector<QSqlRecord> >(this);

}

Database* Database::p_instance = 0;
/**
 * @brief Database::Get
 * Checks if the instance is zero "not inti" then
 * starts a new thread, moving the instace to the new thread
 * finally starting the tread
 * Else if the instance already init, it returns this instance
 * @return p_instance "the static database refrence"

Database* Database::Get()
{
	if ( p_instance == 0){

	//	QThread* thread = new QThread;
		p_instance = new Database();
	//	p_instance->moveToThread(thread);
	//	thread->start();
		}
	return p_instance;
}
 */
QVector<QSqlRecord> Database::threadedSql(const QSqlDatabase &db, const QString &query) {

	connectionName = QString("connection").append(QString::number(rand()));
	QVector<QSqlRecord> results;
	QSqlDatabase localDb = QSqlDatabase::cloneDatabase(db, connectionName);
	if( !localDb.open() )
		{
		qDebug() << __FILE__ << __LINE__ << db.lastError();
		qFatal( "Failed to connect." );
		return results;
		}
	if(localDb.isValid() && localDb.isOpen()) {
		QSqlQuery q(localDb);
		q.prepare(query);
		if(!q.exec()) {
			qDebug() << __FILE__ << __LINE__ <<q.lastError()<<" ERROR IN EXCUTION!";
			}
		else
			while(q.next()) {
			//	qDebug()<< __FILE__ << __LINE__ << "QueryResultss" << q.record();
				results << q.record();
				} //BETTER PERFORMANCE >?
		}
	//qDebug() << "threadedSql Finished";
	localDb.close();




	if(results.count() == 1
			&&(results.first().count() == 1)
			&&(results.first().value("Value") != QVariant::Invalid)){
		emit gotValue(QString(results.first().value("Value").toString()));

		}
	emit queryResults(results);


	return results;
}

bool Database::treadedInsert(const QSqlDatabase &db,const QString& query)
{
	connectionName = QString("connection").append(QString::number(rand()));

	QSqlDatabase localDb = QSqlDatabase::cloneDatabase(db, connectionName);
	if( !localDb.open() )
		{
		qDebug() << __FILE__ << __LINE__ << db.lastError();
		qFatal( "Failed to connect." );
		return false;
		}
	if(localDb.isValid() && localDb.isOpen()) {
		QSqlQuery q(localDb);
		q.prepare(query);
		if(!q.exec()) {
			qDebug() << __FILE__ << __LINE__ <<q.lastError()<<" ERROR IN EXCUTION!";
			}
		else{
			if(q.numRowsAffected() < 1 )
				{
				qDebug() << __FILE__ << __LINE__ << QString("Database::insertNewRecord: could not insert a record into  : %1.").arg(q.lastQuery());
				return false;
				}
			else{
				qDebug()  << __FILE__ << __LINE__<<"LAST INSET/UPDATE ID"<< QString(q.lastInsertId().toString());
				//				qDebug()  << __FILE__ << __LINE__<<"LAST INSET/UPDATE ID"<< QString(q.lastQuery().split(""));
				emit saved(QString(q.lastInsertId().toString()));
				}
			}

		}
	//qDebug() << "threadedSql Finished";
	localDb.close();
	return true;
}



void Database::query( const QString &query) {

//	connect(watcher, SIGNAL(finished()),this, SLOT(gotQueryResutls()));
	qDebug() << __FILE__ << __LINE__ << "Query:" << query;
//	future = QtConcurrent::run(this,&Database::threadedSql, Model::Get()->getDb(), query);
//	watcher->setFuture(future);


	threadedSql(Model::Get()->getDb(),query);
}

void Database::gotQueryResutls()
{
	disconnect(watcher, SIGNAL(finished()),this, SLOT(gotQueryResutls()));
	qDebug() << "gotQueryResutls"<< future.result()  << QString(future.result().first().value("Value").toString());
	if(this->future.result().count() == 1
			&&(future.result().first().count() == 1)
			&&(future.result().first().value("Value") != QVariant::Invalid)){
		emit gotValue(QString(future.result().first().value("Value").toString()));

		}
	emit queryResults(future.result());
}

void Database::getJson(const QString& select,const QString& tabel, const QString& key,const QString& id)
{
	QString query  = "SELECT `id` AS 'id', `"+select+"` FROM `"+tabel;
	if(!key.isEmpty())
		query +=	"` WHERE `key` = '"+key+"'";
	else if(!id.isEmpty())
		query +="` WHERE `id` = '"+id+"'";
	//watcher   = new QFutureWatcher<QVector<QSqlRecord> >(this);
	connect(watcher, SIGNAL(finished()),this, SLOT(gotJson()));
	qDebug() << __FILE__ << __LINE__ << "Query:" << query;
	future = QtConcurrent::run(this,&Database::threadedSql,  Model::Get()->getDb(), query);
	watcher->setFuture(future);
}

void Database::gotJson()
{
	disconnect(watcher, SIGNAL(finished()),this, SLOT(gotJson()));
	if(future.result().count() > 0){
		if(future.result().count() == 1){
			QJsonObject documentObj = QJsonDocument::fromJson(future.result().first().value(1).toString().toUtf8()).object();
			documentObj.insert("document_id",future.result().first().value("id").toString());
			emit gotDocument(QJsonDocument(documentObj));
			}
		else {
			QVector<QJsonDocument> documents;
			foreach(QSqlRecord row,future.result()){
				QJsonObject recordObject;
				recordObject.insert("document_id",row.value("id").toString());
				for(int x=0; x < row.count(); x++) {
					recordObject.insert( row.fieldName(x),
										 QJsonDocument::fromJson(row.value(x).toString().toUtf8()).object());
					}
				documents.append(QJsonDocument(recordObject));
				}
			emit gotDocuments(documents);
			}
		}
}

void Database::deletRow(const QString& tabel, const QString& id)
{
	QString query  = "DELETE FROM FROM "+tabel+
			" WHERE id = "+id;
	//watcher   = new QFutureWatcher<QVector<QSqlRecord> >(this);
	//connect(watcher, SIGNAL(finished()),this, SLOT(gotJson()));
	qDebug() << __FILE__ << __LINE__ << "Query:" << query;
	future = QtConcurrent::run(this,&Database::threadedSql,  Model::Get()->getDb(), query);
	watcher->setFuture(future);
}

void Database::insert(QString query)
{
	//watcher  = new QFutureWatcher<QVector<QSqlRecord> >(this);
	//connect(watcher, SIGNAL(finished()),this, SLOT(gotQueryResutls()));
	qDebug() << __FILE__ << __LINE__ << "INSERT:" << query;
	QtConcurrent::run(this,&Database::treadedInsert, Model::Get()->getDb(), query);
	//watcher->setFuture(future);
}



Database::~Database()
{
	qDebug() << "DELETE ~Database " ;
	//	QSqlDatabase::removeDatabase("QMYSQL");
	QSqlDatabase::removeDatabase(this->connectionName);
}


