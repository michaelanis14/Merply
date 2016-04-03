#include "viewgroup.h"
#include "structureviewedit.h"


ViewGroup::ViewGroup(QWidget *parent, QJsonObject structureView, QJsonObject data) : QWidget (parent)
{

	this->structureView = structureView;
	this->data = data;
	layout = new QVBoxLayout(this);
	layout->setContentsMargins(2,2,2,2);
	layout->setSpacing(0);
	this->setContentsMargins(2,2,2,2);
	this->setObjectName("ViewGroup");
	this->feilds =  QList<FeildUI*>();


	if(structureView.value("Viewgroup").isObject()){
		QJsonObject viewgroup = structureView.value("Viewgroup").toObject();
		if(viewgroup.value("Fields").isArray())
			foreach (QJsonValue fieldVS, viewgroup.value("Fields").toArray()) {


				//qDebug() << fieldVS.toObject();
				FeildUI* feild = new FeildUI(0,fieldVS.toObject(),data);
				layout->addWidget(feild);
				feilds << feild;

			//	StructureViewEdit* svE = new StructureViewEdit(0,fieldVS.toObject());
			//	layout->addWidget(svE);

				}
		}

}

QJsonArray ViewGroup::save()
{
	QJsonArray fields;
	foreach(FeildUI* feild,feilds)
		fields << feild->save();
        fields.append(feild->save());
	return fields;

}
