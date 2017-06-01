#include "printcontroller.h"
#include "controller.h"


PrintController::PrintController(QObject *parent) : QObject(parent)
{
	showDialog = true;
	report = new QtRPT(this);
}
PrintController* PrintController::p_instance = 0;
PrintController* PrintController::Get()
{
	//if (p_instance == 0)
	p_instance = new PrintController();

	return p_instance;
}
void PrintController::printEntity(QString id)
{
	//qDebug() << __FILE__ << __LINE__  <<"printEntity"<< id;
	QStringList idSplit = id.split("::");
	if(idSplit.count() > 1){
		QObject::connect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(gotPrintEntity(QJsonDocument)));
		Controller::Get()->getDoc(" * ",idSplit[0],idSplit[1],"");
		}
}

/**
 * @brief PrintController::gotPrintEntity
 * @param document
 */
void PrintController::gotPrintEntity(QJsonDocument document,bool showDialog)
{
	this->showDialog = showDialog;
	QObject::disconnect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(gotPrintEntity(QJsonDocument)));

	this->printDocumnet = document;
	QString documentID ;
	//qDebug() << document.object().value("document_id").toString();
	if(QString(document.object().value("document_id").toString().split("::")[0]).compare("Page") == 0){
		documentID =  "PrintStructure::P"+document.object().value("document_id").toString().split("::")[1];
		}
	else documentID =  "PrintStructure::"+document.object().value("document_id").toString().split("::")[0];
	getFieldstoValueMap(this->printDocumnet.object());
	QObject::connect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(gotPrintStrct(QJsonDocument)));
	//qDebug() << __FILE__ << __LINE__  <<"gotPrintEntity"<< documentID;
	//Controller::Get()->getDoc(documentID);
	Controller::Get()->getDoc("printstructure","PrintStructure",documentID,"");

}
void PrintController::getFieldstoValueMap(QJsonObject entity)
{
	reportData = QJsonArray();

	QStringList keys;

	keys = entity.keys();
	//qDebug() << __FILE__ << __LINE__  << entity << keys;
	foreach(QString key,keys){


		QJsonValue value = entity.value(key);
		if(value.isString())
			fieldsValues.insert(key,value.toString());
		else if(value.isDouble())
			fieldsValues.insert(key,Controller::Get()->toString("",value));

		else if(value.isObject()){
			if(value.toObject().value("Value") != QJsonValue::Undefined)
				fieldsValues.insert(key,value.toObject().value("Value").toString());
			else if(value.toObject().value("merplyTabel") != QJsonValue::Undefined){
				//qDebug() << value;
				if(value.toObject().value("merplyTabel").isArray()){
					//qDebug() << value.toObject().value("merplyTabel");
					foreach (QJsonValue row, value.toObject().value("merplyTabel").toArray()) {
						if(row.toObject().value("Value") != QJsonValue::Undefined){
							QString rowValue = row.toObject().value("Value").toString();
							if(!rowValue.isEmpty() && rowValue.compare("0") !=0)
								reportData.append(row);
							}
						else if(row.toObject().value("Amount") != QJsonValue::Undefined){
							QString rowAmount = row.toObject().value("Amount").toString();
							if(!rowAmount.isEmpty() && rowAmount.compare("0") !=0)
								reportData.append(row);
							}
						else{
							reportData.append(row);
							//qDebug() << row ;
							}
						}
					//TODO : instead of Merging tables have better refrences

					//qDebug() << reportData;
					}
				}
			}


		//qDebug() << __FILE__ << __LINE__  << fvvapn.toObject().value(key).toString();



		/*
			foreach(QJsonValue subFld,fvvapn.toObject().value("SubFields").toArray()){
				if(subFld.toObject().value("Type").toString().compare("Table") == 0){
					QString tableName= fieldsName.count() > 0?fieldsName.at(fieldsName.count()-1):"";
					fieldsName.removeLast();
					foreach(QJsonValue clmn,subFld.toObject().value("Columns").toArray()){
						fieldsName <<clmn.toObject().value("Header").toString().append("$").append(tableName);
						}
					}
				}
				*/

		}
}
void PrintController::gotPrintStrct(QJsonDocument strct)
{

	QObject::disconnect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(gotPrintStrct(QJsonDocument)));

	this->printStrct = strct;

	//QObject::disconnect(Controller::Get(),SIGNAL(getDocData(QJsonDocument)),this,SLOT(gotPrintStrct(QJsonDocument)));
	QObject::disconnect(report);
	QObject::disconnect(report, SIGNAL(setValue(const int, const QString, QVariant&, const int)),
						this, SLOT(setValue(const int, const QString, QVariant&, const int)));

	QObject::connect(report, SIGNAL(setValue(const int, const QString, QVariant&, const int)),
					 this, SLOT(setValue(const int, const QString, QVariant&, const int)));
	QDomDocument xmlDocument;
	xmlDocument.setContent(printStrct.object().value("XMLSTRCT").toString());
	report->loadReport(xmlDocument);
	report->recordCount << reportData.count();
	//qDebug()<< __FILE__ << __LINE__ << reportData.count();
	//qDebug() << __FILE__ << __LINE__  <<"gotPrintStrct"<< printStrct.object().value("XMLSTRCT").toString();
	report->printExec(true, !showDialog, "printerName");
}

void PrintController::setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage)
{
	//qDebug() << __FILE__ << __LINE__  << paramName << recNo << reportPage;

	//qDebug() << reportData.at(recNo).toObject().value(paramName);
	if(fieldsValues.contains(paramName)){
		if(paramName.compare("") == 0)
			paramValue = Controller::Get()->toString(paramName,fieldsValues.value(paramName)) ;
		paramValue = Controller::Get()->toString(paramName,fieldsValues.value(paramName)) ;
		}
	else if(reportData.at(recNo).toObject().value(paramName) != QJsonValue::Undefined){

		paramValue =reportData.at(recNo).toObject().value(paramName).toString();
		}


}

