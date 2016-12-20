#include "mtabelcombobox.h"
#include <QComboBox>

MTabelCombobox::MTabelCombobox(QObject* parent) : QStyledItemDelegate(parent)
{
}

QWidget* MTabelCombobox::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	// ComboBox ony in column 2
	//if (index.column() != 1)
	//	return QStyledItemDelegate::createEditor(parent, option, index);

	// Create the combobox and populate it
	QComboBox* cb = new QComboBox(parent);
	int row = index.row();
	cb->addItem(QString("one in row %1").arg(row));
	cb->addItem(QString("two in row %1").arg(row));
	cb->addItem(QString("three in row %1").arg(row));
	return cb;
}


void MTabelCombobox::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	if (QComboBox* cb = qobject_cast<QComboBox*>(editor)) {
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
	if (QComboBox* cb = qobject_cast<QComboBox*>(editor))
		// save the current text of the combo box as the current value of the item
		model->setData(index, cb->currentText(), Qt::EditRole);
	else
		QStyledItemDelegate::setModelData(editor, model, index);
}




