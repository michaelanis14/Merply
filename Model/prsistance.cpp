#include "prsistance.h"

#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <model.h>

Prsistance::Prsistance(QObject *parent) : QObject(parent)
{
//	Database::Get();
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
	qDebug() << __FILE__ << __LINE__  <<"Init" << QCoreApplication::applicationDirPath()
				;//<< Count("City::%\"");//<< Count("ViewStructure::Contact\"");
	bool shipping = false;
	//bool shipping = true;

	/*
	if(Count("ContactType") == -1){
		write("ContactType",QString("Name->Customer"));
		write("ContactType",QString("Name->Supplier"));
		write("ContactType",QString("Name->Customer and Supplier"));
		write("ContactType",QString("Name->Employee"));
		write("ContactType",QString("Name->Other"));
		}
*/
	{
	Database* database  = Database::Gett();
	database->query("SELECT (SELECT name  FROM system:indexes WHERE  keyspace_id ='"+QString(DATABASE)+"' AND state = 'deferred')[*].name");
	if(!database->getArray().isEmpty() && database->getArray().count() > 0){
		qDebug() << "Building Indexs";
		/**
		 * @brief building indexes
		 */
		QStringList indexes;
		indexes<<"CREATE INDEX `AM_OrederInproducts_idx` ON '"+QString(DATABASE)+"'(`OrederIn`) WHERE ((((meta(self).`id`) like'OrederIn:products:: %')and (`OrederIn` like   'OrederIn::%' )) and (`OrederIn` is not missing))";
		indexes<<"CREATE INDEX `AM_OrederInO0_idx` ON '"+QString(DATABASE)+"'(`رقم`) WHERE ((meta(self).`id`) like 'OrederIn::%')";
		indexes<<"CREATE INDEX `AM_clientsc0_idx` ON'"+QString(DATABASE)+"'(`رقم`) WHERE ((meta(self).`id`) like 'clients::%')";
		indexes<<"CREATE PRIMARY INDEX `primary-idx` ON '"+QString(DATABASE)+"'";

		for (QStringList::iterator indexes_iterator = indexes.begin();indexes_iterator != indexes.end(); ++indexes_iterator) {
			QString currentIndex = *indexes_iterator;
			database->query(currentIndex);
//			while (CountIndexes(currentIndex.split("INDEX")[1].split("ON")[0]) <1 ) {
//				QThread::sleep(1);
//				}
			}

//		foreach(QJsonValue index,database->getArray().first().object().value("name").toArray()){
//			database->query("BUILD INDEX ON `"+QString(DATABASE)+"`(`"+index.toString()+"`) USING GSI;");
//			while (CountIndexes(index.toString()) <1 ) {
//				QThread::sleep(6);
//				}

//			}



	}
	}
return true;
	if(Count("ViewStructure::Users\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/Users.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		Database* database  = Database::Gett(); database->storeDoc("ViewStructure::Users",doc);
		}

	if(shipping&&Count("NavigationUI::1\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/NavigationUI.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		Database* database  = Database::Gett(); database->storeDoc("NavigationUI::1",doc);
		}
	else if(shipping&&Count("NavigationUI::1\"") ==  0){
		QString jsonFile = readFile(QCoreApplication::applicationDirPath()+"/AM/NAV.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		Database* database  = Database::Gett(); database->storeDoc("NavigationUI::1",doc);
		}
	if(Count("ViewStructure::Groups\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/Groups.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		Database* database  = Database::Gett(); database->storeDoc("ViewStructure::Groups",doc);
		}
	if(Count("ViewStructure::Contact\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/contact.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	Database* database  = Database::Gett(); database->storeDoc("ViewStructure::Contact",doc);
		}
	if(Count("ViewStructure::Country\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/ViewStructureCountry.Json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		Database* database  = Database::Gett(); database->storeDoc("ViewStructure::Country",doc);
		}
	if(Count("ViewStructure::City\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/City.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		Database* database  = Database::Gett(); database->storeDoc("ViewStructure::City",doc);
		}
	if(shipping && Count("ViewStructure::AirlinesCode\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/AirlinesCode.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//Database* database  = Database::Gett(); database->storeDoc("ViewStructure::AirlinesCode",doc);
		}
	if(shipping &&Count("ViewStructure::AirportsCode\"") ==  0){
		QString jsonFile = readFile(":/initData/initData/AirportsCode.json");
		QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//Database* database  = Database::Gett(); database->storeDoc("ViewStructure::AirportsCode",doc);
		}
	if(shipping &&Count("AirlinesCode::%\"") ==  0){
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
				Database* database  = Database::Gett(); database->storeDoc("AirlinesCode",QJsonDocument(c));
				}
			}

		}
	if(shipping &&Count("AirportsCode::%\"") ==  0){
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
				Database* database  = Database::Gett(); database->storeDoc("AirportsCode",QJsonDocument(c));
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
				Database* database  = Database::Gett(); database->storeDoc("Country",QJsonDocument(c));
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

				Database* database  = Database::Gett(); database->storeDoc("City",QJsonDocument(c));
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
			Database* database  = Database::Gett(); database->storeDoc("ContactType",QJsonDocument(fieldsArry));
			}

		}

	if(Count("Contact::%\"") ==10){
		QStringList fileData = readCSVFile("/AM/Clients.csv");
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		for(int i = 0; i < fileData.count();i++){
			QStringList data = fileData.at(i).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("الأسم",  data.at(0));
				}
			if(0 < data.count() && !data.at(1).isEmpty()){
				c.insert("تليفون",  data.at(1));
				}
			if(0 < data.count() && !data.at(2).isEmpty()){
				c.insert("فاكس",  data.at(2));
				}
			if(0 < data.count() && !data.at(3).isEmpty()){
				c.insert("موبيل",  data.at(3));
				}
			if(0 < data.count() && !data.at(4).isEmpty()){
				c.insert("code",  data.at(4));
				}
			if(true){
				QJsonObject country;
				country.insert("Key","Country::315");
				country.insert("Value","Egypt");
				c.insert("البلد",country);
				}
			if(true){
				QJsonObject city;
				city.insert("Key","City::296");
				city.insert("Value","Cairo");
				c.insert("المدينه",city);
				}
			if(true){
				QJsonObject contactType;
				contactType.insert("Key","ContactType::1");
				contactType.insert("Value","عميل");
				c.insert("النوع",contactType);
				}
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << fieldsArry;
				Database* database  = Database::Gett(); database->storeDoc("Contact",QJsonDocument(c));
				}
			}
		}


	if(Count("Category1::%\"") ==0){
		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/C1.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;

			int id = -1;
			if(!data.at(0).isEmpty()){
				id = data.at(0).toInt();
				}
			if(i != id ){
				QJsonObject c;
				c.insert("Name","404");
				Database* database  = Database::Gett(); database->storeDoc("Category1",QJsonDocument(c));
				continue;
				}

			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("رقم",  QString(data.at(0)).toInt());
				}
			if(0 < data.count() && !data.at(1).isEmpty()){
				c.insert("Name",  data.at(1));
				}

			//qDebug() << __FILE__ << __LINE__ << c;
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << fieldsArry;
				Database* database  = Database::Gett(); database->storeDoc("Category1",QJsonDocument(c));
				idx++;
				}
			}
		}
	if(Count("Category2::%\"") ==0){
		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/C2.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			int id;
			if(!data.at(0).isEmpty()){
				id = data.at(0).toInt();
				}
			if(i != id ){
				QJsonObject c;
				c.insert("Name","404");
				Database* database  = Database::Gett(); database->storeDoc("Category2",QJsonDocument(c));
				continue;
				}

			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("رقم",  QString(data.at(0)).toInt());
				}
			if(0 < data.count() && !data.at(1).isEmpty()){
				c.insert("Name",  data.at(1));
				}

			//qDebug() << __FILE__ << __LINE__ << c;
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << fieldsArry;
				Database* database  = Database::Gett(); database->storeDoc("Category2",QJsonDocument(c));
				idx++;
				}
			}
		}
	if(Count("Category3::%\"") ==0){
		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/C3.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			int id = -3;
			if(!data.at(0).isEmpty()){
				id = data.at(0).toInt();
				}
			else{
				idx++;
				continue;
				}
			if(i != id ){
				QJsonObject c;
				c.insert("Name","404");
				Database* database  = Database::Gett();
				database->storeDoc("Category3",QJsonDocument(c));
				continue;
				}

			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("رقم",  QString(data.at(0)).toInt());
				}
			if(0 < data.count() && !data.at(1).isEmpty()){
				c.insert("Name",  data.at(1));
				}

			//qDebug() << __FILE__ << __LINE__ << c;
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << fieldsArry;
				Database* database  = Database::Gett();
				database->storeDoc("Category3",QJsonDocument(c));
				idx++;
				}
			}
		}
	if(Count("Category4::%\"") ==0){
		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/C4.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			int id = -3;
			if(!data.at(0).isEmpty()){
				id = data.at(0).toInt();
				}
			else{
				idx++;
				continue;
				}
			if(i != id ){
				QJsonObject c;
				c.insert("Name","404");
				Database* database  = Database::Gett(); database->storeDoc("Category4",QJsonDocument(c));
				continue;
				}
			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("رقم",  QString(data.at(0)).toInt());
				}
			if(0 < data.count() && !data.at(1).isEmpty()){
				c.insert("Name",  data.at(1));
				}

			//qDebug() << __FILE__ << __LINE__ << c;
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << fieldsArry;
				Database* database  = Database::Gett(); database->storeDoc("Category4",QJsonDocument(c));
				idx++;
				}
			}
		}
	if(Count("Category5::%\"") ==0){
		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/C5.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			int id = -3;
			if(!data.at(0).isEmpty()){
				id = data.at(0).toInt();
				}
			else{
				idx++;
				continue;
				}
			if(i != id ){
				QJsonObject c;
				c.insert("Name","404");
				Database* database  = Database::Gett(); database->storeDoc("Category5",QJsonDocument(c));
				continue;
				}
			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("رقم",  QString(data.at(0)).toInt());
				}
			if(0 < data.count() && !data.at(1).isEmpty()){
				c.insert("Name",  data.at(1));
				}

			//qDebug() << __FILE__ << __LINE__ << c;
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << fieldsArry;
				Database* database  = Database::Gett(); database->storeDoc("Category5",QJsonDocument(c));
				idx++;
				}
			}
		}
	if(Count("Category6::%\"") == 0){
		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/C6.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			int id = -3;
			if(!data.at(0).isEmpty()){
				id = data.at(0).toInt();
				}
			else{
				idx++;
				continue;
				}
			if(i != id ){
				QJsonObject c;
				c.insert("Name","404");
				Database* database  = Database::Gett(); database->storeDoc("Category6",QJsonDocument(c));
				continue;
				}
			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("رقم",  QString(data.at(0)).toInt());
				}
			if(0 < data.count() && !data.at(1).isEmpty()){
				c.insert("Name",  data.at(1));
				}

			//qDebug() << __FILE__ << __LINE__ << c;
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << fieldsArry;
				Database* database  = Database::Gett(); database->storeDoc("Category6",QJsonDocument(c));
				idx++;
				}
			}
		}
	if(Count("Unit::%\"") ==0){
		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/unit.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			int id = -3;
			if(!data.at(0).isEmpty()){
				id = data.at(0).toInt();
				}
			else{
				idx++;
				continue;
				}
			if(i != id ){
				QJsonObject c;
				c.insert("Name","404");
				Database* database  = Database::Gett(); database->storeDoc("Unit",QJsonDocument(c));
				continue;
				}
			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("رقم",  QString(data.at(0)).toInt());
				}
			if(0 < data.count() && !data.at(1).isEmpty()){
				c.insert("Name",  data.at(1));
				idx++;
				}

			//qDebug() << __FILE__ << __LINE__ << c;
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << fieldsArry;
				Database* database  = Database::Gett(); database->storeDoc("Unit",QJsonDocument(c));
				}
			}
		}
	if(Count("CountryArabic::%\"") ==0){
		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/Country.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			int id = -3;
			if(!data.at(0).isEmpty()){
				id = data.at(0).toInt();
				}
			else{
				idx++;
				continue;
				}
			if(i != id ){
				QJsonObject c;
				c.insert("Name","404");
				Database* database  = Database::Gett(); database->storeDoc("CountryArabic",QJsonDocument(c));
				continue;
				}
			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("رقم",  QString(data.at(0)).toInt());
				}
			if(0 < data.count() && !data.at(1).isEmpty()){
				c.insert("Name",  data.at(1));
				}

			//qDebug() << __FILE__ << __LINE__ << c;
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << fieldsArry;
				Database* database  = Database::Gett(); database->storeDoc("CountryArabic",QJsonDocument(c));
				idx++;
				}
			}
		}

	if(Count("Products::%\"") ==0){

		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/products.csv");
		QStringList pc1 = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/PC1.csv");
		QStringList pc2 = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/PC2.csv");
		QString key;

		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData fileData.count();
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			int id = -3;
			if(!data.at(0).isEmpty()){
				id = data.at(0).toInt();
				}
			else{
				idx++;
				continue;
				}
			if(i != id ){
				QJsonObject c;
				c.insert("Name","404");
				Database* database  = Database::Gett(); database->storeDoc("Products",QJsonDocument(c));
				continue;
				}


			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("رقم",  QString(data.at(0)).toInt());
				c.insert("باركود",  QString(data.at(0)).toInt());
				c.insert("حد اعاده الطلب",    1);
				key =  data.at(0);
				}
			if(0 < data.count() && !data.at(1).isEmpty()){
				c.insert("كود الصنف",  data.at(1));
				}
			if(0 < data.count() && !data.at(2).isEmpty()){
				c.insert("أسم الصنف",  data.at(2));
				}
			if(0 < data.count() && !data.at(20).isEmpty())
				if(0 < data.count() && !data.at(21).isEmpty())
					{
					QJsonObject cc;
					cc.insert("Key","Unit::"+data.at(20));
					cc.insert("Value",data.at(21));
					c.insert("وحده الصنف",cc);
					}
			if(0 < data.count() && !data.at(22).isEmpty())
				if(0 < data.count() && !data.at(23).isEmpty())

					{
					QJsonObject cc;
					cc.insert("Key","CountryArabic::"+data.at(22));
					cc.insert("Value",data.at(23));
					c.insert("بلد الصنع",cc);
					}
			if(0 < data.count() && !data.at(24).isEmpty())
				if(0 < data.count() && !data.at(25).isEmpty())

					{
					QJsonObject cc;
					cc.insert("Key","Category3::"+data.at(24));
					cc.insert("Value",data.at(25));
					c.insert("تصنيف السياره",cc);
					}
			if(0 < data.count() && !data.at(26).isEmpty())
				if(0 < data.count() && !data.at(27).isEmpty())

					{
					QJsonObject cc;
					cc.insert("Key","Category4::"+data.at(26));
					cc.insert("Value",data.at(27));
					c.insert("نوع الصنف الجديد",cc);
					}
			if(0 < data.count() && !data.at(28).isEmpty())
				if(0 < data.count() && !data.at(29).isEmpty())

					{
					QJsonObject cc;
					cc.insert("Key","Category5::"+data.at(28));
					cc.insert("Value",data.at(29));
					c.insert("الماركه",cc);
					}
			if(0 < data.count() && !data.at(30).isEmpty())
				if(0 < data.count() && !data.at(31).isEmpty())

					{
					QJsonObject cc;
					cc.insert("Key","Category6::"+data.at(30));
					cc.insert("Value",data.at(31));
					c.insert("ماركه المصنع",cc);
					}


			if(true){
				QJsonObject tbl;
				QJsonArray rows;
				foreach(QString s,pc1){
					QStringList data = s.split(",");
					if(QString(data.at(1)).compare(key) == 0){
						QJsonObject row ;
						row.insert("ID",QString("Category1::").append(data.at(3)));
						row.insert("أسم التصنيف",data.at(4));
						rows.append(row);
						}
					}
				if(!rows.isEmpty())
					tbl.insert("merplyTabel",rows);
				if(!tbl.isEmpty())
					c.insert("categorey1",tbl);
				}
			if(true){
				QJsonObject tbl;
				QJsonArray rows;
				foreach(QString s,pc2){
					QStringList data = s.split(",");
					if(QString(data.at(1)).compare(key) == 0){
						QJsonObject row ;
						row.insert("ID",QString("Category2::").append(data.at(3)));
						row.insert("أسم التصنيف2",data.at(4));
						rows.append(row);
						}
					}
				if(!rows.isEmpty())
					tbl.insert("merplyTabel",rows);
				if(!tbl.isEmpty())
					c.insert("categorey2",tbl);
				}


			if(!c.isEmpty()){
				//	qDebug() << __FILE__ << __LINE__ << c;
				Database* database  = Database::Gett(); database->storeDoc("Products",QJsonDocument(c));
				idx++;
				}
			//if (i % 100 == 0)
			//QThread::sleep(2);
			}
		}

	if(Count("clients::%\"") ==0){
		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/clients.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			int id = -3;
			if(!data.at(0).isEmpty()){
				id = data.at(0).toInt();
				}
			else{
				idx++;
				continue;
				}
			if(i != id ){
				QJsonObject c;
				c.insert("Name","404");
				Database* database  = Database::Gett(); database->storeDoc("clients",QJsonDocument(c));
				continue;
				}

			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("رقم",  QString(data.at(0)).toInt());
				}
			if(0 < data.count() && !data.at(16).isEmpty()){
				c.insert("كود العميل",  data.at(16));
				}
			if(0 < data.count() && !data.at(1).isEmpty()){
				c.insert("أسم العميل",  data.at(1));
				}

			//qDebug() << __FILE__ << __LINE__ << c;
			if(!c.isEmpty()){
				qDebug() << __FILE__ << __LINE__ << c;
				Database* database  = Database::Gett(); database->storeDoc("clients",QJsonDocument(c));
				idx++;
				}
			}

		}
	if(Count("supplier::%\"") ==0){
		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/suppliers.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			int id = -3;
			if(!data.at(0).isEmpty()){
				id = data.at(0).toInt();
				}
			else{
				idx++;
				continue;
				}
			if(i != id ){
				QJsonObject c;
				c.insert("Name","404");
				Database* database  = Database::Gett(); database->storeDoc("supplier",QJsonDocument(c));
				continue;
				}
			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("رقم",  QString(data.at(0)).toInt());
				}
			if(0 < data.count() && !data.at(14).isEmpty()){
				c.insert("كود المورد",  data.at(14));
				}
			if(0 < data.count() && !data.at(1).isEmpty()){
				c.insert("أسم المورد",  data.at(1));
				}

			//	qDebug() << __FILE__ << __LINE__ << data.at(14);
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << c;
				Database* database  = Database::Gett(); database->storeDoc("supplier",QJsonDocument(c));
				idx++;
				}
			}

		}
	if(Count("PaymentMethod::%\"") ==0){
		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/PaymentMethod.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("طريقه الدفع",  data.at(0));
				}
			//	qDebug() << __FILE__ << __LINE__ << data.at(14);
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << c;
				Database* database  = Database::Gett(); database->storeDoc("PaymentMethod",QJsonDocument(c));
				idx++;
				}
			}
		}
	if(Count("Regions::%\"") == 0){
		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/regions.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			int id = -3;
			if(!data.at(0).isEmpty()){
				id = data.at(0).toInt();
				}
			else{
				idx++;
				continue;
				}
			if(i != id ){
				QJsonObject c;
				c.insert("Name","404");
				Database* database  = Database::Gett(); database->storeDoc("Regions",QJsonDocument(c));
				continue;
				}
			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("رقم",  QString(data.at(0)).toInt());
				}
			if(0 < data.count() && !data.at(1).isEmpty()){
				c.insert("المناطق",  data.at(1));
				}
			//qDebug() << __FILE__ << __LINE__ << data.at(1) << data.at(0);
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << c;
				Database* database  = Database::Gett(); database->storeDoc("Regions",QJsonDocument(c));
				idx++;
				}
			}
		}
	if(Count("Safe::%\"") ==0){
		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/safe.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("الخزينه",  data.at(0));
				}
			//	qDebug() << __FILE__ << __LINE__ << data.at(14);
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << c;
				Database* database  = Database::Gett(); database->storeDoc("Safe",QJsonDocument(c));
				idx++;
				}
			}
		}
	if(Count("Stores::%\"") ==0){
		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/stores.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int idx = 1;
		for(int i = 0; idx < fileData.count();i++){
			QStringList data = fileData.at(idx).split(",");
			//qDebug() << __FILE__ << __LINE__ << data << data.count();
			QJsonObject c;
			int id = -3;
			if(!data.at(0).isEmpty()){
				id = data.at(0).toInt();
				}
			else{
				idx++;
				continue;
				}
			if(i != id ){
				QJsonObject c;
				c.insert("Name","404");
				Database* database  = Database::Gett(); database->storeDoc("Stores",QJsonDocument(c));
				continue;
				}

			if(0 < data.count() && !data.at(0).isEmpty()){
				c.insert("رقم",  QString(data.at(0)).toInt());
				}
			if(0 < data.count() && !data.at(1).isEmpty()){
				c.insert("أسم المخزن",  data.at(1));
				}
			//	qDebug() << __FILE__ << __LINE__ << data.at(14);
			if(!c.isEmpty()){
				//qDebug() << __FILE__ << __LINE__ << c;
				Database* database  = Database::Gett(); database->storeDoc("Stores",QJsonDocument(c));
				idx++;
				}
			}
		}

	if(Count("OrederIn::%\"") == 0){


		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/products.csv");

		QJsonObject c;
		QJsonObject tblProd;
		QJsonArray rowsProd;

		c.insert("تاريخ" ,"2006-10-10T00:00:00");
		c.insert("رقم",0);
		{
		QJsonObject cc;
		cc.insert("Key","Stores::1");
		cc.insert("Value","مخزن عين شمس");
		c.insert("المخزن",cc);
		}
		{
		QJsonObject cc;
		cc.insert("Key","supplier::0");
		cc.insert("Value","غير محدد");
		c.insert("المورد",cc);
		}


		for(int i = 0; i < fileData.count();i++){

			QStringList data = fileData.at(i).split(",");
			//	qDebug() << QString(data.at(15)) << QString(data.at(15)).toInt() << QString(data.at(15)).toDouble();
			if(QString(data.at(15)).toDouble() > 0){
				QJsonObject row ;
				row.insert("ID",QString("Products::").append(data.at(0)));
				row.insert("رقم الأصناف",data.at(0));
				row.insert("الأصناف",data.at(2));
				row.insert("كود الأصناف",data.at(1));

				row.insert("الكميه",QString(data.at(15)).toDouble());
				rowsProd.append(row);
				}


			}
		if(!rowsProd.isEmpty())
			tblProd.insert("merplyTabel",rowsProd);
		if(!tblProd.isEmpty())
			c.insert("products",tblProd);
		if(!c.isEmpty()){
			c.insert("document_id","OrederIn");
			Controller::Get()->createEditStore(c);
			}


		}




	if(Count("OrederIn::%\"") < 0){

		Database* databaseStores  = Database::Gett();
		databaseStores->query("SELECT `d`.`أسم المخزن` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS `BB` FROM `AM`  d WHERE meta(`d`).id LIKE 'Stores::%' ORDER BY `BB` ",false);
		QVector<QJsonDocument> stores = databaseStores->getArray();

		Database* databaseClients  = Database::Gett();
		databaseClients->query("SELECT `d`.`أسم العميل` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS BB FROM `AM` d WHERE meta(`d`).id LIKE 'clients::%' ORDER BY `BB` ",false);
		QVector<QJsonDocument> clients = databaseClients->getArray();

		Database* databaseSuppliers  = Database::Gett();
		databaseSuppliers->query("SELECT `d`.`أسم المورد` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS BB FROM `AM` d WHERE meta(`d`).id LIKE 'supplier::%' ORDER BY `BB`",false);
		QVector<QJsonDocument> suppliers = databaseSuppliers->getArray();

		Database* databaseProducts  = Database::Gett();
		databaseProducts->query("SELECT `d`.`أسم الصنف` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS `BB` FROM `AM`  d WHERE meta(`d`).id LIKE 'Products::%' ORDER BY `BB`",false);
		QVector<QJsonDocument> products = databaseProducts->getArray();







		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/1INV.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		//	qDebug() << __FILE__ << __LINE__ << fileData;
		int currentID = -1;
		QJsonObject c;
		QJsonObject tblProd;
		QJsonArray rowsProd;
		bool sellToClient = false;
		bool returns = false;
		bool transferIN = false;
		bool transferOut = false;
		bool newtransferIN = false;
		bool newtransferOut = false;
		int idxOrderIn = 0;
		int idxOrderOut = 0;
		int idxReturns = 0;
		//qDebug() << fileData.count();
		for(int i = 1; i < fileData.count();i++){

			QStringList data = fileData.at(i).split(",");
			bool newSellToClient = false;
			bool newReturn = false;
			//qDebug() << __FILE__ << __LINE__ << data << data.count();

			int newID = -1;
			if(0 < data.count() && !data.at(1).isEmpty()){
				newID =  data.at(1).toInt();
				}
			if(0 < data.count() && !data.at(6).trimmed().isEmpty()){
				if(0 < data.count() && !data.at(7).trimmed().isEmpty()){
					bool ok = false;
					double num = QString(data.at(7).trimmed()).toDouble(&ok);
					if(num > 0){
						newtransferIN = true;
						newtransferOut = false;
						newSellToClient = false;
						newReturn = false;
						}
					}
				if(0 < data.count() && !data.at(11).trimmed().isEmpty()){
					bool ok = false;
					double num = QString(data.at(11).trimmed()).toDouble(&ok);
					if(num > 0){
						newtransferOut = true;
						newtransferIN = false;
						newSellToClient = false;
						newReturn = false;
						}
					}

				}
			else if(0 < data.count() && data.at(4).trimmed().isEmpty()){
				newSellToClient = true;
				newReturn = false;
				newtransferOut = false;
				newtransferIN = false;
				if(0 < data.count() && !data.at(7).trimmed().isEmpty()){
					bool ok = false;
					double num = QString(data.at(7).trimmed()).toDouble(&ok);
					if(num > 0){
						newReturn = true;
						}
					}
				}
			else {
				newSellToClient = false;
				newReturn = false;
				newtransferOut = false;
				newtransferIN = false;
				}



			if(newID == currentID){
				if(newtransferOut || newtransferIN ){
					if(newtransferOut){
						if(newtransferOut == transferOut){
							QJsonObject row ;
							row.insert("ID",QString("Products::").append(data.at(3)));
							if(products.at(data.at(3).toInt()).object().value("N") != QJsonValue::Undefined)
								row.insert("الأصناف",products.at(data.at(3).toInt()).object().value("N").toString());
							else row.insert("الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
							row.insert("الكميه",QString(data.at(11)).toDouble());
							rowsProd.append(row);
							}
						else goto save;
						}
					else 	if(newtransferIN){
						if(newtransferIN == transferIN){
							QJsonObject row ;
							row.insert("ID",QString("Products::").append(data.at(3)));
							if(products.at(data.at(3).toInt()).object().value("N") != QJsonValue::Undefined)
								row.insert("الأصناف",products.at(data.at(3).toInt()).object().value("N").toString());
							else row.insert("الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
							row.insert("الكميه",QString(data.at(7)).toDouble());
							rowsProd.append(row);
							}
						else goto save;
						}
					if(!rowsProd.isEmpty())
						tblProd.insert("merplyTabel",rowsProd);
					}

				else if(newSellToClient == sellToClient){
					QJsonObject row ;
					row.insert("ID",QString("Products::").append(data.at(3)));
					if(products.at(data.at(3).toInt()).object().value("N") != QJsonValue::Undefined)
						row.insert("الأصناف",products.at(data.at(3).toInt()).object().value("N").toString());
					else row.insert("الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
					if(!sellToClient || returns){
						row.insert("الكميه",QString(data.at(7)).toDouble());
						}
					else {

						row.insert("الكميه",QString(data.at(11)).toDouble());
						}
					rowsProd.append(row);
					}
				if(!rowsProd.isEmpty())
					tblProd.insert("merplyTabel",rowsProd);
				}


			else {
save:
				if(true){
					if(!tblProd.isEmpty())
						c.insert("products",tblProd);
					if(!c.isEmpty()){

						if(transferIN){
							c.insert("document_id","TransferTo");
							Controller::Get()->createEditStore(c);
							}
						else if(transferOut){
							c.insert("document_id","TransferFrom");
							Controller::Get()->createEditStore(c);
							}
						else
							if(sellToClient){
								if(returns){
									/*
								if(currentID != -1)
									while(idxReturns != currentID  && idxReturns < currentID){
										QJsonObject c;
										c.insert("Name","404");
										Database::Get()->storeDoc("Returns",QJsonDocument(c));
										idxReturns++;
										}
										*/
									c.insert("document_id","Returns");
									Controller::Get()->createEditStore(c);
									//Database::Get()->storeDoc("Returns",QJsonDocument(c));

									idxReturns++;
									}
								else{
									/*
								if(currentID != -1)

									while(idxOrderOut != currentID  && idxOrderOut < currentID){
										QJsonObject c;
										c.insert("Name","404");
										Database::Get()->storeDoc("OrderOut",QJsonDocument(c));
										idxOrderOut++;
										}
										*/
									c.insert("document_id","OrderOut");
									Controller::Get()->createEditStore(c);
									//Database::Get()->storeDoc("OrderOut",QJsonDocument(c));
									idxOrderOut++;
									}



								}
							else {/*
							if(currentID != -1)
							while(idxOrderIn != currentID  && idxOrderIn < currentID){
								QJsonObject c;
								c.insert("Name","404");
								Database::Get()->storeDoc("OrederIn",QJsonDocument(c));
								idxOrderIn++;
								}
								*/
								c.insert("document_id","OrederIn");
								Controller::Get()->createEditStore(c);

								//Database::Get()->storeDoc("OrederIn",QJsonDocument(c));
								idxOrderIn++;

								}
						}
					currentID = newID;
					sellToClient = newSellToClient;
					returns = newReturn;
					transferIN = newtransferIN;
					transferOut = newtransferOut;

					foreach(QString k,tblProd.keys())
						tblProd.remove(k);
					foreach(QString k,c.keys())
						c.remove(k);
					for(int i = 0; i < rowsProd.count(); i++)
						rowsProd.removeAt(i);

					QDateTime d = QDateTime::fromString(data.at(2),"yyyy-MM-dd hh:mm:ss");
					//qDebug() <<data.at(2)<< d.toString(Qt::ISODate);
					c.insert("تاريخ" ,d.toString(Qt::ISODate));
					c.insert("رقم",currentID);
					{
					QJsonObject cc;
					cc.insert("Key","Stores::"+data.at(23));
					if(stores.at(data.at(23).toInt()).object().value("N") != QJsonValue::Undefined)
						cc.insert("Value",stores.at(data.at(23).toInt()).object().value("N").toString());
					else cc.insert("Value",QString("S").append(QString::number(stores.at(data.at(23).toInt()).object().value("BB").toInt())));
					c.insert("المخزن",cc);
					}


					if(transferIN){
						QJsonObject cc;
						cc.insert("Key","Stores::"+data.at(23));
						if(stores.at(data.at(6).toInt()).object().value("N") != QJsonValue::Undefined)
							cc.insert("Value",stores.at(data.at(6).toInt()).object().value("N").toString());
						else cc.insert("Value",QString("S").append(QString::number(stores.at(data.at(6).toInt()).object().value("BB").toInt())));
						c.insert("المخزن الى",cc);
						{
						QJsonObject cc;
						cc.insert("Key","Stores::4");
						cc.insert("Value",stores.at(4).object().value("N").toString());
						c.insert("من المخزن",cc);
						}
						}
					else if(transferOut){
						QJsonObject cc;
						cc.insert("Key","Stores::"+data.at(23));
						if(stores.at(data.at(6).toInt()).object().value("N") != QJsonValue::Undefined)
							cc.insert("Value",stores.at(data.at(6).toInt()).object().value("N").toString());
						else cc.insert("Value",QString("S").append(QString::number(stores.at(data.at(6).toInt()).object().value("BB").toInt())));
						c.insert("من المخزن",cc);
						{
						QJsonObject cc;
						cc.insert("Key","Stores::4");
						cc.insert("Value",stores.at(4).object().value("N").toString());
						c.insert("المخزن الى",cc);
						}
						}
					else if(!sellToClient){
						if(data.at(4).toInt() > suppliers.count())
							{
							qDebug()<< __FILE__ << __LINE__ <<"ERROR";
							qDebug()<< __FILE__ << __LINE__ << data;
							qDebug()<< __FILE__ << __LINE__ << data.at(4).toInt();
							qDebug()<< __FILE__ << __LINE__ << sellToClient << returns << currentID << newID;
							break;
							}
						QJsonObject cc;
						if(data.at(4).toInt() > suppliers.count() -1 )
							continue;
						qDebug()<< __FILE__ << __LINE__ << data.at(4).toInt() ;
						cc.insert("Key","supplier::"+data.at(4));
						if(suppliers.at(data.at(4).toInt()).object().value("N") != QJsonValue::Undefined)
							cc.insert("Value",suppliers.at(data.at(4).toInt()).object().value("N").toString());
						else cc.insert("Value",QString("S").append(QString::number(suppliers.at(data.at(4).toInt()).object().value("BB").toInt())));

						c.insert("المورد",cc);
						}
					else{
						if(data.at(5).toInt() > clients.count())
							{
							qDebug()<< __FILE__ << __LINE__ <<"ERROR";
							qDebug()<< __FILE__ << __LINE__ << data;
							qDebug()<< __FILE__ << __LINE__ << data.at(5).toInt();
							qDebug()<< __FILE__ << __LINE__ << sellToClient << returns << currentID << newID;
							break;
							}
						QJsonObject cc;
						cc.insert("Key","clients::"+data.at(5));
						if(clients.at(data.at(4).toInt()).object().value("N") != QJsonValue::Undefined)
							cc.insert("Value",clients.at(data.at(5).toInt()).object().value("N").toString());
						else cc.insert("Value",QString("S").append(QString::number(clients.at(data.at(5).toInt()).object().value("BB").toInt())));

						c.insert("العميل",cc);
						}

					}
				//	qDebug() << __FILE__ << __LINE__ << data.at(14);

				//qDebug() << __FILE__ << __LINE__ << c;
				//Database::Get()->storeDoc("Safe",QJsonDocument(c));
				i--;
				}
			if (i % 100 == 0){
				qDebug() << __FILE__ << __LINE__ << i <<"OrderIn:"<<idxOrderIn <<" OrderOut:"<<idxOrderOut<<" Returns:"<<idxReturns;
				//	QThread::sleep(2);
				}
			qDebug() << i;
			}

		}
	//if()






	if(Count("OrderOut::%\"") < 10){

		Database* databaseStores  = Database::Gett();
		databaseStores->query("SELECT `d`.`أسم المخزن` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS `BB` FROM `AM`  d WHERE meta(`d`).id LIKE 'Stores::%' ORDER BY `BB` ",false);
		QVector<QJsonDocument> stores = databaseStores->getArray();

		Database* databaseClients  = Database::Gett();
		databaseClients->query("SELECT `d`.`أسم العميل` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS BB FROM `AM` d WHERE meta(`d`).id LIKE 'clients::%' ORDER BY `BB` ",false);
		QVector<QJsonDocument> clients = databaseClients->getArray();

		Database* databaseProducts  = Database::Gett();
		databaseProducts->query("SELECT `d`.`أسم الصنف` AS `N`,`d`.`كود الصنف` AS `C`,to_number(SPLIT(META(d).id,'::')[1]) AS `BB` FROM `AM`  d WHERE meta(`d`).id LIKE 'Products::%' ORDER BY `BB`",false);
		QVector<QJsonDocument> products = databaseProducts->getArray();

		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/INV.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		int currentID = -1;
		QJsonObject c;
		QJsonObject tblProd;
		QJsonArray rowsProd;
		int idxOrderOut = 0;

		for(int i = 1; i < fileData.count();i++){

			QStringList data = fileData.at(i).split(",");
			int newID;
			//	qDebug() << __FILE__ << __LINE__ << "fileDataOrderOut"<<fileData.count() << QString(data.at(11)).toDouble();

			if(0 < data.count() && !data.at(1).isEmpty()){
				newID =  data.at(1).toInt();
				}

			if(0 < data.count() && !data.at(5).trimmed().isEmpty()
					&& QString(data.at(11)).toDouble() > 0
					&& newID == currentID){

				QJsonObject row ;
				row.insert("ID",QString("Products::").append(data.at(3)));
				if(products.at(data.at(3).toInt()).object().value("N") != QJsonValue::Undefined){
					row.insert("رقم الأصناف",products.at(data.at(3).toInt()).object().value("BB").toInt());
					row.insert("الأصناف",products.at(data.at(3).toInt()).object().value("N").toString());
					row.insert("كود الأصناف",products.at(data.at(3).toInt()).object().value("C").toString());
					}
				else {
					row.insert("رقم الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
					row.insert("الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
					row.insert("كود الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
					}
				row.insert("الكميه",QString(data.at(11)).toDouble());
				rowsProd.append(row);
				if(!rowsProd.isEmpty())
					tblProd.insert("merplyTabel",rowsProd);
				}
			else {

				if(!tblProd.isEmpty())
					c.insert("products",tblProd);
				if(!c.isEmpty()){
					c.insert("document_id","OrderOut");
					Controller::Get()->createEditStore(c);
					//Database::Get()->storeDoc("OrderOut",QJsonDocument(c));
					idxOrderOut++;
					}
				foreach(QString k,tblProd.keys())
					tblProd.remove(k);
				foreach(QString k,c.keys())
					c.remove(k);

				int rowsProdSize = rowsProd.size();
				for(int kk = 0; kk <rowsProdSize; kk++){
					//qDebug()<<rowsProd.size()  << kk;
					rowsProd.removeFirst();
					//	qDebug()<<rowsProd.size() << kk;
					}

				if(0 < data.count() && !data.at(5).trimmed().isEmpty()
						&& QString(data.at(11)).toDouble() > 0){
					currentID = newID;



					QDateTime d = QDateTime::fromString(data.at(2),"yyyy-MM-dd hh:mm:ss");
					//qDebug() <<data.at(2)<< d.toString(Qt::ISODate);
					c.insert("تاريخ" ,d.toString(Qt::ISODate));
					c.insert("رقم",currentID);
					{
					QJsonObject cc;
					cc.insert("Key","Stores::"+data.at(23));
					if(stores.at(data.at(23).toInt()).object().value("N") != QJsonValue::Undefined)
						cc.insert("Value",stores.at(data.at(23).toInt()).object().value("N").toString());
					else cc.insert("Value",QString("S").append(QString::number(stores.at(data.at(23).toInt()).object().value("BB").toInt())));
					c.insert("المخزن",cc);
					}

					QJsonObject cc;
					cc.insert("Key","clients::"+data.at(5));
					cc.insert("Value",clients.at(data.at(5).toInt()).object().value("N").toString());
					c.insert("العميل",cc);


					i--;
					}

				else {
					currentID = -1;
					}

				}

			if (i % 100 == 0){
				//	qDebug() << __FILE__ << __LINE__ << i <<"OrderIn:"<<idxOrderIn <<" OrderOut:"<<idxOrderOut<<" Returns:"<<idxReturns;
				//	QThread::sleep(2);
				}
			//	qDebug() << i;
			}

		}
	//if()


	if(Count("Returns::%\"") < 10){

		Database* databaseStores  = Database::Gett();
		databaseStores->query("SELECT `d`.`أسم المخزن` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS `BB` FROM `AM`  d WHERE meta(`d`).id LIKE 'Stores::%' ORDER BY `BB` ",false);
		QVector<QJsonDocument> stores = databaseStores->getArray();

		Database* databaseClients  = Database::Gett();
		databaseClients->query("SELECT `d`.`أسم العميل` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS BB FROM `AM` d WHERE meta(`d`).id LIKE 'clients::%' ORDER BY `BB` ",false);
		QVector<QJsonDocument> clients = databaseClients->getArray();

		Database* databaseProducts  = Database::Gett();
		databaseProducts->query("SELECT `d`.`أسم الصنف` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS `BB` FROM `AM`  d WHERE meta(`d`).id LIKE 'Products::%' ORDER BY `BB`",false);
		QVector<QJsonDocument> products = databaseProducts->getArray();

		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/INV.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		int currentID = -1;
		QJsonObject c;
		QJsonObject tblProd;
		QJsonArray rowsProd;
		int idxOrderOut = 0;

		for(int i = 1; i < fileData.count();i++){

			QStringList data = fileData.at(i).split(",");
			int newID;
			//	qDebug() << __FILE__ << __LINE__ << "fileDataOrderOut"<<fileData.count() << QString(data.at(11)).toDouble();

			if(0 < data.count() && !data.at(1).isEmpty()){
				newID =  data.at(1).toInt();
				}

			if(0 < data.count() && !data.at(5).trimmed().isEmpty()
					&& QString(data.at(7)).toDouble() > 0
					&& newID == currentID){

				QJsonObject row ;
				row.insert("ID",QString("Products::").append(data.at(3)));
				if(products.at(data.at(3).toInt()).object().value("N") != QJsonValue::Undefined){
					row.insert("رقم الأصناف",products.at(data.at(3).toInt()).object().value("BB").toInt());
					row.insert("الأصناف",products.at(data.at(3).toInt()).object().value("N").toString());
					row.insert("كود الأصناف",products.at(data.at(3).toInt()).object().value("C").toString());
					}
				else {
					row.insert("رقم الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
					row.insert("الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
					row.insert("كود الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
					}	row.insert("الكميه",QString(data.at(7)).toDouble());
				rowsProd.append(row);
				if(!rowsProd.isEmpty())
					tblProd.insert("merplyTabel",rowsProd);
				}
			else {

				if(!tblProd.isEmpty())
					c.insert("products",tblProd);
				if(!c.isEmpty()){
					c.insert("document_id","Returns");
					Controller::Get()->createEditStore(c);
					//Database::Get()->storeDoc("OrderOut",QJsonDocument(c));
					idxOrderOut++;
					}
				foreach(QString k,tblProd.keys())
					tblProd.remove(k);
				foreach(QString k,c.keys())
					c.remove(k);

				int rowsProdSize = rowsProd.size();
				for(int kk = 0; kk <rowsProdSize; kk++){
					//qDebug()<<rowsProd.size()  << kk;
					rowsProd.removeFirst();
					//	qDebug()<<rowsProd.size() << kk;
					}

				if(0 < data.count() && !data.at(5).trimmed().isEmpty()
						&& QString(data.at(7)).toDouble() > 0){
					currentID = newID;



					QDateTime d = QDateTime::fromString(data.at(2),"yyyy-MM-dd hh:mm:ss");
					//qDebug() <<data.at(2)<< d.toString(Qt::ISODate);
					c.insert("تاريخ" ,d.toString(Qt::ISODate));
					c.insert("رقم",currentID);
					{
					QJsonObject cc;
					cc.insert("Key","Stores::"+data.at(23));
					if(stores.at(data.at(23).toInt()).object().value("N") != QJsonValue::Undefined)
						cc.insert("Value",stores.at(data.at(23).toInt()).object().value("N").toString());
					else cc.insert("Value",QString("S").append(QString::number(stores.at(data.at(23).toInt()).object().value("BB").toInt())));
					c.insert("المخزن",cc);
					}

					QJsonObject cc;
					cc.insert("Key","clients::"+data.at(5));
					cc.insert("Value",clients.at(data.at(5).toInt()).object().value("N").toString());

					c.insert("العميل",cc);


					i--;
					}

				else {
					currentID = -1;
					}

				}

			if (i % 100 == 0){
				//	qDebug() << __FILE__ << __LINE__ << i <<"OrderIn:"<<idxOrderIn <<" OrderOut:"<<idxOrderOut<<" Returns:"<<idxReturns;
				//	QThread::sleep(2);
				}
			//	qDebug() << i;
			}

		}
	//if()

	if(Count("OrederIn::%\"") < 10){

		Database* databaseStores  = Database::Gett();
		databaseStores->query("SELECT `d`.`أسم المخزن` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS `BB` FROM `AM`  d WHERE meta(`d`).id LIKE 'Stores::%' ORDER BY `BB` ",false);
		QVector<QJsonDocument> stores = databaseStores->getArray();

		Database* databaseSuppliers  = Database::Gett();
		databaseSuppliers->query("SELECT `d`.`أسم المورد` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS BB FROM `AM` d WHERE meta(`d`).id LIKE 'supplier::%' ORDER BY `BB`",false);
		QVector<QJsonDocument> suppliers = databaseSuppliers->getArray();

		Database* databaseProducts  = Database::Gett();
		databaseProducts->query("SELECT `d`.`أسم الصنف` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS `BB` FROM `AM`  d WHERE meta(`d`).id LIKE 'Products::%' ORDER BY `BB`",false);
		QVector<QJsonDocument> products = databaseProducts->getArray();

		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/INV.csv");
		//qDebug() << fileData;
		//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
		int currentID = -1;
		QJsonObject c;
		QJsonObject tblProd;
		QJsonArray rowsProd;
		int idxOrderOut = 0;

		for(int i = 1; i < fileData.count();i++){

			QStringList data = fileData.at(i).split(",");
			int newID;
			//	qDebug() << __FILE__ << __LINE__ << "fileDataOrderOut"<<fileData.count() << QString(data.at(11)).toDouble();

			if(0 < data.count() && !data.at(1).isEmpty()){
				newID =  data.at(1).toInt();
				}

			if(0 < data.count() && !data.at(4).trimmed().isEmpty()
					&& QString(data.at(7)).toDouble() > 0
					&& newID == currentID){

				QJsonObject row ;
				row.insert("ID",QString("Products::").append(data.at(3)));
				if(products.at(data.at(3).toInt()).object().value("N") != QJsonValue::Undefined){
					row.insert("رقم الأصناف",products.at(data.at(3).toInt()).object().value("BB").toInt());
					row.insert("الأصناف",products.at(data.at(3).toInt()).object().value("N").toString());
					row.insert("كود الأصناف",products.at(data.at(3).toInt()).object().value("C").toString());
					}
				else {
					row.insert("رقم الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
					row.insert("الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
					row.insert("كود الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
					}		row.insert("الكميه",QString(data.at(7)).toDouble());
				rowsProd.append(row);
				if(!rowsProd.isEmpty())
					tblProd.insert("merplyTabel",rowsProd);
				}
			else {

				if(!tblProd.isEmpty())
					c.insert("products",tblProd);
				if(!c.isEmpty()){
					c.insert("document_id","OrederIn");
					Controller::Get()->createEditStore(c);
					//Database::Get()->storeDoc("OrderOut",QJsonDocument(c));
					idxOrderOut++;
					}
				foreach(QString k,tblProd.keys())
					tblProd.remove(k);
				foreach(QString k,c.keys())
					c.remove(k);

				int rowsProdSize = rowsProd.size();
				for(int kk = 0; kk <rowsProdSize; kk++){
					//qDebug()<<rowsProd.size()  << kk;
					rowsProd.removeFirst();
					//	qDebug()<<rowsProd.size() << kk;
					}

				if(0 < data.count() && !data.at(4).trimmed().isEmpty()
						&& QString(data.at(7)).toDouble() > 0){
					currentID = newID;



					QDateTime d = QDateTime::fromString(data.at(2),"yyyy-MM-dd hh:mm:ss");
					//qDebug() <<data.at(2)<< d.toString(Qt::ISODate);
					c.insert("تاريخ" ,d.toString(Qt::ISODate));
					c.insert("رقم",currentID);
					{
					QJsonObject cc;
					cc.insert("Key","Stores::"+data.at(23));
					if(stores.at(data.at(23).toInt()).object().value("N") != QJsonValue::Undefined)
						cc.insert("Value",stores.at(data.at(23).toInt()).object().value("N").toString());
					else cc.insert("Value",QString("S").append(QString::number(stores.at(data.at(23).toInt()).object().value("BB").toInt())));
					c.insert("المخزن",cc);
					}

					QJsonObject cc;
					cc.insert("Key","supplier::"+data.at(4));
					cc.insert("Value",suppliers.at(data.at(4).toInt()).object().value("N").toString());

					c.insert("المورد",cc);


					i--;
					}

				else {
					currentID = -1;
					}

				}

			if (i % 100 == 0){
				//	qDebug() << __FILE__ << __LINE__ << i <<"OrderIn:"<<idxOrderIn <<" OrderOut:"<<idxOrderOut<<" Returns:"<<idxReturns;
				//	QThread::sleep(2);
				}
			//	qDebug() << i;
			}

		}
	//if()


	if(Count("TransferTo::%\"") < 10){

		Database* databaseStores  = Database::Gett();
		databaseStores->query("SELECT `d`.`أسم المخزن` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS `BB` FROM `AM`  d WHERE meta(`d`).id LIKE 'Stores::%' ORDER BY `BB` ",false);
		QVector<QJsonDocument> stores = databaseStores->getArray();

		Database* databaseProducts  = Database::Gett();
		databaseProducts->query("SELECT `d`.`أسم الصنف` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS `BB` FROM `AM`  d WHERE meta(`d`).id LIKE 'Products::%' ORDER BY `BB`",false);
		QVector<QJsonDocument> products = databaseProducts->getArray();

			QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/INV.csv");
			//qDebug() << fileData;
			//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
			int currentID = -1;
			QJsonObject c;
			QJsonObject tblProd;
			QJsonArray rowsProd;
			int idxOrderOut = 0;

			for(int i = 1; i < fileData.count();i++){

				QStringList data = fileData.at(i).split(",");
				int newID;
				//	qDebug() << __FILE__ << __LINE__ << "fileDataOrderOut"<<fileData.count() << QString(data.at(11)).toDouble();

				if(0 < data.count() && !data.at(1).isEmpty()){
					newID =  data.at(1).toInt();
					}

				if(0 < data.count() && !data.at(6).trimmed().isEmpty()
						&& QString(data.at(7)).toDouble() > 0
						&& newID == currentID){

					QJsonObject row ;
					row.insert("ID",QString("Products::").append(data.at(3)));
					if(products.at(data.at(3).toInt()).object().value("N") != QJsonValue::Undefined){
						row.insert("رقم الأصناف",products.at(data.at(3).toInt()).object().value("BB").toInt());
						row.insert("الأصناف",products.at(data.at(3).toInt()).object().value("N").toString());
						row.insert("كود الأصناف",products.at(data.at(3).toInt()).object().value("C").toString());
						}
					else {
						row.insert("رقم الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
						row.insert("الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
						row.insert("كود الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
						}		row.insert("الكميه",QString(data.at(7)).toDouble());
					rowsProd.append(row);
					if(!rowsProd.isEmpty())
						tblProd.insert("merplyTabel",rowsProd);
					}
				else {

					if(!tblProd.isEmpty())
						c.insert("products",tblProd);
					if(!c.isEmpty()){
						c.insert("document_id","TransferTo");
						Controller::Get()->createEditStore(c);

						idxOrderOut++;
						}
					foreach(QString k,tblProd.keys())
						tblProd.remove(k);
					foreach(QString k,c.keys())
						c.remove(k);

					int rowsProdSize = rowsProd.size();
					for(int kk = 0; kk <rowsProdSize; kk++){
						//qDebug()<<rowsProd.size()  << kk;
						rowsProd.removeFirst();
						//	qDebug()<<rowsProd.size() << kk;
						}

					if(0 < data.count() && !data.at(6).trimmed().isEmpty()
							&& QString(data.at(7)).toDouble() > 0){
						currentID = newID;



						QDateTime d = QDateTime::fromString(data.at(2),"yyyy-MM-dd hh:mm:ss");
						//qDebug() <<data.at(2)<< d.toString(Qt::ISODate);
						c.insert("تاريخ" ,d.toString(Qt::ISODate));
						c.insert("رقم",currentID);
						{
						QJsonObject cc;
						cc.insert("Key","Stores::"+data.at(23));
						if(stores.at(data.at(23).toInt()).object().value("N") != QJsonValue::Undefined)
							cc.insert("Value",stores.at(data.at(23).toInt()).object().value("N").toString());
						else cc.insert("Value",QString("S").append(QString::number(stores.at(data.at(23).toInt()).object().value("BB").toInt())));
						c.insert("المخزن",cc);
						}
						{
						QJsonObject cc;
						cc.insert("Key","Stores::"+data.at(6));
						if(stores.at(data.at(6).toInt()).object().value("N") != QJsonValue::Undefined)
							cc.insert("Value",stores.at(data.at(6).toInt()).object().value("N").toString());
						else cc.insert("Value",QString("S").append(QString::number(stores.at(data.at(6).toInt()).object().value("BB").toInt())));
						c.insert("من المخزن",cc);
						}

						i--;
						}

					else {
						currentID = -1;
						}

					}

				if (i % 100 == 0){
					//	qDebug() << __FILE__ << __LINE__ << i <<"OrderIn:"<<idxOrderIn <<" OrderOut:"<<idxOrderOut<<" Returns:"<<idxReturns;
					//	QThread::sleep(2);
					}
				//	qDebug() << i;
				}

			}
		//if()
	if(Count("TransferFrom::%\"") < 10){

		Database* databaseStores  = Database::Gett();
		databaseStores->query("SELECT `d`.`أسم المخزن` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS `BB` FROM `AM`  d WHERE meta(`d`).id LIKE 'Stores::%' ORDER BY `BB` ",false);
		QVector<QJsonDocument> stores = databaseStores->getArray();

		Database* databaseProducts  = Database::Gett();
		databaseProducts->query("SELECT `d`.`أسم الصنف` AS `N`,to_number(SPLIT(META(d).id,'::')[1]) AS `BB` FROM `AM`  d WHERE meta(`d`).id LIKE 'Products::%' ORDER BY `BB`",false);
		QVector<QJsonDocument> products = databaseProducts->getArray();

			QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AM/INV.csv");
			//qDebug() << fileData;
			//QJsonDocument doc = QJsonDocument::fromJson(jsonFile.toUtf8());
			int currentID = -1;
			QJsonObject c;
			QJsonObject tblProd;
			QJsonArray rowsProd;
			int idxOrderOut = 0;

			for(int i = 1; i < fileData.count();i++){

				QStringList data = fileData.at(i).split(",");
				int newID;
				//	qDebug() << __FILE__ << __LINE__ << "fileDataOrderOut"<<fileData.count() << QString(data.at(11)).toDouble();

				if(0 < data.count() && !data.at(1).isEmpty()){
					newID =  data.at(1).toInt();
					}

				if(0 < data.count() && !data.at(6).trimmed().isEmpty()
						&& QString(data.at(11)).toDouble() > 0
						&& newID == currentID){

					QJsonObject row ;
					row.insert("ID",QString("Products::").append(data.at(3)));
					if(products.at(data.at(3).toInt()).object().value("N") != QJsonValue::Undefined){
						row.insert("رقم الأصناف",products.at(data.at(3).toInt()).object().value("BB").toInt());
						row.insert("الأصناف",products.at(data.at(3).toInt()).object().value("N").toString());
						row.insert("كود الأصناف",products.at(data.at(3).toInt()).object().value("C").toString());
						}
					else {
						row.insert("رقم الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
						row.insert("الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
						row.insert("كود الأصناف",QString("P").append(QString::number(products.at(data.at(3).toInt()).object().value("BB").toInt())));
						}	row.insert("الكميه",QString(data.at(11)).toDouble());
					rowsProd.append(row);
					if(!rowsProd.isEmpty())
						tblProd.insert("merplyTabel",rowsProd);
					}
				else {

					if(!tblProd.isEmpty())
						c.insert("products",tblProd);
					if(!c.isEmpty()){
						c.insert("document_id","TransferFrom");
						Controller::Get()->createEditStore(c);

						idxOrderOut++;
						}
					foreach(QString k,tblProd.keys())
						tblProd.remove(k);
					foreach(QString k,c.keys())
						c.remove(k);

					int rowsProdSize = rowsProd.size();
					for(int kk = 0; kk <rowsProdSize; kk++){
						//qDebug()<<rowsProd.size()  << kk;
						rowsProd.removeFirst();
						//	qDebug()<<rowsProd.size() << kk;
						}

					if(0 < data.count() && !data.at(6).trimmed().isEmpty()
							&& QString(data.at(11)).toDouble() > 0){
						currentID = newID;



						QDateTime d = QDateTime::fromString(data.at(2),"yyyy-MM-dd hh:mm:ss");
						//qDebug() <<data.at(2)<< d.toString(Qt::ISODate);
						c.insert("تاريخ" ,d.toString(Qt::ISODate));
						c.insert("رقم",currentID);
						{
						QJsonObject cc;
						cc.insert("Key","Stores::"+data.at(23));
						if(stores.at(data.at(23).toInt()).object().value("N") != QJsonValue::Undefined)
							cc.insert("Value",stores.at(data.at(23).toInt()).object().value("N").toString());
						else cc.insert("Value",QString("S").append(QString::number(stores.at(data.at(23).toInt()).object().value("BB").toInt())));
						c.insert("المخزن",cc);
						}
						{
						QJsonObject cc;
						cc.insert("Key","Stores::"+data.at(6));
						if(stores.at(data.at(6).toInt()).object().value("N") != QJsonValue::Undefined)
							cc.insert("Value",stores.at(data.at(6).toInt()).object().value("N").toString());
						else cc.insert("Value",QString("S").append(QString::number(stores.at(data.at(6).toInt()).object().value("BB").toInt())));
						c.insert("الى المخزن",cc);
						}

						i--;
						}

					else {
						currentID = -1;
						}

					}

				if (i % 100 == 0){
					//	qDebug() << __FILE__ << __LINE__ << i <<"OrderIn:"<<idxOrderIn <<" OrderOut:"<<idxOrderOut<<" Returns:"<<idxReturns;
					//	QThread::sleep(2);
					}
				//	qDebug() << i;
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
		QString line = in.readLine().toUtf8();
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

	Database* database  = Database::Gett();
	QObject::connect(database,SIGNAL(gotDocuments(QVector<QJsonDocument>)),Prsistance::Get(),SLOT(GetJsonListData(QVector<QJsonDocument>)));
	database->query(query);
}

void Prsistance::GetJsonEntityFields(QString table, QString select, QString condition)
{
	//qDebug() << __FILE__ << __LINE__ << table << select << condition;

	QString where;
	if(!condition.isEmpty()){
		if(condition.split("=").count() > 1){
			//where = QString("AND d.`"+condition.split("=")[0]+"` = '"+condition.split("=")[1]+"' ") ;
			where = QString("AND d.").append(condition) ;
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


	QString query = "SELECT  d.`"+select.trimmed()+"` AS `Value`,META(d).id AS `Key`,to_number(SPLIT(META(d).id,'::')[1]) AS BB FROM `"+QString(DATABASE)+"` d WHERE META(d).id LIKE '"+entities+"::%' "+where+"  ORDER BY `BB` ";
	//qDebug() << __FILE__ << __LINE__ << query;
	Database* database  = Database::Gett();
	QObject::connect(database,SIGNAL(gotDocuments(QVector<QJsonDocument>)),Prsistance::Get(),SLOT(GetJsonListData(QVector<QJsonDocument>)));
	database->query(query,true);

}
void Prsistance::GetJsonListData(QVector<QJsonDocument> items)
{
	//QObject::disconnect(Database::Get(),SIGNAL(gotDocuments(QVector<QJsonDocument>)),Prsistance::Get(),SLOT(GetJsonListData(QVector<QJsonDocument>)));
	//	foreach(QJsonDocument doc,items){
	//qDebug() << __FILE__ << __LINE__ << items;
	//	}

	emit GotJsonSelectList(items);
}
int Prsistance::Count(const QString table)
{
	Database* database  = Database::Gett();
	database->query("SELECT COUNT(*) AS count  FROM  "+QString(DATABASE)+" WHERE META( "+QString(DATABASE)+").id LIKE \""+table);

	if(!database->getArray().isEmpty() && database->getArray().count() > 0){
		return database->getArray().first().object().value("count").toInt();
		}
	else{
		//	qDebug() << __FILE__ << __LINE__ <<"-1";
		return 0;
		}

	return -1;
}

int Prsistance::CountIndexes(const QString index)
{
	Database* database  = Database::Gett();
	database->query("SELECT COUNT(*) AS count  FROM  system:indexes WHERE name= '"+index+"' AND keyspace_id = '"+QString(DATABASE)+"' AND state = 'online'");

	if(!database->getArray().isEmpty() && database->getArray().count() > 0){
		return database->getArray().first().object().value("count").toInt();
		}
	else{
		//	qDebug() << __FILE__ << __LINE__ <<"-1";
		return 0;
		}

	return -1;
}

QVector<QJsonDocument> Prsistance::GetALL(const QString entity, const QString condition)
{
	QString where;
	if(!condition.isEmpty())
		where = QString("AND "+condition);
	QString query = QString("SELECT `"+QString(DATABASE)+"`.*,meta("+QString(DATABASE)+").id AS `document_id` FROM `"+QString(DATABASE)+"` WHERE META( `"+QString(DATABASE)+"`).id LIKE '"+entity+"::%' "+where);
	qDebug() << __FILE__ << __LINE__ << query <<"===";
	Database* database  = Database::Gett();
	database->query(query);
	//qDebug() << __FILE__ << __LINE__ << Database::Get()->getArray().first().object().value("count").toInt();
	return database->getArray();
	//return QVector<QJsonDocument>();
}



bool Prsistance::Select(const QString query)
{
	//QStringList tableColumn =  query.split(".");
	//if(tableColumn.count() > 0){
	//	if(Database::Get()->query("S"))
	//		return true;
	//	}

	return query.isEmpty();
}

QString Prsistance::GetDatabaseName()
{
	return QString(DATABASE);
}


