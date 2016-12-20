/*************************************
**   Created on:  10/4/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/

#include "erpcombobox.h"

#include "controller.h"
#include "QDebug"
#include "QCompleter"
#include <QPair>
#include <QJsonArray>

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
	//qDebug() << __FILE__ << __LINE__  << items;
	foreach (const QJsonDocument & value, items){

		//QString valueString = value.object().value("Value").toString();
		QString keyString = value.object().value("Key").toString();
		QString valueString;
		QJsonValue Val = value.object().value("Value");
			//	qDebug() << __FILE__ << __LINE__ <<"VAL" << Val << keyString;
				if(Val.isObject()){
					//qDebug() << __FILE__ << __LINE__  << "isObJect" << Val;
					if(Val.toObject().value("Key") != QJsonValue::Undefined)
						keyString = Val.toObject().value("Key").toString();
					if(Val.toObject().value("Value") != QJsonValue::Undefined)
						valueString = Val.toObject().value("Value").toString();

					QComboBox::insertItem(i,valueString);
					keys.insert(i,keyString);
					i++;
					}
				else if(Val.isArray()){
					foreach(QJsonValue subVal,Val.toArray()){

						//qDebug() << __FILE__ << __LINE__  << "chechkkk" << subVal <<Controller::Get()->toString(subVal);

						valueString = Controller::Get()->toString(subVal);

						QComboBox::insertItem(i,valueString);
						keys.insert(i,keyString);
						i++;
						}
					}
				else{
					QString valueString = Val.toString().trimmed();
					if(valueString.isNull() || valueString.isEmpty()){
						//		qDebug() << __FILE__ << __LINE__ <<"EMPTY"<<i << valueString;
						continue;
						}
					else{
						QComboBox::insertItem(i,valueString);
						//	qDebug() << __FILE__ << __LINE__ <<"NOT ARRY"<<i << valueString;
						keys.insert(i,keyString);
						i++;
						}
					}
				this->addedItems = true;

		}
	this->adjustSize();
	if(count() > 0)
		this->setEnabled(true);
}

void ERPComboBox::focusOutEvent(QFocusEvent *e)
{
	if(this->addedItems && !indexedFill){

		QRegExp re("\\d*");
		if(this->currentText()==""){
			//qDebug() << __FILE__ << __LINE__  <<"EMP";
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
			//qDebug() << __FILE__ << __LINE__   <<"noComp";
			this->clearEditText();
			this->setCurrentText(this->itemText(this->currentIndex()));
			}
		else{
			//qDebug() << __FILE__ << __LINE__  <<this->findText(this->completer()->currentCompletion());

			this->clearEditText();
			this->setCurrentIndex((this->findText(this->completer()->currentCompletion())));

			}

		this->clearFocus();
		this->clearMask();
		}
	QWidget::focusOutEvent(e);

}

QString ERPComboBox::getKey(){

	if(this->addedItems && currentIndex() != -1)
		if(keys.count() > currentIndex())
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

void ERPComboBox::removeSelected()
{
	keys.removeAt(currentIndex());
	removeItem(currentIndex());
	if(count() <= 0)
		this->setEnabled(false);
}

void ERPComboBox::removeList(QStringList list)
{
	QStringList items = getItemsText();
	foreach(QString item,list){
		int i = items.indexOf(item);
		removeItem(i);
		keys.removeAt(i);
		}
	if(count() <= 0)
		this->setEnabled(false);
}



bool ERPComboBox::eventFilter(QObject *obj, QEvent *event)
{
	if (indexedFill && event->type() == QEvent::KeyRelease)
		{
		//QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		//	qDebug() << __FILE__ << __LINE__ <<"CO" << this->completer()->currentCompletion();
		if(oldCompletion.compare(this->completer()->currentCompletion()) != 0){
			oldCompletion = this->completer()->currentCompletion();
			emit indexedFillEvent(oldCompletion);
			//	qDebug() << __FILE__ << __LINE__  << this->completer()->currentCompletion();
			}

		}
	return QObject::eventFilter(obj, event);
}

void ERPComboBox::clear()
{
	keys.clear();
	this->addedItems = false;
	QComboBox::clear();
}

QJsonDocument ERPComboBox::getCurrentJsonItem()
{
	QJsonObject obj;
	QJsonArray v1;
	QJsonArray v2;
	v2.append(this->currentText());
	v1.append(v2);
	obj.insert("Value",v1);
	obj.insert("Key",this->getKey());

	return QJsonDocument(obj);
}
/*
void ERPComboBox::setCurrentIndex(int index)
{
	QComboBox::setCurrentIndex(index);
	emit currentIndexChanged(index);
}
*/
//void ERPComboBox::mousePressEvent(QMouseEvent *event){
//QLabel *child=  static_cast<QLabel *>(childAt(event->pos()));

//	event->accept();
//	qDebug() << __FILE__ << __LINE__  <<"M" << indexedFill;
//if(!this->indexedFill)
//		QWidget::mousePressEvent(event);

//}





