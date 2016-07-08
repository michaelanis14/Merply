#include "feildui.h"
#include "removebtn.h"
#include "QPushButton"

FeildUI::FeildUI(QWidget *parent, QString strID, QJsonObject structureView, QJsonObject data) : QWidget(parent)
{

	//qDebug() << structureView;

	this->layout = new QHBoxLayout(this);
	this->layout->setContentsMargins(0,0,0,0);
	this->setContentsMargins(0,0,0,0);
	this->layout->setSpacing(0);
	this->strID = strID;
	this->structureView = structureView;
	this->subFields = QList<SubFieldUI*>();

	if(structureView.value("Label") != QJsonValue::Undefined){
		label = new QLabel(structureView.value("Label").toString());
		}
	layout->addWidget(label);

	QWidget*fieldsWidget = new QWidget(this);
	fieldsWidget->setContentsMargins(0,0,0,0);
	fieldsWidget->setObjectName("fieldsWidget");
	fieldsWidgetLayout = new QVBoxLayout(fieldsWidget);
	fieldsWidgetLayout->setSpacing(0);
	fieldsWidgetLayout->setMargin(0);
	layout->addWidget(fieldsWidget);


	if(structureView.value("SubFields").isArray()){
		QWidget*subFieldsWidget = new QWidget(this);
		subFieldsWidget->setContentsMargins(0,0,0,0);
		subFieldsWidget->setObjectName("subFieldsWidget");
		QHBoxLayout* subFieldsWidgetLayout = new QHBoxLayout(subFieldsWidget);
		subFieldsWidgetLayout->setSpacing(0);
		subFieldsWidgetLayout->setMargin(0);
		fieldsWidgetLayout->addWidget(subFieldsWidget);

		if(structureView.value("ArrayList") != QJsonValue::Undefined   && structureView.value("ArrayList").toBool()){

			QJsonArray arrDataSubFields = data.value(structureView.value("Label").toString()).toArray();
			if(arrDataSubFields.isEmpty())
				goto emptyData;

			int counter = 0;
			foreach (QJsonValue field, arrDataSubFields) {
				if(counter == 0){
					int d = 0;
					QJsonArray dataSubFields = field.toArray();
					foreach (QJsonValue fieldVS, structureView.value("SubFields").toArray()) {
						SubFieldUI* subfeild = new SubFieldUI(0,this->strID,fieldVS.toObject(),dataSubFields.at(d));
						subFieldsWidgetLayout->addWidget(subfeild);
						subFields << subfeild;
						d++;
						}
					}
				else{
					addsubFields(field.toArray());
					}
				counter++;
				}
			}

		else{
emptyData:
			int d = 0;
			QJsonArray dataSubFields = data.value(structureView.value("Label").toString()).toArray();
			foreach (QJsonValue fieldVS, structureView.value("SubFields").toArray()) {
				SubFieldUI* subfeild = new SubFieldUI(0,this->strID,fieldVS.toObject(),dataSubFields.at(d));
				subFieldsWidgetLayout->addWidget(subfeild);
				subFields << subfeild;
				d++;
				}
			}

		}

	if(structureView.value("ArrayList") != QJsonValue::Undefined   && structureView.value("ArrayList").toBool()){
		QPushButton* arrybtn = new QPushButton(tr("+"));
		QObject::connect(arrybtn,SIGNAL(clicked()),this,SLOT(addsubFields()));
		layout->addWidget(arrybtn);
		}
}

QJsonObject FeildUI::save()
{
	QJsonObject field;

	if(structureView.value("ArrayList") != QJsonValue::Undefined   && structureView.value("ArrayList").toBool()){
		QJsonArray arrySubfieldsValues;

		QJsonArray subfieldsValues;
		foreach(SubFieldUI* subfeild,subFields){
			subfieldsValues.append(subfeild->save());
			}
		arrySubfieldsValues.append(subfieldsValues);

		foreach(QWidget*w,arrySubFields){
			QJsonArray subfieldsValues;
			for (int i = 0; i < w->layout()->count(); i++){
				QWidget *widget = w->layout()->itemAt(i)->widget();
				if(widget != NULL){
					subfieldsValues.append(((SubFieldUI*)widget)->save());
					}
				}
			arrySubfieldsValues.append(subfieldsValues);
			}
		field.insert(this->label->text(),arrySubfieldsValues);
		}
	else{
		QJsonArray subfieldsValues;
		foreach(SubFieldUI* subfeild,subFields){
			subfieldsValues.append(subfeild->save());
			}
		field.insert(this->label->text(),subfieldsValues);
		}
	return field;
}

QString FeildUI::checkMandatory()
{
	foreach(SubFieldUI* subfeild,subFields){
		if(!subfeild->checkMandatory())
		return label->text();
		}
	return "";
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

void FeildUI::addsubFields(QJsonArray arrDataSubFields)
{
	QWidget*subFieldsWidget = new QWidget();
	subFieldsWidget->setContentsMargins(0,0,0,0);
	subFieldsWidget->setObjectName("subFieldsWidget");
	QHBoxLayout* subFieldsWidgetLayout = new QHBoxLayout(subFieldsWidget);
	subFieldsWidgetLayout->setMargin(0);
	int d = 0;
	foreach (QJsonValue fieldVS, structureView.value("SubFields").toArray()) {
		SubFieldUI* subfeild = new SubFieldUI(0,this->strID,fieldVS.toObject(),arrDataSubFields.at(d));
		subFieldsWidgetLayout->addWidget(subfeild);
		d++;
		}
	RemoveBtn* removArrybtn = new RemoveBtn(this,subFieldsWidget);
	QObject::connect(removArrybtn,SIGNAL(remove(QWidget*)),this,SLOT(removsubFields(QWidget*)));
	fieldsWidgetLayout->addWidget(removArrybtn);
	arrySubFields << subFieldsWidget;

}

void FeildUI::removsubFields(QWidget* subField)
{
	arrySubFields.removeOne(subField);
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


