#ifndef MTABELCOMBOBOX_H
#define MTABELCOMBOBOX_H

#include <QStyledItemDelegate>
#include <QJsonDocument>
#include <QJsonObject>


class MTabelCombobox: public QStyledItemDelegate
{
	Q_OBJECT
public:
	MTabelCombobox(QObject* parent=0, QJsonObject strct = QJsonObject());
	virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex& index) const;
	virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;
	virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

private:
	QJsonObject strct;
	QVector<QJsonDocument> items;
public slots:
	void gotReportData(QVector<QJsonDocument> items);
	bool eventFilter(QObject *object, QEvent *event);

};

#endif // MTABELCOMBOBOX_H
