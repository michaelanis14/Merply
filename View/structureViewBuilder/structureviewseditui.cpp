#include "structureviewseditui.h"
#include "settingsctrlsui.h"
#include "controller.h"
#include "removebtn.h"

StructureViewsEditUI::StructureViewsEditUI(QWidget *parent, QJsonObject structureView, QStringList restrictedTypes) : QWidget(parent)
{
	this->structureView = structureView;
	this->restrictedTypes = restrictedTypes;
	this->setContentsMargins(2,2,2,2);

	QVBoxLayout* structureViewGroupsUILayout = new QVBoxLayout(this);
	structureViewGroupsUILayout->setMargin(0);
	structureViewGroupsUILayout->setSpacing(0);


	QWidget* sVGUI = new QWidget(this);
	sVGUI->setContentsMargins(0,0,0,0);
	sVGUI->setObjectName("StructureViewsEditUI");
	sVGUI->setStyleSheet("QWidget#StructureViewsEditUI{ border: 2px solid gray;}");
	sVGUI->setAutoFillBackground(true);

	structureViewGroupsUILayout->addWidget(sVGUI);

	layout = new QVBoxLayout(sVGUI);
	layout->setContentsMargins(2,2,2,2);
	layout->setSpacing(0);
	layout->setAlignment(Qt::AlignTop);
	//layout->setMargin(2);

	topCntrls = new SettingsCtrlsUI();
	topCntrls->setFixedHeight(15);
	topCntrls->addbtn("edit",":/resources/icons/settings.png","Edit");
	QObject::connect(topCntrls, SIGNAL(btnClicked(QString)),this, SLOT(controller_Clicked(QString)));
	layout->addWidget(topCntrls);

	topCntrlsPreview = new SettingsCtrlsUI();
	topCntrlsPreview->hide();
	topCntrlsPreview->setFixedHeight(15);
	//:/resources/icons/save.png
	topCntrlsPreview->addbtn("Delete",":/resources/icons/remove.png","Delete");

	topCntrlsPreview->addbtn("Save",":/resources/icons/save.png","Save");
	topCntrlsPreview->addbtn("Cancel",":/resources/icons/cancel.png","Cancel");
	QObject::connect(topCntrlsPreview, SIGNAL(btnClicked(QString)),this, SLOT(controller_Clicked(QString)));
	layout->addWidget(topCntrlsPreview);


	layoutPreview = new QWidget(this);
	layoutPreview->setContentsMargins(5,0,0,0);
	layoutPreviewLayout = new QHBoxLayout(layoutPreview);
	layoutPreviewLayout->setContentsMargins(0,0,0,0);
	layoutPreviewLayout->setSpacing(0);
	layoutPreviewLayout->setAlignment(Qt::AlignLeft);
	//layoutPreviewLayout;
	layout->addWidget(layoutPreview);


	styleSelect = new QWidget();
	QHBoxLayout* styleSelectLayout = new QHBoxLayout(styleSelect);
	styleSelectLayout->setMargin(0);
	styleSelectLayout->setSpacing(0);
	layout->addWidget(styleSelect);

	QLabel* typelbl = new QLabel(tr("Layout"));
	styleSelectLayout->addWidget(typelbl);
	Style = new ERPComboBox(0);


	styles << "vertical" << "horizontail";
	Style->addItems(styles);

	styleSelectLayout->addWidget(Style);

	imgExplain = new QLabel();
	imgExplain->setFixedHeight(40);
	imgExplain->setFixedWidth(80);
	imgVertical = QPixmap(":/resources/icons/Vertical.png");
	imgHorizontal = QPixmap(":/resources/icons/Horizontal.png");

	styleSelectLayout->addWidget(imgExplain);


	joinGroup = new QWidget();
	QHBoxLayout* joinGroupLayout = new QHBoxLayout(joinGroup);
	joinGroupLayout->setMargin(0);
	joinGroupLayout->setSpacing(0);
	layout->addWidget(joinGroup);

	QLabel* joinlbl = new QLabel(tr("Join Group"));
	joinGroupLayout->addWidget(joinlbl);

	joinCheck = new QCheckBox();
	QObject::connect(joinCheck, SIGNAL(toggled(bool)),this, SLOT(joinGroupChanged(bool)));

	joinGroupLayout->addWidget(joinCheck);




	groupSelect = new QWidget();
	QHBoxLayout* groupSelectLayout = new QHBoxLayout(groupSelect);
	groupSelectLayout->setMargin(0);
	groupSelectLayout->setSpacing(0);
	layout->addWidget(groupSelect);
	groupSelect->setVisible(true);

	QLabel* grouplbl = new QLabel(tr("Group"));
	groupSelectLayout->addWidget(grouplbl);

	groupName = new QLineEdit();
	groupName->setText("General"+QString::number(Controller::Get()->getLayoutViewGroups(structureView.value("Title").toString()).count()));
	groupSelectLayout->addWidget(groupName);

	group = new QComboBox();
	//Group->setEditable(true);
	//QStringList Groups;
	//Groups  << "Main";
	//group->addItems(Groups);
	groupSelectLayout->addWidget(group);




	QObject::connect(Style, SIGNAL(currentIndexChanged(QString)),this, SLOT(styleChanged(QString)));
	QObject::connect(groupName, SIGNAL(textChanged(QString)),this, SIGNAL(styleChanged()));
	QObject::connect(group, SIGNAL(highlighted(int)),this, SLOT(groupActivated(int)));
	//QObject::connect(group, SIGNAL(),this, SLOT(groupActivated(int)));

	hidePreview(true);
	joinGroupChanged(false);


	loadStyle(); //sets the Style selectbox to trctView


	SettingsCtrlsUI* sctrlUI = new SettingsCtrlsUI();
	sctrlUI->addbtn("Add Field",":/resources/icons/add.png","add");
	QObject::connect(sctrlUI, SIGNAL(btnClicked(QString)),this, SLOT(controller_Clicked(QString)));
	sctrlUI->setAutoFillBackground(true);
	layout->addWidget(sctrlUI);
	layout->addStretch(1);

	if(structureView.value("Viewgroup").isObject()){
		QJsonObject viewgroup = structureView.value("Viewgroup").toObject();
		if(viewgroup.value("Fields").isArray())
			foreach (QJsonValue fieldVS, viewgroup.value("Fields").toArray()) {
				addStrField(fieldVS);
				}
		}
	else controller_Clicked("Add");


}

