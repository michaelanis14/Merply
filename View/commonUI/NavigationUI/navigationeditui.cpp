#include "navigationeditui.h"
#include <QDebug>
#include "navigationui.h"
#include "navigationbtn.h"
#include "controller.h"
#include "navigationeditui.h"
#include "mainform.h"
#include <QHeaderView>
#include <QAbstractItemView>
#include <QTreeWidget>


#include "navigationpageeditui.h"
NavigationEditUI::NavigationEditUI(QWidget *parent) : QWidget(parent)
{
	this->setContentsMargins(0,0,0,0);
	this->setObjectName("navigationUI");
	this->layout = new QVBoxLayout(this);
	this->layout->setContentsMargins(0,0,0,0);
	//this->layout->setAlignment(Qt::AlignLeft);
	this->layout->setSpacing(0);
	this->setFixedWidth(Controller::GetNavigationWidth());
	this->setFixedHeight(Controller::GetWindowHeight());

	SettingsCtrlsUI* sctrlUI = new SettingsCtrlsUI();
	sctrlUI->setFixedHeight(Controller::GetNavigationSettingsBarHeight());
	sctrlUI->addbtn("Add",":/resources/icons/add.png","add");
	sctrlUI->addbtn("Save",":/resources/icons/save.png","save");
	sctrlUI->addbtn("Cancel",":/resources/icons/cancel.png","cancel");
	QObject::connect(sctrlUI, SIGNAL(btnClicked(QString)),this, SLOT(btn_Clicked(QString)));
	//sctrlUI->setAutoFillBackground(true);
	layout->addWidget(sctrlUI);


	subNavigation = new QTreeWidget();

	subNavigation->setColumnCount(4);
	subNavigation->setFixedWidth(Controller::GetNavigationWidth());
	subNavigation->setFixedHeight(Controller::GetWindowHeight()-(Controller::GetNavigationSettingsBarHeight() *2)-Controller::GetNavigationMainHeight());
	subNavigation->header()->close();
	subNavigation->setEditTriggers(QAbstractItemView::AllEditTriggers);
	QObject::connect(subNavigation, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(subNavPressed(QTreeWidgetItem*,int)));
	subNavigation->hideColumn(1);
	this->layout->addWidget(subNavigation);

	SettingsCtrlsUI* mainCtrlUI = new SettingsCtrlsUI();
	mainCtrlUI->setFixedHeight(Controller::GetNavigationSettingsBarHeight());
	mainCtrlUI->addbtn("Mainadd",":/resources/icons/add.png","Mainadd");
	QObject::connect(mainCtrlUI, SIGNAL(btnClicked(QString)),this, SLOT(btn_Clicked(QString)));
	mainCtrlUI->setAutoFillBackground(true);
	layout->addWidget(mainCtrlUI);

	mainNavigation = new QTreeWidget();
	mainNavigation->setColumnCount(3);
	mainNavigation->setFixedWidth(Controller::GetNavigationWidth());

	mainNavigation->setFixedHeight(Controller::GetNavigationMainHeight());
	mainNavigation->header()->close();
	mainNavigation->setEditTriggers(QAbstractItemView::AllEditTriggers);
	mainNavigation->setDropIndicatorShown(false);
	QObject::connect(mainNavigation, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(mainNavPressed(QTreeWidgetItem*,int)));
	mainNavigation->hideColumn(0);
	this->layout->addWidget(mainNavigation);

	this->editMode = true;
	this->idCount = 0;

}

NavigationEditUI* NavigationEditUI::p_instance = 0;
NavigationEditUI* NavigationEditUI::Get(){
	if (p_instance == 0){
		p_instance = new NavigationEditUI();
		}
	return p_instance;
}


