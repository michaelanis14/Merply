#include "structureviewedit.h"
#include "removebtn.h"
#include <QWidget>
#include <QPushButton>

StructureViewEdit::StructureViewEdit(QWidget *parent, QJsonValue fieldVS, QStringList restrictedTypes) : QWidget(parent)
{



	this->setContentsMargins(2,2,2,2);

	this->restrictedTypes = restrictedTypes;
	this->structureView = fieldVS.toObject();

	layout = new QHBoxLayout(0);
	layout->setContentsMargins(2,2,2,2);
	layout->setSpacing(0);
	layout->setMargin(0);


	QVBoxLayout* widgetsLayout = new QVBoxLayout();
	widgetsLayout->setContentsMargins(0,0,0,0);
	widgetsLayout->setSpacing(0);
	widgetsLayout->setMargin(1);

	topCntrls = new SettingsCtrlsUI();
	topCntrls->setFixedHeight(15);
	topCntrls->addbtn("edit",":/resources/icons/settings.png","Edit");
	QObject::connect(topCntrls, SIGNAL(btnClicked(QString)),this, SLOT(controller_Clicked(QString)));
	widgetsLayout->addWidget(topCntrls);


	topCntrlsPreview = new SettingsCtrlsUI();
	topCntrlsPreview->hide();
	topCntrlsPreview->setFixedHeight(15);
	//:/resources/icons/save.png
	topCntrlsPreview->addbtn("Delete",":/resources/icons/remove.png","Delete");

	topCntrlsPreview->addbtn("Save",":/resources/icons/save.png","Save");
	topCntrlsPreview->addbtn("Cancel",":/resources/icons/cancel.png","Cancel");
	QObject::connect(topCntrlsPreview, SIGNAL(btnClicked(QString)),this, SLOT(controller_Clicked(QString)));
	widgetsLayout->addWidget(topCntrlsPreview);

	//if(!links){
	sctrlUI = new SettingsCtrlsUI();
	sctrlUI->addbtn("Add",":/resources/icons/add.png","add");
	QObject::connect(sctrlUI, SIGNAL(btnClicked(QString)),this, SLOT(controller_Clicked(QString)));
	//sctrlUI->setAutoFillBackground(true);
	layout->addWidget(sctrlUI);

	//}

	preview = new QWidget(0);
	preview->setContentsMargins(0,0,0,0);
	//preview->setMinimumHeight(35);
	preview->setObjectName("preview");
	previewLayout = new QHBoxLayout(preview);
	previewLayout->setContentsMargins(0,0,0,0);
	previewLayout->setSpacing(0);
	//previewLayout->setMargin(1);
	//this->setStyleSheet();
	layout->addWidget(preview);
	//QLabel * preview = new QLabel("Preview :",0);
	//previewLayout->addWidget(preview);


	label = new QLineEdit();

	//TODO:   QObject::connect(label,SIGNAL(textEdited(QString)),this,SLOT(updatePreview()));
	label->setText(tr("New Field"));
	//labelWidget = new QWidget();
	//labelWidget->setContentsMargins(0,0,0,0);
	//labelWidget->setVisible(true);
	//QVBoxLayout* labelWidgetLayout = new QVBoxLayout(labelWidget);
	//labelWidgetLayout->setContentsMargins(0,0,5,0);
	//labelWidgetLayout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
	//labelWidgetLayout->setLabelAlignment(Qt::AlignLeft);
	//labelWidgetLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
	//labelWidgetLayout->setSpacing(0);
	//labelWidgetLayout->setMargin(0);
	//labelWidgetLayout->setAlignment(Qt::AlignLeft);
	//labelWidgetLayout->addWidget(label);
	layout->addWidget(label,0,Qt::AlignTop);


	hideLabel = new QCheckBox(tr("HL"));
	hideField = new QCheckBox(tr("HF"));
	initData = new QCheckBox(tr("SID"));
	indexField = new QCheckBox(tr("I"));
	showInIdexView = new QCheckBox(tr("SIV"));
	showInIdexView->setChecked(true);
	layout->addWidget(hideLabel,0,Qt::AlignTop);
	layout->addWidget(hideField,0,Qt::AlignTop);
	layout->addWidget(initData,0,Qt::AlignTop);
	layout->addWidget(indexField,0,Qt::AlignTop);
	layout->addWidget(showInIdexView,0,Qt::AlignTop);

	arrayWidget = new QWidget(this);
	arrayWidget->setContentsMargins(2,0,2,0);
	arrayWidget->setObjectName("arrayWidget");
	QHBoxLayout* arrayWidgetLayout = new QHBoxLayout(arrayWidget);
	arrayWidgetLayout->setSpacing(0);
	arrayWidgetLayout->setMargin(0);
	layout->addWidget(arrayWidget);
	QLabel * arraylbl = new QLabel(tr("Array"));
	arrayWidgetLayout->addWidget(arraylbl,0,Qt::AlignTop);
	array = new QCheckBox();
	arrayWidgetLayout->addWidget(array,0,Qt::AlignTop);
	//arrayWidgetLayout->addStretch(1);


	typeFields = new QWidget(this);
	typeFields->setContentsMargins(0,0,0,0);

	typeFields->setObjectName("typeFields");
	typeFieldsLayout = new QHBoxLayout(typeFields);
	typeFieldsLayout->setContentsMargins(2,2,2,2);
	typeFieldsLayout->setSpacing(0);
	typeFieldsLayout->setMargin(0);
	layout->addWidget(typeFields);


	//QPushButton* btnPreview = new QPushButton("Preview");
	//QObject::connect(btnPreview,SIGNAL(pressed()),this,SLOT(updatePreview()));
	//layout->addWidget(btnPreview,0,Qt::AlignRight);



	//this->fill(structureView);


	//this->controller_Clicked("Edit");
	//hideTypeFields();

	//fill(fieldVS.toObject());

	widgetsLayout->addLayout(layout);
	this->setLayout(widgetsLayout);
	this->fill(this->structureView);
	this->setHidden(true);

}



