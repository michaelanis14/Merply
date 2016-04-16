#include "permissionfieldui.h"



#include <QFormLayout>
PermissionFieldUI::PermissionFieldUI(QWidget *parent,QString name) : QWidget(parent)
{

	QFormLayout* layout = new QFormLayout;
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




}

void PermissionFieldUI::showSpcfic(int field)
{
	if(field == 3){

		}
	else{

		}
}
