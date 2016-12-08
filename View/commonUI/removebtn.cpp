#include "removebtn.h"
#include"QDebug"


RemoveBtn::RemoveBtn(QWidget *parent, QWidget* widget) : QWidget(parent)
{
	this->setContentsMargins(2,2,2,2);
	this->widget = widget;
	layout = new QHBoxLayout(this);
	layout->setContentsMargins(2,2,2,2);
	layout->setSpacing(0);
	layout->setMargin(0);

	rmvbtn = new SettingsCtrlsUI();
	rmvbtn->addbtn("Remove",":/resources/icons/remove.png","remove");
	layout->addWidget(rmvbtn);
	QObject::connect(rmvbtn,SIGNAL(btnClicked(QString)),this,SLOT(remove()));


	lblCancel = new QLabel(tr("Cancel"));
	lblCancel->setFixedWidth(lblCancel->text().count()*7);
	lblCancel->setObjectName("cancel");
	lblCancel->setStyleSheet("QLabel { background-color : gray; color : white; }");
	lblCancel->setHidden(true);
	layout->addWidget(lblCancel);

	//widget->setFixedWidth(190);
	layout->addWidget(widget);


	lblDelete = new QLabel(tr("Delete"));
	lblDelete->setFixedWidth(lblDelete->text().count()*7);
	lblDelete->setObjectName("delete");
	lblDelete->setStyleSheet("QLabel { background-color : red; color : white; }");
	lblDelete->setHidden(true);
	layout->addWidget(lblDelete);

	//this->setFixedWidth((lblDelete->text().count()*7)+(lblCancel->text().count()*7)+(widget->width())-30);

}

void RemoveBtn::hideRemovebtn(bool hidden)
{
	rmvbtn->setHidden(hidden);
}

void RemoveBtn::removeAll()
{
	//qDebug() << __FILE__ << __LINE__  << "RemoveAll";
	QList<QWidget *> Widgets = this->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		if(child != NULL){
			//typeFieldsLayout->removeWidget(child);
			child->setHidden(true);
			child->setParent(0);
			child->deleteLater();
			}
		}

	this->setHidden(true);
	this->setParent(0);
}

void RemoveBtn::remove()
{
	//layout->removeWidget(rmvbtn);
	rmvbtn->setHidden(true);
	lblCancel->setHidden(false);
	lblDelete->setHidden(false);
	//((QHBoxLayout*)((QWidget*)widget->parent())->layout())->insertWidget(((QWidget*)widget->parent())->layout()->indexOf(widget)+1,lblDelete);
}



void RemoveBtn::mousePressEvent(QMouseEvent *event){
	QLabel *child=  static_cast<QLabel *>(childAt(event->pos()));
	if  (!child)
		return;
	else {
		if( child->objectName().compare("cancel") == 0){
			lblCancel->setHidden(true);
			rmvbtn->setHidden(false);
			lblDelete->setHidden(true);
			//emit cancel(widget);

			}
		else if(child->objectName().compare("delete") == 0){
			emit remove(widget);
			removeAll();

			}
		}
}