QJsonObject StructureViewEdit::save()
{
	QJsonObject saveObject;
	saveObject.insert("Label",label->text().trimmed());
	if(label->text().trimmed().isEmpty())
		label->setText("F"+QString::number(rand()));
	if(hideLabel->isChecked())
		saveObject.insert("LabelHidden",true);
	if(hideField->isChecked())
		saveObject.insert("FieldHidden",true);
	if(initData->isChecked())
		saveObject.insert("initData",true);
	if(indexField->isChecked())
		saveObject.insert("IndexField",true);
	if(showInIdexView->isChecked())
		saveObject.insert("ShowInIndex",true);

	saveObject.insert("ArrayList",array->isChecked());
	QJsonArray subFields;
	foreach(StructureVieweditSubFeild* svsf, sVSFs){
		QJsonObject sSFSave = svsf->save();

		if(initData->isChecked()){
			QJsonObject* savedPreview;
			previewField->save(savedPreview);
			//	qDebug() << __FILE__ << __LINE__  << savedPreview;
			if(savedPreview->keys().count() > 0 && savedPreview->value(savedPreview->keys().first()) != QJsonValue::Undefined){
				QJsonObject tblObj = savedPreview->value(savedPreview->keys().first()).toArray().first().toObject();
				//	qDebug() << __FILE__ << __LINE__  << tblObj;
				sSFSave.insert("initData",tblObj);
				}
			}
		subFields.append(sSFSave);
		}
	saveObject.insert("SubFields",subFields);
	return saveObject;
}

void StructureViewEdit::showTypeFields()
{
	typeFields->setHidden(false);
}

void StructureViewEdit::hideTypeFields()
{
	typeFields->setHidden(true);
}

QStringList StructureViewEdit::getFieldsType()
{
	QStringList types;
	foreach(StructureVieweditSubFeild* svsf, sVSFs){
		types.append(svsf->getType());
		}
	return types;
}

StructureVieweditSubFeild* StructureViewEdit::getTableFeild()
{
	foreach(StructureVieweditSubFeild* svsf, sVSFs){
		if(svsf->getType().compare("Table") == 0)
			return svsf;
		}
	return new StructureVieweditSubFeild();
}