void NavigationEditUI::loadMainNavigation(QList<QJsonDocument> navDocs)
{
	mainNavigation->clear();
	subNavigation->clear();
	Controller::ClearMainNavigation();
	Controller::ClearSubNavigation();
	//qDebug() << navDocs;
	foreach(QJsonDocument doc,navDocs){
		QString title = doc.object().value("Title").toString();
		int key = doc.object().value("ID").toInt();
		QJsonArray items = doc.object().value("Items").isArray()?doc.object().value("Items").toArray():QJsonArray();
		this->addMainNavTopItem( title, key);
		Controller::AddMainNavigation(key,title);
		Controller::AddSubNavigation(key,loadSubNavigation(items));
		}
	if(mainNavigation->topLevelItemCount() > 0){
		mainNavigation->selectionModel()->select(mainNavigation->model()->index(0,0,QModelIndex()),QItemSelectionModel::Select| QItemSelectionModel::Rows);
		mainNavPressed(mainNavigation->topLevelItem(0),1);
		}

}
QList<QTreeWidgetItem *> NavigationEditUI::loadSubNavigation(QJsonArray subNav)
{
	QList<QTreeWidgetItem *> items;
	foreach(QJsonValue tab,subNav){
		int key = tab.toObject().value("ID").toInt();
		//qDebug() <<"KEY "<< key;
		QString title = tab.toObject().value("Title").toString();
		if(key!=0 && !title.isEmpty())
			Controller::AddPage(key,tab.toObject());
		QTreeWidgetItem*  item = new QTreeWidgetItem();
		item->setText(1,QString::number(key));
		item->setText(0,title);
		item->setFlags(item->flags() | Qt::ItemIsEditable);
		if(tab.toObject().value("Items").isArray())
			item->addChildren(loadSubNavigation(tab.toObject().value("Items").toArray()));
		items.append(item);
		}
	return  items;
}





void NavigationEditUI::subNavPressed(QTreeWidgetItem* item, int column)
{

	//if(column == 0)
	//	emit subNavPressed(Controller::getSubNavigation(item->text(column)));
	//else
	//qDebug()<<"SubNav" << item->text(1) << column;
	subNavigation->resizeColumnToContents(0);

	NavigationPageEditUI::ShowUI(Controller::GetPage(item->text(1).toInt()));
	if(column == 2)
		addSubNavChild(item);
	else if(column == 3){
		if(subNavigation->indexOfTopLevelItem(item) != -1){
			if(subNavigation->takeTopLevelItem(subNavigation->indexOfTopLevelItem(item)))
				Controller::RemoveSubNavigation(item->text(1).toInt());

			}
		else{
			item->parent()->removeChild(item);
			Controller::RemoveSubNavigation(item->text(1).toInt());

			}
		}
	//save();


	//QTreeWidgetItem::
}

QJsonObject NavigationEditUI::saveSubNavigation(QTreeWidgetItem * item)
{

	QJsonObject itemTab = QJsonObject();
	itemTab.insert("Title",item->text(0));
	itemTab.insert("ID",item->text(1).toInt());
	if(item->childCount() > 0){
		QJsonArray items = QJsonArray();
		for(int i = 0; i < item->childCount();i++)
			items << saveSubNavigation(item->child(i));
		itemTab.insert("Items",items);
		}
	return itemTab;
}
void NavigationEditUI::save()
{

	if(mainNavigation->selectedItems().count() > 0)
		{
		subNavigation->clearFocus();
		//subNavigation->clearSelection();
		subNavigation->setEnabled(false);
		mainNavigation->setEnabled(false);
		Controller::ClearSubNavigation();
		Controller::ClearMainNavigation();
		Controller::ClearPages();

		QList<QTreeWidgetItem *> items;

		for(int i = 0; i < subNavigation->topLevelItemCount(); i++) {
			//qDebug() << subNavigation->topLevelItem(i)->text(0);
			Controller::AddPage(subNavigation->topLevelItem(i)->text(1).toInt(),saveSubNavigation((subNavigation->topLevelItem(i))));
			items << subNavigation->topLevelItem(i);
			}
		Controller::AddMainNavigation(mainNavigation->selectedItems().last()->text(0).toInt(),mainNavigation->selectedItems().last()->text(1));
		Controller::AddSubNavigation(mainNavigation->selectedItems().last()->text(0).toInt(),items);
		Controller::SaveNavigation();
		}
	subNavigation->setEnabled(true);
	mainNavigation->setEnabled(true);

}

