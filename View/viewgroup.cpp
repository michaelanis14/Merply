#include "viewgroup.h"
#include "structureviewedit.h"


ViewGroup::ViewGroup(QWidget *parent, QString strID, QJsonObject structureView, QJsonArray data) : QWidget (parent)
{

	this->structureView = structureView;
	layout = new QVBoxLayout(this);
	layout->setContentsMargins(2,2,2,2);
	layout->setSpacing(0);
	this->setContentsMargins(2,2,2,2);
	this->setObjectName("ViewGroup");
	this->feilds =  QList<FeildUI*>();
	this->strID = strID;

//	qDebug() << structureView;
	if(structureView.value("Viewgroup").isObject()){
		QJsonObject viewgroup = structureView.value("Viewgroup").toObject();
		if(viewgroup.value("Fields").isArray()){

			int d = 0;
			//qDebug() << data.at(d);
			foreach (QJsonValue fieldVS, viewgroup.value("Fields").toArray()) {


				//qDebug() << fieldVS.toObject();
				FeildUI* feild = new FeildUI(0,strID,fieldVS.toObject(),data.at(d).toObject());
				layout->addWidget(feild);
				feilds << feild;

				//	StructureViewEdit* svE = new StructureViewEdit(0,fieldVS.toObject());
				//	layout->addWidget(svE);
				d++;
				}
			layout->addStretch();
		}
}
}

QJsonArray ViewGroup::save()
{
	QJsonArray fields;
	foreach(FeildUI* feild,feilds)
		fields.append(feild->save());
	return fields;

}
