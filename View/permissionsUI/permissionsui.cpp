#include "permissionsui.h"


PermissionsUI::PermissionsUI(QWidget *parent) : QWidget(parent)
{
	this->setContentsMargins(0,0,0,0);
	layout = new QVBoxLayout(this);
	layout->setSpacing(0);
	layout->setMargin(0);


	permissionsBox = new QGroupBox(tr("Permissions"));
	QHBoxLayout* permissionsBoxLayout = new QHBoxLayout;
	permissionsBox->setLayout(permissionsBoxLayout);

	//pageDetailsLayout->setLabelAlignment(Qt::AlignLeft);
	//pageEdit = new PageStructureViewEditeUI();

	PermissionFieldUI *pf = new PermissionFieldUI(0,"Read");
	permissionsBoxLayout->addWidget(pf);
	layout->addWidget(permissionsBox);

}
