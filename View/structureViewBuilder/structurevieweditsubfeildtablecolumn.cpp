#include "structurevieweditsubfeildtablecolumn.h"
#include "structureviewedit.h"
#include "controller.h"

StructureVieweditSubFeildTableColumn::StructureVieweditSubFeildTableColumn(QWidget *parent,QJsonObject clmn) : QWidget(parent)
{
	this->setContentsMargins(0,0,5,0);
	this->setObjectName("StructureVieweditSubFeildTableColumn");
	this->clmn = clmn;
	layout = new QFormLayout(this);
	layout->setContentsMargins(0,0,5,0);
	layout->setSpacing(1);
	layout->setAlignment(Qt::AlignLeft);
	layout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
	layout->setLabelAlignment(Qt::AlignLeft);


	header = new QLineEdit(0);
	if(!clmn.value("Header").toString().isEmpty())
		header->setText(clmn.value("Header").toString());
	else header->setText("New Header");
	layout->addRow(new QLabel(tr("Header ")), header);


	type = new ERPComboBox(0);
	QStringList typs;
	typs << "Database" << "Text";
	type->addItems(typs);
	type->setCurrentIndex(typs.indexOf(clmn.value("Type").toString()));
	layout->addRow(new QLabel(tr("Type ")), type);




	Source = new ERPComboBox(0);
	Source->addItems(Controller::Get()->getListItems("ViewStructure","SPLIT(META("+Controller::Get()->getDatabaseName()+").id,\"ViewStructure::\")[1] ","default.Type =\"Entity\""));
	layout->addRow(new QLabel(tr("Source ")), Source);

	Select = new ERPComboBox(0);
	//Select->setText(fieldVS.toObject().value("Select").toString());
	layout->addRow(new QLabel(tr("Select ")), Select);




	defaultValue = new QLineEdit(0);
	defaultValue->setVisible(false);
	defaultValue->setText(clmn.value("Default").toString());
	layout->addRow(new QLabel(tr("Default ")), defaultValue);


	QObject::connect(type,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateFields(QString)));
	type->setCurrentIndex(1);
	this->updateFields(type->currentText());
	QObject::connect(header,SIGNAL(textEdited(QString)),this,SIGNAL(columnChanged()));

	QObject::connect(Source,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateSelect(QString)));
	QObject::connect(Select,SIGNAL(currentIndexChanged(QString)),this,SIGNAL(columnChanged()));

	updateSelect(Source->currentText());


}

QJsonObject StructureVieweditSubFeildTableColumn::save()
{
	QJsonObject clmn;
	clmn.insert("Header",header->text());
	clmn.insert("Type",type->currentText());
	if(type->currentText().compare("Database") == 0){
		clmn.insert("Source",Source->currentText());
		clmn.insert("Select",Select->currentText());
		}
	else clmn.insert("Default",defaultValue->text());
	return clmn;
}

void StructureVieweditSubFeildTableColumn::updateFields(QString value)
{
	if(value.compare("Database") == 0){
		defaultValue->setVisible(false);
		layout->labelForField(defaultValue)->setVisible(false);
		Source->setVisible(true);
		layout->labelForField(Source)->setVisible(true);
		if(!clmn.value("Source").toString().isEmpty())
			Source->setCurrentText(clmn.value("Source").toString());

		Select->setVisible(true);
		layout->labelForField(Select)->setVisible(true);
		if(!clmn.value("Select").toString().isEmpty())
			Select->setCurrentText(clmn.value("Select").toString());
		}
	else{
		Source->setVisible(false);
		layout->labelForField(Source)->setVisible(false);
		Select->setVisible(false);
		layout->labelForField(Select)->setVisible(false);
		defaultValue->setVisible(true);
		layout->labelForField(defaultValue)->setVisible(true);
		if(!clmn.value("Default").toString().isEmpty())
			defaultValue->setText(clmn.value("Default").toString());

		}

	emit columnChanged();
}

void StructureVieweditSubFeildTableColumn::updateSelect(QString entity)
{
	Select->addItems(Controller::Get()->getFields(entity));

}


