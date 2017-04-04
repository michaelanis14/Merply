#include "searchui.h"

SearchUI::SearchUI(QWidget *parent) : MainDisplay(parent)
{
	layout = new QVBoxLayout(formPanel);
	this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	layout->setContentsMargins(2,2,2,2);
	layout->setSpacing(0);
	this->setContentsMargins(2,2,2,2);
	this->setObjectName("SearchUI");

	table = new merplyTabelView(this,false,true);
	table->indexTable("ViewStructure::Clients",QVector<QJsonDocument>());
	layout->addWidget(table);

	//table->indexTable("ViewStructure::clients",QVector<QJsonDocument>());
//	this->
}
SearchUI* SearchUI::p_instance = 0;
void SearchUI::ShowUI(const QString document_id, const QVector<QJsonDocument> documents) {

	if(p_instance == 0)
		p_instance = new SearchUI();
	if(p_instance->document_id.compare(document_id) != 0){
		p_instance->fill(document_id,documents);
		}
	MainForm::Get()->ShowDisplay(p_instance);
//	p_instance->table->generateQuery(50);
}


void SearchUI::fill(const QString document_id,const QVector<QJsonDocument> items){

	this->document_id = document_id;
	qDebug() << __FILE__ << __LINE__  << document_id ;
	table->indexTable(document_id,items);


}


