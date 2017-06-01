#include "structureviewrefrence.h"


#include "controller.h"

StructureViewRefrence::StructureViewRefrence(QWidget *parent,QJsonObject strct,QStringList matchList) : QWidget(parent)
{
	this->setContentsMargins(2,2,2,2);
	this->strct = strct;
	this->matchList = matchList;

	layout = new QFormLayout(this);
	layout->setContentsMargins(2,2,2,2);
	layout->setSpacing(0);
	layout->setMargin(0);

	source = new ERPComboBox(0);
	layout->addRow(new QLabel(tr("Source ")), source);
//	QObject::connect(Controller::Get(),SIGNAL(gotSelectListData(QVector<QSqlRecord>)),this,SLOT(gotSourceData(QVector<QJsonDocument>)));
//	Controller::Get()->getJsonList("ViewStructure","Title","`"+QString(DATABASE).append("`.Type =\"Entity\""));
	gotSourceData();
	getItemsbtn = new QPushButton("Get Items");
	QObject::connect(getItemsbtn,SIGNAL(clicked(bool)),this,SLOT(getItemsbtnClicked(bool)));
	layout->addWidget(getItemsbtn);
	//qDebug() << "addStrRefrence";

	foreach (QJsonValue fieldVS, strct.value("RefrenceSubFields").toArray()) {

		StructureViewRefrenceSubField* fieldSubField= new StructureViewRefrenceSubField(0,fieldVS.toObject(),this->matchList);
		sVRList << fieldSubField;
		this->layout->addWidget(fieldSubField);
		}
}

QJsonObject StructureViewRefrence::save()
{
	QJsonObject save;
	save.insert("Source",source->getKey());
	QJsonArray refrenceSubFieldArray;
	foreach(StructureViewRefrenceSubField* fieldSubField,sVRList){
		refrenceSubFieldArray << fieldSubField->save();
		}
	save.insert("RefrenceSubFields",refrenceSubFieldArray);
	return save;
}

void StructureViewRefrence::gotSourceData()
{
	//qDebug() << __FILE__ << __LINE__<< "gotSourceData" << items;
	//QObject::disconnect(Controller::Get(),SIGNAL(gotSelectListData(QVector<QSqlRecord>)),this,SLOT(gotSourceData(QVector<QJsonDocument>)));
	source->clear();

	source->addItems(Controller::Get()->getCachedViewStructureNames());
	if(strct.value("Source") != QJsonValue::Undefined){
		qDebug() << __FILE__ << __LINE__<< __func__ <<"DATABASE ERR";
//		source->setCurrentIndex(source->keys.indexOf(strct.value("Source").toString()));
		}
}

void StructureViewRefrence::getItemsbtnClicked(bool)
{
//	QObject::disconnect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateSelectData(QList<QString>)));
//	QObject::connect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateSelectData(QList<QString>)));
//	Controller::Get()->getFields(source->getKey());

	updateSelectData(Controller::Get()->getCachedViewStructureFieldsNames(source->getKey()));
}
void StructureViewRefrence::updateSelectData(QList<QString> fields)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateSelectData(QList<QString>)));
	foreach(QString field,fields){
		QJsonObject refFieldObj;
		refFieldObj.insert("Field",field);
		StructureViewRefrenceSubField* fieldSubField= new StructureViewRefrenceSubField(0,refFieldObj,this->matchList);
		sVRList << fieldSubField;
		this->layout->addWidget(fieldSubField);
		}
}

