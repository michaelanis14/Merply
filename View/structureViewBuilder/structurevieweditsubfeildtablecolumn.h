#ifndef STRUCTUREVIEWEDITSUBFEILDTABLECOLUMN_H
#define STRUCTUREVIEWEDITSUBFEILDTABLECOLUMN_H

#include "feildui.h"

#include <QObject>
#include <QWidget>
#include <QFormLayout>

class StructureVieweditSubFeildTableColumn : public QWidget
{
	Q_OBJECT
public:
	explicit StructureVieweditSubFeildTableColumn(QWidget *parent = 0, QJsonObject clmn = QJsonObject());
	QJsonObject save();
private:
	QFormLayout *layout;
	ERPComboBox* type;
	QLineEdit* header;
	ERPComboBox* Source;
	ERPComboBox* Select;
	QLineEdit* defaultValue;
	QJsonObject clmn;
signals:
	void columnChanged();
public slots:
	void updateFields(QString value);
	void updateSelect(QString entity);

	void updateSelectData(QList<QString> fields);
};

#endif // STRUCTUREVIEWEDITSUBFEILDTABLECOLUMN_H
