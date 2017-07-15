#include "prsistance.h"
#include "inittabel.h"


#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <model.h>


Prsistance::Prsistance(QObject *parent) : QObject(parent)
{


	this->ready = false;
	database = new Database();
	QObject::connect(database,SIGNAL(readyToQuery()),this,SLOT(readyToQuery()));
	database->start();

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
	//TODOOO : CHECK IF EACH STRING IN THE STRING LIST IS EMPTY
	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("clients")) ==  0 &&Prsistance::Get()->getTableNumber("clients") !="`0`" ){
		qDebug() << __FILE__ << __LINE__ <<"filling clients table";
		QStringList dataIndex;
		dataIndex << "0"<<"16"<<"1"<<"-"<<"-"<<"-";
		Prsistance::Get()->insertIntoTable("clients","clients",1,dataIndex);
		}
	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("Category1")) ==  0 && Prsistance::Get()->getTableNumber("Category1") !="`0`"){
		QStringList dataIndex;
		dataIndex << "0";
		Prsistance::Get()->insertIntoTable("Category1","C1",0,dataIndex);
		}
	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("Category2")) ==  0 && Prsistance::Get()->getTableNumber("Category2") !="`0`"){
		QStringList dataIndex;
		dataIndex << "0";
		Prsistance::Get()->insertIntoTable("Category2","C2",0,dataIndex);
		}
	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("Category3")) ==  0 && Prsistance::Get()->getTableNumber("Category3") !="`0`"){
		QStringList dataIndex;
		dataIndex << "0";
		Prsistance::Get()->insertIntoTable("Category3","C3",0,dataIndex);

		}
	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("Category4")) ==  0 && Prsistance::Get()->getTableNumber("Category4") !="`0`"){
		QStringList dataIndex;
		dataIndex << "0";
		Prsistance::Get()->insertIntoTable("Category4","C4",0,dataIndex);
		}
	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("Category5")) ==  0 && Prsistance::Get()->getTableNumber("Category5") !="`0`"){
		QStringList dataIndex;
		dataIndex << "0";
		Prsistance::Get()->insertIntoTable("Category5","C5",0,dataIndex);
		}
	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("Category6")) ==  0 && Prsistance::Get()->getTableNumber("Category6") !="`0`"){
		QStringList dataIndex;
		dataIndex << "0";
		Prsistance::Get()->insertIntoTable("Category6","C6",0,dataIndex);
		}

	//ONE MISSING COLUMN
//	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("AirlinesCode")) ==  0 && Prsistance::Get()->getTableNumber("AirlinesCode") !="`0`" )
//		{
//		qDebug() << __FILE__ << __LINE__ <<"filling Airlines table";
//		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AirlinesCodeData.csv");
//		QSqlQuery insertQuery(Prsistance::Get()->database->getDatabase());

//		for(int i = 0; i < fileData.count();i++){
//			QStringList data = fileData.at(i).split(",");
//			qDebug() << __FILE__ << __LINE__ <<"Airlines code table dataa" << data;
//			QString query = "INSERT INTO" + Prsistance::Get()->getTableNumber("AirlinesCode")+"(";
//			QStringList columnsNames = Prsistance::Get()->getColumnsNumber("AirlinesCode");

//			for(int i =0; i<columnsNames.length();i++){
//				query += "`"+ columnsNames[i] +  "`" + ",";
//				}

//			query += "Enabled,Active,ShowOnWebSite,CreatedOn,CreatedByName,EditedByName,CreatedByID,EditedByID,EditedOn)";
//			query += "VALUES(""'" + data.at(1) + "'" + "," +"'" + data.at(2) + "'"+ "," +"'" + data.at(3).toUtf8() + "'" + "," + "'" + data.at(4).toUtf8() + "'"+ ",";
//			query +=" '1', '1', '1', '2017-11-11', 's', 's', 's', 's', '2017-03-05')";
//			//insertQuery.exec(query);
//			qDebug() << __FILE__ << __LINE__ <<"airlinescode query" << query;
//			}
//		}

	//TABLE DOESN'T EXIST
