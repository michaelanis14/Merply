#include "merplyquerysubfield.h"
#include "datefilterui.h"
#include "controller.h"

MerplyQuerySubField::MerplyQuerySubField(QJsonObject strct, QWidget *parent) : QWidget(parent)
{
//	qDebug() << __FILE__ << __LINE__  <<strct;
	this->setContentsMargins(0,0,0,0);
	this->strct = strct;
	this->clmnNumber = strct.value("SubFields").toArray().first().toObject().value("clmnNumber").toString();

	layout = new QFormLayout(this);
	//this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setMargin(0);
	this->setLayout(layout);
	field = new QWidget;

	QString type =  strct.value("SubFields").toArray().first().toObject().value("Type").toString();
	label = strct.value("Label").toString();

	//qDebug() << __FILE__ << __LINE__  <<type <<strct;

	if(strct.value("clmn") != QJsonValue::Undefined){
		label = strct.value("Select").toString();
		QLineEdit* lineEdit = new QLineEdit();
		lineEdit->setObjectName(label);
		lineEdit->setContentsMargins(0,0,0,0);
		layout->addWidget(lineEdit);
		field = lineEdit;
		}
	else if(!strct.value("Source").toString().isEmpty() && strct.value("Source").toString().compare("_") != 0){
		if(!strct.value("Select").toString().isEmpty() && strct.value("Select").toString().compare("ALL") == 0){
			MerplyQueryUI* q= new MerplyQueryUI(this);
			q->fillDocumentID(strct.value("Source").toInt());
			layout->addRow((strct.value("Label").toString()),q);
			field = q;
			}

		else{
			combox = new ERPComboBox(this,false);
			layout->addRow((strct.value("Label").toString()),combox);
			field = combox;
			if(strct.value("Editable").toString().compare("false") == 0)
				combox->setEditable(false);
			QObject::connect(Controller::Get(),SIGNAL(gotSelectListData(QVector<QSqlRecord>)),this,SLOT(refrenceData(QVector<QJsonDocument>)));
			Controller::Get()->getJsonEntityFieldsList(strct.value("Source").toString(),strct.value("Select").toString(),strct.value("Condition").toString());
			}
		}

	else if(type.isEmpty() && strct.value("Type").toString().compare("ID") == 0){
		QLineEdit* lineEdit = new QLineEdit();
		lineEdit->setValidator( new QIntValidator(0, 1000000, this) );
		lineEdit->setObjectName("ID:"+strct.value("strct").toString());
		lineEdit->setContentsMargins(0,0,0,0);
		layout->addWidget(lineEdit);
		field = lineEdit;
		}
	else if(type.compare("Text") == 0
			|| type.compare("Serial") == 0
			){
		QLineEdit* lineEdit = new QLineEdit();
		lineEdit->setObjectName(label);
		lineEdit->setContentsMargins(0,0,0,0);
		layout->addWidget(lineEdit);
		field = lineEdit;
		}
	else if(type.compare("Date") == 0){
		DateFilterUI *date = new DateFilterUI(this);
		layout->addWidget(date);
		date->setObjectName(label);
		field = date;
		}
	else if(type.compare("Refrence") == 0){
		//qDebug() << __FILE__ << __LINE__  <<strct;
		QJsonObject subField = strct.value("SubFields").toArray().first().toObject();
		combox = new ERPComboBox(this,false);
		combox->setObjectName(label);
		layout->addWidget(combox);
		field = combox;
		if(strct.value("Editable").toString().compare("false") == 0)
			combox->setEditable(false);
		QObject::connect(Controller::Get(),SIGNAL(gotSelectListData(QVector<QSqlRecord>)),this,SLOT(refrenceData(QVector<QJsonDocument>)));
		Controller::Get()->getJsonEntityFieldsList(subField.value("Source").toString(),subField.value("Select").toString(),subField.value("Condition").toString());

		}

}

