

#include "structureviewgroupsui.h"
#include "structurevieweditsubfeild.h"
#include "structureviewedit.h"
#include "controller.h"
#include "prsistance.h"

StructureVieweditSubFeild::StructureVieweditSubFeild(QWidget *parent) : QWidget(parent)
{
	//this->setFixedWidth(150);


	this->setContentsMargins(0,0,0,0);
	this->setObjectName("StructureVieweditSubFeild");
	this->setStyleSheet("QWidget2#StructureVieweditSubFeild{ border: 1px solid gray; border-top : 1px solid blue;}");

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


	typeSelect = new ERPComboBox(0);
}


void StructureVieweditSubFeild::fillTypeFields(QString type,QJsonValue fieldVS,QStringList restrictedTypes)
{
	//qDebug() << "fffield" << fieldVS;
	this->filled = true;
	this->type = type;
	this->restrictedTypes = restrictedTypes;
	if(fieldVS.isObject())
		this->fieldVS = fieldVS;

	QStringList types;
	if(!restrictedTypes.isEmpty()){
		types << restrictedTypes;
		}else
		types << "Index"<<"Text"<< "Refrence" <<"Date"<< "Fixed" <<"Serial" << "Table";
	typeSelect->addItems(types);
	typeSelect->setCurrentIndex(types.indexOf(type));
	//if(restrictedTypes.isEmpty())
	layout->addRow(new QLabel(tr("Data Type")), typeSelect);


	QObject::connect(typeSelect,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateFields(QString)));




	if(type.compare("Link") == 0){
		title = new QLineEdit;

		if(!fieldVS.toObject().value("Title").toString().isEmpty())
			title->setText(fieldVS.toObject().value("Title").toString());
		else title->setText(tr("New"));

		layout->addRow(new QLabel(tr("Title")), title);

		Source = new ERPComboBox(0);

		if(!fieldVS.toObject().value("Source").toString().isEmpty())
			Source->setCurrentText(fieldVS.toObject().value("Source").toString());
		layout->addRow(new QLabel(tr("Source ")), Source);
		QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(gotSourceData(QList<QJsonDocument>)));
		Controller::Get()->getJsonList("ViewStructure","Title","default.Type =\"Entity\"");


		Select = new ERPComboBox(0);
		Select->addItems(QStringList() << "Index" <<"New");
		if(!fieldVS.toObject().value("Select").toString().isEmpty())
			Select->setCurrentText(fieldVS.toObject().value("Select").toString());
		layout->addRow(new QLabel(tr("Action ")), Select);


		//QObject::connect(Source,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateSelect(QString)));
		QObject::connect(Select,SIGNAL(currentIndexChanged(QString)),this,SIGNAL(changed()));
		QObject::connect(title,SIGNAL(textChanged(QString)),this,SIGNAL(changed()));

		}
	else if(type.compare("Refrence") == 0){
		Source = new ERPComboBox(0);
		layout->addRow(new QLabel(tr("Source ")), Source);
		QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(gotSourceData(QList<QJsonDocument>)));
		Controller::Get()->getJsonList("ViewStructure","Title","default.Type =\"Entity\"");


		Select = new ERPComboBox(0);
		//
		layout->addRow(new QLabel(tr("Select ")), Select);

		Editable = new QCheckBox(0);
		Editable->setChecked(fieldVS.toObject().value("Editable").toString().compare("true") ==0);
		layout->addRow(new QLabel(tr("Editable ")), Editable);


		initFilterWidget();



		QObject::connect(Source,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateSelect(QString)));
		QObject::connect(Select,SIGNAL(currentIndexChanged(QString)),this,SIGNAL(changed()));


		if(fieldVS.toObject().value("Source") != QJsonValue::Undefined){
			//qDebug() << "Source" << fieldVS.toObject().value("Source").toString();
			Source->setCurrentText(fieldVS.toObject().value("Source").toString());
			}
		else {
			updateSelect(Source->currentText());
			}
		if(fieldVS.toObject().value("Select") != QJsonValue::Undefined){
			//qDebug() << "Select" << fieldVS.toObject().value("Select").toString();
			Select->setCurrentText(fieldVS.toObject().value("Select").toString());
			}
		if(fieldVS.toObject().value("LocalFilter") != QJsonValue::Undefined && fieldVS.toObject().value("LocalFilter").toBool()){
			filterOn->setCurrentIndex(1);
			filterOnChanged(1);
			localFilter->setCurrentText(fieldVS.toObject().value("Local").toString());
			entityFilter->setCurrentText(fieldVS.toObject().value("Entity").toString());
			}


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
		tableEdit = new StructureVieweditSubFeildTable(this);
		tableEdit->fill(fieldVS.toObject());
		QObject::connect(tableEdit,SIGNAL(tableChanged()),this,SIGNAL(changed()));
		layout->addRow("Tabel",tableEdit);
		}
	else if(type.compare("Serial") == 0){
		defaultValue = new QLineEdit(0);
		defaultValue->setText(fieldVS.toObject().value("startNum").toString());
		layout->addRow(new QLabel(tr("Start Number")), defaultValue);
		}
	else if(type.compare("Date") == 0){
		date = new QDateEdit(this);
		date->setDate(QDate::fromString(fieldVS.toObject().value("date").toString(),"dd-MMM-yyyy"));
		layout->addRow("Date", date);
		}

	mandatory = new QCheckBox(this);
	if(fieldVS.toObject().value("Mandatory").toBool())
		mandatory->setChecked(true);
	layout->addRow("Mandatory", mandatory);
	previewLayout->addWidget(new SubFieldUI(0,"V",this->save()));
	//	qDebug() <<this->save();
}