void StructureViewEdit::fill(QJsonObject structureView)
{
	if(!structureView.isEmpty() ){
		this->structureView = structureView;
		if(structureView.value("Label").toString().isEmpty())
			label->setText("F"+QString::number(rand()));
		else
			label->setText(structureView.value("Label").toString());
		label->setMinimumWidth(100);
		if(structureView.value("LabelHidden") != QJsonValue::Undefined)
			hideLabel->setChecked(true);
		if(structureView.value("FieldHidden") != QJsonValue::Undefined)
			hideLabel->setChecked(true);
		if(structureView.value("initData") != QJsonValue::Undefined)
			initData->setChecked(true);
		if(structureView.value("IndexField") != QJsonValue::Undefined)
			indexField->setChecked(true);
		if(structureView.value("ShowInIndex") != QJsonValue::Undefined)
			showInIdexView->setChecked(true);
		else showInIdexView->setChecked(false);


		if(structureView.value("SubFields").isArray() && structureView.value("SubFields").toArray().count() > 0){
			foreach (QJsonValue fieldVS, structureView.value("SubFields").toArray()) {
				QString type = fieldVS.toObject().value("Type").toString();
				StructureVieweditSubFeild * svsf = new StructureVieweditSubFeild(this);
				sVSFs << svsf;
				svsf->fillTypeFields(type,fieldVS,this->restrictedTypes);

				QObject::disconnect(svsf,SIGNAL(changed()),this,SLOT(updatePreview()));
				QObject::connect(svsf,SIGNAL(changed()),this,SLOT(updatePreview()));

				RemoveBtn* rmvtbn =  new RemoveBtn(0,svsf);
				QObject::connect(rmvtbn,SIGNAL(remove(QWidget*)),this,SLOT(removeField(QWidget*)));
				typeFieldsLayout->addWidget(rmvtbn,1,Qt::AlignLeft);

				//typeFieldsLayout->addWidget(svsf,1,Qt::AlignLeft);
				//typeFieldsLayout->addWidget(svsf,1,Qt::AlignLeft);
				}

			}
		else this->addField();

		}
	else this->addField();

	this->updatePreview(true);
}

void StructureViewEdit::clearTypeFields()
{
	sVSFs.clear();
	QList<QWidget *> Widgets = typeFields->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		if(child != NULL){
			typeFieldsLayout->removeWidget(child);
			child->setHidden(true);
			//child->setParent(0);
			child->deleteLater();
			}
		}
}

bool StructureViewEdit::setHidden(bool hidden)
{

	typeFields->setHidden(hidden);
	label->setHidden(hidden);
	arrayWidget->setHidden(hidden);
	hideLabel->setHidden(hidden);
	hideField->setHidden(hidden);
	initData->setHidden(hidden);
	indexField->setHidden(hidden);
	showInIdexView->setHidden(hidden);

	if(sctrlUI) sctrlUI->setHidden(hidden);

	//preview->setHidden(hidden);
	if(hidden){
		topCntrls->setHidden(false);
		topCntrlsPreview->setHidden(true);
		}
	else{
		clearTypeFields();
		fill(this->structureView);
		topCntrls->setHidden(true);
		topCntrlsPreview->setHidden(false);
		}


	return true;
}

void StructureViewEdit::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void StructureViewEdit::updatePreview(bool oldStrct)
{

	QList<QWidget *> Widgets = preview->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		if(child != NULL){
			previewLayout->removeWidget(child);
			child->setHidden(true);
			//child->setParent(0);
			child->deleteLater();
			}
		}

	if(!oldStrct){
		previewField = new FeildUI(0,"this->strID",this->save());
		previewLayout->addWidget(previewField);
		}
	else if(!this->structureView.isEmpty()){
		previewField = new FeildUI(0,"this->strID",this->structureView);
		previewLayout->addWidget(previewField);
		}

	emit changed();
	//<< typeSelect->currentText();
}

void StructureViewEdit::controller_Clicked(QString btn)
{

	if(btn.contains("Edit"))
		typeFields->isHidden()?setHidden(false):setHidden(true);

	else if(btn.contains("Cancel")){
		this->setHidden(true);
		this->updatePreview(true);
		}
	else if(btn.contains("Save")){
		this->structureView = this->save();
		this->updatePreview(false);
		setHidden(true);
		}
	else if(btn.contains("Add")){
		addField();

		}
}

void StructureViewEdit::addField()
{
	QString type = "Text";
	if(restrictedTypes.contains("Links"))
		type = "Link";
	StructureVieweditSubFeild * svsf = new StructureVieweditSubFeild(this);
	svsf->fillTypeFields(type,QJsonObject(),this->restrictedTypes);
	sVSFs << svsf;
	QObject::disconnect(svsf,SIGNAL(changed()),this,SLOT(updatePreview()));
	QObject::connect(svsf,SIGNAL(changed()),this,SLOT(updatePreview()));

	RemoveBtn* rmvtbn =  new RemoveBtn(0,svsf);
	QObject::connect(rmvtbn,SIGNAL(remove(QWidget*)),this,SLOT(removeField(QWidget*)));
	typeFieldsLayout->addWidget(rmvtbn,1,Qt::AlignLeft);

	//typeFieldsLayout->addWidget(svsf,1,Qt::AlignLeft);

	//typeFieldsLayout->addWidget(svsf,1,Qt::AlignLeft);
	this->structureView = this->save();

}

void StructureViewEdit::removeField(QWidget* field)
{
	sVSFs.removeOne((StructureVieweditSubFeild *)field);
}


