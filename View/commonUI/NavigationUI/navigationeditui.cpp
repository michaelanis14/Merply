#include "navigationeditui.h"
#include <QDebug>

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
	this->oldItemSubNavSelected = new QTreeWidgetItem();
	this->layout = new QVBoxLayout(this);
	this->layout->setContentsMargins(0,0,0,0);
	this->rootOnly = false;
	//this->layout->setAlignment(Qt::AlignLeft);
	this->layout->setSpacing(0);
	this->setFixedWidth(Controller::GetNavigationWidth());
	this->setFixedHeight(Controller::GetWindowHeight());

	sctrlUI = new SettingsCtrlsUI();
	sctrlUI->setFixedHeight(Controller::GetNavigationSettingsBarHeight());
	sctrlUI->addbtn("Add",":/resources/icons/add.png","add");
	//sctrlUI->addbtn("Save",":/resources/icons/save.png","save");
	//sctrlUI->ctrlBtns->value(1)->setHidden(true);
	//sctrlUI->addbtn("Cancel",":/resources/icons/cancel.png","cancel");
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
	QObject::connect(mainNavigation, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(mainNavChanged(QTreeWidgetItem*,int)));

	mainNavigation->hideColumn(0);
	this->layout->addWidget(mainNavigation);

	this->editMode = true;
	this->idCount = 0;
	this->currentSubNav = -1;

	QObject::connect(NavigationPageEditUI::Get(), SIGNAL(editControllerCancelPressed()), this, SLOT(editControllerCancelPressed()));
	QObject::connect(NavigationPageEditUI::Get(), SIGNAL(editControllerSavePressed()), this, SLOT(editControllerSavePressed()));


}

NavigationEditUI* NavigationEditUI::p_instance = 0;
NavigationEditUI* NavigationEditUI::Get(){
	if (p_instance == 0){
		p_instance = new NavigationEditUI();
		}
	return p_instance;
}


