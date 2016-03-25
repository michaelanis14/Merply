#include "subfeildui.h"
#include "controller.h"
#include "merplytabelview.h"

SubFieldUI::SubFieldUI(QWidget *parent, QJsonObject structureView, QJsonObject data) : QWidget(parent)
{

	//qDebug() << "wassup" << structureView;

	layout = new QHBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setMargin(0);
	QString type = structureView.value("Type").toString();



	if(type.compare("Refrence") == 0){
		ERPComboBox* combox = new ERPComboBox(this,false);
		combox->addItems(Controller::Get()->getListItems(structureView.value("Source").toString(),structureView.value("Select").toString()));
		if(structureView.value("Editable").toString().compare("false") == 0)
			combox->setEditable(false);
		layout->addWidget(combox);
		field = combox;
		}
	else if(type.compare("Text") == 0){

		QLineEdit* lineEdit = new QLineEdit();
		lineEdit->setContentsMargins(0,0,0,0);
		if(structureView.value("Default") != QJsonValue::Undefined){
			lineEdit->setText(structureView.value("Default").toString());
			}

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
		ERPComboBox* combox = new ERPComboBox(0,true);
		combox->addItems(Controller::Get()->getListItems(structureView.value("Source").toString(),structureView.value("Source").toString("Select")));
		combox->setEditable(true);
		QObject::connect(combox,SIGNAL(indexedFillEvent(QString)),this,SLOT(indexedFillEvent(QString)));
		layout->addWidget(combox);
		field = combox;
		}
	else if(type.compare("Table") == 0){
		merplyTabelView * table = new merplyTabelView(this,"key");
		//QDomNode columns = nodek.namedItem("Columns");
		table->fill(structureView,data);
		layout->addWidget(table);
		field = table;
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
