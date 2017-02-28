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

	QGroupBox *tabGroupBox = new QGroupBox(tr("Tab Permissions"));
	subtabPermissions = new PermissionsUI(this,true,false);
	QHBoxLayout* tabGroupBoxLayout = new QHBoxLayout;
	tabGroupBoxLayout->setMargin(0);
	tabGroupBoxLayout->setSpacing(0);
	tabGroupBoxLayout->addWidget(subtabPermissions);
	tabGroupBox->setLayout(tabGroupBoxLayout);
	layout->addWidget(tabGroupBox);

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
	QHBoxLayout* cardDetailsLayout = new QHBoxLayout;
	cardDetailsLayout->setAlignment(Qt::AlignLeft);
	cardDetailsLayout->setMargin(0);
	cardDetails->setLayout(cardDetailsLayout);
	QLabel* lblCard = new QLabel(tr("Card"));
	//	cardDetailsLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
	//	cardDetailsLayout->setLabelAlignment(Qt::AlignLeft);
	cards = new ERPComboBox(this,false);
	cards->clear();
	cardDetailsLayout->addWidget(lblCard);
	cardDetailsLayout->addWidget(cards);

	QPushButton* btnRemoveCard = new QPushButton(tr("Delete Card"));
	QObject::connect(btnRemoveCard,SIGNAL(clicked(bool)),this,SLOT(deleteCard()));

	cardDetailsLayout->addWidget(btnRemoveCard);

	views = new ERPComboBox(this,false);
	views->clear();

	QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QVector<QJsonDocument>)),this,SLOT(getCardData(QVector<QJsonDocument>)));
	Controller::Get()->getJsonList("ViewStructure","Title","`"+QString(DATABASE).append("`.Type =\"Entity\""));

	//cardDetailsLayout->addRow(tr("View"),view);
	layout->addWidget(cardDetails);

	layout->addWidget(views);

	pageDetails = new QGroupBox(tr("Page Details"));
	QHBoxLayout* pageDetailsLayout = new QHBoxLayout;
	pageDetails->setLayout(pageDetailsLayout);
	pageEdit = new PageStructureViewEditeUI();
	pageEdit->headerlbl->setHidden(true);
	pageEdit->sctrlUI->ctrlBtns->value(1)->setHidden(true);
	pageEdit->sctrlUI->ctrlBtns->value(2)->setHidden(true);
	pageDetailsLayout->addWidget(pageEdit);
	layout->addWidget(pageDetails);

	permissions = new PermissionsUI(this,true,false);
	layout->addWidget(permissions);

	preview = new QGroupBox(tr("Preview"));
	previewLayout = new QHBoxLayout;
	preview->setLayout(previewLayout);
	layout->addWidget(preview);

	cardDetails->setHidden(true);
	pageDetails->setHidden(true);
	newCardDetails->setHidden(true);
	layout->addStretch(1);




	connect(newCard,SIGNAL(toggled(bool)),this,SLOT(updateNewCardPreview()));
	connect(card,SIGNAL(toggled(bool)),this,SLOT(updateCardPreview()));
	connect(page,SIGNAL(toggled(bool)),this,SLOT(updatePagePreview()));
	//QObject::connect(cards,SIGNAL(currentIndexChanged(int)),this,SLOT(updatePreview()));
	//connect(newCard,SIGNAL(toggled(bool)),this,SLOT(updatePreview()));
	//connect(newCard,SIGNAL(toggled(bool)),this,SLOT(updatePreview()));

	QObject::connect(cards,SIGNAL(currentIndexChanged(int)),this,SLOT(updateCardPreview()));
	//QObject::connect(views,SIGNAL(currentIndexChanged(int)),this,SLOT(updateCardPreview()));

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

	//QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QVector<QJsonDocument>)),this,SLOT(getCardData(QVector<QJsonDocument>)));
	//Controller::Get()->getJsonList("ViewStructure","Title",QString(DATABASE).append(".Type =\"Entity\""));

	//if(!structureView.value("Title").toString().isEmpty())
	//	this->headerlbl->setTitle(structureView.value("Title").toString());
	if(structureView.value("Type").toString().compare("Entity") == 0){
		//if(structureView.value("Title").toString().isEmpty())
		//	this->headerlbl->setTitle(tr("New Card"));
		if(structureView.value("CardData") != QJsonValue::Undefined){
			newCard->setChecked(true);
			newCardToggled(true);
			newCardStructure->fill(structureView.value("CardData").toObject());
			updateNewCardPreview();
			}
		else{
			cards->setCurrentIndex(cards->keys.indexOf(structureView.value("Card").toString()));
			if(cards->currentIndex() == -1){
				cards->clear();
				QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QVector<QJsonDocument>)),this,SLOT(getCardData(QVector<QJsonDocument>)));
				Controller::Get()->getJsonList("ViewStructure","Title","`"+QString(DATABASE).append("`.Type =\"Entity\""));
				cards->setCurrentIndex(cards->keys.indexOf(structureView.value("Card").toString()));

				}
			//qDebug() << __FILE__ << __LINE__  << cards->currentIndex() << structureView.value("CardData") << structureView;

			view->setCurrentIndex(viewList.indexOf(structureView.value("Select").toString()));
			card->setChecked(true);
			cardToggled(true);
			}
		}
	else{
		//if(structureView.value("Title").toString().isEmpty())
		//	this->headerlbl->setTitle(tr("New Page"));
		//qDebug() << __FILE__ << __LINE__  << structureView.value("Card").toString();
		if(structureView.value("CardData") != QJsonValue::Undefined){
			this->getPageData(QJsonDocument(structureView.value("CardData").toObject()));
			}
		else{
			QObject::connect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(getPageData(QJsonDocument)));
			Controller::Get()->getDoc(structureView.value("Card").toString());
			}

		}

	subtabPermissions->load(structureView.value("TabPermissions").toObject());
	permissions->load(structureView.value("Permissions").toObject());
}