//	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("AirportsCode")) ==  0 && Prsistance::Get()->getTableNumber("AirportsCode") !="`0`" )
//		{
//		qDebug() << __FILE__ << __LINE__ <<"filling AirportsCode table";
//		QStringList fileData = readCSVFile(QCoreApplication::applicationDirPath()+"/AirportsCodeData.csv");
//		QSqlQuery insertQuery(Prsistance::Get()->database->getDatabase());

//		for(int i = 0; i < fileData.count();i++){
//			QStringList data = fileData.at(i).split(",");
//			qDebug() << __FILE__ << __LINE__ <<"AirportsCodeData code table dataa" << data;
//			QString query = "INSERT INTO" + Prsistance::Get()->getTableNumber("AirportsCode")+"(";
//			QStringList columnsNames = Prsistance::Get()->getColumnsNumber("AirportsCode");

//			for(int i =0; i<columnsNames.length();i++){
//				query += "`"+ columnsNames[i] +  "`" + ",";
//				}

//			query += "Enabled,Active,ShowOnWebSite,CreatedOn,CreatedByName,EditedByName,CreatedByID,EditedByID,EditedOn)";
//			query += "VALUES(""'" + data.at(0).toUtf8() + "'" + "," +"'" + data.at(1).toUtf8() + "'"+ "," +"'" + data.at(2).toUtf8() + "'" + "," + "'" + data.at(3).toUtf8() + "'"+ ","+ "'" + data.at(4).toUtf8() + "'"+ ","+ "'" + data.at(5).toUtf8() + "'"+ ",";
//			query +=" '1', '1', '1', '2017-11-11', 's', 's', 's', 's', '2017-03-05')";
//			insertQuery.exec(query);
//			qDebug() << __FILE__ << __LINE__ <<"AirportsCodeData query" << "in airports code"<<  Prsistance::Get()->getTableNumber("AirportsCode") << query;
//			}
//		}/*
	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("Unit")) ==  0 && Prsistance::Get()->getTableNumber("Unit") !="`0`" )
		{
		QStringList dataIndex;
		dataIndex<<"0";
		Prsistance::Get()->insertIntoTable("Unit","unit",0,dataIndex);
		}
	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("CountryArabic")) ==  0 && Prsistance::Get()->getTableNumber("CountryArabic") !="`0`" )
		{
		QStringList dataIndex;
		dataIndex << "0";
		Prsistance::Get()->insertIntoTable("CountryArabic","Country",0,dataIndex);
		qDebug() << __FILE__ << __LINE__ <<"filling CountryArabic table";
		}
	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("Products")) ==  0 && Prsistance::Get()->getTableNumber("Products") !="`0`")
		{
		QStringList dataIndex;
		dataIndex << "0"<<"1"<<"2"<<"0"<<"20"<<"22"<<"0"<<"24"<<"26"<<"28"<<"30";
		Prsistance::Get()->insertIntoTable("Products","products",0,dataIndex);
		}

	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("supplier")) ==  0 && Prsistance::Get()->getTableNumber("supplier") !="`0`" ){
		QStringList dataIndex;
		dataIndex << "0"<<"14"<<"1"<<"-"<<"-"<<"-";
		Prsistance::Get()->insertIntoTable("supplier","suppliers",0,dataIndex);
		}
	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("PaymentMethod")) ==  0 && Prsistance::Get()->getTableNumber("PaymentMethod") !="`0`" ){
		QStringList dataIndex;
		dataIndex << "0";
		Prsistance::Get()->insertIntoTable("PaymentMethod","PaymentMethod",0,dataIndex);
		}
	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("Regions")) ==  0 && Prsistance::Get()->getTableNumber("Regions") !="`0`" )
		{
		QStringList dataIndex;
		dataIndex << "1";
		Prsistance::Get()->insertIntoTable("Regions","regions",0,dataIndex);
		}
	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("Safe")) ==  0 && Prsistance::Get()->getTableNumber("Safe") !="`0`" )
		{
		QStringList dataIndex;
		dataIndex << "0";
		Prsistance::Get()->insertIntoTable("Safe","safe",0,dataIndex);

		}

	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("Stores")) ==  0 && Prsistance::Get()->getTableNumber("Stores") !="`0`" )
		{
		QStringList dataIndex;
		dataIndex << "0"<<"1";
		Prsistance::Get()->insertIntoTable("Stores","stores",0,dataIndex);

		}

	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("Currency")) ==  0 && Prsistance::Get()->getTableNumber("Currency") !="`0`")
		{
		//STATIC DATA
		qDebug() << __FILE__ << __LINE__ <<"filling currency table";
		QSqlQuery insertQuery(Prsistance::Get()->database->getDatabase());
		QString query = "INSERT INTO" + Prsistance::Get()->getTableNumber("Currency")+"(";
		QStringList columnsNames = Prsistance::Get()->getColumnsNumber("Currency");

		for(int i =0; i<columnsNames.length();i++){
			query += "`"+ columnsNames[i] +  "`" + ",";
			}

		query += "Enabled,Active,ShowOnWebSite,CreatedOn,CreatedByName,EditedByName,CreatedByID,EditedByID,EditedOn)";
		query += "VALUES('Egyptian pound','EGP','0.0',0.0,";
		query +=" '1', '1', '1', '2017-07-05', 'Merply', 'Merply', '1', '1', '2017-07-05')";
		insertQuery.exec(query);
		qDebug() << __FILE__ << __LINE__ <<"Currency query"<< query;
		}
	if(Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("OrderOut")) ==  0 && Prsistance::Get()->getTableNumber("OrderOut") !="`0`" &&
			Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("OrederIn")) ==  0 && Prsistance::Get()->getTableNumber("OrederIn") !="`0`"&&
			Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("TransferFrom")) ==  0 && Prsistance::Get()->getTableNumber("TransferFrom") !="`0`" &&
			Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("TransferTo")) ==  0 && Prsistance::Get()->getTableNumber("TransferTo") !="`0`" &&
			Prsistance::Get()->countRecords(Prsistance::Get()->getTableNumber("Returns")) ==  0 && Prsistance::Get()->getTableNumber("Returns") !="`0`")
		{

		QStringList fileData = readCSVFile(":/initData/initData/Filtered/1INV.csv");
		QString query;
		QSqlQuery insertQuery(Prsistance::Get()->database->getDatabase());
		for(int i = 0; i < fileData.count();i++){
			QStringList data = fileData.at(i).split(",");
			QString modifiedDate =  data.at(2).split(QRegExp("\\s+"), QString::SkipEmptyParts).at(0);
			// NOFromToStoreID + supplier + InQuantity  = OrderIn
			if(data.at(6).trimmed().isEmpty() && !data.at(4).trimmed().isEmpty() && data.at(7).toDouble()>0  && data.count()>0)
				{
				query = "INSERT INTO" + Prsistance::Get()->getTableNumber("OrederIn")+"(";
				QStringList columnsNames = Prsistance::Get()->getColumnsNumber("OrederIn");

				for(int i =0; i<columnsNames.length();i++){
					query += "`"+ columnsNames[i] +  "`" + ",";
					}
				query += "Enabled,Active,ShowOnWebSite,CreatedOn,CreatedByName,EditedByName,CreatedByID,EditedByID,EditedOn)";

				query += "VALUES(" +data.at(0) + "," "'"+modifiedDate + "'" +","  + data.at(4) + "," + data.at(23) + ","+ "1" + ","+ "'-'"+ "," + "'0.00'" +"," + "0.00" +","+ "'0.00'" +",";
				qDebug() << __FILE__ << __LINE__ <<"OrederIn query"<< query;
				}
			// noFromToStoreID + ClientID + OutQuantity  = OrderOut
			else if(data.at(6).trimmed().isEmpty() && !data.at(5).trimmed().isEmpty() && data.at(11).toDouble()>0  && data.count()>0){
				query = "INSERT INTO" + Prsistance::Get()->getTableNumber("OrderOut")+"(";
				QStringList columnsNames = Prsistance::Get()->getColumnsNumber("OrderOut");
				for(int i =0; i<columnsNames.length();i++){
					query += "`"+ columnsNames[i] +  "`" + ",";
					}
				query += "Enabled,Active,ShowOnWebSite,CreatedOn,CreatedByName,EditedByName,CreatedByID,EditedByID,EditedOn)";
				query += "VALUES(" +data.at(0) + "," "'"+modifiedDate + "'" +","  + data.at(5) + "," + data.at(23) + ","+ "'-'"+ "," + "'0.00'" +"," + "0.00" +","+ "'0.00'" +",";
				qDebug() << __FILE__ << __LINE__ <<"OrederOut query"<< query;
			}
			//TransferFromTo+OutQuantity = TransferFrom
			else if(!data.at(6).trimmed().isEmpty()&& data.at(11).toDouble()>0  && data.count()>0){
				QSqlQuery insertQuery(Prsistance::Get()->database->getDatabase());
				query = "INSERT INTO" + Prsistance::Get()->getTableNumber("TransferFrom")+"(";
				QStringList columnsNames = Prsistance::Get()->getColumnsNumber("TransferFrom");
				for(int i =0; i<columnsNames.length();i++){
					query += "`"+ columnsNames[i] +  "`" + ",";
					}
				query += "Enabled,Active,ShowOnWebSite,CreatedOn,CreatedByName,EditedByName,CreatedByID,EditedByID,EditedOn)";
				query += "VALUES(" +data.at(0) + "," "'"+modifiedDate + "'" +","  + data.at(6) + "," + data.at(23) + ","+ "'-'"+",";
				qDebug() << __FILE__ << __LINE__ <<"Transfer From query"<< query;
				}
			//TransferFromTo+InQuantity = TransferTo
			else if(!data.at(6).trimmed().isEmpty()&& data.at(7).toDouble()>0  && data.count()>0){
				query = "INSERT INTO" + Prsistance::Get()->getTableNumber("TransferTo")+"(";
				QStringList columnsNames = Prsistance::Get()->getColumnsNumber("TransferTo");
				for(int i =0; i<columnsNames.length();i++){
					query += "`"+ columnsNames[i] +  "`" + ",";
					}
				query += "Enabled,Active,ShowOnWebSite,CreatedOn,CreatedByName,EditedByName,CreatedByID,EditedByID,EditedOn)";
				query += "VALUES(" +data.at(0) + "," "'"+modifiedDate + "'" +","  + data.at(6) + "," + data.at(23) + ","+ "'-'"+",";
				qDebug() << __FILE__ << __LINE__ <<"Transfer To query"<< query;
				}
			//ClientID +InQuantity = Returns
			else if(!data.at(5).trimmed().isEmpty() && data.at(7).toDouble()>0  && data.count()>0){
				query = "INSERT INTO" + Prsistance::Get()->getTableNumber("Returns")+"(";
				QStringList columnsNames = Prsistance::Get()->getColumnsNumber("Returns");
				for(int i =0; i<columnsNames.length();i++){
					query += "`"+ columnsNames[i] +  "`" + ",";
					}
				query += "Enabled,Active,ShowOnWebSite,CreatedOn,CreatedByName,EditedByName,CreatedByID,EditedByID,EditedOn)";
				query += "VALUES(" +data.at(0) + "," "'"+modifiedDate + "'" +","  + data.at(5) + "," + data.at(23) + ","+ "'-'"+ "," + "'0.00'" +"," + "0.00" +","+ "'0.00'" +",";
				qDebug() << __FILE__ << __LINE__ <<"Returns query"<< query;
				}
			query +=" '1', '1', '1', '2017-07-05', 'root', 'root', '1', '1', '2017-07-05')";
			insertQuery.exec(query);
			}
		}
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
	qDebug() << __FILE__ << __LINE__  <<"file path"<< path;
	QStringList lines;

	QFile file(path);
	if(!file.open(QIODevice::ReadOnly)) {
		qDebug() << __FILE__ << __LINE__   <<"file error"<< file.errorString();
		}

	QTextStream in(&file);

	while(!in.atEnd()) {
		QString line = in.readLine();
		lines.append(line.toUtf8());
		}

	file.close();

	return lines;
}
/*
void Prsistance::GetJsonList(QString table, QString select,QString condition)
{
	QString where;
	if(!condition.isEmpty())
		where = QString("AND "+condition);
	QString query = "SELECT ARRAY_REPEAT(TOARRAY("+select.trimmed()+"),1) AS `Value`,META( `"+QString(DATABASE)+"`).id AS `Key`  FROM  `"+QString(DATABASE)+"` WHERE META( `"+QString(DATABASE)+"`).id LIKE \""+table+"::%\" "+where;
	//qDebug() << __FILE__ << __LINE__ << query;


	QObject::connect(database,SIGNAL(gotDocuments(QVector<QJsonDocument>)),Prsistance::Get(),SLOT(GetSelectListData(QVector<QJsonDocument>)));
	database->query(query);
}
*/
void Prsistance::GetSelectList(QString table, QString select, QString condition)
{
		//qDebug() << __FILE__ << __LINE__ << table << select << condition;

	QString where;
	if(!condition.isEmpty()){
		where = QString("WHERE ").append(condition) ;
		}
	QString entities = table.split("::").count() > 1 ?table.split("::")[1]:table;

	//QString query = "SELECT fin."+select.trimmed()+"[0] AS `Value`,META(d).id AS `Key`  FROM "+QString(DATABASE)+" d UNNEST d.Fields f UNNEST f fin WHERE fin."+select+" AND META(d).id LIKE \""+table+"::%\" "+where;
	//QString query = "SELECT fin."+select.trimmed()+"[0] AS `Value`,META(d).id AS `Key`  FROM "+QString(DATABASE)+" d UNNEST d.Fields f UNNEST f fin WHERE fin."+select+" AND META(d).id LIKE \""+table+"::%\" "+where;
	//QString query ="SELECT Array item.`"+select.trimmed()+"` FOR item IN f END As `Value`,META(d).id AS `Key`  FROM "+QString(DATABASE)+" d UNNEST d.Fields f WHERE  META(d).id LIKE '"+entities+"::%' "+where;


	QString query = "SELECT  `"+select.trimmed()+"` AS 'Value',`id` AS 'Key',`id` AS 'BB' FROM `"+entities+"` "+where+" ";
	//qDebug() << __FILE__ << __LINE__ <<"GetJsonEntityFields REMAP" << query;

	QObject::connect(Prsistance::Get()->database,SIGNAL(queryResults(QVector<QSqlRecord>)),Prsistance::Get(),SLOT(GetSelectListData(QVector<QSqlRecord>)));
	Prsistance::Get()->database->query(query);

}
void Prsistance::GetSelectListData(QVector<QSqlRecord> items)
{
	QObject::disconnect(Prsistance::Get()->database,SIGNAL(queryResults(QVector<QSqlRecord>)),Prsistance::Get(),SLOT(GetSelectListData(QVector<QSqlRecord>)));

	emit GotSelectList(items);
}


