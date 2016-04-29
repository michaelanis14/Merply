#include "settingsctrlsui.h"

#include <QPushButton>
SettingsCtrlsUI::SettingsCtrlsUI(QWidget *parent) : QWidget(parent)
{
	this->setContentsMargins(0,0,0,0);
	this->setObjectName("SettingsCtrlsUI");
	layout = new QHBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setAlignment(Qt::AlignRight);
	this->setFixedHeight(25);
	//this->setStyleSheet("background: #DCDFE0;");
	//color: #0FB9F2;
	title = new QLabel(this);
	//title->setStyleSheet("QLineEdit {background: #DCDFE0; border : 0px;font-weight: normal;font-size: 20px; color:black; }");
	title->move(2,-4);
	title->setEnabled(false);

	ctrlBtns = new QMap<int,QWidget*>();

	//title->setGeometry(5,5,200,200);
}


void SettingsCtrlsUI::addbtn(QString name,QString icon,QString action){

	QPushButton* btn = new QPushButton();
	btn->setObjectName(name+"->"+action);
	//btn->setText(name);
	btn->setFixedHeight(this->height());
	btn->setFixedWidth(this->height());
	btn->setFlat(true);
	btn->setToolTip(name);
	btn->setIcon(QIcon(icon));
	btn->setIconSize(QSize(this->height(),this->height()));


	QObject::connect(btn, SIGNAL(clicked()),this, SLOT(btn_Clicked()));
	ctrlBtns->insert(ctrlBtns->count(),btn);
	layout->addWidget(btn);

}

QString SettingsCtrlsUI::getTitle() const
{
	return title->text();
}

void SettingsCtrlsUI::setTitle(QString value)
{
	title->setText(value);
}

void SettingsCtrlsUI::clear()
{
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

void SettingsCtrlsUI::btn_Clicked()
{
	if(sender()->objectName().contains("Delete")){
		emit removeClicked();
		}
	emit btnClicked(sender()->objectName());
}
void SettingsCtrlsUI::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
