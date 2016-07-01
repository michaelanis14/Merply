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
		QJsonObject save();
		static  ViewGroups* Create(QJsonObject structureView, QJsonObject data);
		static ViewGroups* Get();
		static QList<ViewGroup*> Viewgroups;
		static QHash<QString,FeildUI*> Fieldsgroups;
		QString checkMandatory();
signals:

private:
	explicit ViewGroups(QWidget *parent = 0,QJsonObject structureView = QJsonObject(), QJsonObject data = QJsonObject());
	static ViewGroups* p_instance;
	QVBoxLayout * layout;
	QHash<QString,QWidget*>HViewGroups;
	QJsonObject structureView;

	//should be moved to the controller

protected:
	//void showEvent(QShowEvent *);
	void paintEvent(QPaintEvent*event);

public slots:
	void btn_Clicked(QString btn);
};

#endif // VIEWGROUPS_H