QJsonObject StructureVieweditSubFeild::save()
{
	QJsonObject saveObject;
	if(!this->type.isEmpty() && filled)
		{
		//qDebug() << this->type << filled << Link;
		saveObject.insert("Type",type);
		saveObject.insert("Mandatory",mandatory->isChecked());
		if(type.compare("Link") == 0){
			saveObject.insert("Select",Select->currentText());
			saveObject.insert("Source",Source->getKey());
			saveObject.insert("Title",title->text());
			}

		else if(type.compare("Refrence") == 0){
			qDebug() <<"Save Refrence subfield:206"<< Select->getKey() << Source->getKey();
			saveObject.insert("Select",Select->currentText());
			saveObject.insert("Source",Source->getKey());
			saveObject.insert("Editable",Editable->isChecked());
			if(filterOn->currentIndex() == 1){
				saveObject.insert("LocalFilter",true);
				saveObject.insert("Local",localFilter->currentText());
				saveObject.insert("Entity",entityFilter->currentText());
				}
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
			saveObject.insert("Source",Source->getKey());
			}
		else if(type.compare("Table") == 0){
			//qDebug() << tableEdit->save();
			saveObject = tableEdit->save();
			}
		else  if(type.compare("Serial") == 0){
			if(!defaultValue->text().isEmpty())
				saveObject.insert("startNum",defaultValue->text().toInt());
			}
		else if(type.compare("Date") == 0){
			//qDebug() << date->date().toString(Qt::DefaultLocaleShortDate);
			//	saveObject.insert("date",date->date().toString(Qt::DefaultLocaleShortDate));
			}
		}
	return saveObject;
}

QString StructureVieweditSubFeild::getType()
{
	return this->type;
}

StructureVieweditSubFeildTable* StructureVieweditSubFeild::getTableEdit() const
{
	return tableEdit;
}

