#include "printcontroller.h"
#include "controller.h"


PrintController::PrintController(QObject *parent) : QObject(parent)
{
	report = new QtRPT(this);
}
PrintController* PrintController::p_instance = 0;
PrintController* PrintController::Get()
{
	if (p_instance == 0)
		p_instance = new PrintController();

	return p_instance;
}
void PrintController::printEntity(QString id)
{
	//qDebug() << __FILE__ << __LINE__  <<"printEntity"<< id;
	QObject::connect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(gotPrintEntity(QJsonDocument)));
	Controller::Get()->getDoc(id);
}


void PrintController::gotPrintEntity(QJsonDocument document)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(gotPrintEntity(QJsonDocument)));

	this->printDocumnet = document;
	QString documentID = "PrintStructure::"+document.object().value("document_id").toString().split("::")[0];
	getFieldstoValueMap(this->printDocumnet.object());
	QObject::connect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(gotPrintStrct(QJsonDocument)));
	//qDebug() << __FILE__ << __LINE__  <<"gotPrintEntity"<< documentID;
	Controller::Get()->getDoc(documentID);

}
void PrintController::getFieldstoValueMap(QJsonObject entity)
{

	foreach(QJsonValue fv,entity.value("Fields").toArray()){
		foreach(QJsonValue fvvapn,fv.toArray()){
			QStringList keys;

			keys = fvvapn.toObject().keys();
			//qDebug() << __FILE__ << __LINE__  << fvvapn.toObject() << keys;
			foreach(QString key,keys){

				foreach(QJsonValue value,fvvapn.toObject().value(key).toArray())
					{

					if(value.isString())
						fieldsValues.insert(key,value.toString());
					else if(value.isObject()){
						if(value.toObject().value("Value") != QJsonValue::Undefined)
							fieldsValues.insert(key,value.toObject().value("Value").toString());
						else if(value.toObject().value("merplyTabel") != QJsonValue::Undefined){
							//	qDebug() << value;
							if(value.toObject().value("merplyTabel").isArray()){

								foreach (QJsonValue row, value.toObject().value("merplyTabel").toArray()) {
									QString rowValue = row.toObject().value("Value").toString();
									if(!rowValue.isEmpty() && rowValue.compare("0") !=0)
										reportData.append(row);
									}
								//TODO : instead of Merging tables have better refrences

								//qDebug() << reportData;
								}
							}
						}
					}

				//qDebug() << __FILE__ << __LINE__  << fvvapn.toObject().value(key).toString();
				}


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
	//qDebug() << reportData.count();
	//qDebug() << __FILE__ << __LINE__  <<"gotPrintStrct"<< printStrct.object().value("XMLSTRCT").toString();
	report->printExec();
}

void PrintController::setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage)
{
	//qDebug() << __FILE__ << __LINE__  << paramName << recNo << reportPage;

	//qDebug() << reportData.at(recNo).toObject().value(paramName);
	if(fieldsValues.contains(paramName))
		paramValue = fieldsValues.value(paramName) ;
	else if(reportData.at(recNo).toObject().value(paramName) != QJsonValue::Undefined){

		paramValue =reportData.at(recNo).toObject().value(paramName).toString();
		}


}