void NavigationEditUI::addSubNavChild(QTreeWidgetItem* parent)
{
	QTreeWidgetItem* child = new QTreeWidgetItem();

	int key = ++idCount;
	child->setText(1,QString::number(key));
	child->setText(0,"New Button");
	child->setFlags(child->flags() | Qt::ItemIsEditable);
	//subNavigation->insertTopLevelItems(0,Controller::getMainNavigation(item->text(0)));
	Controller::AddPage(key,QJsonObject());
	parent->addChild(child);
	child->setSelected(true);



	QLabel* add = new QLabel();
	QPixmap addpix (":/resources/icons/1457665371_plus.png");
	add->setPixmap(addpix.scaled(20,20,Qt::KeepAspectRatio));
	add->setMaximumSize(QSize(20,20));

	QLabel* remove = new QLabel();
	QPixmap removepix(":/resources/icons/1457665374_minus.png");
	remove->setPixmap(removepix.scaled(20,20,Qt::KeepAspectRatio));
	remove->setMaximumSize(QSize(20,20));


	subNavigation->setItemWidget(child,2,add);
	subNavigation->setItemWidget(child,3,remove);

	subNavigation->resizeColumnToContents(0);
	subNavigation->setColumnWidth(2,30);
	subNavigation->setColumnWidth(3,30);

	subNavigation->scrollToItem(child);

	//subNavPressed(child, 0);


	QItemSelectionModel *selection = new QItemSelectionModel( subNavigation->model() );


	QItemSelectionModel *select = subNavigation->selectionModel();

	//qDebug() << select->hasSelection() ;//check if has selection
	//qDebug() << select->selectedRows().last() ;// return selected row(s)

	selection->select(select->selectedRows().last(), QItemSelectionModel::Select | QItemSelectionModel::Rows);
	subNavigation->resizeColumnToContents(select->selectedRows().last().column());
	subNavigation->setSelectionModel(selection);




}

void NavigationEditUI::addSubNavTopItem()
{
	QTreeWidgetItem* child = new QTreeWidgetItem();

	int key = ++idCount;
	child->setText(1,QString::number(key));
	child->setText(0,"New Top Button");
	child->setFlags(child->flags() | Qt::ItemIsEditable);
	subNavigation->insertTopLevelItem(subNavigation->topLevelItemCount(),child);
	Controller::AddPage(key,QJsonObject());

	child->setSelected(true);



	QLabel* add = new QLabel();
	QPixmap addpix (":/resources/icons/1457665371_plus.png");
	add->setPixmap(addpix.scaled(20,20,Qt::KeepAspectRatio));
	add->setMaximumSize(QSize(20,20));

	QLabel* remove = new QLabel();
	QPixmap removepix(":/resources/icons/1457665374_minus.png");
	remove->setPixmap(removepix.scaled(20,20,Qt::KeepAspectRatio));
	remove->setMaximumSize(QSize(20,20));


	subNavigation->setItemWidget(child,2,add);
	subNavigation->setItemWidget(child,3,remove);

	subNavigation->resizeColumnToContents(0);
	subNavigation->setColumnWidth(2,30);
	subNavigation->setColumnWidth(3,30);

	subNavigation->scrollToItem(child);

	//subNavPressed(child, 0);


	QItemSelectionModel *selection = new QItemSelectionModel( subNavigation->model() );


	QItemSelectionModel *select = subNavigation->selectionModel();

	//qDebug() << select->hasSelection() ;//check if has selection
	//qDebug() << select->selectedRows().last() ;// return selected row(s)

	QList<QTreeWidgetItem*> subNav =  Controller::GetSubNavigation(mainNavigation->selectedItems().last()->text(0).toInt());
	subNav.append(child);
	Controller::AddSubNavigation(mainNavigation->selectedItems().last()->text(0).toInt(),subNav);
	selection->select(select->selectedRows().last(), QItemSelectionModel::Select | QItemSelectionModel::Rows);
	subNavigation->resizeColumnToContents(select->selectedRows().last().column());
	subNavigation->setSelectionModel(selection);



}

