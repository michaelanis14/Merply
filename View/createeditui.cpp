#include "createeditui.h"
#include "mainform.h"
#include "hcontrollers.h"



CreateEditUI::CreateEditUI(QWidget* parent, QJsonObject viewStructure, QJsonObject data) : MainDisplay(parent)
{

	this->setContentsMargins(0,0,0,0);
	this->layout = new QVBoxLayout(this);
	this->layout->setContentsMargins(0,0,0,0);
	this->layout->setSpacing(0);

	QStringList btnsList;
	btnsList << "Save->Save";

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
	viewGroups = new ViewGroups(0,viewStructure,data) ;
	createEditWidgetLayout->addWidget(viewGroups);
	//this->layout->addWidget(createEditWidget);
}

void CreateEditUI::clear()
{
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
		//	IndexUI::ShowUI(this->id);
			}
		else if(nActon.at(1).compare("Save") == 0){
			viewGroups->save();
			//if(){
		//		IndexUI::ShowUI(this->id);
				//	IndexUI::ShowUI(this->id);
				//	IndexUI::ShowUI(this->id);
				//	IndexUI::ShowUI(this->id);
			//	}
			}
		/*else
			if(nActon.at(1).compare("clear") == 0){
			this->update = false;
			foreach(Entity * entity,commands){
				entity->clear();
				Database::Get()->setLastKeyID("");
				}
			}
*/
		}
}
