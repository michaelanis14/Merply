#ifndef QTOOLTIPPER_H_
#define QTOOLTIPPER_H_

#include"merplytabelview.h"

#include <QObject>
#include <QAbstractItemView>
#include <QHelpEvent>
#include <QToolTip>
#include <QDebug>


class QToolTipper : public QObject
{
	Q_OBJECT
public:
	explicit QToolTipper(QObject* parent = NULL)
		: QObject(parent)
	{
	}

protected:
	bool eventFilter(QObject* obj, QEvent* event)
	{

		if (event->type() == QEvent::ToolTip)
			{
			//qDebug() << obj->parent();
			QTableView* view = qobject_cast<QTableView*>(obj->parent());
			if (!view)
				{

				return false;
				}

			QHelpEvent* helpEvent = static_cast<QHelpEvent*>(event);
			QPoint pos = helpEvent->pos();
			//qDebug() << pos;
			QModelIndex index = view->indexAt(pos);
			//qDebug() << index;
			if (!index.isValid())
				return false;

			QString itemText = view->model()->data(index,Qt::DisplayRole).toString();
			//qDebug() << itemText;
			QString itemTooltip = view->model()->data(index, Qt::ToolTipRole).toString();
			//qDebug() << itemTooltip;
			QFontMetrics fm(view->font());
			int itemTextWidth = fm.width(itemText);
			QRect rect = view->visualRect(index);
			int rectWidth = rect.width();

			if ((itemTextWidth > rectWidth) && !itemTooltip.isEmpty())
				{
				QToolTip::showText(helpEvent->globalPos(), itemTooltip, view, rect);
				}
			else
				{
				QToolTip::hideText();
				}
			return true;
			}
		return false;
	}
};

#endif
