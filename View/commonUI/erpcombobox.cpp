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
	this->addedItems = false;
	this->indexedFill = indexedFill;
	if(indexedFill)
		this->setObjectName("ERPComboBoxIndexed");
	else this->setObjectName("ERPComboBox");
	this->installEventFilter(this);

}
void ERPComboBox::addJsonItems(QList<QJsonDocument> items){
	int i = 0;
	foreach (const QJsonDocument & value, items){
		//qDebug() << select.trimmed() << value.object().keys();
		QString valueString = value.object().value("Value").toString();
		QString keyString = value.object().value("Key").toString();
		if(!valueString.isEmpty() && !keyString.isEmpty()){
			QComboBox::insertItem(i,valueString.trimmed());
			keys.insert(i,keyString);
			i++;
			this->addedItems = true;
			}
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

QString ERPComboBox::getKey(){
	if(this->addedItems)
		return keys.at(currentIndex());
	return "_";

}

QStringList ERPComboBox::getItemsText()
{
	QStringList itemsText;
	for(int i = 0; i < this->count(); i++){
		itemsText.append(this->itemText(i));
		}
	 return itemsText;
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





