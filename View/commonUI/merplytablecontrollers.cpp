#include "merplytablecontrollers.h"

merplyTableControllers::merplyTableControllers(QWidget *parent,QString id, const bool edit, const bool remove) : QWidget(parent)
{
	this->id = id;
	layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setAlignment(Qt::AlignCenter);


	if(edit){
		btn_edit = new QPushButton();
		btn_edit->setObjectName("Edit");
		btn_edit->setText("Edit");
		QObject::connect(btn_edit, SIGNAL(clicked()),this, SLOT(btn_editClicked()));
		layout->addWidget(btn_edit);
		}
	if(remove){
		btn_delete = new QPushButton();
		btn_delete->setObjectName("Delete");
		btn_delete->setText("Delete");
		QObject::connect(btn_delete, SIGNAL(clicked()),this, SLOT(btn_deleteClicked()));
		layout->addWidget(btn_delete);
		}
	this->setLayout(layout);
}

void merplyTableControllers::btn_editClicked()
{
	emit editClicked(id);
	//qDebug() << "Edit" << id;
}

void merplyTableControllers::btn_deleteClicked()
{
	emit deleteClicked(id);
	//	qDebug() <<"Delete" << id;
}