void StructureVieweditSubFeild::initFilterWidget()
{
	filterWidget = new QWidget(0);
	filterWidget->setContentsMargins(0,0,0,0);
	filterWidget->setObjectName("filterWidget");
	filterWidgetLayout = new QFormLayout(filterWidget);
	filterWidgetLayout->setFormAlignment(Qt::AlignLeft);
	filterWidgetLayout->setLabelAlignment(Qt::AlignLeft);
	filterWidgetLayout->setSpacing(0);
	filterWidgetLayout->setMargin(0);

	filterOn = new ERPComboBox(filterWidget);
	filterWidgetLayout->addRow(new QLabel(tr("Filter on    ")), filterOn);
	QStringList filterItems;
	filterItems <<tr("none")<< tr("local match") << tr("Other");
	filterOn->addItems(filterItems);
	//fieldsWidgetLayout->addWidget(filterWidget);
	QObject::connect(filterOn,SIGNAL(currentIndexChanged(int)),this,SLOT(filterOnChanged(int)));


	localFilterWidget = new QWidget(0);
	localFilterWidget->setAutoFillBackground(true);
	localFilterWidget->setContentsMargins(0,0,0,0);
	localFilterWidget->setObjectName("localFilterWidget");
	localFilterWidgetLayout = new QFormLayout(localFilterWidget);
	localFilterWidgetLayout->setAlignment(Qt::AlignLeft);
	//localFilterWidgetLayout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
	localFilterWidgetLayout->setLabelAlignment(Qt::AlignLeft);
	localFilterWidgetLayout->setSpacing(0);
	localFilterWidgetLayout->setMargin(0);

	localFilter = new ERPComboBox(0);
	localFilterWidgetLayout->addRow(new QLabel(tr("Local Filter")), localFilter);
	entityFilter = new ERPComboBox(0);
	localFilterWidgetLayout->addRow(new QLabel(tr("Entity Filter")), entityFilter);
	//QObject::connect(localFilter,SIGNAL(currentIndexChanged(int)),this,SLOT(filterOnChanged(int)));
	localFilterWidget->setHidden(true);
	filterWidgetLayout->addRow(localFilterWidget);

	layout->addRow(filterWidget);
}

void StructureVieweditSubFeild::updateFields(QString type)
{
	this->type = type;
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

	this->fillTypeFields(type,this->fieldVS,this->restrictedTypes);
	emit changed();
}

void StructureVieweditSubFeild::updateSelect(QString)
{
	QObject::connect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateSelectData(QList<QString>)));
	Controller::Get()->getFields(Source->getKey());


}

void StructureVieweditSubFeild::updateSelectData(QList<QString> fields)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateSelectData(QList<QString>)));
	Select->clear();
	Select->addItems(fields);
}

void StructureVieweditSubFeild::gotSourceData(QList<QJsonDocument> items)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(gotSourceData(QList<QJsonDocument>)));
	Source->clear();
	Source->addJsonItems(items);
}

void StructureVieweditSubFeild::filterOnChanged(int index)
{
	if(filterWidget){
		if(index == 0){
			localFilterWidget->setHidden(true);
			}
		else if(index == 1){
			QObject::connect(StructureViewGroupsUI::GetUI(),SIGNAL(gotFieldsNames(QStringList)),this,SLOT(fillLocalFilter(QStringList)));
			StructureViewGroupsUI::GetUI()->getFeildsNames();
			entityFilter->addItems(Select->getItemsText());
			entityFilter->adjustSize();
			localFilterWidget->setHidden(false);
			}
		else if(index == 2){
			localFilterWidget->setHidden(true);
			}
		}
}

void StructureVieweditSubFeild::fillLocalFilter(QStringList feilds)
{
	QObject::disconnect(StructureViewGroupsUI::GetUI(),SIGNAL(gotFieldsNames(QStringList)),this,SLOT(fillLocalFilter(QStringList)));

	if(localFilterWidget){
		localFilter->clear();
		localFilter->addItems(feilds);
		}
}



void StructureVieweditSubFeild::paintEvent(QPaintEvent * event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(event);
}


