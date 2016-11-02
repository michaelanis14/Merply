#include "structureviewgroupsui.h"
#include "viewgroups.h"
#include "controller.h"
#include "removebtn.h"

#include<QJsonDocument>

StructureViewGroupsUI::StructureViewGroupsUI(QWidget *parent, QJsonObject structureView, QStringList restrictedTypes,bool scroll) : MainDisplay(parent)
{

	this->structureView = structureView;
	this->restrictedTypes = restrictedTypes;
	this->setContentsMargins(0,0,0,0);
	if(scroll)
		structureViewGroupsUILayout = new QVBoxLayout(formPanel);
	else
		structureViewGroupsUILayout = new QVBoxLayout(this);
	structureViewGroupsUILayout->setMargin(0);
	structureViewGroupsUILayout->setSpacing(0);



	QWidget* sVGUI = new QWidget(this);
	sVGUI->setContentsMargins(0,0,0,0);
	sVGUI->setObjectName("StructureViewGroupsUI");
	sVGUI->setStyleSheet("QWidget#StructureViewGroupsUI{ border: 1px solid gray;}");
	sVGUI->setAutoFillBackground(true);

	structureViewGroupsUILayout->addWidget(sVGUI);



	layout = new QVBoxLayout(sVGUI);
	layout->setSpacing(0);
	layout->setMargin(2);
	layout->setSizeConstraint(QLayout::SetMaximumSize);


	headerlbl = new HeaderLabel();
	if(!structureView.value("Title").toString().isEmpty())
		headerlbl->setTitle(structureView.value("Title").toString());
	else headerlbl->setTitle("New Card");///+QString::number(Controller::Get()->Count("ViewStructure")));
	layout->addWidget(headerlbl);


	sctrlUI = new SettingsCtrlsUI();
	sctrlUI->addbtn("Add",":/resources/icons/add.png","add");
	sctrlUI->addbtn("Save",":/resources/icons/save.png","save");

	sctrlUI->addbtn("Cancel",":/resources/icons/cancel.png","cancel");

	QObject::connect(sctrlUI, SIGNAL(btnClicked(QString)),this, SLOT(btn_Clicked(QString)));
	sctrlUI->setAutoFillBackground(true);
	layout->addWidget(sctrlUI);



	//contrls->setAutoFillBackground(true);

	viewGroups = new QWidget();
	viewGroups->setContentsMargins(0,0,0,0);
	viewGroupsLayout = new QVBoxLayout(viewGroups);
	viewGroupsLayout->setMargin(0);
	viewGroupsLayout->setSpacing(0);
	layout->addWidget(viewGroups);
	fill(structureView);


	//	this->setLayout(layout);
	init = true;
	layout->addStretch(1);
}




QJsonObject StructureViewGroupsUI::save()
{

	QJsonObject saveObject;
	if(!init)
		return saveObject;
	saveObject.insert("Title",headerlbl->getTitle());
	saveObject.insert("Type","Entity");
	QJsonArray ViewGroups;
	foreach(StructureViewsEditUI * strcViewUI,sVSFUIs){
		QJsonObject viewGroup;
		viewGroup.insert("Viewgroup",strcViewUI->save());
		ViewGroups << viewGroup;
		}
	saveObject.insert("Viewgroups",ViewGroups);
	if(!document_id.isEmpty()){
		saveObject.insert("cas_value",cas_value);
		saveObject.insert("document_id",document_id);
		}

	return saveObject;
}




StructureViewGroupsUI* StructureViewGroupsUI::p_instance = 0;
void StructureViewGroupsUI::ShowUI(QJsonObject structureView) {

	if(p_instance == 0)
		p_instance = new StructureViewGroupsUI(0,structureView,QStringList(),true);
	else p_instance->fill(structureView);

	p_instance->setObjectName("StructureViewGroupsUI");
	//p_instance->clear();
	MainForm::Get()->ShowDisplay(p_instance);
}

void StructureViewGroupsUI::fill(QJsonObject structureView)
{
	//	qDebug() << structureView.value("document_id").toString() << structureView;
	this->cas_value = structureView.value("cas_value").toString();
	this->document_id = structureView.value("document_id").toString();

	if(!structureView.value("Title").toString().isEmpty())
		headerlbl->setTitle(structureView.value("Title").toString());
	else headerlbl->setTitle("New Card");///+QString::number(Controller::Get()->Count("ViewStructure")));


	QList<QWidget *> Widgets = viewGroups->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		if(child != NULL){
			viewGroupsLayout->removeWidget(child);
			child->setHidden(true);
			//child->setParent(0);
			child->deleteLater();
			}
		}
	sVSFUIs.clear();
	HViewGroups.clear();

	if(structureView.value("Viewgroups").isArray()){
		foreach (QJsonValue item, structureView.value("Viewgroups").toArray()) {
			StructureViewsEditUI* viewgroup = new StructureViewsEditUI(0,item.toObject(),this->restrictedTypes);

			QObject::connect(viewgroup,SIGNAL(updateLayout()),this,SLOT(updateLayout()));
			QObject::connect(viewgroup, SIGNAL(styleChanged()),this, SLOT(viewGroupStyleChanged()));
			viewgroup->loadGroup();
			QJsonObject viewGroupObject = item.toObject().value("Viewgroup").toObject();


			RemoveBtn* viewgroupRmv =  new RemoveBtn(0,viewgroup);
			QObject::connect(viewgroupRmv,SIGNAL(remove(QWidget*)),this,SLOT(removeViewgroup(QWidget*)));
			viewgroupRmv->hideRemovebtn(true);
			QObject::connect(viewgroup->topCntrlsPreview,SIGNAL(removeClicked()),viewgroupRmv,SLOT(remove()));


			if(viewGroupObject.value("Style").toString().compare("horizontail") == 0){
				QString group = viewGroupObject.value("Group").toString().toLower().trimmed();
				if(!(group.isEmpty()) && HViewGroups.find(group) == HViewGroups.end()){

					QWidget* vW = new QWidget();
					vW->setContentsMargins(0,0,0,0);
					QHBoxLayout* HLayout = new QHBoxLayout(vW);
					HLayout->setContentsMargins(2,2,2,2);
					HLayout->addWidget(viewgroupRmv);
					HLayout->setSpacing(1);
					HViewGroups.insert(group,vW);


					viewGroupsLayout->addWidget(vW);
					}
				else {
					if(HViewGroups.find(group) != HViewGroups.end())
						if(HViewGroups.find(group).value()->layout())
							HViewGroups.find(group).value()->layout()->addWidget(viewgroupRmv);
					}
				}
			else 	viewGroupsLayout->addWidget(viewgroupRmv);
			sVSFUIs  << viewgroup;

			}
		}
	this->adjustSize();
}

