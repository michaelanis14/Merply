#include "navigationpageeditui.h"
#include "settingsctrlsui.h"
#include "erpcombobox.h"
#include "controller.h"
#include "structureviewgroupsui.h"


NavigationPageEditUI::NavigationPageEditUI(QWidget *parent) : MainDisplay(parent)
{
	this->setContentsMargins(0,0,0,0);
	layout = new QVBoxLayout(this);
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


	newCardDetails = new QGroupBox(tr("new Card Details"));
	QHBoxLayout* newCardDetailsLayout = new QHBoxLayout;
	newCardDetails->setLayout(newCardDetailsLayout);
	newCardStructure = new StructureViewGroupsUI();
	newCardStructure->headerlbl->setHidden(true);
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
	view = new ERPComboBox(this,false);
	viewList << "Index" << "New";
	view->addItems(viewList);
	cardDetailsLayout->addRow(tr("View"),view);
	layout->addWidget(cardDetails);



	pageDetails = new QGroupBox(tr("Page Details"));
	QHBoxLayout* pageDetailsLayout = new QHBoxLayout;
	pageDetails->setLayout(pageDetailsLayout);
	pageEdit = new PageStructureViewEditeUI();
	pageDetailsLayout->addWidget(pageEdit);
	layout->addWidget(pageDetails);

	layout->addWidget(new PermissionsUI());


	cardDetails->setHidden(true);
	pageDetails->setHidden(true);
	newCardDetails->setHidden(true);
	layout->addStretch(1);
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
	if(!structureView.value("Title").toString().isEmpty())
		this->headerlbl->setTitle(structureView.value("Title").toString());
	if(structureView.value("Type").toString().compare("Entity") == 0){
		if(structureView.value("Title").toString().isEmpty())
			this->headerlbl->setTitle(tr("New Card"));
		card->setChecked(true);
		cardToggled(true);
		cards->setCurrentIndex(cards->getItemsText().indexOf(structureView.value("Card").toString()));
		view->setCurrentIndex(viewList.indexOf(structureView.value("Select").toString()));
		}
	else{
		if(structureView.value("Title").toString().isEmpty())
			this->headerlbl->setTitle(tr("New Page"));
		page->setChecked(true);
		pageToggled(true);
		pageEdit->fill(structureView);
		}



}

QJsonObject NavigationPageEditUI::save()
{
	QJsonObject save;
	if(page->isChecked()){
		save = pageEdit->save();
		save.insert("Type","Page");

		}
	else{
		save.insert("Card",cards->currentText());
		save.insert("Select",view->currentText());
		save.insert("Type","Entity");

		}
	save.insert("Title",headerlbl->getTitle());
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
		headerlbl->setHidden(false);
		}
	else{
		newCardDetails->setHidden(true);
		}
}

void NavigationPageEditUI::cardToggled(bool state)
{
	if(state){
		cardDetails->setHidden(false);
		}
	else cardDetails->setHidden(true);
}

void NavigationPageEditUI::pageToggled(bool state)
{
	if(state){
		pageDetails->setHidden(false);
		headerlbl->setHidden(false);
		}
	else{
		pageDetails->setHidden(true);
		headerlbl->setHidden(true);
		}
}

void NavigationPageEditUI::getCardData(QList<QJsonDocument> items)
{
	cards->addJsonItems(items);
}
