#ifndef STRUCTUREVIEWREFRENCESUBFIELD_H
#define STRUCTUREVIEWREFRENCESUBFIELD_H


#include "erpcombobox.h"


#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

class StructureViewRefrenceSubField : public QWidget
{
	Q_OBJECT
public:
	explicit StructureViewRefrenceSubField(QWidget *parent = 0, QJsonObject strct= QJsonObject(), QStringList fieldsName =QStringList());
	QJsonObject save();
private:
	QHBoxLayout *layout;
	QLabel* FieldNamelbl;
	ERPComboBox* combox;
signals:

public slots:
};

#endif // STRUCTUREVIEWREFRENCESUBFIELD_H
