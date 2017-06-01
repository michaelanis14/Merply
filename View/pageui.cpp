#include "pageui.h"
#include "mainform.h"
#include "controller.h"
#include "printcontroller.h"

PageUI::PageUI(QWidget *parent, QJsonObject viewStructure) : MainDisplay(parent)
{
	this->setContentsMargins(0,0,0,0);
	this->layout = new QVBoxLayout(formPanel);
	this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	this->layout->setContentsMargins(0,0,0,0);
	this->layout->setSpacing(0);
	controllers = new HControllers;
	controllers->setObjectName("controllers");
	controllers->clear();
	QStringList btns;
	btns << "Print->Print";
	controllers->fill(btns);
	layout->addWidget(controllers);
	this->headerlbl = new HeaderLabel();
	this->headerlbl->setTitle("Page");
	layout->addWidget(headerlbl);
	connect(controllers, SIGNAL(btnClicked(const QString&)), this, SLOT(controller_Clicked(QString)));
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
	//qDebug() << __FILE__ << __LINE__<< viewStructure;
	this->document_id = viewStructure.value("document_id").toString();
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

void PageUI::controller_Clicked(QString nameAction)
{
		QStringList nActon = nameAction.split("->");
		if(nActon.count() > 1){
			if(nActon.at(1).compare("Print") == 0){
				qDebug()<< __FILE__ << __LINE__ << "TODO" << "PRINTING ";
				//TODO PRINTINGG

				//QJsonObject toPrint = viewGroups->save();
				//qDebug() << toPrint;
				//toPrint.insert("document_id",document_id);
			///	PrintController::Get()->gotPrintEntity(QJsonDocument(toPrint));
			//	PrintController::Get()->printEntity("id");
				//////////////				Controller::Get()->queryIndexView(this->viewStructure.value("document_id").toString());
				}
}
}
