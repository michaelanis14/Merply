#include "merplyqueryui.h"
#include "controller.h"

#include <QDebug>

MerplyQueryUI::MerplyQueryUI(QWidget *parent) : QWidget(parent)
{
	this->setContentsMargins(0,0,0,0);
	layout = new QHBoxLayout(this);
	//this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setMargin(0);
	this->setLayout(layout);
	fields = QVector<QWidget*>();
}

void MerplyQueryUI::fill(QJsonObject strct)
{

	foreach(QJsonValue vg,strct.value("Viewgroups").toArray()){
		QWidget * viewgrp  = new QWidget;
		viewgrp->setContentsMargins(0,0,0,0);
		QFormLayout* fieldslayout = new QFormLayout(viewgrp);
		fieldslayout->setContentsMargins(0,0,0,0);
		fieldslayout->setSpacing(4);
		fieldslayout->setMargin(0);
		this->layout->addWidget(viewgrp);
		foreach(QJsonValue vf,vg.toObject().value("Viewgroup").toObject().value("Fields").toArray()){
			QJsonObject subfield = vf.toObject().value("SubFields").toArray().first().toObject(); //TODO: LOOP ON ALL SUBFIELDS
			QString label = vf.toObject().value("Label").toString();
			QString type =  subfield.value("Type").toString();
			qDebug() << type << subfield;
			if(type.compare("Text") == 0){
				QLineEdit* lineEdit = new QLineEdit();
				lineEdit->setObjectName(label);
				lineEdit->setContentsMargins(0,0,0,0);
				fieldslayout->addRow(label,lineEdit);
				fields << lineEdit;
				}
			}
		}
	QPushButton* btnFilter  = new QPushButton("Filter",this);
	QObject::connect(btnFilter,SIGNAL(pressed()),this,SLOT(generateQuery()));
	this->layout->addWidget(btnFilter);

}

void MerplyQueryUI::fillDocumentID(QString document_id)
{
	if(!document_id.isEmpty() && document_id.split("::").count() > 1){
		this->document_id = document_id;
		QObject::connect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(fillData(QJsonDocument)));
		Controller::Get()->getDoc(document_id);

		}
}

void MerplyQueryUI::fillData(QJsonDocument strct)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(fillData(QJsonDocument)));
	this->fill(strct.object());
}

void MerplyQueryUI::generateQuery()
{
	QString save ;
	foreach(QWidget* field,fields){

		if(QString(field->metaObject()->className()).compare("ERPComboBox") == 0 ){
			//	save += component.name;
			QString value = ((QComboBox*)field)->currentText();
			if(!value.trimmed().isEmpty()){
				QJsonObject comboFields;
				comboFields.insert("Value", ((QComboBox*)field)->currentText());
				comboFields.insert("Key", ((ERPComboBox*)field)->getKey());
				//		save = comboFields;
				}
			//save +=" ";
			}
		else if(QString(field->metaObject()->className()).compare("QLineEdit") == 0 ){
			//	save += component.name;
			if(!((QLineEdit*)field)->text().trimmed().isEmpty()){
				save = QString("`"+((QLineEdit*)field)->objectName()+"`").append(QString("LIKE ")).append("`"+((QLineEdit*)field)->text().trimmed()+"`");
				}
			//	save =" ";
			}
		else if(QString(field->metaObject()->className()).compare("QTextEdit") == 0 ){
			if(!((QTextEdit*)field)->toPlainText().trimmed().isEmpty())
				save =((QTextEdit*)field)->toPlainText();
			}
		else if(QString(field->metaObject()->className()).compare("QCheckBox") == 0 ){
			//	save = component.name;
			save =((QCheckBox*)field)->isChecked();
			//	save =" ";
			}
		else if(QString(field->metaObject()->className()).compare("merplyTabelView") == 0){
			//	save = component.name;
			//		save =((merplyTabelView*)field)->save("this->key");
			QJsonObject tblSave = ((merplyTabelView*)field)->save();
			if(!tblSave.isEmpty())
				//	save = tblSave;
				save =" ";
			}
		else if(QString(field->metaObject()->className()).compare("QDateTimeEdit") == 0){
			save =((QDateTimeEdit*)field)->dateTime().toString(Qt::DefaultLocaleShortDate);
			//qDebug() << save;
			}
		}
	qDebug() << "SELECT *  FROM "<<QString(DATABASE) << "WHERE META('"<<QString(DATABASE)<<"').id LIKE"<<document_id<<" AND "<<save;
	//return save;
}