StructureViewGroupsUI* StructureViewGroupsUI::GetUI()
{
	if (p_instance == 0)
		p_instance = new StructureViewGroupsUI();
	return p_instance;
}

void StructureViewGroupsUI::btn_Clicked(QString btn)
{
	//qDebug() << btn;
	if(btn.contains("Settings")){
		//StructureViewGroupsUI::ShowUI(this->structureView);

		}
	else if(btn.contains("Add")){

		addViewgroup();

		}
	else if(btn.contains("Save")){
		//	qDebug() << this->save();
		this->editControllerSavePressed();
		}
	else if(btn.contains("Cancel")){
		this->editControllerCancelPressed();
		}
}

void StructureViewGroupsUI::viewGroupStyleChanged()
{
	Controller::Get()->updateLayoutViewGroups(structureView.value("Title").toString(),sVSFUIs);
}

void StructureViewGroupsUI::updateLayout()
{

	fill(this->save());
}

void StructureViewGroupsUI::removeViewgroup(QWidget* field)
{

	sVSFUIs.removeOne((StructureViewsEditUI*) field);
	updateLayout();
}

void StructureViewGroupsUI::editControllerCancelPressed()
{
	emit cancel();
	Controller::Get()->editControllerCancelPressed();
}

void StructureViewGroupsUI::editControllerSavePressed()
{
	QJsonObject savedObj = this->save();
	//qDebug() <<"SAVE: editControllerSavePressed"<< savedObj;
	if(savedObj.value("document_id") == QJsonValue::Undefined)
		Controller::Get()->storeDoc("ViewStructure",QJsonDocument(savedObj));
	else Controller::Get()->UpdateDoc(QJsonDocument(savedObj));

	Controller::Get()->editControllerCancelPressed();
}

void StructureViewGroupsUI::getFeildsNames()
{
	QStringList feildNames;
	foreach(StructureViewsEditUI* vg,sVSFUIs){
		foreach (StructureViewEdit* feild, vg->sVSFs) {
			if(!feild->label->text().trimmed().isEmpty() && !feild->getFieldsType().contains("Table"))
				feildNames << feild->label->text();
			}
		}
	emit gotFieldsNames(feildNames);
}

void StructureViewGroupsUI::getTableFields(ERPComboBox* excludeSource)
{
	QList<QList<QJsonDocument> > sourcesList;
	foreach(StructureViewsEditUI* vg,sVSFUIs){
		foreach (StructureViewEdit* feild, vg->sVSFs) {
			StructureVieweditSubFeild* svsf = feild->getTableFeild();
			if(svsf->getType().contains("Table")){
				sourcesList.append(svsf->getTableEdit()->getClmnsSources(excludeSource));
				}
			}
		}
	emit gotSourcesJson(sourcesList);
}


void StructureViewGroupsUI::paintEvent(QPaintEvent * event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(event);
}

void StructureViewGroupsUI::addViewgroup()
{
	StructureViewsEditUI * strcViewUI = new StructureViewsEditUI(0,structureView,this->restrictedTypes);
	QObject::connect(strcViewUI,SIGNAL(updateLayout()),this,SLOT(updateLayout()));

	sVSFUIs << strcViewUI;
	RemoveBtn* viewgroupRmv =  new RemoveBtn(0,strcViewUI);
	QObject::connect(viewgroupRmv,SIGNAL(remove(QWidget*)),this,SLOT(removeViewgroup(QWidget*)));
	viewgroupRmv->setAutoFillBackground(true);
	viewgroupRmv->hideRemovebtn(true);
	QObject::connect(strcViewUI->topCntrlsPreview,SIGNAL(removeClicked()),viewgroupRmv,SLOT(remove()));

	viewGroupsLayout->addWidget(viewgroupRmv,1);
}

void StructureViewGroupsUI::mousePressEvent(QMouseEvent *event){

	QWidget *child=  static_cast<QWidget *>(childAt(event->pos()));
	if  (!child)
		return;
	//else qDebug() << child->objectName();

}

