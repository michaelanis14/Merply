#include "permissionfieldui.h"


#include <QHeaderView>

PermissionFieldUI::PermissionFieldUI(QWidget *parent,QString name) : QWidget(parent)
{

	layout = new QFormLayout;
	this->setLayout(layout);
	this->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setMargin(0);
	layout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
	QStringList basicPermissons;
	basicPermissons << tr("Any One") << tr("No One") <<tr("Specific");
	readPermissons = new ERPComboBox();
	readPermissons->addItems(basicPermissons);
	layout->addRow(tr(name.toStdString().c_str()), readPermissons);

	QObject::connect(readPermissons,SIGNAL(currentIndexChanged(int)),this,SLOT(showSpcfic(int)));


	allowGroupBox = new QGroupBox(tr("Permissions"));
	QHBoxLayout* allowGroupBoxLayout = new QHBoxLayout;
	allowGroupBox->setLayout(allowGroupBoxLayout);
	layout->addWidget(allowGroupBox);


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


	denyGroup = new QTreeWidget();
	denyGroup->setColumnCount(3);
	//denyGroup->setFixedWidth(Controller::GetNavigationWidth());

	//denyGroup->setFixedHeight(Controller::GetNavigationMainHeight());
	denyGroup->header()->close();
	//denyGroup->setEditTriggers(QAbstractItemView::AllEditTriggers);
	denyGroup->setDropIndicatorShown(false);
	QObject::connect(denyGroup, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(denyGroupPressed(QTreeWidgetItem*,int)));
	denyGroup->hideColumn(0);
	this->layout->addWidget(denyGroup);

}

void PermissionFieldUI::showSpcfic(int field)
{
	if(field == 3){

		}
	else{

		}
}

void PermissionFieldUI::allowGroupPressed(QTreeWidgetItem* item, int column)
{

}

void PermissionFieldUI::denyGroupPressed(QTreeWidgetItem* item, int column)
{

}