void Prsistance::count(const QString& table)
{

	QObject::connect(database,SIGNAL(gotValue(QString)),Prsistance::Get(),SLOT(gotCount(QString)));
	database->query("SELECT COUNT(*) AS Value  FROM  "+table);
}

/**
 * @brief Prsistance::countRecords
 * @param table
 * @return
 * @details countRecords counts all the rows in a given table
 */
int Prsistance::countRecords(QString table)
{

	QSqlQuery query(database->getDatabase());
	query.exec("SELECT count(*) FROM " +table);
	int rowsCount = 0;

	while (query.next())
		rowsCount =  query.value(0).toInt();
	qDebug() << __FILE__ << __LINE__ <<"row countsss"<<rowsCount<<table;
	return rowsCount;
}

void Prsistance::countTabel(const QString& table)
{

	QObject::connect(database,SIGNAL(gotValue(QString)),Prsistance::Get(),SLOT(gotCount(QString)));
	database->query("SELECT count(*) AS Value FROM information_schema.tables WHERE table_schema = '"+QString(DATABASE)+"' AND table_name = '"+table+"'");
}
void Prsistance::gotCount(QString value)
{
	QObject::disconnect(database,SIGNAL(gotValue(QString)),Prsistance::Get(),SLOT(gotCount(QString)));
	emit count(value.toInt());
}

