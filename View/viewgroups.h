#ifndef VIEWGROUPS_H
#define VIEWGROUPS_H

#include "settingsctrlsui.h"

#include "viewgroup.h"
#include "feildui.h"

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QDataWidgetMapper>

class ViewGroup;
class ViewGroups : public QWidget
{
	Q_OBJECT
public:
	explicit ViewGroups(QWidget *parent = 0,QJsonObject structureView = QJsonObject()
			,QHash<QString,FeildUI*> *fieldsgroups = new QHash<QString,FeildUI*>(),QDataWidgetMapper *mapper = new QDataWidgetMapper());
		QPair<QString, QString> save(bool newDocument);
	//	static  ViewGroups* Create(QJsonObject structureView, QJsonObject data);
	//	static ViewGroups* Get();

		QString checkMandatory();
signals:

private:
	static ViewGroups* p_instance;
	QVBoxLayout * layout;
	QHash<QString,QWidget*>HViewGroups;
	QJsonObject structureView;
	QList<ViewGroup*> viewgroups;
	QHash<QString, FeildUI*>* fieldsgroups;
	//should be moved to the controller

protected:
	//void showEvent(QShowEvent *);
	void paintEvent(QPaintEvent*event);

public slots:
	void btn_Clicked(QString btn);
	void gotSetttingsDocument(QJsonDocument strct);
};

#endif // VIEWGROUPS_H
