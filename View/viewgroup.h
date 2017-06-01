#ifndef VIEWGROUP_H
#define VIEWGROUP_H

#include <viewgroups.h>
#include <feildui.h>

#include <QObject>
#include <QWidget>
#include <QGroupBox>
class ViewGroup  : public QGroupBox
{
public:
	explicit ViewGroup(QWidget *parent = 0, QString strID = ""
			, QJsonObject structureView = QJsonObject(), QJsonObject data = QJsonObject(), QHash<QString, FeildUI*>* fieldsgroups =new  QHash<QString, FeildUI*>());
	void save(QPair<QString, QString>* insertQuery);

	QList<FeildUI*> feilds;
private:
	QJsonObject structureView;
	QVBoxLayout * layout;
	QString strID;

};

#endif // VIEWGROUP_H
