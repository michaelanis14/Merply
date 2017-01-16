#ifndef ACCESSCONTROLLER_H
#define ACCESSCONTROLLER_H

#include "database.h"

#include <QObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

class AccessController :public QObject
{
	Q_OBJECT
public:
	static AccessController* Get();

	void login(QString username,QString password);
	bool hasRootGroupAccess();
	bool hasAdminGroupAccess();
	bool hasAccess(QString group);
	bool hasReadAccess(QJsonObject permissions);
	bool hasWriteAccess(QJsonObject permissions);
	QString getUserName();
	QString getUserID();
	void logout();

private:
	explicit AccessController(QObject * parent = 0);
	static AccessController* p_instance;


signals:
	void successLogin();
	void faildLogin();
public slots:
		void loginData(QVector<QJsonDocument> user);
};

#endif // ACCESSCONTROLLER_H
