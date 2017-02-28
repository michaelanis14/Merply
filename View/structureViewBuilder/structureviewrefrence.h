#ifndef STRUCTUREVIEWREFRENCE_H
#define STRUCTUREVIEWREFRENCE_H


#include "erpcombobox.h"
#include "structureviewrefrencesubfield.h"

#include <QObject>
#include <QWidget>
#include <QFormLayout>
#include <QPushButton>

class StructureViewRefrence : public QWidget
{
	Q_OBJECT
public:
	explicit StructureViewRefrence(QWidget *parent = 0, QJsonObject strct = QJsonObject(), QStringList matchList = QStringList());
	QJsonObject save();
private:
	QFormLayout *layout;
	ERPComboBox* source;
	QJsonObject strct;
	QStringList matchList;
	QPushButton* getItemsbtn;
	QVector<StructureViewRefrenceSubField*>sVRList;
signals:

public slots:
	void gotSourceData(QVector<QJsonDocument> items);
	void getItemsbtnClicked(bool);
	void updateSelectData(QList<QString> fields);
};

#endif // STRUCTUREVIEWREFRENCE_H