void NavigationPageEditUI::save(bool updateDataBase)
{
	this->saveObject = QJsonObject();
	this->saveObject.insert("Title",headerlbl->getTitle());
	this->saveObject.insert("Permissions",permissions->save());
	this->saveObject.insert("TabPermissions",subtabPermissions->save());
	if(page->isChecked()){
		saveObject.insert("Type","Page");
		QJsonObject savedPage = pageEdit->save() ;
		if(updateDataBase){
			if(savedPage.value("document_id") != QJsonValue::Undefined){
				//qDebug() << __FILE__ << __LINE__  << savedPage.value("document_id");
				saveObject.insert("Card",savedPage.value("document_id").toString());
				Controller::Get()->UpdateDoc(QJsonDocument(savedPage));
				emit this->saved(saveObject);
				}
			else {
				QObject::connect(Controller::Get(),SIGNAL(gotLastKey(QString)),this,SLOT(gotLastKeyData(QString)));
				Controller::Get()->getLastKey();
				Controller::Get()->storeDoc("Page",QJsonDocument(savedPage));
				}
			}
		}
	else if(card->isChecked()){
		saveObject.insert("Card",cards->getKey());
		saveObject.insert("Select",view->currentText());
		saveObject.insert("Type","Entity");
		emit this->saved(saveObject);
		}
	else if(newCard->isChecked()){
		saveObject.insert("Select",view->currentText());
		saveObject.insert("Type","Entity");
		newCardStructure->headerlbl->setTitle(this->headerlbl->getTitle());

		if(updateDataBase){
			QObject::connect(Controller::Get(),SIGNAL(saved(QString)),this,SLOT(gotLastKeyData(QString)));
			//Controller::Get()->getLastKey();
			QJsonObject newsStruct = newCardStructure->save() ;
			Controller::Get()->storeDoc("ViewStructure::"+newsStruct.value("Title").toString(),QJsonDocument(newsStruct));

			}
		//	else
		//	{
		//	saveObject.insert("CardData",newCardStructure->save());
		//;

		//	while(Controller::getLastKeyID().toDouble() == -1){
		//	qDebug() << __FILE__ << __LINE__  << Controller::getLastKeyID();
		//		}

		//	emit this->saved(saveObject);
		//		}
		}



}
void NavigationPageEditUI::gotLastKeyData(QString key)
{
	//qDebug() << __FILE__ << __LINE__  << "KEYYYYYYY" << key;
	QObject::disconnect(Controller::Get(),SIGNAL(saved(QString)),this,SLOT(gotLastKeyData(QString)));
	saveObject.insert("Card",key);
	emit this->saved(saveObject);
	//qDebug() << __FILE__ << __LINE__  << "GOTTTTLASTTTTKEYYY DATAAA" <<  key;
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
		//	qDebug() << __FILE__ << __LINE__  << this->save();
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
		QObject::connect(this, SIGNAL(editControllerCancelPressed()), newCardStructure, SLOT(editControllerCancelPressed()));
		//QObject::connect(this, SIGNAL(editControllerSavePressed()), newCardStructure, SLOT(editControllerSavePressed()));

		newCardDetails->setHidden(false);
		qDebug() << __FILE__ << __LINE__  << "newCard" ;
		newCardDetails->layout()->itemAt(0)->widget()->setHidden(false);
		headerlbl->setEnabled(true);
		headerlbl->setTitle("New Card");
		viewBox->setHidden(false);
		}
	else{
		QObject::disconnect(this, SIGNAL(editControllerCancelPressed()), newCardStructure, SLOT(editControllerCancelPressed()));
		//QObject::disconnect(this, SIGNAL(editControllerSavePressed()), newCardStructure, SLOT(editControllerSavePressed()));

		newCardDetails->setHidden(true);
		}
}

