#include "subfeildui.h"
#include "controller.h"
#include "merplytabelview.h"

SubFieldUI::SubFieldUI(QWidget *parent,QString strID, QJsonObject structureView, QJsonValue data) : QWidget(parent)
{

	//qDebug() << "wassup" << structureView;
	//	qDebug() << "data" << data;
	this->structureView = QJsonObject();
	this->structureView = structureView;
	layout = new QHBoxLayout(this);
	this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setMargin(0);
	this->strID = strID;
	this->combox = 0;
	QString type = structureView.value("Type").toString();



	if(type.compare("Refrence") == 0){
		combox = new ERPComboBox(this,false);
		//qDebug()<<"SELECT" << structureView.value("Select");
		if(structureView.value("Editable").toString().compare("false") == 0)
			combox->setEditable(false);

		layout->addWidget(combox);
		field = combox;


		if(structureView.value("LocalFilter") != QJsonValue::Undefined && structureView.value("LocalFilter").toBool()){
			//qDebug() << "local Field"<< structureView.value("Local").toString();
			//qDebug() << Controller::Get()->getFirstSubField(structureView.value("Local").toString());
			SubFieldUI* localFilter = Controller::Get()->getFirstSubField(structureView.value("Local").toString());
			if(localFilter->combox){
				QObject::connect(localFilter->combox,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateFilter(QString)));
				this->updateFilter(localFilter->combox->currentText());
				//emit localFilter->combox->currentIndexChanged(localFilter->combox->currentIndex());
				}
			else{
				qDebug() <<"Not Init";
				}
			}
		else{
			//qDebug() << "NOT LOACL FILTER";
			QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(refrenceData(QList<QJsonDocument>)));
			Controller::Get()->getJsonEntityFieldsList(structureView.value("Source").toString(),structureView.value("Select").toString(),structureView.value("Condition").toString());
			}
		QJsonObject dataObj = data.toObject();
		//qDebug() << data;
		if(!dataObj.isEmpty()){
			combox->setCurrentIndex(combox->findText(dataObj.value("Value").toString()));
			}
		//qDebug() << structureView.value("Source").toString() << structureView.value("Select").toString();
		}
	else if(type.compare("Text") == 0){

		QLineEdit* lineEdit = new QLineEdit();
		lineEdit->setContentsMargins(0,0,0,0);
		if(structureView.value("Default") != QJsonValue::Undefined){
			lineEdit->setText(structureView.value("Default").toString());
			}
		lineEdit->setText(data.toString());
		if(structureView.value("CharCount") != QJsonValue::Undefined && structureView.value("CharCount").toInt() > 0)
			lineEdit->setMaxLength(structureView.value("CharCount").toInt());
		if(structureView.value("InputDataType").toString().compare("IntToMillion") == 0)
			lineEdit->setValidator( new QIntValidator(0, 1000000, this) );
		else if(structureView.value("InputDataType").toString().compare("DoubleToMillion")== 0)
			lineEdit->setValidator( new QDoubleValidator(0, 1000000,2, this) );
		layout->addWidget(lineEdit);
		field = lineEdit;
		}
	else if(type.compare("TextArea") == 0){

		QTextEdit* lineEdit = new QTextEdit();
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
		QString dataString = data.toString();
		if(!dataString.isEmpty()){
			combox->setCurrentIndex(combox->findText(dataString));
			}
		}
	else if(type.compare("Table") == 0){
		merplyTabelView * table = new merplyTabelView(this,true,false);
		//qDebug() << data.toObject() << structureView;
		//Controller::Get()->getReportTableData(structureView);
		table->fill(structureView);
		QJsonObject dataObj = data.toObject();
		if(!dataObj.isEmpty())
			table->fillText(dataObj);
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
	else if(type.compare("Date") == 0){
		QDateEdit *date = new QDateEdit(this);
		if(data.toString().isEmpty())
			date->setDate(QDate::currentDate());
		else date->setDate(QDate::fromString(data.toString(),Qt::DefaultLocaleShortDate));
		layout->addWidget(date);
		field = date;
		}


}

void SubFieldUI::clear()
{

}

QJsonValue SubFieldUI::save()
{
	QJsonValue save;
	if(QString(field->metaObject()->className()).compare("ERPComboBox") == 0 ){
		//	save += component.name;
		QJsonObject comboFields;
		comboFields.insert("Value", ((QComboBox*)field)->currentText());
		comboFields.insert("Key", ((ERPComboBox*)field)->getKey());
		save = comboFields;
		//save +=" ";
		}
	else if(QString(field->metaObject()->className()).compare("QLineEdit") == 0 ){
		//	save += component.name;

		save =((QLineEdit*)field)->text();
		//	save =" ";
		}
	else if(QString(field->metaObject()->className()).compare("QTextEdit") == 0 ){
		save =((QTextEdit*)field)->toPlainText();
		}
	else if(field->objectName().compare("checkbox") == 0){
		//	save = component.name;
		save =((QCheckBox*)field)->isChecked();
		//	save =" ";
		}
	else if(QString(field->metaObject()->className()).compare("merplyTabelView") == 0){
		//	save = component.name;
		//		save =((merplyTabelView*)field)->save("this->key");

		save = ((merplyTabelView*)field)->save();
		//	save =" ";
		}
	else if(QString(field->metaObject()->className()).compare("QDateEdit") == 0){
		save =((QDateEdit*)field)->date().toString(Qt::DefaultLocaleShortDate);
		}

	return save;
}

bool SubFieldUI::checkMandatory()
{

	if(structureView.isEmpty()
			&& structureView.value("Mandatory") != QJsonValue::Undefined
			&& structureView.value("Mandatory").toBool()){
		if(this->save().toString().isEmpty()){
			field->setObjectName("error");
			field->style()->unpolish(field);
			field->style()->polish(field);
			field->update();
			return false;
			}

		}
	return true;
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
	if(combox){
		combox->clear();
		combox->addJsonItems(items);
		}
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

void SubFieldUI::updateFilter(QString filter)
{
	//qDebug() <<"filter" << filter;
	QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(refrenceData(QList<QJsonDocument>)));
	Controller::Get()->getJsonEntityFieldsList(structureView.value("Source").toString(),structureView.value("Select").toString(),structureView.value("Entity").toString()+"="+filter);

}
