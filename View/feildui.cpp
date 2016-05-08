#include "feildui.h"



FeildUI::FeildUI(QWidget *parent, QJsonObject structureView, QJsonObject data) : QWidget(parent)
{

	//qDebug() << structureView;

	this->layout = new QHBoxLayout(this);
	this->layout->setContentsMargins(0,0,0,0);
	this->setContentsMargins(0,0,0,0);
	this->layout->setSpacing(0);

	if(structureView.value("Label") != QJsonValue::Undefined){
		label = new QLabel(structureView.value("Label").toString());
		//qDebug() << structureView.value("Label").toString();
		}
	layout->addWidget(label);

	if(structureView.value("SubFields").isArray()){
		int d = 0;
		QJsonArray dataSubFields = data.value(structureView.value("Label").toString()).toArray();
		foreach (QJsonValue fieldVS, structureView.value("SubFields").toArray()) {
			//qDebug() << dataSubFields.at(d);
			SubFieldUI* subfeild = new SubFieldUI(0,fieldVS.toObject(),dataSubFields.at(d));
			layout->addWidget(subfeild);
			subFields << subfeild;

			d++;
			}

		}
}

QJsonObject FeildUI::save()
{
	QJsonObject field;
	QJsonArray subfieldsValues;
	foreach(SubFieldUI* subfeild,subFields){
		subfieldsValues.append(subfeild->save());
		}
	field.insert(this->label->text(),subfieldsValues);
	return field;
}

void FeildUI::btnRemovePressed()
{
	QList<QWidget *> Widgets = this->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		layout->removeWidget(child);
		child->setHidden(true);
		child->setParent(0);
		child->deleteLater();  // TODO : check the stability of the app
		this->deleteLater();
		}
}
void FeildUI::mousePressEvent(QMouseEvent *event){
	QLabel *child=  static_cast<QLabel *>(childAt(event->pos()));
	if  (!child)
		return;
	else {
		if( child->objectName().compare("14") == 0){
			if(child->parent())
				if(child->parent()->parent()){
					//	MainController::Get()->updateCommand("TESTT",((value*)child->parent())->dataModel_);
					//	MainController::Get()->saveModel();
					//	optionalPropertyLayout->addWidget(new value(((value*)child->parent())->field_,((value*)child->parent())->dataModel_));
					}
			}
		else if(child->objectName().compare("13") == 0){
			//btnRemovePressed();
			}
		}
	event->accept();
	QWidget::mousePressEvent(event);

}


