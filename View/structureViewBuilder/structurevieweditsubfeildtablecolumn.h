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
	ERPComboBox* getSource() const;
	void fill(QJsonObject clmn);
private:
	QFormLayout *layout;
	ERPComboBox* type;
	QLineEdit* header;
	ERPComboBox* Source;
	ERPComboBox* Select;
	QLineEdit* defaultValue;
	QJsonObject clmn;

	void initFilterWidget();
	QWidget*filterWidget;
	ERPComboBox* filterOn;
	QFormLayout* filterWidgetLayout;

	QWidget*localFilterWidget;
	ERPComboBox* localFilter;
	ERPComboBox* entityFilter;
	QFormLayout* localFilterWidgetLayout;
	QStringList typsList;


signals:
	void columnChanged();
public slots:
	void updateFields(int value);
	void updateSelect(QString);
	void updateSelectData(QList<QString> fields);
	void selectData(QList<QJsonDocument> items);
	void filterOnChanged(int index);
	void fillLocalFilter(QList<QJsonDocument> feilds);
	void localFilterChanged(int);
	void updatelocalFilterData(QList<QString> fields);
};

#endif // STRUCTUREVIEWEDITSUBFEILDTABLECOLUMN_H
