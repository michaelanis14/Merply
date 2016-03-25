#include "filepathui.h"
#include <QFileDialog>

filepathUI::filepathUI(QWidget *parent) : QWidget(parent)
{
	this->setAutoFillBackground(true);
	filepathLayout = new QHBoxLayout(this);
	open = new QLabel();
	open->setObjectName("open");
	open->setPixmap(QPixmap(":/resources/folder"));
	open->setFixedSize(16,16);
	lineEdit = new QLineEdit();

	filepathLayout->addWidget(lineEdit);
	filepathLayout->addWidget(open);


}
QLineEdit* filepathUI::getLineEdit() const
{
	return lineEdit;
}

void filepathUI::setLineEdit(QLineEdit* value)
{
	lineEdit = value;
}

void filepathUI::mousePressEvent(QMouseEvent *event){

	QLabel *child=  static_cast<QLabel *>(childAt(event->pos()));
	if  (!child)
		return;
	else {
		if( child->objectName().compare("open") == 0){
			QString filepath = QFileDialog::getOpenFileName(0, tr("Open File"));
			if(!filepath.isEmpty())
				getLineEdit()->setText(filepath);
			}


		}

	event->accept();


}


