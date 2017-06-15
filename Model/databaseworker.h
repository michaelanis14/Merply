#ifndef DATABASEWORKER_H
#define DATABASEWORKER_H

#include <QObject>
#include <QDebug>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>

class DatabaseWorker : public QObject
{
	Q_OBJECT
public:
	explicit DatabaseWorker(QObject *parent = 0);
	~DatabaseWorker();

public slots:
	void slotExecute( const QString& query );

signals:
	void results( const QVector<QSqlRecord>& records );

private:
	QSqlDatabase m_database;
};

#endif // DATABASEWORKER_H
