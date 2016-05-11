

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


void StructureVieweditSubFeild::fillTypeFields(QString type,QJsonValue fieldVS,bool links)
{
	//qDebug() << "fffield" << fieldVS;
	this->filled = true;
	this->type = type;
	this->links = links;
	if(fieldVS.isObject())
		this->fieldVS = fieldVS;

	ERPComboBox* typeSelect = new ERPComboBox(0);
	QStringList types;
	if(links)
		types << "Link";
	else
		types << "Index"<<"Text"<< "Refrence" << "Fixed" <<"Serial" << "Table";
	typeSelect->addItems(types);
	typeSelect->setCurrentIndex(types.indexOf(type));
	if(!links)
		layout->addRow(new QLabel(tr("Data Type")), typeSelect);


	QObject::connect(typeSelect,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateFields(QString)));



	if(links){
		title = new QLineEdit;

		if(!fieldVS.toObject().value("Title").toString().isEmpty())
			title->setText(fieldVS.toObject().value("Title").toString());
		else title->setText(tr("New "));

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

		//this->preview->hide();
		}
	else

		if(type.compare("Refrence") == 0){
			Source = new ERPComboBox(0);
			layout->addRow(new QLabel(tr("Source ")), Source);
			QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(gotSourceData(QList<QJsonDocument>)));
			Controller::Get()->getJsonList("ViewStructure","Title","default.Type =\"Entity\"");


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
		else if(type.compare("Serial") == 0){
			defaultValue = new QLineEdit(0);
			defaultValue->setText(fieldVS.toObject().value("startNum").toString());
			layout->addRow(new QLabel(tr("Start Number")), defaultValue);
			}


	previewLayout->addWidget(new SubFieldUI(0,this->save()));
	//	qDebug() <<this->save();
}

QJsonObject StructureVieweditSubFeild::save()
{
	QJsonObject saveObject;
	if(!this->type.isEmpty() && filled)
		{
		//qDebug() << this->type << filled << links;
		saveObject.insert("Type",type);
		if(links){
			saveObject.insert("Select",Select->currentText());
			saveObject.insert("Source",Source->currentText());
			saveObject.insert("Title",title->text());

			}
		else
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
			else  if(type.compare("Serial") == 0){
				if(!defaultValue->text().isEmpty())
					saveObject.insert("startNum",defaultValue->text().toInt());
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

	this->fillTypeFields(type,this->fieldVS,this->links);
	emit changed();
}

void StructureVieweditSubFeild::updateSelect(QString title)
{
	QObject::connect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateSelectData(QList<QString>)));
	Controller::Get()->getFields(title);


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

void StructureVieweditSubFeild::paintEvent(QPaintEvent * event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(event);
}


