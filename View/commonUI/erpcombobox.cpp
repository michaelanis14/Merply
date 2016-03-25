/*************************************
**   Created on:  10/4/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/

#include "erpcombobox.h"
#include "QDebug"
#include "QCompleter"
#include <QPair>

ERPComboBox::ERPComboBox(QWidget *parent, bool indexedFill) :
	QComboBox(parent)
{
	this->setEditable(true);
	this->setInsertPolicy(QComboBox::NoInsert);
	this->setAutoCompletion(true);
	this->items = QList<QString >();
	this->addedItems = false;
	this->indexedFill = indexedFill;
	if(indexedFill)
		this->setObjectName("ERPComboBoxIndexed");
	else this->setObjectName("ERPComboBox");
	this->installEventFilter(this);

}
void ERPComboBox::addItems(QList<QString> pairList){
	int c = this->count();
	for(int i = 0; i < c;i++){
		QComboBox::removeItem(0);
		}

	this->items = pairList;
	QList<QString> list;
	for(int i = 0; i < pairList.length();i++) {
		this->addedItems = true;
		QComboBox::insertItem(i,pairList.at(i));
		list.append(pairList.at(i));
		}

}

void ERPComboBox::focusOutEvent(QFocusEvent *e)
{
	if(this->addedItems && !indexedFill){

		QRegExp re("\\d*");
		if(this->currentText()==""){
			//qDebug() <<"EMP";
			this->clearEditText();
			this->setCurrentText(this->itemText(this->currentIndex()));
			}
		else if (re.exactMatch(this->currentText())){
			int index = this->currentText().toInt()-1;

			if(index > -1 && index < this->count() )
				this->setCurrentIndex(index);
			else
				this->setCurrentText(this->itemText(this->currentIndex()));
			}
		else if(this->completer()->currentCompletion() ==""){
			//qDebug()  <<"noComp";
			this->clearEditText();
			this->setCurrentText(this->itemText(this->currentIndex()));
			}
		else{
			//qDebug() <<this->findText(this->completer()->currentCompletion());

			this->clearEditText();
			this->setCurrentText(this->itemText(this->findText(this->completer()->currentCompletion())));

			}

		this->clearFocus();
		this->clearMask();
		}
	QWidget::focusOutEvent(e);

}

int ERPComboBox::getKey(){
	if(this->addedItems){
		//	qDebug() << currentIndex()<< items.at(currentIndex()).first << items.at(currentIndex()).second;
		return items.indexOf(items.at(currentIndex()));
		}
	return 0;
}

bool ERPComboBox::eventFilter(QObject *obj, QEvent *event)
{
	if (indexedFill && event->type() == QEvent::KeyRelease)
		{
		//QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
	//	qDebug()<<"CO" << this->completer()->currentCompletion();
		if(oldCompletion.compare(this->completer()->currentCompletion()) != 0){
			oldCompletion = this->completer()->currentCompletion();
			emit indexedFillEvent(oldCompletion);
		//	qDebug() << this->completer()->currentCompletion();
			}

		}
	return QObject::eventFilter(obj, event);
}
//void ERPComboBox::mousePressEvent(QMouseEvent *event){
	//QLabel *child=  static_cast<QLabel *>(childAt(event->pos()));

	//	event->accept();
//	qDebug() <<"M" << indexedFill;
	//if(!this->indexedFill)
//		QWidget::mousePressEvent(event);

//}





