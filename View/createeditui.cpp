#include "createeditui.h"
#include "mainform.h"
#include "hcontrollers.h"
#include "controller.h"
#include "indexui.h"



CreateEditUI::CreateEditUI(QWidget* parent, QJsonObject viewStructure, QJsonObject data) : MainDisplay(parent)
{

	this->setContentsMargins(0,0,0,0);
	this->layout = new QVBoxLayout(this);
	this->layout->setContentsMargins(0,0,0,0);
	this->layout->setSpacing(0);
	this->data = data;
	QStringList btnsList;
	btnsList << "Save->Save"<< "Cancel->Cancel";

	HControllers* contrls = new HControllers(0,btnsList);
	connect(contrls, SIGNAL(btnClicked(const QString&)), this, SLOT(controller_Clicked(QString)));
	contrls->setObjectName("ViewGroup");
	this->layout->addWidget(contrls);

	createEditWidget = new QWidget();
	createEditWidget->setContentsMargins(0,0,0,0);
	createEditWidgetLayout = new QVBoxLayout(createEditWidget);
	createEditWidgetLayout->setContentsMargins(0,0,0,0);
	createEditWidgetLayout->setSpacing(0);
	this->layout->addWidget(createEditWidget);

	HControllers* ndcontrls = new HControllers(0,btnsList);
	ndcontrls->setObjectName("ViewGroup");
	connect(ndcontrls, SIGNAL(btnClicked(const QString&)), this, SLOT(controller_Clicked(QString)));
	this->layout->addWidget(ndcontrls);

	fill(viewStructure,data);



}

CreateEditUI* CreateEditUI::p_instance = 0;
void CreateEditUI::ShowUI(QJsonObject viewStructure, QJsonObject data) {

	if(p_instance == 0){
		p_instance = new CreateEditUI(0,viewStructure, data);
		}
	else{
		p_instance->clear();
		p_instance->fill(viewStructure, data);
		}
	MainForm::Get()->ShowDisplay(p_instance);
}

void CreateEditUI::fill(QJsonObject viewStructure, QJsonObject data)
{
	if(!viewStructure.isEmpty()){
		this->viewStructure = viewStructure;
		}

	this->data = data;


	viewGroups = new ViewGroups(0,this->viewStructure,data) ;
	createEditWidgetLayout->addWidget(viewGroups);
	this->cas = data.value("cas_value").toString();
	//this->layout->addWidget(createEditWidget);
}

void CreateEditUI::clear()
{
	this->cas = "";
	QList<QWidget *> Widgets = createEditWidget->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		if(child != NULL){
			createEditWidgetLayout->removeWidget(child);
			child->setHidden(true);
			//child->setParent(0);
			child->deleteLater();
			}
		}
}
void CreateEditUI::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void CreateEditUI::controller_Clicked(QString nameAction)
{
	QStringList nActon = nameAction.split("->");
	if(nActon.count() > 1){

		if(nActon.at(1).compare("cancel") == 0){
			Controller::Get()->queryIndexView(this->viewStructure.value("document_id").toString());
			}
		else if(nActon.at(1).compare("Save") == 0){
			if(this->cas.isEmpty()){
				QString key = this->viewStructure.value("document_id").toString().replace("ViewStructure::","");
				QJsonObject vgsSave = viewGroups->save();
				vgsSave.insert("cas_value",this->cas);
				Controller::Get()->storeDoc(key,QJsonDocument(vgsSave));
				}
			else{
				QJsonObject vgsSave = viewGroups->save();
				vgsSave.insert("cas_value",this->cas);
				vgsSave.insert("document_id",this->data.value("document_id").toString());
				Controller::Get()->UpdateDoc(QJsonDocument(vgsSave));
				}

			}
		}

	Controller::Get()->queryIndexView(this->viewStructure.value("document_id").toString());
}
