#include "structureviewedit.h"
#include "removebtn.h"
#include <QWidget>
#include <QPushButton>

StructureViewEdit::StructureViewEdit(QWidget *parent, QJsonValue fieldVS, bool links) : QWidget(parent)
{



	this->setContentsMargins(2,2,2,2);

	this->links = links;
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

	QObject::connect(label,SIGNAL(textEdited(QString)),this,SLOT(updatePreview()));
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
	saveObject.insert("Label",label->text());
	QJsonArray subFields;
	foreach(StructureVieweditSubFeild* svsf, sVSFs){
		subFields.append(svsf->save());
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

void StructureViewEdit::fill(QJsonObject structureView)
{
	if(!structureView.isEmpty() ){
		this->structureView = structureView;
		label->setText(structureView.value("Label").toString());
		label->setMinimumWidth(100);
		if(structureView.value("SubFields").isArray() && structureView.value("SubFields").toArray().count() > 0){
			foreach (QJsonValue fieldVS, structureView.value("SubFields").toArray()) {
				QString type = fieldVS.toObject().value("Type").toString();
				StructureVieweditSubFeild * svsf = new StructureVieweditSubFeild(this);
				svsf->fillTypeFields(type,fieldVS,this->links);
				sVSFs << svsf;
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
	if(sctrlUI) sctrlUI->setHidden(hidden);

	preview->setHidden(!hidden);
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
		previewLayout->addWidget(new FeildUI(0,"this->strID",this->save()));
		}
	else if(!this->structureView.isEmpty()){
		previewLayout->addWidget(new FeildUI(0,"this->strID",this->structureView));
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
	if(links)
		type = "Link";
	StructureVieweditSubFeild * svsf = new StructureVieweditSubFeild(this);
	svsf->fillTypeFields(type,QJsonObject(),this->links);
	sVSFs << svsf;
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


