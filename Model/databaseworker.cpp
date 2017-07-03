#include "databaseworker.h"
#include "db.h"

DatabaseWorker::DatabaseWorker(QObject *parent) : QObject(parent)
{
	QString connectionName = QString("connection").append(QString::number(rand()));

	m_database = QSqlDatabase::addDatabase( DATABASE_DRIVER,
											connectionName ); // named connection
	m_database.setDatabaseName( DATABASE_NAME );
	m_database.setHostName( DATABASE_HOST );
	m_database.setUserName( DATABASE_USER );
	m_database.setPassword( DATABASE_PASS );
	if ( !m_database.open() )
		{
		qWarning() << "Unable to connect to database, giving up:" << m_database.lastError().text();
		qFatal( "Failed to connect." );
		return;
		}


	/*
	if ( !m_database.tables().contains( "item" ) )
	{
		// some data
		m_database.exec( "create table item(id int, name varchar);" );
		m_database.transaction();
		QSqlQuery query(m_database);
		query.prepare("INSERT INTO item (id, name) "
					  "VALUES (?,?)");
		for ( int i = 0; i < SAMPLE_RECORDS; ++i )
		{
			query.addBindValue(i);
			query.addBindValue(QString::number(i));
			query.exec();
		}
		m_database.commit();
	}
	*/
}
void DatabaseWorker::slotExecute( const QString& query )
{
	QVector<QSqlRecord> recs;
	QSqlQuery sql( query, m_database );
	while ( sql.next() )
		{
		recs.push_back( sql.record() );
		}
	emit results( recs );
}

QSqlDatabase DatabaseWorker::database() const
{
	return m_database;
}
DatabaseWorker::~DatabaseWorker()
{
	m_database.close();
}