void NavigationEditUI::addMainNavTopItem(QString title,int key)
{


	if(title.isEmpty())title = "New";
	if(key <= 0) key =  ++idCount;
	QTreeWidgetItem* maintab = new QTreeWidgetItem();
	maintab->setText(0,QString::number(key));
	maintab->setText(1,title);
	mainNavigation->insertTopLevelItem(mainNavigation->topLevelItemCount(),maintab);

	QLabel* remove = new QLabel();
	QPixmap removepix(":/resources/icons/1457665374_minus.png");
	remove->setPixmap(removepix.scaled(20,20,Qt::KeepAspectRatio));
	remove->setMaximumSize(QSize(25,25));
	mainNavigation->setItemWidget(maintab,2,remove);

	mainNavigation->setColumnWidth(1,Controller::GetNavigationWidth() - 30);
	mainNavigation->setColumnWidth(2,30);





	Controller::AddMainNavigation(key,title);

	if(mainNavigation->topLevelItemCount()-1 > 0){
		mainNavigation->clearSelection();
		mainNavigation->selectionModel()->select(mainNavigation->model()->index(mainNavigation->topLevelItemCount()-1,0,QModelIndex()),QItemSelectionModel::Select| QItemSelectionModel::Rows);
		mainNavPressed(mainNavigation->topLevelItem(mainNavigation->topLevelItemCount()-1),1);
		}
}

void NavigationEditUI::fillSubNavigation(int key)
{
	QList<QTreeWidgetItem*> subNavItems = Controller::GetSubNavigation(key);
	//qDebug() << subNavItems.count() << subNavItems;
	subNavigation->clearSelection();
	int count = subNavigation->topLevelItemCount();
	for(int i = 0; i < count;i++){
		subNavigation->takeTopLevelItem(0);
		}

	if(subNavItems.count() > 0){
		subNavigation->insertTopLevelItems(0,subNavItems);
		QTreeWidgetItemIterator it(subNavigation);
		while (*it) {

			QLabel* add = new QLabel();
			QPixmap addpix (":/resources/icons/1457665371_plus.png");
			add->setPixmap(addpix.scaled(20,20,Qt::KeepAspectRatio));
			add->setMaximumSize(QSize(20,20));

			QLabel* remove = new QLabel();
			QPixmap removepix(":/resources/icons/1457665374_minus.png");
			remove->setPixmap(removepix.scaled(20,20,Qt::KeepAspectRatio));
			remove->setMaximumSize(QSize(20,20));


			subNavigation->setItemWidget((*it),2,add);
			subNavigation->setItemWidget((*it),3,remove);

			//subNavigation->resizeColumnToContents(0);
			subNavigation->setColumnWidth(2,30);
			subNavigation->setColumnWidth(3,30);


			if((*it)->text(1).toInt() > idCount)
				idCount = (*it)->text(1).toInt();
			++it;
			}
		if(subNavigation->topLevelItemCount() > 0){
			subNavigation->selectionModel()->select(subNavigation->model()->index(0,0,QModelIndex()),QItemSelectionModel::Select| QItemSelectionModel::Rows);
			subNavPressed(subNavigation->topLevelItem(0),0);
			}
		}
}

void NavigationEditUI::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void NavigationEditUI::btn_Clicked(QString btn)
{
	//qDebug() << btn;
	if(btn.contains("settings")){
		//	navigationUI::Get()->setHidden(true);
		//	NavigationEditUI::Get()->setParent(MainForm::Get());
		//	NavigationEditUI::Get()->loadMainNavigation(Controller::Get()->getAll("NavigationUI",""));
		//	NavigationEditUI::Get()->setHidden(false);

		}


	//qDebug() << btn;
	if(btn.contains("Cancel")){
		navigationUI::Get()->setHidden(false);
		navigationUI::Get()->setParent(MainForm::Get());
		navigationUI::Get()->loadMainNavigation(Controller::Get()->getAll("NavigationUI",""));
		NavigationEditUI::Get()->setHidden(true);

		}
	else if(btn.contains("Add")){

		addSubNavTopItem();
		}
	else if(btn.contains("Save")){
		this->save();
		this->btn_Clicked("Cancel");
		}
	else if(btn.contains("Mainadd")){
		addMainNavTopItem();
		}
}
void NavigationEditUI::mainNavPressed(QTreeWidgetItem* item, int column)
{

	//qDebug() << "Main" <<item->text(0)  << column;

	//item->setText(0,"Pressedd");
	//
	//subNavigation->clear();
	if(column == 2){
		qDebug() << "Remove Main Nav"<< item->text(0) << column;

		}
	else  fillSubNavigation(item->text(0).toInt());


	subNavigation->clearFocus();
}
