#include "structurevieweditsubfeild.h"
#include "structureviewedit.h"
#include "controller.h"
#include "prsistance.h"

StructureVieweditSubFeild::StructureVieweditSubFeild(QWidget *parent) : QWidget(parent)
{
	//this->setFixedWidth(150);


	this->setContentsMargins(0,0,0,0);
	this->setObjectName("StructureVieweditSubFeild");
	this->setStyleSheet("QWidget#StructureVieweditSubFeild{ border: 1px solid gray; border-top : 1px solid blue;}");

	layout = new QFormLayout(this);
	layout->setContentsMargins(0,0,5,0);
	layout->setSpacing(1);
	//layout->setMargin(0);
	layout->setAlignment(Qt::AlignLeft);
	//layout->setHorizontalSpacing(1);
	//layout->setRowWrapPolicy();
	//this->setAutoFillBackground(true);
	//layout->setRowWrapPolicy(QFormLayout::DontWrapRows);
	//layout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
	layout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
	layout->setLabelAlignment(Qt::AlignLeft);
	this->filled = false;

	preview = new QWidget();
	preview->setContentsMargins(0,0,0,0);
	//preview->setMinimumHeight(35);
	preview->setObjectName("preview");
	previewLayout = new QHBoxLayout(preview);
	previewLayout->setContentsMargins(0,0,0,0);
	previewLayout->setSpacing(0);
	previewLayout->setMargin(1);
	//this->setStyleSheet();
	layout->addRow(preview);

}


void StructureVieweditSubFeild::fillTypeFields(QString type,QJsonValue fieldVS)
{
	//qDebug() << "fffield" << fieldVS;
	this->filled = true;
	this->type = type;
	if(fieldVS.isObject())
		this->fieldVS = fieldVS;

	ERPComboBox* typeSelect = new ERPComboBox(0);
	QStringList types;
	types << "Index"<<"Text"<< "Refrence" << "Fixed" << "Table";
	typeSelect->addItems(types);
	typeSelect->setCurrentIndex(types.indexOf(type));
	layout->addRow(new QLabel(tr("Data Type")), typeSelect);

	QObject::connect(typeSelect,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateFields(QString)));





	if(type.compare("Refrence") == 0){
		Source = new ERPComboBox(0);
		Source->addItems(Controller::Get()->getListItems("ViewStructure","SPLIT(META("+Controller::Get()->getDatabaseName()+").id,\"ViewStructure::\")[1] ","default.Type =\"Entity\""));
		layout->addRow(new QLabel(tr("Source ")), Source);

		Select = new ERPComboBox(0);
		//Select->setText(fieldVS.toObject().value("Select").toString());
		layout->addRow(new QLabel(tr("Select ")), Select);

		Editable = new QCheckBox(0);
		Editable->setChecked(fieldVS.toObject().value("Editable").toString().compare("true") ==0);
		layout->addRow(new QLabel(tr("Editable ")), Editable);

		QObject::connect(Source,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateSelect(QString)));
		QObject::connect(Select,SIGNAL(currentIndexChanged(QString)),this,SIGNAL(changed()));

		updateSelect(Source->currentText());

		}
	else if(type.compare("Text") == 0){

		defaultValue = new QLineEdit(0);
		defaultValue->setText(fieldVS.toObject().value("Default").toString());
		layout->addRow(new QLabel(tr("Default ")), defaultValue);
		}
	else if(type.compare("Fixed") == 0){

		defaultValue = new QLineEdit(0);
		defaultValue->setText(fieldVS.toObject().value("Default").toString());
		layout->addRow(new QLabel(tr("Default ")), defaultValue);
		}
	else if(type.compare("Index") == 0){
		Source = new ERPComboBox(0);
		//Source->setText(fieldVS.toObject().value("Source").toString());
		layout->addRow(new QLabel(tr("Source ")), Source);

		Select = new ERPComboBox(0);
		//	Select->setText(fieldVS.toObject().value("Select").toString());
		layout->addRow(new QLabel(tr("Select ")), Select);
		}
	else if(type.compare("Table") == 0){
		tableEdit = new StructureVieweditSubFeildTable(this,fieldVS.toObject());
		QObject::connect(tableEdit,SIGNAL(tableChanged()),this,SIGNAL(changed()));

		layout->addRow("Tabel",tableEdit);


		}
	previewLayout->addWidget(new SubFieldUI(0,this->save()));
//	qDebug() <<this->save();
}

QJsonObject StructureVieweditSubFeild::save()
{
	QJsonObject saveObject;
	if(!this->type.isEmpty() && filled)
		{
		saveObject.insert("Type",type);
		if(type.compare("Refrence") == 0){
			saveObject.insert("Select",Select->currentText());
			saveObject.insert("Source",Source->currentText());
			saveObject.insert("Editable",Editable->isChecked());

			}
		else if(type.compare("Text") == 0){
			if(!defaultValue->text().isEmpty())
				saveObject.insert("Default",defaultValue->text());
			}
		else  if(type.compare("Fixed") == 0){
			if(!defaultValue->text().isEmpty())
				saveObject.insert("Default",defaultValue->text());
			}
		else  if(type.compare("Index") == 0){
			saveObject.insert("Select",Select->currentText());
			saveObject.insert("Source",Source->currentText());
			}
		else if(type.compare("Table") == 0){
			//qDebug() << tableEdit->save();
			saveObject = tableEdit->save();
			}
		}
	return saveObject;
}

void StructureVieweditSubFeild::updateFields(QString type)
{
	QList<QWidget *> Widgets = this->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		if(child != NULL && child->objectName().compare("preview") !=0 ){
			layout->removeWidget(child);
			child->setHidden(true);
			//child->setParent(0);
			child->deleteLater();
			}
		}

	this->fillTypeFields(type,this->fieldVS);
	emit changed();
}

void StructureVieweditSubFeild::updateSelect(QString entity)
{
	Select->addItems(Controller::Get()->getFields(entity));

}

void StructureVieweditSubFeild::paintEvent(QPaintEvent * event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(event);
}


