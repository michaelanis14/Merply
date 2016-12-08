#include "permissionfieldui.h"
#include "controller.h"

#include <QHeaderView>
#include <QLabel>

PermissionFieldUI::PermissionFieldUI(QWidget *parent, QString name) : QWidget(parent)
{
	//qDebug() << __FILE__ << __LINE__ <<"SAVED" << saved;
	layout = new QFormLayout;
	this->setLayout(layout);
	this->setContentsMargins(0,0,0,0);
	//layout->setSpacing(0);
	layout->setMargin(0);
	layout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
	QStringList basicPermissons;
	basicPermissons << tr("Everyone") << tr("None") <<tr("Specific");
	readPermissons = new ERPComboBox();
	readPermissons->addItems(basicPermissons);
	layout->addRow(tr(name.toStdString().c_str()), readPermissons);


	QJsonObject basicPermissonsItem;
	QJsonObject basicPermissonsItem2;
	basicPermissonsItem.insert("Value","Everyone");
	basicPermissonsItem.insert("Key","000100");
	basicPermissonsItem2.insert("Value","None");
	basicPermissonsItem2.insert("Key","000101");
	basicPermissonsKeys.append(QJsonDocument(basicPermissonsItem));
	//basicPermissonsKeys.append(QJsonDocument(basicPermissonsItem2));


	allowGroupBox = new QGroupBox();
	allowGroupBox->setContentsMargins(0,0,0,0);
	QVBoxLayout* allowGroupBoxLayout = new QVBoxLayout;
	allowGroupBoxLayout->setContentsMargins(0,0,0,0);
	allowGroupBox->setLayout(allowGroupBoxLayout);
	layout->addRow(tr("Allowed Group"),allowGroupBox);


	allowGroup = new QTreeWidget();
	allowGroup->setColumnCount(3);
	//allowGroup->setFixedWidth(Controller::GetNavigationWidth());

	//allowGroup->setFixedHeight(Controller::GetNavigationMainHeight());
	allowGroup->header()->close();
	//allowGroup->setEditTriggers(QAbstractItemView::AllEditTriggers);
	allowGroup->setDropIndicatorShown(false);
	QObject::connect(allowGroup, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(allowGroupPressed(QTreeWidgetItem*,int)));
	allowGroup->hideColumn(0);
	allowGroupBoxLayout->addWidget(allowGroup);

	usersforAllowedList = new ERPComboBox();

	allowGroupBoxLayout->addWidget(usersforAllowedList);

	btnAddAllowed = new QPushButton(tr("Add"));
	QObject::connect(btnAddAllowed, SIGNAL(pressed()), this, SLOT(addAllowed()));
	allowGroupBoxLayout->addWidget(btnAddAllowed);


	denyGroupBox = new QGroupBox();
	denyGroupBox->setContentsMargins(0,0,0,0);
	QVBoxLayout* denyGroupBoxLayout = new QVBoxLayout;
	denyGroupBoxLayout->setContentsMargins(0,0,0,0);
	denyGroupBox->setLayout(denyGroupBoxLayout);
	layout->addRow(tr("Denied Group"),denyGroupBox);
	denyGroup = new QTreeWidget();
	denyGroup->setColumnCount(3);
	//denyGroup->setFixedWidth(Controller::GetNavigationWidth());

	//denyGroup->setFixedHeight(Controller::GetNavigationMainHeight());
	denyGroup->header()->close();
	//denyGroup->setEditTriggers(QAbstractItemView::AllEditTriggers);
	denyGroup->setDropIndicatorShown(false);
	QObject::connect(denyGroup, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(denyGroupPressed(QTreeWidgetItem*,int)));
	denyGroup->hideColumn(0);
	denyGroupBoxLayout->addWidget(denyGroup);

	usersforDeniedList = new ERPComboBox();

	denyGroupBoxLayout->addWidget(usersforDeniedList);

	btnAddDeny = new QPushButton(tr("Add"));
	QObject::connect(btnAddDeny, SIGNAL(pressed()), this, SLOT(addDenied()));
	denyGroupBoxLayout->addWidget(btnAddDeny);


	QObject::connect(readPermissons,SIGNAL(currentIndexChanged(int)),this,SLOT(showSpcfic(int)));
	showSpcfic(0);



}

