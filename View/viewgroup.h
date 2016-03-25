#ifndef VIEWGROUP_H
#define VIEWGROUP_H

#include <feildui.h>

#include <QObject>
#include <QWidget>

class ViewGroup  : public QWidget
{
public:
	explicit ViewGroup(QWidget *parent = 0,QJsonObject structureView = QJsonObject(),QJsonObject data = QJsonObject());
	QJsonArray save();
private:
	QJsonObject structureView;
	QJsonObject data;
	QVBoxLayout * layout;
	QList<FeildUI*> feilds;
};

#endif // VIEWGROUP_H
