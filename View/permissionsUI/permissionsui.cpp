#include "permissionsui.h"
#include <QDebug>

PermissionsUI::PermissionsUI(QWidget *parent, QJsonObject saved) : QWidget(parent)
{
	this->setContentsMargins(0,0,0,0);
	layout = new QVBoxLayout(this);
	layout->setSpacing(0);
	layout->setMargin(0);


	permissionsBox = new QGroupBox(tr("Permissions"));
	QHBoxLayout* permissionsBoxLayout = new QHBoxLayout;
	permissionsBox->setLayout(permissionsBoxLayout);
	permissionsBox->setHidden(true);

	//pageDetailsLayout->setLabelAlignment(Qt::AlignLeft);
	//pageEdit = new PageStructureViewEditeUI();
	btnExpand = new ExpandButton(0,"Permissions");
	layout->addWidget(btnExpand);


	QObject::connect(btnExpand, SIGNAL(show()),this, SLOT(showPermissions()));
	QObject::connect(btnExpand, SIGNAL(hide()),this, SLOT(hidePermissions()));

	pfRead = new PermissionFieldUI(0,"Read",saved);
	permissionsBoxLayout->addWidget(pfRead);
	layout->addWidget(permissionsBox);


}

QJsonObject PermissionsUI::save()
{
	QJsonObject save;
	save.insert("Read",pfRead->save());
	return save;
}

void PermissionsUI::load(QJsonObject saved)
{
	pfRead->load(saved.value("Read").toObject());
	updateDescription();
}

void PermissionsUI::updateDescription()
{
	QJsonObject pfRead = this->pfRead->save();
	if(pfRead.value("Permissions").toString().toInt() == 100)
		btnExpand->updateDescription("Can read Everyone");
	else if(pfRead.value("Permissions").toString().toInt() == 101)
		btnExpand->updateDescription("Can read None");
	else if(pfRead.value("Permissions").toString().toInt() == 111)
		btnExpand->updateDescription("Can read Specific");
}

void PermissionsUI::showPermissions()
{
	permissionsBox->setHidden(false);
	//updateDescription();
}

void PermissionsUI::hidePermissions()
{
	permissionsBox->setHidden(true);
	updateDescription();
}



