#include "structureviewrefrencesubfield.h"
#include <QDebug>

StructureViewRefrenceSubField::StructureViewRefrenceSubField(QWidget *parent,QJsonObject strct,QStringList fieldsName) : QWidget(parent)
{
	this->setContentsMargins(0,0,0,0);
	layout = new QHBoxLayout(this);
	this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setMargin(0);
	FieldNamelbl = new QLabel(strct.value("Field").toString());
	layout->addWidget(FieldNamelbl);
	combox = new ERPComboBox(this,false);
	combox->addItems(fieldsName);
	layout->addWidget(combox);
	if(strct.value("RefrenceValue") != QJsonValue::Undefined){
	//	qDebug() << combox->getItemsText().indexOf(strct.value("RefrenceValue").toString()) << strct.value("RefrenceValue").toString() <<fieldsName;
		combox->setCurrentText(strct.value("RefrenceValue").toString());
	// 	combox->setCurrentIndex(combox->getItemsText().indexOf(strct.value("RefrenceValue").toString()));
		}
}

QJsonObject StructureViewRefrenceSubField::save()
{
	QJsonObject save;
	save.insert("Field",FieldNamelbl->text());
	save.insert("RefrenceValue",combox->currentText());
	return save;
}
