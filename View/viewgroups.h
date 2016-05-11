#ifndef VIEWGROUPS_H
#define VIEWGROUPS_H

#include "settingsctrlsui.h"

#include "viewgroup.h"
#include "feildui.h"

#include <QObject>
#include <QWidget>
#include <QPainter>

class ViewGroup;
class ViewGroups : public QWidget
{
	Q_OBJECT
public:
	explicit ViewGroups(QWidget *parent = 0,QJsonObject structureView = QJsonObject(), QJsonObject data = QJsonObject());
	QJsonObject save();
signals:

private:
	QVBoxLayout * layout;
	QList<ViewGroup*> viewgroups;
	QHash<QString,QWidget*>HViewGroups;
	QJsonObject structureView;
protected:
	//void showEvent(QShowEvent *);
	void paintEvent(QPaintEvent*event);
public slots:
	void btn_Clicked(QString btn);
};

#endif // VIEWGROUPS_H
