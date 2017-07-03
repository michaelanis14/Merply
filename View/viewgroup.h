#ifndef VIEWGROUP_H
#define VIEWGROUP_H

#include <viewgroups.h>
#include <feildui.h>

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QDataWidgetMapper>
class ViewGroup  : public QGroupBox
{
public:
	explicit ViewGroup(QWidget *parent = 0, QString strID = ""
			, QJsonObject structureView = QJsonObject(), QHash<QString, FeildUI*>* fieldsgroups =new  QHash<QString, FeildUI*>(),QDataWidgetMapper *mapper = new QDataWidgetMapper());
	void save(QPair<QString, QString>* insertQuery, bool newDocument);

	QList<FeildUI*> feilds;
private:
	QJsonObject structureView;
	QVBoxLayout * layout;
	QString strID;

};

#endif // VIEWGROUP_H
