#include "database.h"
#include "model.h"

#include <QDebug>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

Database::Database(QObject *parent) : QThread(parent)
{
	m_worker = new DatabaseWorker();
}

bool Database::treadedInsert(const QSqlDatabase &db,const QString& query)
{
	QString connectionName = QString("connection").append(QString::number(rand()));

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
	qDebug() << __FILE__ << __LINE__ << "Query:" << query;
	emit executefwd( query );
}

void Database::gotQueryResutls(const QVector<QSqlRecord> results)
{
	if(results.count() == 1
			&&(results.first().count() == 1)
			&&(results.first().value("Value") != QVariant::Invalid)){
		emit gotValue(QString(results.first().value("Value").toString()));

		}
	emit queryResults(results);
}

void Database::getJson(const QString& select,const QString& tabel, const QString& key,const QString& id)
{
	QString query  = "SELECT `id` AS 'id', `"+select+"` FROM `"+tabel;
	if(!key.isEmpty())
		query +=	"` WHERE `key` = '"+key+"'";
	else if(!id.isEmpty())
		query +="` WHERE `id` = '"+id+"'";

	qDebug() << __FILE__ << __LINE__ << "Query:" << query;

	connect( m_worker, SIGNAL( results( const QVector<QSqlRecord>& ) ),
			 this, SLOT( gotJson( const QVector<QSqlRecord>& ) ) );
	emit executefwd( query );
}

void Database::gotJson(const QVector<QSqlRecord> results)
{
	disconnect( m_worker, SIGNAL( results( const QVector<QSqlRecord>& ) ),
				this, SLOT( gotJson( const QVector<QSqlRecord>& ) ) );

	if(results.count() > 0){
		if(results.count() == 1){
			QJsonObject documentObj = QJsonDocument::fromJson(results.first().value(1).toString().toUtf8()).object();
			documentObj.insert("document_id",results.first().value("id").toString());
			emit gotDocument(QJsonDocument(documentObj));
			}
		else {
			QVector<QJsonDocument> documents;
			foreach(QSqlRecord row,results){
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
	//	future = QtConcurrent::run(this,&Database::threadedSql,  Model::Get()->getDb(), query);
	//	watcher->setFuture(future);
}

void Database::insert(QString query)
{
	//watcher  = new QFutureWatcher<QVector<QSqlRecord> >(this);
	//connect(watcher, SIGNAL(finished()),this, SLOT(gotQueryResutls()));
	qDebug() << __FILE__ << __LINE__ << "INSERT:" << query;
	//	QtConcurrent::run(this,&Database::treadedInsert, Model::Get()->getDb(), query);
	//watcher->setFuture(future);
}


void Database::execute( const QString& query )
{
	emit executefwd( query ); // forwards to the worker
}

QSqlDatabase Database::getDatabase() const
{
	return this->m_worker->database();
}

void Database::run()
{
	emit ready(false);
	emit progress( "DataBaseThread starting, one moment please..." );

	// Create worker object within the context of the new thread
	//	m_worker = new DatabaseWorker();

	connect( this, SIGNAL( executefwd( const QString& ) ),
			 m_worker, SLOT( slotExecute( const QString& ) ) );

	// Critical: register new type so that this signal can be
	// dispatched across thread boundaries by Qt using the event
	// system
	qRegisterMetaType< QList<QSqlRecord> >( "QList<QSqlRecord>" );

	// forward final signal
	connect( m_worker, SIGNAL( results( const QVector<QSqlRecord>& ) ),
			 this, SLOT( gotQueryResutls( const QVector<QSqlRecord>& ) ) );


	emit progress( "DatabaseThread is Ready" );
	emit ready(true);
	emit readyToQuery();

	qDebug() << "Ready";

	exec();  // our event loop
}


Database::~Database()
{
	qDebug() << "DELETE ~Database " ;
	delete m_worker;
}

//#include "database.moc"

