#include "navigationpageeditui.h"
#include "settingsctrlsui.h"
#include "erpcombobox.h"
#include "controller.h"
#include "structureviewgroupsui.h"

#include "viewgroups.h"
#include "pageui.h"


NavigationPageEditUI::NavigationPageEditUI(QWidget *parent) : MainDisplay(parent)
{



	this->setContentsMargins(0,0,0,0);
	layout = new QVBoxLayout(formPanel);
	layout->setSpacing(0);
	layout->setMargin(0);




	headerlbl = new HeaderLabel();
	//if(!structureView.value("Title").toString().isEmpty()) //"structureView.value("Title").toString()"
	headerlbl->setTitle("Page");
	//else headerlbl->setTitle("New Card"+QString::number(Controller::Get()->Count("ViewStructure")));
	layout->addWidget(headerlbl);

	SettingsCtrlsUI* sctrlUI = new SettingsCtrlsUI();
	sctrlUI->addbtn("Adddd",":/resources/icons/add.png","add");
	sctrlUI->addbtn("Save",":/resources/icons/save.png","save");

	sctrlUI->addbtn("Cancel",":/resources/icons/cancel.png","cancel");

	QObject::connect(sctrlUI, SIGNAL(btnClicked(QString)),this, SLOT(btn_Clicked(QString)));
	sctrlUI->setAutoFillBackground(true);
	layout->addWidget(sctrlUI);




	QGroupBox *groupBox = new QGroupBox(tr("Select Type"));

	newCard = new QRadioButton(tr("&New Card"));
	connect(newCard,SIGNAL(toggled(bool)),this,SLOT(newCardToggled(bool)));

	card = new QRadioButton(tr("&Card Refrence"));
	connect(card,SIGNAL(toggled(bool)),this,SLOT(cardToggled(bool)));

	page = new QRadioButton(tr("Custom Page"));
	connect(page,SIGNAL(toggled(bool)),this,SLOT(pageToggled(bool)));

	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget(newCard);
	hbox->addWidget(card);
	hbox->addWidget(page);
	hbox->addStretch(1);
	groupBox->setLayout(hbox);
	layout->addWidget(groupBox);



	viewBox = new QGroupBox(tr("View Details"));
	QFormLayout* viewBoxLayout = new QFormLayout;
	viewBox->setLayout(viewBoxLayout);
	viewBoxLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
	viewBoxLayout->setLabelAlignment(Qt::AlignLeft);
	view = new ERPComboBox(this,false);
	viewList << "Index" << "New";
	view->addItems(viewList);
	//QObject::connect(view,SIGNAL(currentIndexChanged(int)),this,SLOT(updatePreview()));
	viewBoxLayout->addRow(tr("View"),view);
	layout->addWidget(viewBox);


	newCardDetails = new QGroupBox(tr("New Card Details"));
	QHBoxLayout* newCardDetailsLayout = new QHBoxLayout;
	newCardDetails->setLayout(newCardDetailsLayout);

	newCardStructure = new StructureViewGroupsUI();
	newCardStructure->headerlbl->setHidden(true);
	newCardStructure->sctrlUI->ctrlBtns->value(1)->setHidden(true);
	newCardStructure->sctrlUI->ctrlBtns->value(2)->setHidden(true);
	newCardDetailsLayout->addWidget(newCardStructure);
	layout->addWidget(newCardDetails);


	cardDetails = new QGroupBox(tr("Card Details"));
	QFormLayout* cardDetailsLayout = new QFormLayout;
	cardDetails->setLayout(cardDetailsLayout);
	cardDetailsLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
	cardDetailsLayout->setLabelAlignment(Qt::AlignLeft);
	cards = new ERPComboBox(this,false);
	cardDetailsLayout->addRow(tr("Card"),cards);

	QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(getCardData(QList<QJsonDocument>)));
	Controller::Get()->getJsonList("ViewStructure","Title","default.Type =\"Entity\"");

	//cardDetailsLayout->addRow(tr("View"),view);
	layout->addWidget(cardDetails);



	pageDetails = new QGroupBox(tr("Page Details"));
	QHBoxLayout* pageDetailsLayout = new QHBoxLayout;
	pageDetails->setLayout(pageDetailsLayout);
	pageEdit = new PageStructureViewEditeUI();
	pageEdit->sctrlUI->ctrlBtns->value(1)->setHidden(true);
	pageEdit->sctrlUI->ctrlBtns->value(2)->setHidden(true);
	pageDetailsLayout->addWidget(pageEdit);
	layout->addWidget(pageDetails);

	permissions = new PermissionsUI();
	layout->addWidget(permissions);

	preview = new QGroupBox(tr("Preview"));
	previewLayout = new QHBoxLayout;
	preview->setLayout(previewLayout);
	layout->addWidget(preview);

	cardDetails->setHidden(true);
	pageDetails->setHidden(true);
	newCardDetails->setHidden(true);
	layout->addStretch(1);


	QObject::connect(this, SIGNAL(editControllerCancelPressed()), newCardStructure, SLOT(editControllerCancelPressed()));
	QObject::connect(this, SIGNAL(editControllerSavePressed()), newCardStructure, SLOT(editControllerSavePressed()));


	connect(newCard,SIGNAL(toggled(bool)),this,SLOT(updatePreview()));
	connect(card,SIGNAL(toggled(bool)),this,SLOT(updatePreview()));
	connect(page,SIGNAL(toggled(bool)),this,SLOT(updatePreview()));
	QObject::connect(cards,SIGNAL(currentIndexChanged(int)),this,SLOT(updatePreview()));
	//connect(newCard,SIGNAL(toggled(bool)),this,SLOT(updatePreview()));
	//connect(newCard,SIGNAL(toggled(bool)),this,SLOT(updatePreview()));

	QObject::connect(cards,SIGNAL(currentIndexChanged(int)),this,SLOT(updatePreview()));

}

