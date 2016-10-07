#include "prsistance.h"

#include<QFile>
#include<QMessageBox>

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



bool Prsistance::write(QString table, QList<QString> lines, bool update){
	QJsonObject json = QJsonObject();
	foreach(QString line,lines){
		int splitCount = line.split("->").count();
		if(splitCount > 0){
			if(splitCount == 2){
				json[line.split("->")[0]] = line.split("->")[1];

				}
			else{
				QJsonArray array;

				QJsonArray table = Prsistance::table(line);
				if(!table.isEmpty()){
					//	qDebug() << "table";
					array = table;
					}

				else{
					QJsonArray inArray;
					for(int i = 1;splitCount > i;i++){
						inArray << line.split("->").at(i);
						//qDebug()<<line.split("->")[0]<<line << line.split("->").at(i);
						}
					array << inArray;

					//	qDebug() << line.split("->")[0] <<json.value(line.split("->")[0]);
					if(json.value(line.split("->")[0]) == QJsonValue::Undefined){
						json.insert(line.split("->")[0],array);
						}
					else{
						QJsonArray tempArray;
						if(json.value(line.split("->")[0]).isArray())
							tempArray = json.value(line.split("->")[0]).toArray();

						else {
							{
							QJsonArray temp;
							temp << json.value(line.split("->")[0]).toString();
							tempArray <<temp;
							}
							}
						tempArray << inArray;
						json.insert(line.split("->")[0],tempArray);
						}



					}

				}
			}

		/*		else{
					//qDebug() << "NOT Array"<< line;
					QJsonArray tempArray;
					QJsonArray table = Prsistance::table(line);

					if(!table.isEmpty()){
						tempArray <<table;
						qDebug() << table;
						}

					*/
		}


	//qDebug() << line;


	QJsonDocument doc(json);

	//QString strJson(doc.toJson(QJsonDocument::Indented));
	//qDebug() << strJson;
	if(update)
		return	Database::Get()->updateDoc(doc);
	else return Database::Get()->storeDoc(table,doc);


}

void Prsistance::write(QString table, QString line)
{
	QList<QString> lines;
	lines.append(line);
	Prsistance::write(table,lines,false);
}



QJsonArray Prsistance::table(QString line)
{
	QJsonArray array;
	QString key = line.split("->")[0];
	line.replace(0,QString(line.split("->")[0]).count(),"");
	//qDebug() << line;
	QString s =  QString("->")+QString(key) + QString("->");
	int splitCount = line.split(s).count();
	//qDebug() << s << line.split(s);
	if(line.split(s).count() > 1){
		//array
		for(int i = 0; i < splitCount; i++){
			QJsonArray row;
			//	qDebug() << "QString(line.split(s)[i]).split()" << QString(line.split(s)[i]).split("->");
			for(int j = 0; j < QString(line.split(s)[i]).split("->").count(); j++){
				QString rowString = QString(line.split(s)[i]).split("->")[j];
				if(!(rowString.trimmed().isEmpty())){
					//		qDebug() << rowString.trimmed();
					row <<  rowString.trimmed();
					//	qDebug() << row << array;
					}
				}
			if(!row.isEmpty())
				array << row;
			}

		}
	return array;


}