QJsonObject PermissionFieldUI::save()
{
	QJsonObject save;

	if(readPermissons->currentIndex() == 0)
		save.insert("Permissions","000100");
	else if(readPermissons->currentIndex() == 1)
		save.insert("Permissions","000101");
	else{
		if(allowGroup->topLevelItemCount() == 0 && denyGroup->topLevelItemCount() == 0){
			Controller::Get()->showWarning(tr("Allowed and Denied Groups are Empty"));
			Controller::Get()->showWarning(tr("Permissions set to Everyone"));
			save.insert("Permissions","000100");
			return save;
			}
		save.insert("Permissions","000111");
		QJsonArray allowed;
		for(int i = 0; i < allowGroup->topLevelItemCount();i++){
			QTreeWidgetItem *tab = allowGroup->topLevelItem(i);
			QJsonObject tabObject;
			tabObject.insert("Key",tab->text(0));
			tabObject.insert("Value",tab->text(1));
			allowed << tabObject;
			//qDebug() << __FILE__ << __LINE__  << tab->text(1) << tab->text(0);
			}
		save.insert("Allowed",allowed);

		QJsonArray denied;
		for(int i = 0; i < denyGroup->topLevelItemCount();i++){
			QTreeWidgetItem *tab = denyGroup->topLevelItem(i);
			QJsonObject tabObject;
			tabObject.insert("Key",tab->text(0));
			tabObject.insert("Value",tab->text(1));
			denied << tabObject;
			//qDebug() << __FILE__ << __LINE__  << tab->text(1) << tab->text(0);
			}
		save.insert("Denied",denied);
		}
	return save;
}

QStringList PermissionFieldUI::getAllowed()
{
	QStringList all;
	for(int i = 0; i < allowGroup->topLevelItemCount();i++){
		all << allowGroup->topLevelItem(i)->text(1);
		}
	return all;
}

QStringList PermissionFieldUI::getDenied()
{
	QStringList all;
	for(int i = 0; i < denyGroup->topLevelItemCount();i++){
		all << denyGroup->topLevelItem(i)->text(1);
		}
	return all;
}

void PermissionFieldUI::addAllowed(QString title, QString key)
{
	//if(key <= 0) key =  ++idCount;
	QTreeWidgetItem* maintab = new QTreeWidgetItem();
	maintab->setText(0,key);
	maintab->setText(1,title);
	allowGroup->insertTopLevelItem(allowGroup->topLevelItemCount(),maintab);

	QLabel* remove = new QLabel();
	QPixmap removepix(":/resources/icons/1457665374_minus.png");
	remove->setPixmap(removepix.scaled(20,20,Qt::KeepAspectRatio));
	remove->setMaximumSize(QSize(25,25));
	allowGroup->setItemWidget(maintab,2,remove);

	allowGroup->setColumnWidth(1,100 - 30);
	allowGroup->setColumnWidth(2,30);

	if(title.compare("Everyone") == 0){
		usersforAllowedList->setEnabled(false);
		btnAddAllowed->setEnabled(false);
		}

	usersforAllowedList->removeSelected();
	usersforDeniedList->removeList(getAllowed());

}

void PermissionFieldUI::addDenied(QString title, QString key)
{
	QTreeWidgetItem* maintab = new QTreeWidgetItem();
	maintab->setText(0,key);
	maintab->setText(1,title);
	denyGroup->insertTopLevelItem(denyGroup->topLevelItemCount(),maintab);

	QLabel* remove = new QLabel();
	QPixmap removepix(":/resources/icons/1457665374_minus.png");
	remove->setPixmap(removepix.scaled(20,20,Qt::KeepAspectRatio));
	remove->setMaximumSize(QSize(25,25));
	denyGroup->setItemWidget(maintab,2,remove);

	denyGroup->setColumnWidth(1,100 - 30);
	denyGroup->setColumnWidth(2,30);
	if(title.compare("Everyone") == 0){
		usersforDeniedList->setEnabled(false);
		btnAddDeny->setEnabled(false);
		}
	usersforDeniedList->removeSelected();
	usersforAllowedList->removeList(getDenied());

}

void PermissionFieldUI::loadUsersGroups()
{
	usersforAllowedList->clear();
	usersforDeniedList->clear();

	usersforAllowedList->addJsonItems(basicPermissonsKeys);
	usersforDeniedList->addJsonItems(basicPermissonsKeys);

	QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(loadUsers(QList<QJsonDocument>)));
	Controller::Get()->getJsonList("Users","Fields[0][0].Name[0]");
	QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(loadUsers(QList<QJsonDocument>)));
	Controller::Get()->getJsonList("Groups","Fields[0][0].Name[0]");

}

