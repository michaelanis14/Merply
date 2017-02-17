#include "merplyqueryui.h"
#include "controller.h"




#include <QDebug>

MerplyQueryUI::MerplyQueryUI(QWidget *parent,bool btnFilter) : QWidget(parent)
{
	this->btnFilterFlag = btnFilter;
	this->setContentsMargins(0,0,0,0);
	layout = new QHBoxLayout(this);
	//this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setMargin(0);
	this->setLayout(layout);
	fields = QVector<MerplyQuerySubField*>();
}

void MerplyQueryUI::fill(QJsonObject strct)
{
	clear();
	{
	QWidget * viewgrp  = new QWidget;
	viewgrp->setContentsMargins(0,0,0,0);
	QFormLayout* fieldslayout = new QFormLayout(viewgrp);
	fieldslayout->setContentsMargins(0,0,0,0);
	fieldslayout->setSpacing(4);
	fieldslayout->setMargin(0);
	this->layout->addWidget(viewgrp);
	QJsonObject objID;
	objID.insert("Type","ID");
	objID.insert("strct",strct.value("document_id").toString().split("::")[1]);
	//qDebug() << strct;
	MerplyQuerySubField* qSubField = new MerplyQuerySubField(objID,0);
	fieldslayout->addRow("ID.No.",qSubField);
	fields << qSubField;
	}

	foreach(QJsonValue vg,strct.value("Viewgroups").toArray()){
		QWidget * viewgrp  = new QWidget;
		viewgrp->setContentsMargins(0,0,0,0);
		QFormLayout* fieldslayout = new QFormLayout(viewgrp);
		fieldslayout->setContentsMargins(0,0,0,0);
		fieldslayout->setSpacing(4);
		fieldslayout->setMargin(0);
		this->layout->addWidget(viewgrp);
		foreach(QJsonValue vf,vg.toObject().value("Viewgroup").toObject().value("Fields").toArray()){
			//QJsonObject subfield = vf.toObject().value("SubFields").toArray().first().toObject(); //TODO: LOOP ON ALL SUBFIELDS
			QString label = vf.toObject().value("Label").toString();
			MerplyQuerySubField* qSubField = new MerplyQuerySubField(vf.toObject(),0);
			fieldslayout->addRow(label,qSubField);
			fields << qSubField;
			}
		}
	if(btnFilterFlag){
		btnFilter  = new QPushButton("Filter",this);
		this->btnFilter->setDisabled(false);
		QObject::connect(btnFilter,SIGNAL(clicked(bool)),this,SLOT(disablebutton()));
		this->layout->addWidget(btnFilter);
		}

}

void MerplyQueryUI::fillEntityQuery(QJsonObject strct)
{
	this->strct = strct;
	//qDebug() << strct;
	foreach(QJsonValue clmn,strct.value("ColumnsQuery").toArray()){
		MerplyQuerySubField* qSubField = new MerplyQuerySubField(clmn.toObject(),0);
		layout->addWidget(qSubField);
		fields << qSubField;
		}
	if(btnFilterFlag){
		btnFilter  = new QPushButton("Filter",this);
		this->btnFilter->setDisabled(false);
		QObject::connect(btnFilter,SIGNAL(clicked(bool)),this,SLOT(disablebutton()));
		this->layout->addWidget(btnFilter);
		}
}

void MerplyQueryUI::fillDocumentID(QString document_id)
{

	if(!document_id.isEmpty() && document_id.split("::").count() > 1){
		this->document_id = document_id;
		QObject::connect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(fillData(QJsonDocument)));
		Controller::Get()->getDoc(document_id);

		}
}

QString MerplyQueryUI::getFields(QString entity)
{
	QString save="";
	foreach(MerplyQuerySubField* field,fields){
		QString fieldSTring = field->getValue(entity);
		if(!fieldSTring.isEmpty()){
			if(!save.isEmpty())
				save+= " AND ";
			save+=fieldSTring;
			}
		}
	return save;

}

void MerplyQueryUI::clear()
{
	fields.clear();
	QList<QWidget *> Widgets = this->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		layout->removeWidget(child);
		child->setHidden(true);
		child->setParent(0);
		//child->deleteLater();  // TODO : check the stability of the app
		//this->deleteLater();
		}
}

void MerplyQueryUI::fillData(QJsonDocument strct)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(fillData(QJsonDocument)));
	this->fill(strct.object());
}

void MerplyQueryUI::generateQuery()
{
	QString save="";
	QString query="";

	save += getFields("");

	//qDebug() << __FILE__ << __LINE__  << save;
	//qDebug() << __FILE__ << __LINE__  <<  this->strct.value("Query");
	if(this->strct.value("Query") != QJsonValue::Undefined){
		if(!save.isEmpty())
			save.prepend(" AND ");
		QString q = this->strct.value("Query").toString();
		q.replace("#QUERYMERPLY",save);
		query += q;
		}
	else if(!save.isEmpty()){
		query += "SELECT `"+QString(DATABASE)+"`.*,to_number(SPLIT(META(`"+QString(DATABASE)+"`).id,'::')[1]) AS `ID.No.` FROM  `"+QString(DATABASE)+"`  WHERE META(`"+QString(DATABASE)+"`).id LIKE '"+this->document_id.split("::")[1]+"::%'  AND "+save;
		}
	if(!query.isEmpty()){
		qDebug() << query;
		QObject::connect(Controller::Get(),SIGNAL(gotReportData(QVector<QJsonDocument>)),this,SLOT(gotData(QVector<QJsonDocument>)));
		Controller::Get()->query(query,false);
		}
	else{

		this->btnFilter->setDisabled(false);
		}
	//qDebug() << "SELECT *  FROM "<<QString(DATABASE) << "WHERE META('"<<QString(DATABASE)<<"').id LIKE"<<document_id<<" AND "<<save;
	//return save;
}

void MerplyQueryUI::gotData(QVector<QJsonDocument> items)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotReportData(QVector<QJsonDocument>)),this,SLOT(gotData(QVector<QJsonDocument>)));
	emit queryResults(items);
	this->btnFilter->setDisabled(false);
}

void MerplyQueryUI::disablebutton()
{
	this->btnFilter->setDisabled(true);
	generateQuery();
}
