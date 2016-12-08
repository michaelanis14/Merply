#include "user.h"

#include <QDebug>
User::User(QString id,QString username,QString name)
{
	this->id = id;
	this->username = username;
	this->name = name;
	//qDebug() << __FILE__ << __LINE__  << name << username;
}

QString User::getUsername() const
{
	return username;
}


QString User::getName() const
{
	return name;
}


QString User::getId() const
{
	return id;
}
