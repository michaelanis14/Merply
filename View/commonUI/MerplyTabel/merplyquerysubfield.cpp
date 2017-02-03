#include "merplyquerysubfield.h"
#include "controller.h"

MerplyQuerySubField::MerplyQuerySubField(QJsonObject strct, QWidget *parent) : QWidget(parent)
{
	this->setContentsMargins(0,0,0,0);
	this->strct = strct;
	layout = new QFormLayout(this);
	//this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setMargin(0);
	this->setLayout(layout);

	if(!strct.value("Source").toString().isEmpty() && strct.value("Source").toString().compare("_") != 0){
		if(!strct.value("Select").toString().isEmpty() && strct.value("Select").toString().compare("ALL") == 0){
			MerplyQueryUI* q= new MerplyQueryUI(this);
			q->fillDocumentID(strct.value("Source").toString());
			layout->addRow((strct.value("Label").toString()),q);
			field = q;
			}

		else{

			combox = new ERPComboBox(this,false);
			layout->addRow((strct.value("Label").toString()),combox);
			field = combox;

			if(strct.value("Editable").toString().compare("false") == 0)
				combox->setEditable(false);

			QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QVector<QJsonDocument>)),this,SLOT(refrenceData(QVector<QJsonDocument>)));
			Controller::Get()->getJsonEntityFieldsList(strct.value("Source").toString(),strct.value("Select").toString(),strct.value("Condition").toString());
			}
		}
}

QString MerplyQuerySubField::getValue()
{
	QString where = "";
	//qDebug() << __FILE__ << __LINE__  << field->metaObject()->className();
	if(QString(field->metaObject()->className()).compare("ERPComboBox") == 0 ){
		if(((ERPComboBox*)field)->currentIndex() > 0){
			//	save += component.name;
			if(strct.value("BeforFilter") != QJsonValue::Undefined)
				where += this->strct.value("BeforFilter").toString();
			if(strct.value("matchID") != QJsonValue::Undefined)
				where += ((ERPComboBox*)field)->getKey();
			else where += ((QComboBox*)field)->currentText();
			if(strct.value("AfterFilter")!= QJsonValue::Undefined)
				where += this->strct.value("AfterFilter").toString();
			//qDebug() << __FILE__ << __LINE__  << where;
			}
		}
	else if(QString(field->metaObject()->className()).compare("MerplyQueryUI") == 0 ){
		qDebug() << __FILE__ << __LINE__  << "TODO";
		}
	return where;
}

void MerplyQuerySubField::refrenceData(QVector<QJsonDocument> items)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotJsonListData(QVector<QJsonDocument>)),this,SLOT(refrenceData(QVector<QJsonDocument>)));

	if(combox){
		combox->clear();
		QJsonObject v;
		v.insert("Key",0);
		v.insert("Value",0);
		QJsonObject vv;
		vv.insert("Value",v);
		items.insert(items.size(),QJsonDocument(vv));
		combox->addJsonItems(items);

		}
	//qDebug() << __FILE__ << __LINE__  << items;
}
