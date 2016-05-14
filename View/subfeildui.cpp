#include "subfeildui.h"
#include "controller.h"
#include "merplytabelview.h"

SubFieldUI::SubFieldUI(QWidget *parent,QString strID, QJsonObject structureView, QJsonValue data) : QWidget(parent)
{

	//qDebug() << "wassup" << structureView;
	//	qDebug() << "data" << data;
	this->structureView = structureView;
	layout = new QHBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setMargin(0);
	this->strID = strID;
	QString type = structureView.value("Type").toString();



	if(type.compare("Refrence") == 0){
		combox = new ERPComboBox(this,false);
		if(structureView.value("Editable").toString().compare("false") == 0)
			combox->setEditable(false);
		layout->addWidget(combox);
		field = combox;

		QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(refrenceData(QList<QJsonDocument>)));
		Controller::Get()->getJsonEntityFieldsList(structureView.value("Source").toString(),structureView.value("Select").toString());

		//qDebug() << structureView.value("Source").toString() << structureView.value("Select").toString();
		}
	else if(type.compare("Text") == 0){

		QLineEdit* lineEdit = new QLineEdit();
		lineEdit->setContentsMargins(0,0,0,0);
		if(structureView.value("Default") != QJsonValue::Undefined){
			lineEdit->setText(structureView.value("Default").toString());
			}
		lineEdit->setText(data.toString());
		layout->addWidget(lineEdit);
		field = lineEdit;
		}
	else if(type.compare("Fixed") == 0){
		QLineEdit* lineEdit = new QLineEdit();
		lineEdit->setContentsMargins(0,0,0,0);
		if(structureView.value("Default") != QJsonValue::Undefined){
			lineEdit->setText(structureView.value("Default").toString());
			}
		lineEdit->setEnabled(false);
		lineEdit->setStyleSheet("QLineEdit{background: white; color:black; border:0;}");

		layout->addWidget(lineEdit);
		field = lineEdit;
		}
	else if(type.compare("Index") == 0){
		combox = new ERPComboBox(0,true);
		combox->setEditable(true);
		QObject::connect(combox,SIGNAL(indexedFillEvent(QString)),this,SLOT(indexedFillEvent(QString)));
		layout->addWidget(combox);
		field = combox;

		QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(refrenceData(QList<QJsonDocument>)));
		Controller::Get()->getJsonList(structureView.value("Source").toString(),structureView.value("Select").toString());

		}
	else if(type.compare("Table") == 0){
		merplyTabelView * table = new merplyTabelView(this,"key");
		//QDomNode columns = nodek.namedItem("Columns");
		table->fill(structureView,data.toObject());
		layout->addWidget(table);
		field = table;
		}
	else if(type.compare("Link") == 0){
		QPushButton* btn  = new QPushButton(structureView.value("Title").toString(),this);
		QObject::connect(btn,SIGNAL(pressed()),this,SLOT(linkPressed()));
		layout->addWidget(btn);
		field = btn;
		}
	else if(type.compare("Serial") == 0){
		QLineEdit* lineEdit = new QLineEdit();
		field = lineEdit;
		lineEdit->setContentsMargins(0,0,0,0);
		lineEdit->setEnabled(false);
		QString dataString = data.toString();
		if(!dataString.isEmpty()){
			lineEdit->setText(dataString);
			}
		else{
		if(structureView.value("startNum") != QJsonValue::Undefined){
			lineEdit->setText(QString::number(structureView.value("startNum").toInt()));
			}

		QStringList id = this->strID.split("ViewStructure::");
		if(id.count() > 1){
			QObject::connect(Controller::Get(),SIGNAL(gotValue(QString)),this,SLOT(serialData(QString)));
			Controller::Get()->getValue(id[1]);
			}
			}
		//lineEdit->setText(data.toString());
		layout->addWidget(lineEdit);

		}

}

void SubFieldUI::clear()
{

}

QString SubFieldUI::save()
{
	QString save;

	if(field->objectName().compare("combobox") == 0  || field->objectName().compare("ERPComboBoxIndexed") == 0 ){
		//	save += component.name;
		save +=((QComboBox*)field)->currentText();
		//save +=" ";
		}
	else if(QString(field->metaObject()->className()).compare("QLineEdit") == 0 ){
		//	save += component.name;
		save +=((QLineEdit*)field)->text();
		//	save +=" ";
		}
	else if(field->objectName().compare("checkbox") == 0){
		//	save += component.name;
		save +=((QCheckBox*)field)->isChecked();
		//	save +=" ";
		}
	else if(field->objectName().compare("merplyTabelView") == 0){
		//	save += component.name;
		save +=((merplyTabelView*)field)->save("this->key");
		//	save +=" ";
		}


	return save.trimmed();
}

void SubFieldUI::indexedFillEvent(QString completion)
{
	qDebug() << completion;

}

void SubFieldUI::linkPressed()
{
	Controller::Get()->linkPressed(this->structureView);
}

void SubFieldUI::refrenceData(QList<QJsonDocument> items)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(refrenceData(QList<QJsonDocument>)));
	if(combox)
		combox->addJsonItems(items);

	//qDebug() << items;
}

void SubFieldUI::serialData(QString serial)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotValue(QString)),this,SLOT(serialData(QString)));
	if(structureView.value("startNum") != QJsonValue::Undefined){
		int i = structureView.value("startNum").toInt();
		int current = serial.toInt();
		int serialized = i + current;
		//qDebug() << serialized << i << current;
		if(serialized > i)
			((QLineEdit*)field)->setText(QString::number(serialized));
		}
}
