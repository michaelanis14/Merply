#ifndef STRUCTUREVIEWEDITSUBFEILD_H
#define STRUCTUREVIEWEDITSUBFEILD_H

#include "subfeildui.h"

#include "structurevieweditsubfeildtable.h"

#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QFormLayout>
#include <QDateEdit>


class StructureVieweditSubFeild : public QWidget
{
	Q_OBJECT
public:
	explicit StructureVieweditSubFeild(QWidget *parent = 0);
	void fillTypeFields(QString type, QJsonValue fieldVS, QStringList restrictedTypes);
	QJsonObject save();
	QFormLayout *layout;
	QString getType();
private:
	StructureVieweditSubFeildTable* tableEdit;
	ERPComboBox* Source;
	ERPComboBox* Select;
	QCheckBox* Editable;
	QLineEdit* defaultValue;
	QLineEdit* title;
	QDateEdit *date;
	QString type;
	QJsonValue fieldVS;
	bool filled;
	QWidget* preview;
	QHBoxLayout* previewLayout;
	QStringList restrictedTypes;
	QCheckBox* mandatory;
	void initFilterWidget();
	QWidget*filterWidget;
	ERPComboBox* filterOn;
	QFormLayout* filterWidgetLayout;
	ERPComboBox* typeSelect;
	QWidget*localFilterWidget;
	ERPComboBox* localFilter;
	ERPComboBox* entityFilter;
	QFormLayout* localFilterWidgetLayout;
	void paintEvent(QPaintEvent *event);
signals:
	void changed();

public slots:
	void updateFields(QString type);
	void updateSelect(QString);
	void updateSelectData(QList<QString> fields);
	void gotSourceData(QList<QJsonDocument> items);
	void filterOnChanged(int index);
	void fillLocalFilter(QStringList feilds);
};

#endif // STRUCTUREVIEWEDITSUBFEILD_H
