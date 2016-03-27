#include "navigationpageeditui.h"
#include "settingsctrlsui.h"

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




	QGroupBox *groupBox = new QGroupBox(tr("Exclusive Radio Buttons"));

	QRadioButton *radio1 = new QRadioButton(tr("&Radio button 1"));
	QRadioButton *radio2 = new QRadioButton(tr("R&adio button 2"));
	QRadioButton *radio3 = new QRadioButton(tr("Ra&dio button 3"));

	radio1->setChecked(true);
	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget(radio1);
	hbox->addWidget(radio2);
	hbox->addWidget(radio3);
	hbox->addStretch(1);
	groupBox->setLayout(hbox);
	layout->addWidget(groupBox);
	layout->addStretch(1);
}

NavigationPageEditUI* NavigationPageEditUI::p_instance = 0;
void NavigationPageEditUI::ShowUI(QJsonObject structureView) {

	if(p_instance == 0)
		p_instance = new NavigationPageEditUI();
	p_instance->setObjectName("NavigationPageEditUI");
	//p_instance->clear();
	//p_instance->fill(id);
	MainForm::Get()->ShowDisplay(p_instance);
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
