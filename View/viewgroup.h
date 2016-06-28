#ifndef VIEWGROUP_H
#define VIEWGROUP_H

#include <viewgroups.h>
#include <feildui.h>

#include <QObject>
#include <QWidget>

class ViewGroup  : public QWidget
{
public:
	explicit ViewGroup(QWidget *parent = 0,QString strID = ""
			,QJsonObject structureView = QJsonObject(),QJsonArray data = QJsonArray());
	QJsonArray save();

	QList<FeildUI*> feilds;
private:
	QJsonObject structureView;
	QVBoxLayout * layout;
	QString strID;

};

#endif // VIEWGROUP_H
