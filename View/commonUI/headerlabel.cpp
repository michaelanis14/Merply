#include "headerlabel.h"

HeaderLabel::HeaderLabel(QWidget *parent) : QWidget(parent)
{
	this->setContentsMargins(0,0,0,0);
	this->setObjectName("HeaderLabel");
	layout = new QHBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setAlignment(Qt::AlignLeft);
//	this->setFixedHeight(45);
	//this->setStyleSheet("background: #DCDFE0;");
	//color: #0FB9F2;
	title = new QLineEdit();
	title->setStyleSheet("QLineEdit { border : 0px;border-bottom : 3px solid gray;font-weight: normal;font-size: 25px; color:#0FB9F2; }");
	layout->addWidget(title);


}

QString HeaderLabel::getTitle() const
{
	return title->text();
}

void HeaderLabel::setTitle(QString value)
{
	title->setText(value);
}

void HeaderLabel::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