QJsonObject StructureViewsEditUI::save()
{
	QJsonObject saveObject;
	//if(!init)
	//	return saveObject;

	saveObject.insert("Style",Style->currentText());
	if(this->Style->currentText().compare("horizontail") == 0){
		if(this->joinCheck->isChecked()){
			saveObject.insert("Group",group->currentText());
			}
		else {
			saveObject.insert("Group",groupName->text());
			}
		}

	QJsonArray fields;
	foreach(StructureViewEdit * strcView,sVSFs){
		fields << strcView->save();
		}
	saveObject.insert("Fields",fields);

	return saveObject;
}

void StructureViewsEditUI::loadGroup()
{

	if(structureView.value("Viewgroup").toObject().value("Style").toString().compare("horizontail") == 0){


		QString group = structureView.value("Viewgroup").toObject().value("Group").toString();
		//qDebug() << group;
		emit styleChanged();
		//qDebug() << Controller::Get()->getLayoutViewGroups(this->entityName).contains(group);
		//if()

		if(!Controller::Get()->getLayoutViewGroups(structureView.value("Title").toString()).contains(group)){
			joinCheck->setChecked(false);
			groupName->setText(group);
			}
		else {
			joinCheck->setChecked(true);
			groupActivated(1);
			this->group->setCurrentIndex(Controller::Get()->getLayoutViewGroups(structureView.value("Title").toString()).indexOf(group));

			}
		}
	hidePreview(true);
}

bool StructureViewsEditUI::hidePreview(bool hide)
{
	if(hide){
		//clearTypeFields();
		topCntrls->setHidden(false);
		topCntrlsPreview->setHidden(true);
		updateLayoutPreview();
		layoutPreview->setHidden(false);
		styleSelect->setHidden(true);
		joinGroup->setHidden(true);
		groupSelect->setHidden(true);

		}
	else{
		//fill(this->structureView);
		topCntrls->setHidden(true);
		topCntrlsPreview->setHidden(false);
		layoutPreview->setHidden(true);
		styleSelect->setHidden(false);
		styleChanged(Style->currentText());
		}
	return true;
}