void PermissionFieldUI::load(QJsonObject saved)
{
	allowGroup->clear();
	denyGroup->clear();
	btnAddAllowed->setEnabled(true);
	btnAddDeny->setEnabled(true);

	//qDebug() << __FILE__ << __LINE__  << saved.value("Permissions").toString().toInt();
	if(saved.value("Permissions").toString().toInt() == 100)
		readPermissons->setCurrentIndex(0);
	else if(saved.value("Permissions").toString().toInt() == 101)
		readPermissons->setCurrentIndex(1);
	else if(saved.value("Permissions").toString().toInt() == 111){
		readPermissons->setCurrentIndex(2);
		loadUsersGroups();
		foreach(QJsonValue allow,saved.value("Allowed").toArray()){
			usersforAllowedList->setCurrentIndex(usersforAllowedList->keys.indexOf(allow.toObject().value("Key").toString()));
			addAllowed(allow.toObject().value("Value").toString(),allow.toObject().value("Key").toString());
			}
		foreach(QJsonValue deny,saved.value("Denied").toArray()){
			usersforDeniedList->setCurrentIndex(usersforDeniedList->keys.indexOf(deny.toObject().value("Key").toString()));
			addDenied(deny.toObject().value("Value").toString(),deny.toObject().value("Key").toString());
			}

		}
}

void PermissionFieldUI::showSpcfic(int field)
{
	if(field == 2){
		allowGroupBox->setHidden(false);
		denyGroupBox->setHidden(false);
		layout->labelForField(allowGroupBox)->setHidden(false);
		layout->labelForField(denyGroupBox)->setHidden(false);
		loadUsersGroups();
		}
	else{
		allowGroupBox->setHidden(true);
		denyGroupBox->setHidden(true);
		layout->labelForField(allowGroupBox)->setHidden(true);
		layout->labelForField(denyGroupBox)->setHidden(true);
		}
}

void PermissionFieldUI::allowGroupPressed(QTreeWidgetItem* item, int column)
{
	if(column == 2){
		if(allowGroup->indexOfTopLevelItem(item) != -1){
			if(allowGroup->takeTopLevelItem(allowGroup->indexOfTopLevelItem(item))){
				QList<QJsonDocument> items;
				QJsonObject jsonitem;
				jsonitem.insert("Value",item->text(1));
				jsonitem.insert("Key",item->text(0));
				items.append(QJsonDocument(jsonitem));
				usersforAllowedList->addJsonItems(items);
				usersforDeniedList->addJsonItems(items);
				if(item->text(1).compare("Everyone") == 0){
					usersforAllowedList->setEnabled(true);
					btnAddAllowed->setEnabled(true);
					usersforDeniedList->setEnabled(true);
					btnAddDeny->setEnabled(true);
					}
				}
			//Controller::RemoveSubNavigation(item->text(1).toInt());

			}
		else{
			item->parent()->removeChild(item);
			//Controller::RemoveSubNavigation(item->text(1).toInt());

			}

		}
}

void PermissionFieldUI::denyGroupPressed(QTreeWidgetItem* item, int column)
{
	if(column == 2){
		if(denyGroup->indexOfTopLevelItem(item) != -1){
			if(denyGroup->takeTopLevelItem(denyGroup->indexOfTopLevelItem(item))){
				QList<QJsonDocument> items;
				QJsonObject jsonitem;
				jsonitem.insert("Value",item->text(1));
				jsonitem.insert("Key",item->text(0));
				items.append(QJsonDocument(jsonitem));
				usersforAllowedList->addJsonItems(items);
				usersforDeniedList->addJsonItems(items);
				//qDebug() << __FILE__ << __LINE__  << item->text(1) << item->text(0);
				if(item->text(1).compare("Everyone") == 0){
					usersforAllowedList->setEnabled(true);
					btnAddAllowed->setEnabled(true);
					usersforDeniedList->setEnabled(true);
					btnAddDeny->setEnabled(true);
					}
				}
			//Controller::RemoveSubNavigation(item->text(1).toInt());

			}
		else{
			//qDebug() << __FILE__ << __LINE__  << item->text(1).toInt() << item->text(0);
			item->parent()->removeChild(item);
			//Controller::RemoveSubNavigation(item->text(1).toInt());

			}

		}
}

void PermissionFieldUI::addDenied()
{
	if(usersforDeniedList->currentIndex() >= 0 && !(usersforDeniedList->currentText().isEmpty()) ){
		QString title = usersforDeniedList->currentText();
		QString key = usersforDeniedList->getKey();
		//if(key <= 0) key =  ++idCount;
		addDenied(title,key);
		}
}

void PermissionFieldUI::addAllowed()
{
	if(usersforAllowedList->currentIndex() >= 0 && !(usersforAllowedList->currentText().isEmpty()) ){
		QString title = usersforAllowedList->currentText();
		QString key = usersforAllowedList->getKey();
		addAllowed(title,key);
		}
	//qDebug() << __FILE__ << __LINE__  << save();
}

void PermissionFieldUI::loadUsers(QList<QJsonDocument> users)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(loadUsers(QList<QJsonDocument>)));
	usersforAllowedList->addJsonItems(users);
	usersforDeniedList->addJsonItems(users);
}
