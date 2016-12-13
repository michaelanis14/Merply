#include "createeditui.h"
#include "mainform.h"
#include "hcontrollers.h"
#include "controller.h"
#include "indexui.h"



CreateEditUI::CreateEditUI(QWidget* parent ) : MainDisplay(parent)
{

}

CreateEditUI::CreateEditUI(QWidget* parent, QJsonObject viewStructure, QJsonObject data) : MainDisplay(parent)
{

	this->setContentsMargins(0,0,0,0);
	this->layout = new QVBoxLayout(formPanel);
	this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	this->layout->setContentsMargins(0,0,0,0);
	this->layout->setSpacing(0);
	this->data = data;
	this->cas = "";
	QStringList btnsList;
	btnsList << "Save->Save"<< "Cancel->Cancel";

	HControllers* contrls = new HControllers(0,btnsList);
	connect(contrls, SIGNAL(btnClicked(const QString&)), this, SLOT(controller_Clicked(QString)));
	contrls->setObjectName("ViewGroup");
	this->layout->addWidget(contrls);

	errorsWidget = new QWidget();
	errorsWidget->setObjectName("errorsWidget");
	errorsWidget->setContentsMargins(0,0,0,0);
	errorsWidgetLayout = new QVBoxLayout(errorsWidget);
	errorsWidgetLayout->setContentsMargins(0,0,0,0);
	errorsWidgetLayout->setSpacing(0);
	this->layout->addWidget(errorsWidget);


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
void CreateEditUI::ShowUI(QJsonObject viewStructure, QJsonObject data,bool create) {

	//CreateEditUI* p_instance;
	QString key = viewStructure.value("document_id").toString().split("::").count() > 1?viewStructure.value("document_id").toString().split("::")[1]:"";
	if(!key.isEmpty())
		{

		if( create || !Controller::Get()->isCachedCreateEditUI(key)){
			CreateEditUI* p =  new CreateEditUI(0,viewStructure, data);
			//qDebug() << __FILE__ << __LINE__ << "insertCachedCreateEditUI"<<key<< &p_instance;
			Controller::Get()->insertCachedCreateEditUI(key,p);
			p_instance = p;
			}
		else{
			//qDebug() << __FILE__ << __LINE__ << "getCachedCreateEditUI"<<key;
			p_instance = (CreateEditUI*)(Controller::Get()->getCachedCreateEditUI(key));
			}
		}
	else if(!data.isEmpty()){
		p_instance->clear();
		p_instance->fill(QJsonObject(), data);
		}
	else {
		qDebug() << __FILE__ << __LINE__ << __FILE__ << __LINE__ << "ERRLOG" << viewStructure.value("document_id").toString() << "SPLIT COUNT";
		return;
		}
	MainForm::Get()->ShowDisplay(p_instance);
}

void CreateEditUI::fill(QJsonObject viewStructure, QJsonObject data)
{
	if(!viewStructure.isEmpty()){
		this->viewStructure = viewStructure;
		}

	this->data = data;
	this->cas = data.value("cas_value").toString();
	//qDebug() << __FILE__ << __LINE__  <<"Fill"<< this->cas;

	viewGroups = ViewGroups::Create(this->viewStructure,data) ;
	createEditWidgetLayout->addWidget(viewGroups);

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

void CreateEditUI::clearErrorsWidget()
{
	QList<QWidget *> Widgets = errorsWidget->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		errorsWidgetLayout->removeWidget(child);
		child->setHidden(true);
		child->setParent(0);
		child->deleteLater();  // TODO : check the stability of the app
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

		if(nActon.at(1).compare("Cancel") == 0){
			Controller::Get()->queryIndexView(this->viewStructure.value("document_id").toString());
			}
		else if(nActon.at(1).compare("Save") == 0){
			this->clearErrorsWidget();
			QString errs = viewGroups->checkMandatory();
			if(errs.isEmpty()){
				//	qDebug() << __FILE__ << __LINE__ <<"Controller Clicked to save" << this->cas;
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

				Controller::Get()->queryIndexView(this->viewStructure.value("document_id").toString());
				}
			else{
				foreach(QString err,errs.split(";")){
					errorsWidgetLayout->addWidget(new QLabel(err +" can not be empty"));
					}
				}
			}

		}


}
