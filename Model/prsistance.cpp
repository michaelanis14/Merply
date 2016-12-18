#include "prsistance.h"

#include <QFile>
#include <QMessageBox>
#include <model.h>

Prsistance::Prsistance(QObject *parent) : QObject(parent)
{
	Database::Get();
}
Prsistance* Prsistance::p_instance = 0;
Prsistance*Prsistance::Get()
{
	if (p_instance == 0)
		p_instance = new Prsistance();

	return p_instance;
}




bool Prsistance::init()
{
	qDebug() << __FILE__ << __LINE__  <<"Init" ;//<< Count("City::%\"");//<< Count("ViewStructure::Contact\"");
	/*
	if(Count("ContactType") == -1){
		write("ContactType",QString("Name->Customer"));
		write("ContactType",QString("Name->Supplier"));
		write("ContactType",QString("Name->Customer and Supplier"));
		write("ContactType",QString("Name->Employee"));
		write("ContactType",QString("Name->Other"));
		}
*/
	if(Count("ViewStructure::Users\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/Users.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		Database::Get()->storeDoc("ViewStructure::Users",doc);
		}
	if(Count("NavigationUI::1\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/NavigationUI.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		Database::Get()->storeDoc("NavigationUI::1",doc);
		}
	if(Count("ViewStructure::Groups\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/Groups.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		Database::Get()->storeDoc("ViewStructure::Groups",doc);
		}
	if(Count("ViewStructure::Contact\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/contact.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		Database::Get()->storeDoc("ViewStructure::Contact",doc);
		}
	if(Count("ViewStructure::Country\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/ViewStructureCountry.Json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		Database::Get()->storeDoc("ViewStructure::Country",doc);
		}
	if(Count("ViewStructure::City\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/City.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		Database::Get()->storeDoc("ViewStructure::City",doc);
		}
	if(Count("ViewStructure::AirlinesCode\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/AirlinesCode.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		Database::Get()->storeDoc("ViewStructure::AirlinesCode",doc);
		}
	if(Count("ViewStructure::AirportsCode\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/AirportsCode.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		Database::Get()->storeDoc("ViewStructure::AirportsCode",doc);
		}
	if(Count("AirlinesCode::%\"") ==  0){
		QStringList fileData = readCSVFile(":/initData/initData/AirlinesCodeData.csv");
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		for(int i = 0; i < fileData.count();i++){
			QStringList data = fileData.at(i).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("Prefix",  data.at(0));
				}
			if(1 < data.count() && !data.at(1).isEmpty()){
				c.insert("ICAO",  data.at(1));

				}
			if(2 <= data.count() && !data.at(2).isEmpty()){
				c.insert("IATA",  data.at(2));

				}
			if(3 < data.count() && !data.at(3).isEmpty()){
				c.insert("Name",  data.at(3));

				}
			if(4 < data.count() && !data.at(4).isEmpty()){
				QJsonObject country;
				country.insert("Value",data.at(4));
				c.insert("Country",country);
				}
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << fieldsArry;
				Database::Get()->storeDoc("AirlinesCode",QJsonDocument(c));
				}
			}

		}
	if(Count("AirportsCode::%\"") ==  0){
		QStringList fileData = readCSVFile(":/initData/initData/AirportsCodeData.csv");
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		for(int i = 0; i < fileData.count();i++){
			QStringList data = fileData.at(i).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("Airport",  data.at(0));
				}
			if(1 < data.count() && !data.at(1).isEmpty()){
				QJsonObject city;
				city.insert("Value",data.at(1));
				c.insert("City",   city);

				}
			if(2 < data.count() && !data.at(2).isEmpty()){
				QJsonObject country;
				country.insert("Value",data.at(2));
				c.insert("Country",  country);
				}
			if(3 <= data.count() && !data.at(3).isEmpty()){
				c.insert("IATA",  data.at(3));
				}
			if(4 < data.count() && !data.at(4).isEmpty()){
				c.insert("ICAO",  data.at(4));
				}
			if(5 < data.count() && !data.at(5).isEmpty()){
				c.insert("FAA",  data.at(5));
				}
			if(!c.isEmpty()){
					//qDebug() << __FILE__ << __LINE__ << fieldsArry;
				Database::Get()->storeDoc("AirportsCode",QJsonDocument(c));
				}
			}

		}
	if(Count("Country::%\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/Countries.Json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		foreach(QJsonValue country,doc.object().value("countries").toObject().value("country").toArray()){
			//QJsonObject c;
			QJsonObject c;
			if(country.toObject().value("countryCode") != QJsonValue::Undefined){

				c.insert("Code",  country.toObject().value("countryCode").toString());

				}
			if(country.toObject().value("countryName") != QJsonValue::Undefined){

				c.insert("Name",  country.toObject().value("countryName").toString());

				}
			if(country.toObject().value("currencyCode") != QJsonValue::Undefined){

				c.insert("Currency",  country.toObject().value("currencyCode").toString());

				}
			if(country.toObject().value("capital") != QJsonValue::Undefined){

				c.insert("Capital",  country.toObject().value("capital").toString());

				}
			if(country.toObject().value("continentName") != QJsonValue::Undefined){

				c.insert("Continent",  country.toObject().value("continentName").toString());

				}
			if(country.toObject().value("continent") != QJsonValue::Undefined){

				c.insert("ContinentCode",  country.toObject().value("continent").toString());

				}
			if(country.toObject().value("languages") != QJsonValue::Undefined){

				c.insert("Languages",  country.toObject().value("languages").toString());

				}
			if(!c.isEmpty()){
				Database::Get()->storeDoc("Country",QJsonDocument(c));
				}
			}
		}

	if(Count("City::%\"") == 0){
		QString jsonFile = readFile(":/initData/initData/countriesToCities.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//qDebug() << __FILE__ << __LINE__ << jsonFile << doc;
		QString jsonFileC = readFile(":/initData/initData/Countries.Json");
		QJsonDocument docC = QJsonDocument::fromJson(jsonFileC.toUtf8());
		//	qDebug() << __FILE__ << __LINE__  << docC;
		foreach(QJsonValue country,docC.object().value("countries").toObject().value("country").toArray()){

	QJsonObject c;
			if(doc.object().value(country.toObject().value("countryName").toString()) != QJsonValue::Undefined){
				//qDebug() << __FILE__ << __LINE__ << c;

				c.insert("Country",country.toObject().value("countryName").toString());


				QJsonArray cities;
				foreach(QJsonValue city,doc.object().value(country.toObject().value("countryName").toString()).toArray()){
					cities << QString(QString(city.toString()).toUtf8());
					}

				c.insert("Cities", cities);
				//qDebug() << __FILE__ << __LINE__ <<doc.object().value(country.toObject().value("countryName").toString()).toArray();
				}
			if(!c.isEmpty()){

				Database::Get()->storeDoc("City",QJsonDocument(c));
				}
			}


		}
	if(Count("ContactType::%\"") == 100){



		QJsonArray arryObj;


		QJsonArray typesall;
		QStringList types;
		types << "Customer" << "Supplier";

		foreach(QString typ,types){
			QJsonArray typarr;
			typarr << typ;
			typesall << typarr;
			}

		QJsonObject ci;
		ci.insert("Type", typesall);
		arryObj << ci;
		//qDebug() << __FILE__ << __LINE__ <<doc.object().value(country.toObject().value("countryName").toString()).toArray();

		if(!arryObj.isEmpty()){
			QJsonObject fieldsArry;
			fieldsArry.insert("Fields",QJsonArray() << arryObj);
			Database::Get()->storeDoc("ContactType",QJsonDocument(fieldsArry));
			}

		}

	//if()
	return true;
}


QString Prsistance::readFile(QString path)
{
	qDebug() << __FILE__ << __LINE__ << path;
	QString jsonFile;
	QFile file(path);
	if(!file.open(QIODevice::ReadOnly)) {
		qDebug() << __FILE__ << __LINE__   << file.errorString();
		}

	QTextStream in(&file);

	while(!in.atEnd()) {
		QString line = in.readLine();
		jsonFile.append(line);
		}

	file.close();

	return jsonFile.toUtf8();
}

QStringList Prsistance::readCSVFile(QString path)
{
	qDebug() << __FILE__ << __LINE__  << path;
	QStringList lines;

	QFile file(path);
	if(!file.open(QIODevice::ReadOnly)) {
		qDebug() << __FILE__ << __LINE__   << file.errorString();
		}

	QTextStream in(&file);

	while(!in.atEnd()) {
		QString line = in.readLine();
		lines.append(line.toUtf8());
		}

	file.close();

	return lines;
}

void Prsistance::GetJsonList(QString table, QString select,QString condition)
{
	QString where;
	if(!condition.isEmpty())
		where = QString("AND "+condition);
	QString query = "SELECT ARRAY_REPEAT(TOARRAY("+select.trimmed()+"),1) AS `Value`,META( `"+QString(DATABASE)+"`).id AS `Key`  FROM  `"+QString(DATABASE)+"` WHERE META( `"+QString(DATABASE)+"`).id LIKE \""+table+"::%\" "+where;
	//qDebug() << __FILE__ << __LINE__ << query;

	QObject::connect(Database::Get(),SIGNAL(gotDocuments(QList<QJsonDocument>)),Prsistance::Get(),SLOT(GetJsonListData(QList<QJsonDocument>)));
	Database::Get()->query(query);
}

void Prsistance::GetJsonEntityFields(QString table, QString select, QString condition)
{
	//qDebug() << __FILE__ << __LINE__ << table << select << condition;

	QString where;
	if(!condition.isEmpty()){
		if(condition.split("=").count() > 1){
			where = QString("AND d.`"+condition.split("=")[0]+"` = \""+condition.split("=")[1]+"\" ") ;

			//where = QString("AND ANY item in f SATISFIES item.[0] =  END ");
			}
		else{
			where = QString("AND "+condition);
			}
		}
	QString entities = table.split("::").count() > 1 ?table.split("::")[1]:table;

	//QString query = "SELECT fin."+select.trimmed()+"[0] AS `Value`,META(d).id AS `Key`  FROM "+QString(DATABASE)+" d UNNEST d.Fields f UNNEST f fin WHERE fin."+select+" AND META(d).id LIKE \""+table+"::%\" "+where;
	//QString query = "SELECT fin."+select.trimmed()+"[0] AS `Value`,META(d).id AS `Key`  FROM "+QString(DATABASE)+" d UNNEST d.Fields f UNNEST f fin WHERE fin."+select+" AND META(d).id LIKE \""+table+"::%\" "+where;
	//QString query ="SELECT Array item.`"+select.trimmed()+"` FOR item IN f END As `Value`,META(d).id AS `Key`  FROM "+QString(DATABASE)+" d UNNEST d.Fields f WHERE  META(d).id LIKE '"+entities+"::%' "+where;


	QString query = "SELECT  d.`"+select.trimmed()+"` AS `Value`,META(d).id AS `Key` FROM `"+QString(DATABASE)+"` d WHERE META(d).id LIKE '"+entities+"::%' "+where;
	//qDebug() << __FILE__ << __LINE__ << query;
	QObject::connect(Database::Get(),SIGNAL(gotDocuments(QList<QJsonDocument>)),Prsistance::Get(),SLOT(GetJsonListData(QList<QJsonDocument>)));
	Database::Get()->query(query);

}
void Prsistance::GetJsonListData(QList<QJsonDocument> items)
{
	QObject::disconnect(Database::Get(),SIGNAL(gotDocuments(QList<QJsonDocument>)),Prsistance::Get(),SLOT(GetJsonListData(QList<QJsonDocument>)));
	//	foreach(QJsonDocument doc,items){
	//qDebug() << __FILE__ << __LINE__ << items;
	//	}

	emit GotJsonSelectList(items);
}
int Prsistance::Count(const QString table)
{

	Database::Get()->query("SELECT COUNT(*) AS count  FROM  "+QString(DATABASE)+" WHERE META( "+QString(DATABASE)+").id LIKE \""+table);

	if(!Database::Get()->getArray().isEmpty() && Database::Get()->getArray().count() > 0){
		return Database::Get()->getArray().first().object().value("count").toInt();
		}
	else{
		//	qDebug() << __FILE__ << __LINE__ <<"-1";
		return 0;
		}

	return -1;
}

int Prsistance::CountIndexes(const QString index)
{
	Database::Get()->query("SELECT COUNT(*) AS count  FROM  system:indexes WHERE name= \""+index+"\"");

	if(!Database::Get()->getArray().isEmpty() && Database::Get()->getArray().count() > 0){
		return Database::Get()->getArray().first().object().value("count").toInt();
		}
	else{
		//	qDebug() << __FILE__ << __LINE__ <<"-1";
		return 0;
		}

	return -1;
}

QList<QJsonDocument> Prsistance::GetALL(const QString entity, const QString condition)
{
	QString where;
	if(!condition.isEmpty())
		where = QString("AND "+condition);
	QString query = QString("SELECT `"+QString(DATABASE)+"`.*,meta("+QString(DATABASE)+").id AS `document_id` FROM `"+QString(DATABASE)+"` WHERE META( `"+QString(DATABASE)+"`).id LIKE '"+entity+"::%' "+where);
		qDebug() << __FILE__ << __LINE__ << query <<"===";
	Database::Get()->query(query);
	//qDebug() << __FILE__ << __LINE__ << Database::Get()->getArray().first().object().value("count").toInt();
	return Database::Get()->getArray();
	//return QList<QJsonDocument>();
}



bool Prsistance::Select(const QString query)
{
	//QStringList tableColumn =  query.split(".");
	//if(tableColumn.count() > 0){
	//	if(Database::Get()->query("S"))
	//		return true;
	//	}

	return false;
}

QString Prsistance::GetDatabaseName()
{
	return QString(DATABASE);
}


