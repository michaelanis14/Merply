#include "pageui.h"
#include "mainform.h"

PageUI::PageUI(QWidget *parent, QJsonObject viewStructure) : MainDisplay(parent)
{
	this->setContentsMargins(0,0,0,0);
	this->layout = new QVBoxLayout(this);
	this->layout->setContentsMargins(0,0,0,0);
	this->layout->setSpacing(0);
	this->headerlbl = new HeaderLabel();
	this->headerlbl->setTitle("Page");
	layout->addWidget(headerlbl);

	fill(viewStructure);
}


PageUI* PageUI::p_instance = 0;


void PageUI::ShowUI(QJsonObject viewStructure) {

	if(p_instance == 0){
		p_instance = new PageUI(0,viewStructure);
		}
	else {
		p_instance->clear();
		p_instance->fill(viewStructure);
		}
	MainForm::Get()->ShowDisplay(p_instance);
}
void PageUI::fill(QJsonObject viewStructure)
{
	headerlbl->setTitle(viewStructure.value("Title").toString());
	viewGroups = new ViewGroups(0,viewStructure,QJsonObject()) ;
	viewGroups->setHidden(false);
	layout->addWidget(viewGroups);
	//this->layout->addWidget(createEditWidget);
}

void PageUI::clear()
{

	layout->removeWidget(viewGroups);
	viewGroups->setHidden(true);
	//child->setParent(0);
	viewGroups->deleteLater();


}
