#include "hcontrollers.h"

HControllers::HControllers(QWidget *parent,QStringList btns) : QWidget(parent)
{
	this->setContentsMargins(0,0,0,0);
	this->layout = new QHBoxLayout(this);
	this->layout->setAlignment(Qt::AlignRight);
	this->layout->setContentsMargins(0,0,0,0);
	//this->layout->setSpacing(1);
	this->setMaximumHeight(40);


	this->fill(btns);
}
void HControllers::btn_Clicked()
{
	emit btnClicked(sender()->objectName());
}
void HControllers::clear(){

	QList<QWidget *> Widgets = this->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		if(child != NULL){
			layout->removeWidget(child);
			child->setHidden(true);
			//child->setParent(0);
			child->deleteLater();
			}
		}
}
void HControllers::fill(QStringList btns){
	foreach(QString btnName,btns){
		QPushButton* btn = new QPushButton();
		btn->setMinimumHeight(40);
		btn->setMinimumWidth(70);
		QStringList nameAction = btnName.split("->");
		btn->setObjectName(btnName);
		btn->setText(nameAction.first());
		QObject::connect(btn, SIGNAL(clicked()),this, SLOT(btn_Clicked()));
		layout->addWidget(btn);
		}
}


void HControllers::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
