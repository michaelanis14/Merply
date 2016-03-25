#include "navigationbtn.h"

NavigationBtn::NavigationBtn(QWidget *parent,QString title) : QWidget(parent)
{
	root = new QTreeWidgetItem(QStringList(title));
	this->setObjectName("Tab");
}

void NavigationBtn::addChild(QString title, QJsonObject view)
{
	QTreeWidgetItem*  item = new QTreeWidgetItem( QStringList(title));

	root->addChild(item);

}