void Prsistance::readyToQuery(bool ready)
{
	this->ready = ready;
}



int Prsistance::CountIndexes(const QString index)
{
	//
	//	database->query("SELECT COUNT(*) AS count  FROM  system:indexes WHERE name= '"+index+"' AND keyspace_id = '"+QString(DATABASE)+"' AND state = 'online'");
	/*
	if(!database->getArray().isEmpty() && database->getArray().count() > 0){
		return database->getArray().first().object().value("count").toInt();
		}
	else{
		//	qDebug() << __FILE__ << __LINE__ <<"-1";
		return 0;
		}
*/
	return 1;
}

QVector<QJsonDocument> Prsistance::GetALL(const QString entity, const QString condition)
{
	/*
	QString where;
	if(!condition.isEmpty())
		where = QString("AND "+condition);
	QString query = QString("SELECT `"+QString(DATABASE)+"`.*,meta("+QString(DATABASE)+").id AS `document_id` FROM `"+QString(DATABASE)+"` WHERE META( `"+QString(DATABASE)+"`).id LIKE '"+entity+"::%' "+where);
	qDebug() << __FILE__ << __LINE__ << query <<"===";

	database->query(query);
	//qDebug() << __FILE__ << __LINE__ <<new Database()->getArray().first().object().value("count").toInt();
	return database->getArray();
	*/
	return QVector<QJsonDocument>();
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

bool Prsistance:: CreateViewStructureTabels()
{
	qDebug() << __FILE__ << __LINE__  <<"In create view structure tables";
	QMap<int,QJsonObject>* builtTabels  = new QMap<int,QJsonObject>();
	InitTabel* initT = new InitTabel(0,"");
	while (builtTabels->count() < Model::Get()->cachedViewStructures.count()) {
		QMapIterator<int, QJsonObject> i(Model::Get()->cachedViewStructures);
		while (i.hasNext()) {
			outerloop:
			i.next();
			if(builtTabels->contains(i.key())){
				continue;
				}
			else{
				foreach(QJsonObject subField,Model::Get()->cachedViewStructureSubFields.value(i.key())){
					if(subField.value("Type").toString().compare("Refrence") == 0){
						if(!builtTabels->contains(subField.value("Source").toString().toInt())){
							goto outerloop;
							}
						}
					}
					initT->count(QString::number(i.key()));
					builtTabels->insert(i.key(),i.value());

				}


			}
		}
}
/**
 * @brief Prsistance::getTableNumber
 * @param table
 * @return
 * @details getTableNumber returns the number of a given table name
 */
QString Prsistance::getTableNumber(const QString table)
{
	qDebug()<<__FILE__<<__LINE__<<"table is: "<<table<<QString::number(Controller::Get()->getCachedViewStructureNames(table));
	return "`"+ QString::number(Controller::Get()->getCachedViewStructureNames(table))+"`";
}

/**
 * @brief Prsistance::getColumnsNumber
 * @param table
 * @return
 * @details this method returns the columns names of each table in the database in sequence
 */
QStringList Prsistance::getColumnsNumber(QString table){

	QJsonDocument cachedViewStructure = QJsonDocument(Controller::Get()->getCachedViewStructure(Controller::Get()->getCachedViewStructureNames(table)));
	QStringList columnNames;
	int index =0;
	foreach(QJsonValue vg,cachedViewStructure.object().value("Viewgroups").toArray()){
		foreach(QJsonValue fv,vg.toObject().value("Viewgroup").toObject().value("Fields").toArray()){
			foreach(QJsonValue subFld,fv.toObject().value("SubFields").toArray()){
				QString type = subFld.toObject().value("Type").toString();
				if(! type.compare("Table") == 0)
					columnNames << QString::number(index);
				index ++;
				}
			}
		}
	qDebug()<<__FILE__<<__LINE__<<"columns"<<columnNames;

	return columnNames;
}
/**
 * @brief Prsistance::insertIntoTable
 * @param tableName
 * @param fileName
 * @param startingRow
 * @param dataIndex
 * @details this method seeds the database by passing to it the name of the table, the name of the file to be read, the starting row to read the file from, and the indices containing the right data in the file. This method discards insertion in a column if its type is table!
 */
void Prsistance::insertIntoTable(QString tableName, QString fileName, int startingRow, QStringList dataIndex){

	QJsonDocument cachedViewStructure = QJsonDocument(Controller::Get()->getCachedViewStructure(Controller::Get()->getCachedViewStructureNames(tableName)));
	QStringList fileData = readCSVFile(":/initData/initData/Filtered/" + fileName +".csv");
	QSqlQuery alterQuery(Prsistance::Get()->database->getDatabase());
	QString alterQ = "ALTER TABLE" +  Prsistance::Get()->getTableNumber(tableName)+ "AUTO_INCREMENT=0";
	alterQuery.exec(alterQ);
	QSqlQuery insertQuery(Prsistance::Get()->database->getDatabase());
	int indexCount = 0;
	QString query;
	for(int i = startingRow; i < fileData.count();i++){

		QStringList data = fileData.at(i).split(",");
		query = "INSERT INTO" + Prsistance::Get()->getTableNumber(tableName)+"(";
		QStringList columnsNames = Prsistance::Get()->getColumnsNumber(tableName);

		for(int i =0; i<columnsNames.length();i++){
			query += "`"+ columnsNames[i] +  "`" + ",";
			}

		query += "Enabled,Active,ShowOnWebSite,CreatedOn,CreatedByName,EditedByName,CreatedByID,EditedByID,EditedOn)";
		query += "VALUES(";

		foreach(QJsonValue vg,cachedViewStructure.object().value("Viewgroups").toArray()){
			foreach(QJsonValue fv,vg.toObject().value("Viewgroup").toObject().value("Fields").toArray()){
				if(indexCount >= dataIndex.length()){
					indexCount = 0;
					}
				foreach(QJsonValue subFld,fv.toObject().value("SubFields").toArray()){

					QString type = subFld.toObject().value("Type").toString();
					QRegExp digit("\\d*");
					if( type.compare("TextArea") == 0 ){
						if(digit.exactMatch(dataIndex.at(indexCount)))
							query +="'"+data.at(dataIndex.at(indexCount).toInt())+ "'"+ ",";
						else
							query +="'لا يوجد',";
						indexCount++;
						}
					if(type.compare("Date") == 0){
						if(digit.exactMatch(dataIndex.at(indexCount)))
							query +="'"+data.at(dataIndex.at(indexCount).toInt())+ "'"+ ",";
						else
							query +="'2017-07-14',";
						indexCount++;
						}
					else if(type.compare("Refrence") == 0 || type.compare("Serial") == 0 ){
						if(digit.exactMatch(dataIndex.at(indexCount)))
							query +=data.at(dataIndex.at(indexCount).toInt())+",";

						else
							query +="0,";
						indexCount++;
						}
					else if(type.compare("Equation") == 0 || type.compare("Text") == 0 ){
						if(digit.exactMatch(dataIndex.at(indexCount))){
							if(subFld.toObject().value("InputDataType").toString().compare("IntToMillion") == 0)
								query +=data.at(dataIndex.at(indexCount).toInt())+",";
							else
								query +="'"+data.at(dataIndex.at(indexCount).toInt())+"'"+",";
							}
						else
							query +="'0',";
						indexCount++;
						}
					}
				}
			}

		query +=" '1', '1', '1', '2017-07-05', 'root', 'root', '1', '1','2017-07-05')";
		insertQuery.exec(query);
		qDebug() << __FILE__ << __LINE__ <<fileName + "query" << query;
		}


}



