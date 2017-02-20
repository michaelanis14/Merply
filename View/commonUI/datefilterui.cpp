#include "datefilterui.h"
#include <QLabel>

DateFilterUI::DateFilterUI(QWidget *parent) : QWidget(parent)
{
	this->setContentsMargins(0,0,0,0);
	layout = new QFormLayout(this);
	//this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setMargin(0);
	this->setLayout(layout);

	from = new QDateTimeEdit();
	//from->setDateTime(QDateTime::currentDateTime());
	//from->setDateTime(QDateTime::fromString("2017/1/1",Qt::ISODate));
	from->setDateTime(QDateTime::currentDateTime().addYears(-1));
	from->setDisplayFormat("dd/MM/yyyy");
	layout->addRow(tr("From :"),from);


	to = new QDateTimeEdit();
	to->setDateTime(QDateTime::currentDateTime());
	to->setDisplayFormat("dd/MM/yyyy");
	layout->addRow(tr("To :"),to);

}

QString DateFilterUI::getToDateTime()
{
	return (to)->dateTime().toString(Qt::DefaultLocaleShortDate);
}

QString DateFilterUI::getFromDateTime()
{
	return (from)->dateTime().toString(Qt::DefaultLocaleShortDate);
}
