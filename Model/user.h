#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
	User(QString id,QString username,QString name);
	QString getUsername() const;
	QString getName() const;
	QString getId() const;
private:
	QString username;
	QString name;
	QString id;

};

#endif // USER_H
