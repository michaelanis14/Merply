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
	sctrlUI->addbtn("Add",":/resources/icons/add.png","add");
	sctrlUI->addbtn("Save",":/resources/icons/save.png","save");

	sctrlUI->addbtn("Cancel",":/resources/icons/cancel.png","cancel");

	QObject::connect(sctrlUI, SIGNAL(btnClicked(QString)),this, SLOT(btn_Clicked(QString)));
	sctrlUI->setAutoFillBackground(true);
	layout->addWidget(sctrlUI);




	QGroupBox *groupBox = new QGroupBox(tr("Select Type"));
	QRadioButton *card = new QRadioButton(tr("&Card Refrence"));
	connect(card,SIGNAL(toggled(bool)),this,SLOT(cardToggled(bool)));
	QRadioButton *page = new QRadioButton(tr("Custom Page"));
	connect(page,SIGNAL(toggled(bool)),this,SLOT(pageToggled(bool)));

	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget(card);
	hbox->addWidget(page);
	hbox->addStretch(1);
	groupBox->setLayout(hbox);
	layout->addWidget(groupBox);

	cardDetails = new QGroupBox(tr("Card Details"));
	QFormLayout* cardDetailsLayout = new QFormLayout;
	cardDetails->setLayout(cardDetailsLayout);
	cardDetailsLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
	cardDetailsLayout->setLabelAlignment(Qt::AlignLeft);

	ERPComboBox* cards = new ERPComboBox(this,false);
	cards->addItems(Controller::Get()->getListItems("ViewStructure","Title","default.Type =\"Entity\""));
	cardDetailsLayout->addRow(tr("Card"),cards);

	ERPComboBox* View = new ERPComboBox(this,false);
	QStringList viewList;
	viewList << "Index" << "New";
	View->addItems(viewList);
	cardDetailsLayout->addRow(tr("View"),View);

	layout->addWidget(cardDetails);



	pageDetails = new QGroupBox(tr("Page Details"));
	QFormLayout* pageDetailsLayout = new QFormLayout;
	pageDetails->setLayout(pageDetailsLayout);
	pageDetailsLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
	pageDetailsLayout->setLabelAlignment(Qt::AlignLeft);

	pageDetailsLayout->addRow("Test",new PageStructureViewEditeUI());

	layout->addWidget(pageDetails);

	card->setChecked(true);
	pageDetails->setHidden(true);




	layout->addStretch(1);
}

NavigationPageEditUI* NavigationPageEditUI::p_instance = 0;
void NavigationPageEditUI::ShowUI(QJsonObject structureView) {

	if(p_instance == 0)
		p_instance = new NavigationPageEditUI();
	p_instance->setObjectName("NavigationPageEditUI");
	//p_instance->clear();
	p_instance->fill(structureView);
	MainForm::Get()->ShowDisplay(p_instance);
}

void NavigationPageEditUI::fill(QJsonObject structureView)
{
	this->structureView = structureView;
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
		}
	else if(btn.contains("Cancel")){
		//emit cancel();
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
		}
	else pageDetails->setHidden(true);
}
