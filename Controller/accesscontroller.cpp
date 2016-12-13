#include "accesscontroller.h"
#include "model.h"
#include "prsistance.h"
#include "loginui.h"\


AccessController::AccessController(QObject* parent):
	QObject(parent)
{

}



AccessController* AccessController::p_instance = 0;
AccessController*AccessController::Get()
{
	if (p_instance == 0)
		p_instance = new AccessController();

	return p_instance;
}

void AccessController::login(QString username, QString password)
{
	if(username.compare("merplyroot") == 0 && password.compare("LilyMichael") == 0){
		Model::Get()->login("merplyroot","root","Merply");
		emit successLogin();
		}
	else{
		QObject::connect(Database::Get(),SIGNAL(gotDocuments(QList<QJsonDocument>)),this,SLOT(loginData(QList<QJsonDocument>)));
		QString query = QString("SELECT (`"+QString(DATABASE)+"`).*  ,META( `"+QString(DATABASE)+"`).id AS `Key`  FROM  `"+QString(DATABASE)+"` WHERE META( `"+QString(DATABASE)+"`).id LIKE \"Users::%\"  AND Fields[0][0].`Username`[0] = '"+username+"' AND Fields[0][1].`UserPassword`[0] = '"+password+"'");
		//qDebug() << __FILE__ << __LINE__ <<"Q : " << query;
		Database::Get()->query(query);
		}
}

bool AccessController::hasRootGroupAccess()
{
	if(Model::Get()->getUserID().compare("merplyroot") == 0 )
		return true;
	return false;
}

bool AccessController::hasAdminGroupAccess()
{
	if(hasRootGroupAccess())
		return true;
	return false;
}

bool AccessController::hasAccess(QString group)
{
	if(Model::Get()->getUserID().isEmpty()){
		LoginUI::ShowUI();
		return false;
		}
	else if(Model::Get()->getUserID().compare("merplyroot") == 0 )
		return true;
	else if(group.compare("3") == 0)
		return false;

	return false;
}

void AccessController::loginData(QList<QJsonDocument> user)
{
	QObject::disconnect(Database::Get(),SIGNAL(gotDocuments(QList<QJsonDocument>)),this,SLOT(loginData(QList<QJsonDocument>)));
	if(user.isEmpty()){
		qDebug() << __FILE__ << __LINE__  << "user login faild : Wrong Password or UserName";
			emit faildLogin();
		}
	else{
		QJsonObject userObject = user.first().object();
		if(!userObject.value("document_id").toString().isEmpty()){
			QString username;
			QString name;
			QJsonArray userFields = userObject.value("Fields").toArray();
			foreach(QJsonValue field,userFields){
				foreach(QJsonValue subfield,field.toArray()){
					if(subfield.toObject().value("Name") != QJsonValue::Undefined){
						name = subfield.toObject().value("Name").toArray().at(0).toString();
						}
					else if(subfield.toObject().value("Username") != QJsonValue::Undefined){
						username = subfield.toObject().value("Username").toArray().at(0).toString();
						}

					}
				}
			Model::Get()->login(userObject.value("document_id").toString(),username,name);
			emit successLogin();
			}
		else emit faildLogin();
		//qDebug() << __FILE__ << __LINE__  << userFields  << userFields.at(0).toArray().at(0).toObject().value("Name").toString();
		}
}

bool AccessController::hasReadAccess(QJsonObject permissions)
{
	if(Model::Get()->getUserID().isEmpty()){
		LoginUI::ShowUI();
		return false;
		}
	else if(Model::Get()->getUserID().compare("merplyroot") == 0 )
		return true;


	permissions = permissions.value("Permissions").toObject().value("Read").toObject();
	if(permissions.value("Permissions").toString().toInt() == 111){
		foreach(QJsonValue deny,permissions.value("Denied").toArray()){
			if(deny.toObject().value("Key").toString().compare(Model::Get()->getUserID()) == 0){
				//	qDebug() << __FILE__ << __LINE__  << "At Deny: "<<permissions << Model::Get()->getUserID();
				return false;
				}
			}
		foreach(QJsonValue allow,permissions.value("Allowed").toArray()){
			if(allow.toObject().value("Key").toString().compare(Model::Get()->getUserID()) == 0 || allow.toObject().value("Key").toString().toInt() == 100)
				//qDebug() << __FILE__ << __LINE__  << "At Allow: "<<permissions << Model::Get()->getUserID() << allow.toObject().value("Key").toString().toInt();
				return true;
			}
		}
	else if(permissions.value("Permissions").toString().toInt() == 100)
		return true;
	else if(permissions.value("Permissions").toString().toInt() == 101){
		//qDebug() << __FILE__ << __LINE__  << "Denied all: "<<permissions << Model::Get()->getUserID();
		return false;
		}
	//	qDebug() << __FILE__ << __LINE__  << "Permission all fail: "<<permissions << Model::Get()->getUserID();
	return false;
}
bool AccessController::hasWriteAccess(QJsonObject permissions)
{
	if(Model::Get()->getUserID().isEmpty()){
		LoginUI::ShowUI();
		return false;
		}
	else if(Model::Get()->getUserID().compare("merplyroot") == 0 )
		return true;

	permissions = permissions.value("Permissions").toObject().value("Write").toObject();
	if(permissions.value("Permissions").toString().toInt() == 111){
		foreach(QJsonValue deny,permissions.value("Denied").toArray()){
			if(deny.toObject().value("Key").toString().compare(Model::Get()->getUserID()) == 0){
				//	qDebug() << __FILE__ << __LINE__  << "At Deny: "<<permissions << Model::Get()->getUserID();
				return false;
				}
			}
		foreach(QJsonValue allow,permissions.value("Allowed").toArray()){
			if(allow.toObject().value("Key").toString().compare(Model::Get()->getUserID()) == 0 || allow.toObject().value("Key").toString().toInt() == 100)
				//qDebug() << __FILE__ << __LINE__  << "At Allow: "<<permissions << Model::Get()->getUserID() << allow.toObject().value("Key").toString().toInt();
				return true;
			}
		}
	else if(permissions.value("Permissions").toString().toInt() == 100)
		return true;
	else if(permissions.value("Permissions").toString().toInt() == 101){
		//qDebug() << __FILE__ << __LINE__  << "Denied all: "<<permissions << Model::Get()->getUserID();
		return false;
		}
	//	qDebug() << __FILE__ << __LINE__  << "Permission all fail: "<<permissions << Model::Get()->getUserID();
	return false;
}

QString AccessController::getUserName()
{
	return Model::Get()->getUserName();
}

void AccessController::logout()
{
	Model::Get()->logout();
	LoginUI::ShowUI();
}

