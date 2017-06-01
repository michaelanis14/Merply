#ifndef STRUCTUREVIEWEDITSUBFEILD_H
#define STRUCTUREVIEWEDITSUBFEILD_H

#include "subfeildui.h"

#include "structurevieweditsubfeildtable.h"
#include "structurevieweditsubfeildequation.h"


#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QFormLayout>
#include <QDateEdit>
#include <QTextEdit>


class StructureVieweditSubFeild : public QWidget
{
	Q_OBJECT
public:
	explicit StructureVieweditSubFeild(QWidget *parent = 0);
	void fillTypeFields(QString type, QJsonValue fieldVS, QStringList restrictedTypes);
	QJsonObject save();
	QFormLayout *layout;
	QString getType();
	StructureVieweditSubFeildTable* getTableEdit() const;

private:
	StructureVieweditSubFeildTable* tableEdit;
	ERPComboBox* Source;
	ERPComboBox* Select;
	QTextEdit* condition;
	QCheckBox* Editable;
	QLineEdit* defaultValue;
	QLineEdit* charCount;
	ERPComboBox* inputDataType;
	bool loadData;
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
	bool filledLocalfilter;
	QFormLayout* localFilterWidgetLayout;
	QTextEdit* textEdit;
	void initEquationWidget();
	QWidget*equationWidget;
	QFormLayout* equationWidgetLayout;
	QList<StructureVieweditSubFeildEquation*> equationElements;
	void paintEvent(QPaintEvent *event);
	QLineEdit* clmnNumber;
signals:
	void changed();

public slots:
	void updateFields(QString type);
	void updateSelect(QString);
	void updateSelectData(QList<int> fields);
	void setSourceData();
	void filterOnChanged(int index);
	void fillLocalFilter(QStringList feilds);

	void addEquationWidget(QJsonObject data = QJsonObject());
	void removeEqElement(QWidget* eqElement);
};

#endif // STRUCTUREVIEWEDITSUBFEILD_H