bool Prsistance::init()
{
		qDebug() <<"Init" ;//<< Count("City::%\"");//<< Count("ViewStructure::Contact\"");
	/*
	if(Count("ContactType") == -1){
		write("ContactType",QString("Name->Customer"));
		write("ContactType",QString("Name->Supplier"));
		write("ContactType",QString("Name->Customer and Supplier"));
		write("ContactType",QString("Name->Employee"));
		write("ContactType",QString("Name->Other"));
		}
*/

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
	//	qDebug() << fileData;
		for(int i = 0; i < fileData.count();i++){
			QStringList data = fileData.at(i).split(",");
			//qDebug() << data << data.count();
			QJsonArray arryObj;
			if(0 < data.count() && !data.at(0).isEmpty()){
				QJsonObject c;
				c.insert("Prefix",QJsonArray() <<data.at(0));
				arryObj << c;
				}
			if(1 < data.count() && !data.at(1).isEmpty()){
				QJsonObject c;
				c.insert("ICAO",QJsonArray() <<data.at(1));
				arryObj << c;
				}
			if(2 <= data.count() && !data.at(2).isEmpty()){
				QJsonObject c;
				c.insert("IATA",QJsonArray() <<data.at(2));
				arryObj << c;
				}
			if(3 < data.count() && !data.at(3).isEmpty()){
				QJsonObject c;
				c.insert("Name",QJsonArray() <<data.at(3));
				arryObj << c;
				}
			if(4 < data.count() && !data.at(4).isEmpty()){
				QJsonObject c;
				QJsonObject country;
				country.insert("Value",data.at(4));
				c.insert("Country",QJsonArray() <<country);
				arryObj << c;
				}
			if(!arryObj.isEmpty()){
				QJsonObject fieldsArry;
				fieldsArry.insert("Fields",QJsonArray() << arryObj);
				//qDebug() << fieldsArry;
				Database::Get()->storeDoc("AirlinesCode",QJsonDocument(fieldsArry));
				}
			}

		}
	if(Count("AirportsCode::%\"") ==  0){
		QStringList fileData = readCSVFile(":/initData/initData/AirportsCodeData.csv");
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
	//	qDebug() << fileData;
		for(int i = 0; i < fileData.count();i++){
			QStringList data = fileData.at(i).split(",");
			//qDebug() << data << data.count();
			QJsonArray arryObj;
			if(0 < data.count() && !data.at(0).isEmpty()){
				QJsonObject c;
				c.insert("Airport",QJsonArray() <<data.at(0));
				arryObj << c;
				}
			if(1 < data.count() && !data.at(1).isEmpty()){
				QJsonObject c;
				QJsonObject city;
				city.insert("Value",data.at(1));
				c.insert("City",QJsonArray() << city);
				arryObj << c;
				}
			if(2 < data.count() && !data.at(2).isEmpty()){
				QJsonObject c;
				QJsonObject country;
				country.insert("Value",data.at(2));
				c.insert("Country",QJsonArray() <<country);
				arryObj << c;
				}
			if(3 <= data.count() && !data.at(3).isEmpty()){
				QJsonObject c;
				c.insert("IATA",QJsonArray() <<data.at(3));
				arryObj << c;
				}
			if(4 < data.count() && !data.at(4).isEmpty()){
				QJsonObject c;
				c.insert("ICAO",QJsonArray() <<data.at(4));
				arryObj << c;
				}
			if(5 < data.count() && !data.at(5).isEmpty()){
				QJsonObject c;
				c.insert("FAA",QJsonArray() <<data.at(5));
				arryObj << c;
				}
			if(!arryObj.isEmpty()){
				QJsonObject fieldsArry;
				fieldsArry.insert("Fields",QJsonArray() << arryObj);
				//qDebug() << fieldsArry;
				Database::Get()->storeDoc("AirportsCode",QJsonDocument(fieldsArry));
				}
			}

		}
	if(Count("Country::%\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/Countries.Json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		foreach(QJsonValue country,doc.object().value("countries").toObject().value("country").toArray()){
			//QJsonObject c;
			QJsonArray arryObj;

			if(country.toObject().value("countryCode") != QJsonValue::Undefined){
				QJsonObject c;
				c.insert("Code",QJsonArray() <<country.toObject().value("countryCode").toString());
				arryObj << c;
				}
			if(country.toObject().value("countryName") != QJsonValue::Undefined){
				QJsonObject c;
				c.insert("Name",QJsonArray() <<country.toObject().value("countryName").toString());
				arryObj << c;
				}
			if(country.toObject().value("currencyCode") != QJsonValue::Undefined){
				QJsonObject c;
				c.insert("Currency",QJsonArray() <<country.toObject().value("currencyCode").toString());
				arryObj << c;
				}
			if(country.toObject().value("capital") != QJsonValue::Undefined){
				QJsonObject c;
				c.insert("Capital",QJsonArray() <<country.toObject().value("capital").toString());
				arryObj << c;
				}
			if(country.toObject().value("continentName") != QJsonValue::Undefined){
				QJsonObject c;
				c.insert("Continent",QJsonArray() <<country.toObject().value("continentName").toString());
				arryObj << c;
				}
			if(country.toObject().value("continent") != QJsonValue::Undefined){
				QJsonObject c;
				c.insert("ContinentCode",QJsonArray() <<country.toObject().value("continent").toString());
				arryObj << c;
				}
			if(country.toObject().value("languages") != QJsonValue::Undefined){
				QJsonObject c;
				c.insert("Languages",QJsonArray() <<country.toObject().value("languages").toString());
				arryObj << c;
				}
			if(!arryObj.isEmpty()){
				QJsonObject fieldsArry;
				fieldsArry.insert("Fields",QJsonArray() << arryObj);
				Database::Get()->storeDoc("Country",QJsonDocument(fieldsArry));
				}
			}
		}

	if(Count("City::%\"") == 0){
		QString jsonFile = readFile(":/initData/initData/countriesToCities.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//qDebug() << jsonFile << doc;
		QString jsonFileC = readFile(":/initData/initData/Countries.Json");
		QJsonDocument docC = QJsonDocument::fromJson(jsonFileC.toUtf8());
		//	qDebug()  << docC;
		foreach(QJsonValue country,docC.object().value("countries").toObject().value("country").toArray()){
			QJsonArray arryObj;

			if(doc.object().value(country.toObject().value("countryName").toString()) != QJsonValue::Undefined){
				//qDebug() << c;
				QJsonObject c;
				c.insert("Country",QJsonArray() <<country.toObject().value("countryName").toString());
				arryObj << c;

				QJsonArray cities;
				foreach(QJsonValue city,doc.object().value(country.toObject().value("countryName").toString()).toArray()){
					QJsonArray cityarr;
					cityarr << QString(QString(city.toString().toLatin1()).toUtf8());
					cities << cityarr;
					}

				QJsonObject ci;
				ci.insert("Cities", cities);
				arryObj << ci;
				//qDebug() <<doc.object().value(country.toObject().value("countryName").toString()).toArray();
				}
			if(!arryObj.isEmpty()){
				QJsonObject fieldsArry;
				fieldsArry.insert("Fields",QJsonArray() << arryObj);
				Database::Get()->storeDoc("City",QJsonDocument(fieldsArry));
				}
			}


		}
	if(Count("ContactType::%\"") == 0){



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
		//qDebug() <<doc.object().value(country.toObject().value("countryName").toString()).toArray();

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
	qDebug() << path;
	QString jsonFile;
	QFile file(path);
	if(!file.open(QIODevice::ReadOnly)) {
		qDebug() << __FILE__ << __LINE__ << file.errorString();
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
	qDebug() << path;
	QStringList lines;

	QFile file(path);
	if(!file.open(QIODevice::ReadOnly)) {
		qDebug() << __FILE__ << __LINE__ << file.errorString();
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
	//qDebug() << query;

	QObject::connect(Database::Get(),SIGNAL(gotDocuments(QList<QJsonDocument>)),Prsistance::Get(),SLOT(GetJsonListData(QList<QJsonDocument>)));
	Database::Get()->query(query);
}

void Prsistance::GetJsonEntityFields(QString table, QString select, QString condition)
{
	//qDebug() << table << select << condition;
	QString where;
	if(!condition.isEmpty()){
		if(condition.split("=").count() > 1){
			where = QString("AND ANY item in f SATISFIES item."+condition.split("=")[0]+"[0] = \""+condition.split("=")[1]+"\" END ");
			}
		else{
			where = QString("AND "+condition);
			}
		}
	QString entities = table.split("::").count() > 1 ?table.split("::")[1]:table;

	//QString query = "SELECT fin."+select.trimmed()+"[0] AS `Value`,META(d).id AS `Key`  FROM "+QString(DATABASE)+" d UNNEST d.Fields f UNNEST f fin WHERE fin."+select+" AND META(d).id LIKE \""+table+"::%\" "+where;
	//QString query = "SELECT fin."+select.trimmed()+"[0] AS `Value`,META(d).id AS `Key`  FROM "+QString(DATABASE)+" d UNNEST d.Fields f UNNEST f fin WHERE fin."+select+" AND META(d).id LIKE \""+table+"::%\" "+where;
	QString query ="SELECT Array item.`"+select.trimmed()+"` FOR item IN f END As `Value`,META(d).id AS `Key`  FROM "+QString(DATABASE)+" d UNNEST d.Fields f WHERE  META(d).id LIKE '"+entities+"::%' "+where;
//	qDebug() << query;

	QObject::connect(Database::Get(),SIGNAL(gotDocuments(QList<QJsonDocument>)),Prsistance::Get(),SLOT(GetJsonListData(QList<QJsonDocument>)));
	Database::Get()->query(query);

}
void Prsistance::GetJsonListData(QList<QJsonDocument> items)
{
	QObject::disconnect(Database::Get(),SIGNAL(gotDocuments(QList<QJsonDocument>)),Prsistance::Get(),SLOT(GetJsonListData(QList<QJsonDocument>)));
	emit GotJsonSelectList(items);
}
int Prsistance::Count(const QString table)
{

	Database::Get()->query("SELECT COUNT(*) AS count  FROM  "+QString(DATABASE)+" WHERE META( "+QString(DATABASE)+").id LIKE \""+table);

		if(!Database::Get()->getArray().isEmpty() && Database::Get()->getArray().count() > 0){
			return Database::Get()->getArray().first().object().value("count").toInt();
			}
		else{
			//	qDebug() <<"-1";
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
	//	qDebug() << query <<"===";
	Database::Get()->query(query);
		//qDebug() << Database::Get()->getArray().first().object().value("count").toInt();
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


