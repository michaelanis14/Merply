#include "viewgroups.h"


ViewGroups::ViewGroups(QWidget *parent, QJsonObject structureView, QJsonObject data) : QWidget(parent)
{
	this->setObjectName("ViewGroups");
	layout = new QVBoxLayout(this);
	layout->setContentsMargins(2,2,2,2);
	layout->setSpacing(0);
	this->viewgroups =  QList<ViewGroup*>();
	this->structureView = structureView;

	SettingsCtrlsUI* sctrlUI = new SettingsCtrlsUI();
	sctrlUI->addbtn("Settings",":/resources/icons/settings.png","settings");
	QObject::connect(sctrlUI, SIGNAL(btnClicked(QString)),this, SLOT(btn_Clicked(QString)));
	layout->addWidget(sctrlUI);


	if(structureView.value("Viewgroups").isArray()){
		foreach (QJsonValue item, structureView.value("Viewgroups").toArray()) {
			ViewGroup* viewgroup = new ViewGroup(0,item.toObject(),data);

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
				else HViewGroups.find(group).value()->layout()->addWidget(viewgroup);
				}
			else 	layout->addWidget(viewgroup);
			viewgroups << viewgroup;

			}
		}

}

QJsonDocument ViewGroups::save()
{
	QJsonObject entity;
	QJsonArray fields;
	foreach(ViewGroup* vg,viewgroups){
		fields << vg->save();
        fields.append(vg->save());
		}
	entity.insert("Fields",fields);
	//entity.insert("Title",this->structureView.value("Title"))
	qDebug() << entity;
	return QJsonDocument(entity);
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
	//qDebug() << btn;
	if(btn.contains("settings")){
		StructureViewGroupsUI::ShowUI(this->structureView);

		}
}