QString MerplyQuerySubField::getValue(QString entity)
{
	QString save = "";
	//qDebug() << __FILE__ << __LINE__  << field->metaObject()->className();


	if(QString(field->metaObject()->className()).compare("ERPComboBox") == 0 ){
		//	qDebug() << __FILE__ << __LINE__  << this->strct;
		if(((ERPComboBox*)field)->currentIndex() > 0){
			//	save += component.name;
			if(strct.value("BeforFilter") != QJsonValue::Undefined){

				if(strct.value("BeforFilter") != QJsonValue::Undefined)
					save += this->strct.value("BeforFilter").toString();
				if(strct.value("matchID") != QJsonValue::Undefined)
					save += ((ERPComboBox*)field)->getKey();
				else save += ((QComboBox*)field)->currentText();
				if(strct.value("AfterFilter")!= QJsonValue::Undefined)
					save += this->strct.value("AfterFilter").toString();
				}
			else if(strct.value("Type") == QJsonValue::Undefined){
				if(!entity.trimmed().isEmpty()){
					save +=QString(""+entity.trimmed()+".`").append(((QComboBox*)field)->objectName().append("`.`Key` Like '")).append(((ERPComboBox*)field)->getKey()).append("'");
					}
				else {
					save +="`"+((QComboBox*)field)->objectName().append("`.`Key` Like '").append(((ERPComboBox*)field)->getKey()).append("'");
					}
				}
			//qDebug() << __FILE__ << __LINE__  << where;
			}
		}

	else if(QString(field->metaObject()->className()).compare("MerplyQuerySubField") == 0 ){
		//	qDebug() <<"MerplyQuerySubField"<< strct.value("Entity").toString();
		QString where = ((MerplyQuerySubField*)field)->getValue(strct.value("Entity").toString());

		if(!where.trimmed().isEmpty()){
			if(!save.trimmed().isEmpty())
				save.append(" AND ");
			save += where;
			}
		}
	else if(QString(field->metaObject()->className()).compare("QLineEdit") == 0 ){
		//	save += component.name;
		if(!((QLineEdit*)field)->text().trimmed().isEmpty()){
			if(((QLineEdit*)field)->objectName().contains("ID:")){
				if(!entity.trimmed().isEmpty()){
					//qDebug() << __FILE__ << __LINE__  << entity.trimmed();
					save += "META(`"+QString(DATABASE)+"`).id LIKE '"+entity.replace("`","")+"::"+((QLineEdit*)field)->text()+"'";
					}
				else {
					save += "META(`"+QString(DATABASE)+"`).id LIKE '"+((QLineEdit*)field)->objectName().split(":")[1]+"::"+((QLineEdit*)field)->text()+"'";
					}
				}
			else if(!entity.trimmed().isEmpty()){
				//qDebug() << __FILE__ << __LINE__  << entity.trimmed();
				save += QString("to_string("+entity.trimmed()+".`"+((QLineEdit*)field)->objectName()+"`)").append(QString("LIKE  ")).append("'"+((QLineEdit*)field)->text().trimmed().replace("٪","")+"'");
				}
			else {
				if(strct.value("clmn") != QJsonValue::Undefined)
					save += QString("`"+this->clmnNumber+"` ").append(QString("LIKE  ")).append("'"+((QLineEdit*)field)->text().trimmed().replace("٪","")+"'");
				else
					save += QString("`"+this->clmnNumber+"` ").append(QString("LIKE  ")).append("'"+((QLineEdit*)field)->text().trimmed().replace("٪","")+"'");
				}
			}
		//	save =" ";
		}
	else if(QString(field->metaObject()->className()).compare("QTextEdit") == 0 ){
		if(!((QTextEdit*)field)->toPlainText().trimmed().isEmpty())
			save =((QTextEdit*)field)->toPlainText();
		}
	else if(QString(field->metaObject()->className()).compare("QCheckBox") == 0 ){
		//	save = component.name;
		save =((QCheckBox*)field)->isChecked();
		//	save ="";
		}
	else if(QString(field->metaObject()->className()).compare("merplyTabelView") == 0){
		//	save = component.name;
		//		save =((merplyTabelView*)field)->save("this->key");
		QJsonObject tblSave = ((merplyTabelView*)field)->save();
		if(!tblSave.isEmpty())
			//	save = tblSave;
			save ="";
		}
	else if(QString(field->metaObject()->className()).compare("DateFilterUI") == 0){

		if(!save.trimmed().isEmpty())
			save.append(" AND ");

		//qDebug() << ((DateFilterUI*)field)->to->dateTime().toMSecsSinceEpoch()  <<((DateFilterUI*)field)->from->dateTime().toMSecsSinceEpoch() ;
		//	save += "STR_TO_MILLIS(`d`.`"+((DateFilterUI*)field)->objectName() +"`) BETWEEN STR_TO_MILLIS('"+QString::number(((DateFilterUI*)field)->from->dateTime().toMSecsSinceEpoch())+"') AND STR_TO_MILLIS('"+QString::number(((DateFilterUI*)field)->to->dateTime().toMSecsSinceEpoch())+"')";
		//save =((DateFilterUI*)field)->dateTime().toString(Qt::DefaultLocaleShortDate);
		//qDebug() << save;

		save += "STR_TO_MILLIS(`"+((DateFilterUI*)field)->objectName() +"`) BETWEEN STR_TO_MILLIS('"+QString(((DateFilterUI*)field)->from->dateTime().toString(Qt::ISODate))+"') AND STR_TO_MILLIS('"+QString(((DateFilterUI*)field)->to->dateTime().toString(Qt::ISODate))+"')";

		}
	else if(QString(field->metaObject()->className()).compare("MerplyQueryUI") == 0 ){
		//qDebug() << __FILE__ << __LINE__  << "TODO";
		//qDebug() << strct.value("Entity").toString();
		save += ((MerplyQueryUI*)field)->getFields(strct.value("Entity").toString());
		}
	return save;
}

int MerplyQuerySubField::getLayoutCount()
{
	return this->layout->count();
}

void MerplyQuerySubField::refrenceData(QVector<QJsonDocument> items)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotSelectListData(QVector<QSqlRecord>)),this,SLOT(refrenceData(QVector<QJsonDocument>)));

	if(combox){
		combox->clear();
		QJsonObject v;
		v.insert("Key",0);
		v.insert("Value",0);
		QJsonObject vv;
		vv.insert("Value",v);
		items.insert(0,QJsonDocument(vv));
		combox->addJsonItems(items);

		}
	//qDebug() << __FILE__ << __LINE__  << items;
}
