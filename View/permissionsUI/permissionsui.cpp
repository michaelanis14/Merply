#include "permissionsui.h"
#include <QDebug>

PermissionsUI::PermissionsUI(QWidget *parent, bool read, bool write) : QWidget(parent)
{
	this->setContentsMargins(0,0,0,0);
	layout = new QVBoxLayout(this);
	layout->setSpacing(0);
	layout->setMargin(0);

	this->read = read;
	this->write = write;

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

	if(read){
		pfRead = new PermissionFieldUI(this,"Read");
		permissionsBoxLayout->addWidget(pfRead);
		}
	if(write){
		pfWrite = new PermissionFieldUI(this,"Write");
		permissionsBoxLayout->addWidget(pfWrite);
		}
	layout->addWidget(permissionsBox);


}

QJsonObject PermissionsUI::save()
{
	QJsonObject save;
	if(read)
		save.insert("Read",pfRead->save());
	if(write)
		save.insert("Write",pfWrite->save());

	return save;
}

void PermissionsUI::load(QJsonObject saved)
{
	if(read)
		pfRead->load(saved.value("Read").toObject());
	if(write)
		pfWrite->load(saved.value("Write").toObject());
	updateDescription();
}

void PermissionsUI::updateDescription()
{
	QString description = "";
	if(read){
		QJsonObject pfRead = this->pfRead->save();
		if(pfRead.value("Permissions").toString().toInt() == 100)
			description += tr("Can read Everyone ");
		else if(pfRead.value("Permissions").toString().toInt() == 101)
			description += tr("Can read None ");
		else if(pfRead.value("Permissions").toString().toInt() == 111)
			description += tr("Can read Specific ");
		}
	if(write){
		QJsonObject pfWriteObj = this->pfWrite->save();
		if(pfWriteObj.value("Permissions").toString().toInt() == 100)
			description += tr("- Can write Everyone");
		else if(pfWriteObj.value("Permissions").toString().toInt() == 101)
			description += tr("- Can write None");
		else if(pfWriteObj.value("Permissions").toString().toInt() == 111)
			description += tr("- Can write Specific");
		}

	btnExpand->updateDescription(description);
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