void NavigationPageEditUI::cardToggled(bool state)
{
	if(state){
		this->headerlbl->setTitle(structureView.value("Title").toString());
		headerlbl->setEnabled(true);
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

void NavigationPageEditUI::getCardData(QVector<QJsonDocument> items)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotJsonListData(QVector<QJsonDocument>)),this,SLOT(getCardData(QVector<QJsonDocument>)));
	cards->clear();
	cards->addJsonItems(items);
}

void NavigationPageEditUI::getPageData(QJsonDocument page){
	QObject::disconnect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(getPageData(QJsonDocument)));
	this->page->setChecked(true);
	pageToggled(true);
	this->pageEdit->fill(page.object());
	updatePagePreview();
}

void NavigationPageEditUI::updatePagePreview()
{
	if(page->isChecked()){

		//	qDebug() << __FILE__ << __LINE__  << "updatePAge";
		clearPreview();
		PageUI*page = new PageUI(0,pageEdit->save() );
		page->headerlbl->setHidden(true);
		previewLayout->addWidget(page);
		}
}

void NavigationPageEditUI::deleteCard()
{
	QString id  = cards->getKey();
	if(Controller::Get()->ShowQuestion(tr("Are you sure you want to delete?")))
		if(Controller::Get()->deleteDocument(id)){
			cards->removeSelected();
			}
	//Controller::Get()->queryIndexView("ViewStructure::"+id.split("::")[0]);

}

void NavigationPageEditUI::updateNewCardPreview()
{
	if(newCard->isChecked()){
		//qDebug() << __FILE__ << __LINE__  << "newCard";
		clearPreview();
		ViewGroups* vg = ViewGroups::Create(newCardStructure->save() ,QJsonObject());
		previewLayout->addWidget(vg);
		}
}

void NavigationPageEditUI::updateCardPreview()
{
	if(card->isChecked()){
		if(currentCardKey.compare(cards->getKey()) != 0){
			clearPreview();
			currentCardKey = cards->getKey();
			QObject::connect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(loadCard(QJsonDocument)));
			Controller::Get()->getDoc(this->currentCardKey);
			}
		}

}
void NavigationPageEditUI::clearPreview()
{
	this->currentCardKey = "";
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

void NavigationPageEditUI::loadCard(QJsonDocument document)
{
	//	qDebug() << __FILE__ << __LINE__  << "Reploaded" << preview->isHidden() << document.object();
	QObject::disconnect(Controller::Get(),SIGNAL(gotDocument(QJsonDocument)),this,SLOT(loadCard(QJsonDocument)));
	previewLayout->addWidget(ViewGroups::Create(document.object(),QJsonObject()));
}