void NavigationEditUI::loadMainNavigation(QJsonDocument navDoc)
{
	mainNavigation->clear();
	subNavigation->clear();
	Controller::ClearMainNavigation();
	Controller::ClearSubNavigation();
	//qDebug() << navDocs;
	foreach(QJsonValue mainNav,navDoc.object().value("MainNavigations").toArray()){
		QString title = mainNav.toObject().value("Title").toString();

		double key = mainNav.toObject().value("ID").toDouble();
		QJsonArray items = mainNav.toObject().value("Items").isArray()?mainNav.toObject().value("Items").toArray():QJsonArray();
		this->addMainNavTopItem( title, key);
		Controller::AddMainNavigation(key,title);
		Controller::AddSubNavigation(key,loadSubNavigation(items));
		}
	if(mainNavigation->topLevelItemCount() > 0){
		mainNavigation->clearSelection();
		mainNavigation->selectionModel()->select(mainNavigation->model()->index(0,0,QModelIndex()),QItemSelectionModel::Select| QItemSelectionModel::Rows);
		mainNavPressed(mainNavigation->topLevelItem(0),1);
		}
	else{
		subNavigation->setEnabled(false);
		sctrlUI->setEnabled(false);
		}

}
QList<QTreeWidgetItem *> NavigationEditUI::loadSubNavigation(QJsonArray subNav)
{
	QList<QTreeWidgetItem *> items;
	foreach(QJsonValue tab,subNav){
		double key = tab.toObject().value("ID").toDouble();
		//qDebug() <<"KEY "<< key;
		QString title = tab.toObject().value("Title").toString();
		if(key!=0 && !title.isEmpty())
			Controller::AddPage(key,tab.toObject().value("Page").toObject());
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


	if(column == 2)
		addSubNavChild(item);
	else if(column == 3){
		if(subNavigation->indexOfTopLevelItem(item) != -1){
			if(subNavigation->takeTopLevelItem(subNavigation->indexOfTopLevelItem(item)))
				Controller::RemoveSubNavigation(item->text(1).toDouble());

			}
		else{
			item->parent()->removeChild(item);
			Controller::RemoveSubNavigation(item->text(1).toDouble());

			}
		}
	else if(column == 0 && currentSubNav != item->text(1).toDouble() && oldItemSubNavSelected){
		//qDebug() << oldItemSubNavSelected << oldItemSubNavSelected->isSelected() << oldItemSubNavSelected->childCount() << oldItemSubNavSelected->text(1);
		oldItemSubNavSelected->setSelected(true);
		QItemSelectionModel *selection = new QItemSelectionModel( subNavigation->model() );
		QItemSelectionModel *select = subNavigation->selectionModel();
		selection->select(select->selectedRows().last(), QItemSelectionModel::Select | QItemSelectionModel::Rows);
		subNavigation->setSelectionModel(selection);
		savePage();
		oldItemSubNavSelected->setSelected(false);

		oldItemSubNavSelected = item;
		oldItemSubNavSelected->setSelected(true);


		page =  (Controller::GetPage(item->text(1).toDouble()));
		NavigationPageEditUI::ShowUI(page);
		currentSubNav = item->text(1).toDouble();
		}

}


void NavigationEditUI::save()
{

	if(mainNavigation->selectedItems().count() > 0)
		{
		subNavigation->clearFocus();
		//subNavigation->clearSelection();
		subNavigation->setEnabled(false);
		mainNavigation->setEnabled(false);
		Controller::SaveNavigation();
		}
	subNavigation->setEnabled(true);
	mainNavigation->setEnabled(true);

}

void NavigationEditUI::addSubNavChild(QTreeWidgetItem* parent)
{
	QTreeWidgetItem* child = new QTreeWidgetItem();

	double key = ++idCount;
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

	double key = ++idCount;
	child->setText(1,QString::number(key));
	child->setText(0,"New Top Button");
	child->setFlags(child->flags() | Qt::ItemIsEditable);
	subNavigation->insertTopLevelItem(subNavigation->topLevelItemCount(),child);
	Controller::AddPage(key,QJsonObject());

	child->setSelected(true);

	if(!rootOnly){

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

		subNavigation->setColumnWidth(2,30);
		subNavigation->setColumnWidth(3,30);
		}
	else{
		//	subNavigation->setColumnCount(1);
		}

	subNavigation->resizeColumnToContents(0);


	subNavigation->scrollToItem(child);

	//subNavPressed(child, 0);


	QItemSelectionModel *selection = new QItemSelectionModel( subNavigation->model() );


	QItemSelectionModel *select = subNavigation->selectionModel();

	//qDebug() << select->hasSelection() ;//check if has selection
	//qDebug() << select->selectedRows().last() ;// return selected row(s)

	QList<QTreeWidgetItem*> subNav =  Controller::GetSubNavigation(mainNavigation->selectedItems().last()->text(0).toDouble());
	subNav.append(child);
	Controller::AddSubNavigation(mainNavigation->selectedItems().last()->text(0).toDouble(),subNav);
	selection->select(select->selectedRows().last(), QItemSelectionModel::Select | QItemSelectionModel::Rows);
	subNavigation->resizeColumnToContents(select->selectedRows().last().column());
	subNavigation->setSelectionModel(selection);



}

void NavigationEditUI::addMainNavTopItem(QString title,double key)
{

	this->rootOnly = (key == -14);
	if(this->rootOnly)
		this->rootOnly = !Controller::Get()->hasRootGroupAccess();

	if(title.isEmpty())title = "New";
	if(key == 0 || key == -1) key =  ++idCount;
	QTreeWidgetItem* maintab = new QTreeWidgetItem();
	maintab->setFlags(maintab->flags() | Qt::ItemIsEditable);
	maintab->setText(0,QString::number(key));
	maintab->setText(1,title);
	mainNavigation->insertTopLevelItem(mainNavigation->topLevelItemCount(),maintab);

	if(!rootOnly){
		QLabel* remove = new QLabel();
		QPixmap removepix(":/resources/icons/1457665374_minus.png");
		remove->setPixmap(removepix.scaled(20,20,Qt::KeepAspectRatio));
		remove->setMaximumSize(QSize(25,25));
		mainNavigation->setColumnCount(3);
		mainNavigation->setItemWidget(maintab,2,remove);
		mainNavigation->setColumnWidth(2,30);

		}
	else{
		mainNavigation->setColumnCount(2);
		}
	mainNavigation->setColumnWidth(1,Controller::GetNavigationWidth() - 30);






	Controller::AddMainNavigation(key,title);

	if(mainNavigation->topLevelItemCount() > 0){
		mainNavigation->clearSelection();
		mainNavigation->selectionModel()->select(mainNavigation->model()->index(mainNavigation->topLevelItemCount()-1,0,QModelIndex()),QItemSelectionModel::Select| QItemSelectionModel::Rows);
		mainNavPressed(mainNavigation->topLevelItem(mainNavigation->topLevelItemCount()-1),1);
		subNavigation->setEnabled(true);
		sctrlUI->setEnabled(true);
		}

}

void NavigationEditUI::fillSubNavigation(double key)
{

	this->rootOnly = (key == -14);
	if(this->rootOnly)
		this->rootOnly = !Controller::Get()->hasRootGroupAccess();

	QList<QTreeWidgetItem*> subNavItems = Controller::GetSubNavigation(key);
	//qDebug() << subNavItems.count() << subNavItems;
	subNavigation->clearSelection();
	int count = subNavigation->topLevelItemCount();
	for(int i = 0; i < count;i++){
		subNavigation->takeTopLevelItem(0);
		}

	if(subNavItems.count() > 0){
		subNavigation->insertTopLevelItems(0,subNavItems);

		if(!rootOnly){
			subNavigation->setColumnCount(4);
			QTreeWidgetItemIterator it(subNavigation);
			while (*it) {

				QLabel* add = new QLabel();
				QPixmap addpix (":/resources/icons/1457665371_plus.png");
				add->setPixmap(addpix.scaled(20,20,Qt::KeepAspectRatio));
				add->setMaximumSize(QSize(20,20));
				subNavigation->setItemWidget((*it),2,add);

				QLabel* remove = new QLabel();
				QPixmap removepix(":/resources/icons/1457665374_minus.png");
				remove->setPixmap(removepix.scaled(20,20,Qt::KeepAspectRatio));
				remove->setMaximumSize(QSize(20,20));
				subNavigation->setItemWidget((*it),3,remove);





				//subNavigation->resizeColumnToContents(0);
				subNavigation->setColumnWidth(2,30);
				subNavigation->setColumnWidth(3,30);


				if((*it)->text(1).toDouble() > idCount)
					idCount = (*it)->text(1).toDouble();
				++it;
				}
			}
		else {
			subNavigation->setColumnCount(2);
			}
		if(subNavigation->topLevelItemCount() > 0){
			//qDebug() << page << subNavigation->topLevelItem(0)->text(1).toDouble();
			subNavigation->selectionModel()->select(subNavigation->model()->index(0,0,QModelIndex()),QItemSelectionModel::Select| QItemSelectionModel::Rows);
			page =  (Controller::GetPage(subNavigation->topLevelItem(0)->text(1).toDouble()));
			NavigationPageEditUI::ShowUI(page);
			currentSubNav = subNavigation->topLevelItem(0)->text(1).toDouble();
			oldItemSubNavSelected = subNavigation->topLevelItem(0);
			subNavPressed(subNavigation->topLevelItem(0),0);
			}
		}
}

void NavigationEditUI::savePage()
{
	QJsonObject newPage = NavigationPageEditUI::Get()->save();
	if(!Controller::Compare(page,newPage)){
		subNavigation->setEnabled(false);
		if(Controller::ShowQuestion(tr("Do you want to save changes ?")))
			Controller::AddPage(currentSubNav,newPage);
		}
	subNavigation->setEnabled(true);
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
		this->editControllerCancelPressed();
		}
	else if(btn.contains("Add")){
		if(!rootOnly)
			addSubNavTopItem();
		}
	else if(btn.contains("Save") ){
		if(!rootOnly)
			this->editControllerSavePressed();
		}
	else if(btn.contains("Mainadd")){
		if(!rootOnly)
			addMainNavTopItem();
		}
}