NavigationPageEditUI* NavigationPageEditUI::p_instance = 0;
void NavigationPageEditUI::ShowUI(QJsonObject structureView) {

	if(p_instance == 0){
		p_instance = new NavigationPageEditUI();
		p_instance->setObjectName("NavigationPageEditUI");
		}
	//p_instance->clear();
	p_instance->fill(structureView);
	MainForm::Get()->ShowDisplay(p_instance);
}

void NavigationPageEditUI:: fill(QJsonObject structureView)
{

	this->structureView = structureView;
	cards->clear();
	QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(getCardData(QList<QJsonDocument>)));
	Controller::Get()->getJsonList("ViewStructure","Title","default.Type =\"Entity\"");

	//if(!structureView.value("Title").toString().isEmpty())
	//	this->headerlbl->setTitle(structureView.value("Title").toString());
	if(structureView.value("Type").toString().compare("Entity") == 0){
		//if(structureView.value("Title").toString().isEmpty())
		//	this->headerlbl->setTitle(tr("New Card"));
		card->setChecked(true);
		cardToggled(true);
		cards->setCurrentIndex(cards->keys.indexOf(structureView.value("Card").toString()));
		view->setCurrentIndex(viewList.indexOf(structureView.value("Select").toString()));
		}
	else{
		//if(structureView.value("Title").toString().isEmpty())
		//	this->headerlbl->setTitle(tr("New Page"));
		page->setChecked(true);
		pageToggled(true);
		pageEdit->fill(structureView);
		}


	permissions->load(structureView.value("Permissions").toObject());
}

QJsonObject NavigationPageEditUI::save()
{
	QJsonObject save;
	if(page->isChecked()){
		save = pageEdit->save();
		save.insert("Type","Page");

		}
	else if(card->isChecked()){
		save.insert("Card",cards->getKey());
		save.insert("Select",view->currentText());
		save.insert("Type","Entity");

		}
	else if(newCard->isChecked()){
		newCardStructure->headerlbl->setTitle(this->headerlbl->getTitle());
		newCardStructure->editControllerSavePressed();
		save.insert("Card",Controller::getLastKeyID());
		save.insert("Select",view->currentText());
		save.insert("Type","Entity");
		}
	save.insert("Title",headerlbl->getTitle());
	save.insert("Permissions",permissions->save());
	return save;
}

NavigationPageEditUI*NavigationPageEditUI::Get()
{
	if(p_instance == 0){
		p_instance = new NavigationPageEditUI();
		p_instance->setObjectName("NavigationPageEditUI");
		}
	return p_instance;
}

void NavigationPageEditUI::btn_Clicked(QString btn)
{
	if(btn.contains("Settings")){
		//StructureViewGroupsUI::ShowUI(this->structureView);

		}
	else if(btn.contains("Add")){

		//	addViewgroup();
		}
	else if(btn.contains("Save")){
		//	qDebug() << this->save();
		//Controller::Get()->storeDoc("ViewStructure",QJsonDocument(this->save()));
		emit editControllerSavePressed();
		}
	else if(btn.contains("Cancel")){
		emit editControllerCancelPressed();
		//emit cancel();
		}
}

void NavigationPageEditUI::newCardToggled(bool state)
{
	if(state){
		newCardDetails->setHidden(false);
		headerlbl->setEnabled(true);
		headerlbl->setTitle("New Card");
		viewBox->setHidden(false);
		}
	else{
		newCardDetails->setHidden(true);
		}
}

void NavigationPageEditUI::cardToggled(bool state)
{
	if(state){
		this->headerlbl->setTitle(structureView.value("Title").toString());
		headerlbl->setEnabled(false);
		cardDetails->setHidden(false);
		viewBox->setHidden(false);

		}
	else {
		cardDetails->setHidden(true);

		}
}

void NavigationPageEditUI::pageToggled(bool state)
{

	if(state){
		headerlbl->setEnabled(true);
		this->headerlbl->setTitle(structureView.value("Title").toString());
		pageDetails->setHidden(false);
		if(structureView.value("Title").toString().isEmpty())
			this->headerlbl->setTitle(tr("New Page"));
		viewBox->setHidden(true);

		}
	else{
		pageDetails->setHidden(true);
		viewBox->setHidden(false);
		}
}

void NavigationPageEditUI::getCardData(QList<QJsonDocument> items)
{
	cards->addJsonItems(items);
}
void NavigationPageEditUI::clearPreview()
{
	QList<QWidget *> Widgets = preview->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		if(child != NULL && previewLayout->count() > 0){
			previewLayout->removeWidget(child);
			child->setHidden(true);
			//child->setParent(0);
			child->deleteLater();
			}
		}
}
void NavigationPageEditUI::updatePreview()
{
	clearPreview();

	if(newCard->isChecked()){
		//previewLayout->addWidget(new ViewGroups(0,newCardStructure->save()));
		}
	else if(page->isChecked()){
	//	previewLayout->addWidget( new PageUI(0,pageEdit->save()) );
		}
	else if(card->isChecked()){
		//QObject::connect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(loadCard(QJsonDocument)));
		//Controller::Get()->getDoc(cards->getKey());
		}
}

void NavigationPageEditUI::loadCard(QJsonDocument document)
{
	//qDebug() << "Reploaded";
	//QObject::disconnect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(loadCard(QJsonDocument)));
	//previewLayout->addWidget(new ViewGroups(0,document.object()));
}
