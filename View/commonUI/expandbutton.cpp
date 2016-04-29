#include "expandbutton.h"

ExpandButton::ExpandButton(QWidget *parent, QString title) : QWidget(parent)
{

	this->setContentsMargins(5,0,0,0);
	layout = new QHBoxLayout(this);
	layout->setSpacing(5);
	layout->setMargin(0);
	layout->setAlignment(Qt::AlignLeft);

	this->title = title;

	description = new QLabel(title + " : " );

	btnArroW = new QPushButton();
	btnArroW->setObjectName("show");
	//btn->setText(name);
	btnArroW->setFixedHeight(25);
	btnArroW->setFixedWidth(40);
	btnArroW->setFlat(true);
	btnArroW->setToolTip("Show Permissions");
	btnArroW->setIcon(QIcon(":/resources/icons/arrow-up.png"));
	btnArroW->setIconSize(QSize(15,15));

	layout->addWidget(btnArroW);
	layout->addWidget(description);
	hidden = true;
	QObject::connect(btnArroW, SIGNAL(clicked()),this, SLOT(btnArroW_Clicked()));
}

void ExpandButton::btnArroW_Clicked()
{
	if(hidden){
		btnArroW->setIcon(QIcon(":/resources/icons/arrow-down.png"));
		//description->setHidden(true);
		description->setText(title);
		hidden = false;
		emit show();
		}
	else{
		btnArroW->setIcon(QIcon(":/resources/icons/arrow-up.png"));
		//description->setHidden(false);
		hidden = true;
		emit hide();
		}
}

void ExpandButton::updateDescription(QString text)
{
	this->description->setText(title +" : " + text);
}
