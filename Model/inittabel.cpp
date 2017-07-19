#include "InitTabel.h"
#include "model.h"

InitTabel::InitTabel(QObject *parent,QString tblName) : QObject(parent)
{


	persistance = Prsistance::Get();
	QObject::connect(persistance,SIGNAL(count(int)),this,SLOT(gotCounterT(int)));

	if(!tblName.isEmpty()){
		count(tblName);
		}
}

void InitTabel::count(QString tblName)
{
	this->tblName = tblName;
	persistance->countTabel(tblName);
	//QThread::sleep(4);
}




void InitTabel::gotCounterT(int tblCount)
{
	if(tblCount == 0){
		QString query;
		query = genetrateCreateTabelQuery(QJsonDocument(Model::Get()->cachedViewStructures.value(this->tblName.toInt())));


		//Database* database  = new Database();
		QObject::connect(Controller::Get()->getDatabase(),SIGNAL(queryResults(QVector<QSqlRecord>)),this,SLOT(gotResults(QVector<QSqlRecord>)));
		foreach (QString q, query.split(";")) {
			if(!q.isEmpty()){
				Controller::Get()->getDatabase()->query(q);
				qDebug()<< __FILE__ << __LINE__ << "NewTabel :::::::::" << q;
				}
			}


		}
}

void InitTabel::gotResults(QVector<QSqlRecord> results)
{
	qDebug()<< __FILE__ << __LINE__ <<"*INIT TABEL*"<< results;
}



QString InitTabel::genetrateCreateTabelQuery(QJsonDocument document)
{

	QString query;
	QString oneToManyQueries = "";

	query += "CREATE TABLE `"+document.object().value("document_id").toString() + "` (";
	query +="`id` INT NOT NULL AUTO_INCREMENT, "
			"PRIMARY KEY (`id`), ";
	foreach(QJsonValue vg,document.object().value("Viewgroups").toArray()){
		//	qDebug() << vg.toObject() << vg.toObject().value("Viewgroup");
		foreach(QJsonValue fv,vg.toObject().value("Viewgroup").toObject().value("Fields").toArray()){
			QString fieldName = fv.toObject().value("Label").toString(); //category not categorey
			fieldName.replace(0,1,fieldName[0].toUpper()); // Change first letter to capital letter to match cached QMap
			int tableNumber = Controller::Get()->getCachedViewStructureNames(fieldName);
			qDebug()<<__FILE__<<__LINE__<<"Field name" <<fieldName <<tableNumber ;

			//	if(fv.toObject().value("ShowInIndex") != QJsonValue::Undefined)
			//		indexFieldsName << fv.toObject().value("Label").toString();
			//	fieldsName << fv.toObject().value("Label").toString();
			foreach(QJsonValue subFld,fv.toObject().value("SubFields").toArray()){
				QString type = subFld.toObject().value("Type").toString();
				QString clmNo = subFld.toObject().value("clmnNumber").toString();
				bool mandatory  = subFld.toObject().value("Mandatory").toBool();

				if(type.compare("TextArea") == 0){
					query += "`"+clmNo+"` VARCHAR(90) ";
					if(mandatory)
						query +=" NOT NULL ";
					query +=", ";
					}
				else if(type.compare("Text") == 0 || type.compare("Equation") == 0){

					int maxLength = 7;
					if(subFld.toObject().value("CharCount") != QJsonValue::Undefined && subFld.toObject().value("CharCount").toInt() > 0)
						maxLength = subFld.toObject().value("CharCount").toInt();
					if(subFld.toObject().value("InputDataType").toString().compare("IntToMillion") == 0)
						query += "`"+clmNo+"` INT("+QString::number(maxLength)+") ";
					else if(subFld.toObject().value("InputDataType").toString().compare("DoubleToMillion")== 0)
						query += "`"+clmNo+"` DECIMAL("+QString::number(maxLength)+",2) ";
					else query += "`"+clmNo+"` VARCHAR(40) ";

					if(mandatory)
						query +=" NOT NULL ";
					query +=", ";
					}
				else if(type.compare("Refrence") == 0){
					query += "`"+clmNo+"` INT NOT NULL,";
					query += "FOREIGN KEY (`"+clmNo+"`) REFERENCES `"+subFld.toObject().value("Source").toString()+"`(`id`) ON UPDATE CASCADE ON DELETE CASCADE ";
					query +=", ";
					}
				else if(type.compare("Serial") == 0){
					query += "`"+clmNo+"` INT NOT NULL UNIQUE ";
					query +=", KEY(`"+clmNo+"`),";
					}
				else if(type.compare("Date") == 0){
					query += "`"+clmNo+"` DATE ";
					if(mandatory)
						query +=" NOT NULL ";
					query +=", ";
					}
				else if(type.compare("Table") == 0){
					oneToManyQueries +=  genetrateCreateTabelQueryForTabel(document.object().value("document_id").toString(),tableNumber,subFld);
					}
				//	subfields.append(subFld.toObject());

				/*

				*/
				}
			}
		}

	query += "`Enabled` VARCHAR(1) NOT NULL, "
			 "`Active` VARCHAR(1) NOT NULL, "
			 "`ShowOnWebSite` VARCHAR(1) NOT NULL, "
			 "`CreatedOn` DATE NOT NULL, "
			 "`CreatedByName` VARCHAR(40) NOT NULL, "
			 "`EditedByName` VARCHAR(40) NOT NULL, "
			 "`CreatedByID` VARCHAR(40) NOT NULL, "
			 "`EditedByID` VARCHAR(40) NOT NULL, "
			 "`EditedOn` DATE NOT NULL, KEY(`EditedOn`) )ENGINE=INNODB DEFAULT CHARSET=`utf8mb4`; ";
	//query += oneToManyQueries //I COMMENTED THIS;
	//query = oneToManyQueries;

	return query;
}

