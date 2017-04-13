
#include "searchui.h"
#include "controller.h"

SearchUI::SearchUI(QWidget *parent) : MainDisplay(parent)
{
	layout = new QVBoxLayout(formPanel);
	this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	layout->setContentsMargins(2,2,2,2);
	layout->setSpacing(0);
	this->setContentsMargins(2,2,2,2);
	this->setObjectName("SearchUI");

	table = new merplyTabelView(this,false,true);

	this->strID = strID;
	QObject::connect(table,SIGNAL(doubleClicked()),this,SLOT(showEditUI()));
	QPushButton *back = new QPushButton("back");
	sctrlUI = new SettingsCtrlsUI();
	sctrlUI->addbtn("Back",":/resources/icons/back.png","back");
	layout->addWidget(sctrlUI);
	layout->addWidget(table);


	QObject::connect(sctrlUI, SIGNAL(btnClicked(QString)),this, SLOT(showEditUI()));

}
SearchUI* SearchUI::p_instance = 0;

void SearchUI::ShowUI(const QString document_id, const QVector<QJsonDocument> documents,QString strID)
{
	p_instance = new SearchUI();
	Get()->strID = strID;
	if(p_instance->document_id.compare(document_id) != 0){
		p_instance->fill(document_id,documents);
		}
	MainForm::Get()->ShowDisplay(p_instance);

}

void SearchUI::fill(const QString document_id,const QVector<QJsonDocument> items)
{
	this->document_id = document_id;
	table->indexTable(document_id,items);
}

void SearchUI::showEditUI()
{
	Controller::Get()->showCreateEditeStrUI(strID,false);
}

merplyTabelView* SearchUI::getTable() {
	return this->table;
}


SearchUI* SearchUI::Get()
{
	if (p_instance == 0)
		p_instance = new SearchUI();

	return p_instance;
}

