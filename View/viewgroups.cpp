#include "viewgroups.h"
#include "controller.h"

#include "structureviewgroupsui.h"


ViewGroups::ViewGroups(QWidget *parent, QJsonObject structureView, QJsonObject data, QHash<QString, FeildUI*>* fieldsgroups) : QWidget(parent)
{
	this->setObjectName("ViewGroups");
	this->structureView = structureView;
	layout = new QVBoxLayout(this);
	layout->setContentsMargins(2,2,2,2);
	//layout->setSpacing(0);
	this->fieldsgroups = fieldsgroups;

	viewgroups =  QList<ViewGroup*>();


	if(AccessController::Get()->hasAdminGroupAccess()){
		SettingsCtrlsUI* sctrlUI = new SettingsCtrlsUI();
		sctrlUI->addbtn("Settings",":/resources/icons/settings.png","settings");
		QObject::connect(sctrlUI, SIGNAL(btnClicked(QString)),this, SLOT(btn_Clicked(QString)));
		layout->addWidget(sctrlUI);
		}

	if(structureView.value("Viewgroups").isArray()){
		int d = 0;
	//	QJsonArray dataVGs =data.value("Fields").toArray();

		foreach (QJsonValue item, structureView.value("Viewgroups").toArray()) {
			ViewGroup* viewgroup = new ViewGroup(0,structureView.value("document_id").toString(),item.toObject(),data,fieldsgroups);
			QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
			spRight.setHorizontalStretch(1);
			viewgroup->setSizePolicy(spRight);

			QJsonObject viewGroupObject = item.toObject().value("Viewgroup").toObject();
			if(viewGroupObject.value("Style").toString().compare("horizontail") == 0){
				QString group = viewGroupObject.value("Group").toString().toLower().trimmed();

				if(!(group.isEmpty()) && HViewGroups.find(group) == HViewGroups.end()){

					QWidget* vW = new QWidget();
					vW->setContentsMargins(0,0,0,0);
					QHBoxLayout* HLayout = new QHBoxLayout(vW);
					HLayout->setContentsMargins(2,2,2,2);
					HLayout->addWidget(viewgroup);
					HLayout->setSpacing(1);
					HViewGroups.insert(group,vW);
					layout->addWidget(vW);
					}
				else{
					if(HViewGroups.find(group) != HViewGroups.end())
						if(HViewGroups.find(group).value()->layout()){
							HViewGroups.find(group).value()->layout()->addWidget(viewgroup);
							}
					}
				}
			else 	layout->addWidget(viewgroup);
			viewgroups  << viewgroup;

			d++;
			}
		}

}


QJsonObject ViewGroups::save()
{
	QJsonObject* entity = new QJsonObject();

	foreach(ViewGroup* vg,viewgroups ){
		vg->save(entity);
		}
	//entity.insert("Fields",fields);
	//entity.insert("Title",this->structureView.value("Title"))
	//qDebug() << __FILE__ << __LINE__  << entity;
	return *(entity);
}
/*
QHash<QString,FeildUI*> ViewGroups::Fieldsgroups = QHash<QString,FeildUI*>();
QList<ViewGroup*> ViewGroups::Viewgroups =  QList<ViewGroup*>();
ViewGroups* ViewGroups::p_instance = 0;
ViewGroups*ViewGroups::Create(QJsonObject structureView, QJsonObject data)
{
	p_instance = new ViewGroups(0,structureView, data);
	return p_instance;
}

ViewGroups* ViewGroups::Get()
{
	if(p_instance == 0)
		p_instance = new ViewGroups;
	return p_instance;
}
*/
QString ViewGroups::checkMandatory()
{
	QString errs;
	QHash<QString,FeildUI*>::iterator i = fieldsgroups->begin();
	while (i != fieldsgroups->end()) {
		QString err = i.value()->checkMandatory();
		if(!err.isEmpty()){
			if(!errs.isEmpty())
				errs.append(";");
			errs.append(err);

			}

		++i;
		}
	return errs;
}
void ViewGroups::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ViewGroups::btn_Clicked(QString btn)
{
	//qDebug() << __FILE__ << __LINE__  << btn;
	if(btn.contains("settings")){
		QObject::connect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(gotSetttingsDocument(QJsonDocument)));
		Controller::Get()->getDoc(this->structureView.value("document_id").toString());
		}
}

void ViewGroups::gotSetttingsDocument(QJsonDocument strct)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(gotSetttingsDocument(QJsonDocument)));

	this->structureView = strct.object();
	StructureViewGroupsUI::ShowUI(strct.object());
}
