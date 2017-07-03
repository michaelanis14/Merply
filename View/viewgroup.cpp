#include "viewgroup.h"
#include "structureviewedit.h"


ViewGroup::ViewGroup(QWidget *parent, QString strID, QJsonObject structureView, QHash<QString,FeildUI*>* fieldsgroups,QDataWidgetMapper *mapper ) : QGroupBox (parent)
{

	this->structureView = structureView;

	layout = new QVBoxLayout(this);

	//layout->setContentsMargins(2,2,2,2);
	//layout->setSpacing(0);
	//this->setContentsMargins(2,2,2,2);
	//this->setObjectName("ViewGroup");
	this->feilds =  QList<FeildUI*>();
	this->strID = strID;
	//qDebug() << __FILE__ << __LINE__  << structureView.value("Viewgroup").toObject().value("GroupTitle").toString();
		//qDebug() << __FILE__ << __LINE__  << structureView;
	if(structureView.value("Viewgroup").isObject()){

		QJsonObject viewgroup = structureView.value("Viewgroup").toObject();
		this->setTitle(viewgroup.value("GroupTitle").toString());

		if(viewgroup.value("Fields").isArray()){
			int d = 0;
			//qDebug() << __FILE__ << __LINE__  << data.at(d);
			foreach (QJsonValue fieldVS, viewgroup.value("Fields").toArray()) {
				//qDebug() << __FILE__ << __LINE__  << fieldVS.toObject();
				FeildUI* feild = new FeildUI(0,strID,fieldVS.toObject(),mapper);
				feilds << feild;
				fieldsgroups->insert(fieldVS.toObject().value("Label").toString().trimmed(),feild);
				layout->addWidget(feild);
				d++;
				}
			layout->addStretch();
			}
		}
}

void ViewGroup::save(QPair<QString,QString> *insertQuery,bool newDocument)
{
	foreach(FeildUI* feild,feilds)
		feild->save(insertQuery,newDocument);
}
