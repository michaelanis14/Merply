#include "mtabelcombobox.h"
#include <erpcombobox.h>
#include "controller.h"
#include <QDebug>
#include <QEvent>

MTabelCombobox::MTabelCombobox(QObject* parent,QJsonObject strct) : QStyledItemDelegate(parent)
{
	this->strct = strct;
	this->items = QList<QJsonDocument>();
//	qDebug() << __FILE__ << __LINE__   <<"MTabelCombobox"<< strct;
	QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(gotReportData(QList<QJsonDocument>)));
	Controller::Get()->getJsonEntityFieldsList(strct.value("Source").toString(),strct.value("Select").toString(),strct.value("Condition").toString());

}

QWidget* MTabelCombobox::createEditor(QWidget* parent, const QStyleOptionViewItem& , const QModelIndex& index) const
{
	//qDebug() << "createEditor";
	ERPComboBox* cb = new ERPComboBox(parent);
		cb->removeEventFilter(parent);
	cb->installEventFilter(parent);
	if(!this->items.isEmpty())
		cb->addJsonItems(this->items);
	//setEditorData(cb, index);
	//	int row = index.row();
	return cb;
}


void MTabelCombobox::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	//qDebug() << index.data(Qt::EditRole).toString();
	if (ERPComboBox* cb = qobject_cast<ERPComboBox*>(editor)) {
		// get the index of the text in the combobox that matches the current value of the itenm
		QString currentText = index.data(Qt::EditRole).toString();
		int cbIndex = cb->findText(currentText);
		// if it is valid, adjust the combobox
		if (cbIndex >= 0)
			cb->setCurrentIndex(cbIndex);
		} else {
		QStyledItemDelegate::setEditorData(editor, index);
		}
}


void MTabelCombobox::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{

	//qDebug() << __FILE__ << __LINE__  << qobject_cast<ERPComboBox*>(editor)->currentText();
	if (ERPComboBox* cb = qobject_cast<ERPComboBox*>(editor))
		// save the current text of the combo box as the current value of the item
		model->setData(index, cb->currentText(), Qt::EditRole);
	else
		QStyledItemDelegate::setModelData(editor, model, index);
}

void MTabelCombobox::gotReportData(QList<QJsonDocument> items)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotJsonListData(QList<QJsonDocument>)),this,SLOT(gotReportData(QList<QJsonDocument>)));
	this->items = items;
	//qDebug() << items;
}

bool MTabelCombobox::eventFilter(QObject* object, QEvent* event) {
	if(event->type() == QEvent::FocusIn) {
		ERPComboBox* cb = qobject_cast<ERPComboBox*>(object);
		if(cb) {
			cb->removeEventFilter(this);
			//cb->showPopup();
			//important to handle it only the first time, otherwise will result in
			//focus glitches
			cb->removeEventFilter(this);
			}
		}
	//return QStyledItemDelegate::eventFilter(object, event);
}



