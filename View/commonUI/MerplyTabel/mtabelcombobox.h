#ifndef MTABELCOMBOBOX_H
#define MTABELCOMBOBOX_H

#include <QStyledItemDelegate>

class MTabelCombobox: public QStyledItemDelegate
{
	Q_OBJECT
public:
	MTabelCombobox(QObject* parent=0);
	virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;
	virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

};

#endif // MTABELCOMBOBOX_H