void StructureViewsEditUI::updateLayoutPreview()
{

	QList<QWidget *> Widgets = layoutPreview->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		if(child != NULL){
			layoutPreviewLayout->removeWidget(child);
			child->setHidden(true);
			//child->setParent(0);
			child->deleteLater();
			}
		}

	QLabel* layoutlbl = new QLabel("Layout:");
	layoutPreviewLayout->addWidget(layoutlbl);
	layoutPreviewLayout->addWidget(new QLabel(Style->currentText()));

	if(this->Style->currentText().compare("horizontail") == 0){
		layoutPreviewLayout->addSpacing(15);
		layoutPreviewLayout->addWidget(new QLabel("Group:"));
		if(this->joinCheck->isChecked()){
			layoutPreviewLayout->addWidget(new QLabel(group->currentText()));
			}
		else {
			layoutPreviewLayout->addWidget(new QLabel(groupName->text()));

			}
		}
	//layoutPreview->raise();
	emit changed();
}

void StructureViewsEditUI::loadStyle()
{
	if(!structureView.value("Viewgroup").toObject().value("Style").toString().isEmpty()){
		Style->setCurrentIndex(styles.indexOf(structureView.value("Viewgroup").toObject().value("Style").toString()));
		styleChanged(structureView.value("Viewgroup").toObject().value("Style").toString());
		}
	else{
		Style->setCurrentIndex(0);
		styleChanged("vertical");
		}

}

void StructureViewsEditUI::addStrField(QJsonValue fieldVS)
{

	StructureViewEdit * strcView = new StructureViewEdit(0,fieldVS,this->restrictedTypes);
	QObject::connect(strcView,SIGNAL(changed()),this,SIGNAL(changed()));
	sVSFs << strcView;
	layout->setStretch(layout->count()-1,0);
	RemoveBtn* rmvtbn =  new RemoveBtn(0,strcView);
	rmvtbn->hideRemovebtn(true);
	QObject::connect(rmvtbn,SIGNAL(remove(QWidget*)),this,SLOT(removeField(QWidget*)));
	QObject::connect(strcView->topCntrlsPreview,SIGNAL(removeClicked()),rmvtbn,SLOT(remove()));

	layout->addWidget(rmvtbn);
	layout->addStretch(1);
}

void StructureViewsEditUI::controller_Clicked(QString btn)
{

	if(btn.contains("Add")){
		addStrField(QJsonValue());

		}
	else if(btn.contains("Edit")){
		topCntrls->isHidden()?hidePreview(true):hidePreview(false);
		}
	else if(btn.contains("Save")){
		topCntrls->isHidden()?hidePreview(true):hidePreview(false);
		emit updateLayout();
		}
	else if(btn.contains("Cancel")){
		loadStyle();
		topCntrls->isHidden()?hidePreview(true):hidePreview(false);

		}
	else if(btn.contains("Delete")){

		}
}

void StructureViewsEditUI::styleChanged(QString layout)
{

	int w = imgExplain->width();
	int h = imgExplain->height();
	if(layout.contains("vertical")){
		imgExplain->setPixmap(imgVertical.scaled(w,h,Qt::KeepAspectRatio));
		groupSelect->setHidden(true);
		joinGroup->setHidden(true);


		}
	else {
		imgExplain->setPixmap(imgHorizontal.scaled(w,h,Qt::KeepAspectRatio));
		groupActivated(0);
		groupSelect->setHidden(false);
		joinGroup->setHidden(false);
		}

}

void StructureViewsEditUI::joinGroupChanged(bool join)
{
	emit styleChanged();
	if(join){
		groupName->setHidden(true);

		groupActivated(0);
		group->setHidden(false);

		}
	else {
		groupName->setHidden(false);
		group->setHidden(true);
		}
}

void StructureViewsEditUI::groupActivated(int)
{
	//group->blockSignals(true);
	group->clear();
	emit styleChanged();
	group->addItems(Controller::Get()->getLayoutViewGroups(structureView.value("Title").toString()));
	group->setCurrentIndex(0);
	//group->blockSignals(false);
}

void StructureViewsEditUI::removeField(QWidget* field)
{
	sVSFs.removeOne((StructureViewEdit *)field);
}

