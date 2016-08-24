#include "structurevieweditsubfeildtablecolumn.h"
#include "structureviewedit.h"
#include "structureviewgroupsui.h"
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

	//	qDebug()  << clmn;
	type = new ERPComboBox(0);
	QStringList typs;
	typs << "Database" << "Text";
	type->addItems(typs);
	type->setCurrentIndex(typs.indexOf(clmn.value("Type").toString()));
	layout->addRow(new QLabel(tr("Type ")), type);




	Source = new ERPComboBox(0);
	layout->addRow(new QLabel(tr("Source ")), Source);
	QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(selectData(QList<QJsonDocument>)));
	Controller::Get()->getJsonList("ViewStructure","Title","default.Type =\"Entity\"");

	Select = new ERPComboBox(0);
	//Select->setText(fieldVS.toObject().value("Select").toString());
	layout->addRow(new QLabel(tr("Select ")), Select);


	initFilterWidget();

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


}

QJsonObject StructureVieweditSubFeildTableColumn::save()
{
	QJsonObject clmn;
	clmn.insert("Header",header->text());
	clmn.insert("Type",type->currentText());
	if(type->currentIndex() == 0){
		clmn.insert("Source",Source->getKey());
		clmn.insert("Select",Select->currentText());
		if(filterOn->currentIndex() ==1){
			clmn.insert("LocalFilter",localFilter->getKey());
			clmn.insert("EntityFilter",entityFilter->currentText());
			}
		else if(filterOn->currentIndex() ==2){
			clmn.insert("LocalSource",true);
			}
		}

	else clmn.insert("Default",defaultValue->text());

	return clmn;
}

ERPComboBox* StructureVieweditSubFeildTableColumn::getSource() const
{
	return Source;
}

void StructureVieweditSubFeildTableColumn::fill(QJsonObject clmn)
{
	this->type->setCurrentIndex(type->getItemsText().indexOf(clmn.value("Type").toString().trimmed()));
	this->Source->setCurrentIndex(Source->keys.indexOf(clmn.value("Source").toString().trimmed()));
	updateSelect(Source->currentText());
	this->Select->setCurrentIndex(Select->getItemsText().indexOf(clmn.value("Select").toString().trimmed()));

	if(clmn.value("LocalFilter") != QJsonValue::Undefined){
		filterOn->setCurrentIndex(1);
		localFilter->setCurrentIndex(localFilter->keys.indexOf(clmn.value("LocalFilter").toString()));
		//localFilterChanged(0);
		entityFilter->setCurrentText(clmn.value("EntityFilter").toString());
		}
	else if(clmn.value("LocalSource") != QJsonValue::Undefined){
		filterOn->setCurrentIndex(2);
		}
	//qDebug() << clmn;
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

void StructureVieweditSubFeildTableColumn::updateSelect(QString )
{
	QObject::connect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateSelectData(QList<QString>)));
	Controller::Get()->getFields(Source->getKey());
}
void StructureVieweditSubFeildTableColumn::updateSelectData(QList<QString> fields)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateSelectData(QList<QString>)));
	Select->clear();
	Select->addItems(fields);
}

void StructureVieweditSubFeildTableColumn::selectData(QList<QJsonDocument> items)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(selectData(QList<QJsonDocument>)));
	Source->clear();
	Source->addJsonItems(items);
}

void StructureVieweditSubFeildTableColumn::filterOnChanged(int index)
{
	if(filterWidget){
		if(index == 0){
			localFilterWidget->setHidden(true);
			}
		else if(index == 1){

			QObject::connect(StructureViewGroupsUI::GetUI(),SIGNAL(gotSourcesJson(QList<QJsonDocument>)),this,SLOT(fillLocalFilter(QList<QJsonDocument>)));
			StructureViewGroupsUI::GetUI()->getTableFields(Source);

			//entityFilter->addItems(Select->getItemsText());
			//entityFilter->adjustSize();

			}
		else if(index == 2){
			localFilterWidget->setHidden(true);
			}
		}
}

void StructureVieweditSubFeildTableColumn::fillLocalFilter(QList<QJsonDocument> feilds)
{

	QObject::disconnect(StructureViewGroupsUI::GetUI(),SIGNAL(gotSourcesJson(QList<QJsonDocument>)),this,SLOT(fillLocalFilter(QList<QJsonDocument>)));
	if(localFilterWidget){
		localFilter->clear();
		localFilter->addJsonItems(feilds);
		localFilterChanged(0);
		localFilterWidget->setHidden(false);
		}
}


void StructureVieweditSubFeildTableColumn::initFilterWidget()
{
	filterWidget = new QWidget(0);
	filterWidget->setContentsMargins(0,0,0,0);
	filterWidget->setAutoFillBackground(true);
	filterWidget->setObjectName("filterWidget");
	filterWidgetLayout = new QFormLayout(filterWidget);
	filterWidgetLayout->setFormAlignment(Qt::AlignLeft);
	filterWidgetLayout->setLabelAlignment(Qt::AlignLeft);
	filterWidgetLayout->setSpacing(0);
	filterWidgetLayout->setMargin(0);

	filterOn = new ERPComboBox(filterWidget);
	filterWidgetLayout->addRow(new QLabel(tr("Match on    ")), filterOn);
	QStringList filterItems;
	filterItems <<tr("None")<< tr("Local Match") << tr("Local Source");
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
	QObject::connect(localFilter,SIGNAL(currentIndexChanged(int)),this,SLOT(localFilterChanged(int)));
	localFilterWidget->setHidden(true);
	filterWidgetLayout->addRow(localFilterWidget);

	layout->addRow(filterWidget);
}
void StructureVieweditSubFeildTableColumn::localFilterChanged(int)
{

	QObject::connect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updatelocalFilterData(QList<QString>)));
	Controller::Get()->getFields(this->Source->getKey());
}

void StructureVieweditSubFeildTableColumn::updatelocalFilterData(QList<QString> fields)
{
	//qDebug() << "Changed" << fields;
	QObject::disconnect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updatelocalFilterData(QList<QString>)));
	entityFilter->clear();
	//entityFilter->addItem("ID");
	entityFilter->addItems(fields);
}