void NavigationEditUI::editControllerCancelPressed()
{
	Controller::Get()->editControllerCancelPressed();
}

void NavigationEditUI::editControllerSavePressed()
{
	if(!rootOnly){
		this->savePage();
		this->save();
		}
	this->editControllerCancelPressed();

}

void NavigationEditUI::mainNavPressed(QTreeWidgetItem* item, int column)
{

	//qDebug() << "Main" <<item->text(0)  << column;

	//item->setText(0,"Pressedd");
	//
	//subNavigation->clear();
	if(column == 2){
		if(Controller::ShowQuestion(tr("Are you sure you want to remove this main Navigation Tab ?"))){
			if(Controller::ShowQuestion(tr("This will also remove all linked sub-navigation tabs"))){
				subNavigation->clear();
				if(mainNavigation->indexOfTopLevelItem(item) != -1)
					if(mainNavigation->takeTopLevelItem(mainNavigation->indexOfTopLevelItem(item)))
						Controller::RemoveMainNavigation(item->text(0).toDouble());
				}
			//qDebug() << "Remove Main Nav"<< item->text(0) << column;
			if(mainNavigation->topLevelItem(0)){
				fillSubNavigation(mainNavigation->topLevelItem(0)->text(0).toDouble());
				}
			else {
				subNavigation->setEnabled(false);
				sctrlUI->setEnabled(false);
				}
			}
		}
	else  fillSubNavigation(item->text(0).toDouble());


	//subNavigation->clearFocus();
}

void NavigationEditUI::mainNavChanged(QTreeWidgetItem* item, int)
{
	Controller::AddMainNavigation(item->text(0).toDouble(),item->text(1));
}


