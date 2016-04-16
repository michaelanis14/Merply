#include "permissionfieldui.h"


#include <QHeaderView>
#include <QPushButton>
#include <QLabel>

PermissionFieldUI::PermissionFieldUI(QWidget *parent,QString name) : QWidget(parent)
{

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

	ERPComboBox* usersforAllowedList = new ERPComboBox();
	usersforAllowedList->addItems(basicPermissons);
	allowGroupBoxLayout->addWidget(usersforAllowedList);

	QPushButton* btnAddAllowed = new QPushButton(tr("Add"));
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

	ERPComboBox* usersforDeniedList = new ERPComboBox();
	usersforDeniedList->addItems(basicPermissons);
	denyGroupBoxLayout->addWidget(usersforDeniedList);

	QPushButton* btnAddDeny = new QPushButton(tr("Add"));
	QObject::connect(btnAddDeny, SIGNAL(pressed()), this, SLOT(addDenied()));
	denyGroupBoxLayout->addWidget(btnAddDeny);


	QObject::connect(readPermissons,SIGNAL(currentIndexChanged(int)),this,SLOT(showSpcfic(int)));
	showSpcfic(0);
}

void PermissionFieldUI::showSpcfic(int field)
{
	if(field == 2){
		allowGroupBox->setHidden(false);
		denyGroupBox->setHidden(false);
		layout->labelForField(allowGroupBox)->setHidden(false);
		layout->labelForField(denyGroupBox)->setHidden(false);
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

				}
				//Controller::RemoveSubNavigation(item->text(1).toInt());

			}
		else{
			item->parent()->removeChild(item);
			//Controller::RemoveSubNavigation(item->text(1).toInt());

			}

		}
}

void PermissionFieldUI::addDenied()
{
	QString title = "New";
	int key = 9;
	//if(key <= 0) key =  ++idCount;
	QTreeWidgetItem* maintab = new QTreeWidgetItem();
	maintab->setText(0,QString::number(key));
	maintab->setText(1,title);
	denyGroup->insertTopLevelItem(denyGroup->topLevelItemCount(),maintab);

	QLabel* remove = new QLabel();
	QPixmap removepix(":/resources/icons/1457665374_minus.png");
	remove->setPixmap(removepix.scaled(20,20,Qt::KeepAspectRatio));
	remove->setMaximumSize(QSize(25,25));
	denyGroup->setItemWidget(maintab,2,remove);

	denyGroup->setColumnWidth(1,100 - 30);
	denyGroup->setColumnWidth(2,30);
}

void PermissionFieldUI::addAllowed()
{

	QString title = "New";
	int key = 9;
	//if(key <= 0) key =  ++idCount;
	QTreeWidgetItem* maintab = new QTreeWidgetItem();
	maintab->setText(0,QString::number(key));
	maintab->setText(1,title);
	allowGroup->insertTopLevelItem(allowGroup->topLevelItemCount(),maintab);

	QLabel* remove = new QLabel();
	QPixmap removepix(":/resources/icons/1457665374_minus.png");
	remove->setPixmap(removepix.scaled(20,20,Qt::KeepAspectRatio));
	remove->setMaximumSize(QSize(25,25));
	allowGroup->setItemWidget(maintab,2,remove);

	allowGroup->setColumnWidth(1,100 - 30);
	allowGroup->setColumnWidth(2,30);


}