QString InitTabel::genetrateCreateTabelQueryForTabel(QString parentEntity,int tableNumber,QJsonValue tabel)
{
	QString query;
	if(tabel.toObject().value("Type").toString().compare("Table") == 0){
		query += "CREATE TABLE `"+parentEntity+"_"+QString::number(tableNumber)+"` (";
		query +="`id` INT NOT NULL,";
		//query += "FOREIGN KEY (`"+parentEntity+"ID`) REFERENCES `"+parentEntity+"`(`id`)  ON DELETE CASCADE, ";
		query += "FOREIGN KEY (`id`) REFERENCES `"+parentEntity+"`(`id`)  ON DELETE CASCADE, ";

		int i = 0;
		foreach(QJsonValue clmn,tabel.toObject().value("Columns").toArray()){

			QString type = clmn.toObject().value("Type").toString();
			if(type.compare("Refrence") == 0){
				if(!clmn.toObject().value("Source").toString().isEmpty()){
					query +="`"+QString::number(i)+"` INT,";
					query += "FOREIGN KEY (`"+QString::number(i)+"`) REFERENCES `"+clmn.toObject().value("Source").toString()+"`(`id`)  ON DELETE CASCADE, ";
					}



				}
			else if(type.compare("Equation") == 0){
				query += "`"+QString::number(i)+"` DECIMAL(6,2), ";

				}
			else {
				query += "`"+QString::number(i)+"` VARCHAR(40), ";
				}

			clmn.toObject().value("Header").toString();
			i++;
			}
		}



	query += "`Enabled` VARCHAR(1) NOT NULL, "
			 "`Active` VARCHAR(1) NOT NULL, "
			 "`ShowOnWebSite` VARCHAR(1) NOT NULL, "
			 "`CreatedOn` DATE NOT NULL, "
			 "`CreatedByName` VARCHAR(40) NOT NULL, "
			 "`EditedByName` VARCHAR(40) NOT NULL, "
			 "`CreatedByID` VARCHAR(40) NOT NULL, "
			 "`EditedByID` VARCHAR(40) NOT NULL, "
			 "`EditedOn` DATE NOT NULL, KEY(`EditedOn`) )ENGINE=INNODB DEFAULT CHARSET=`utf8mb4` ;";

	//qDebug()<<__FILE__<<__LINE__<<"query in table is" <<query;
	return query;

}



