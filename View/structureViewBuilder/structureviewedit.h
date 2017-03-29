#ifndef STRUCTUREVIEWEDIT_H
#define STRUCTUREVIEWEDIT_H

#include "feildui.h"

#include "settingsctrlsui.h"
#include "structurevieweditsubfeild.h"
#include <hcontrollers.h>
#include <QObject>
#include <QWidget>
#include <QPainter>

class StructureViewEdit : public QWidget
{
	Q_OBJECT
public:
	//is it initialied with two quotations?
	explicit StructureViewEdit(QWidget *parent = 0, QJsonValue fieldVS = QJsonValue(), QStringList restrictedTypes = QStringList(), QString document_id = "");
	QJsonObject save();
	void showTypeFields();
	void hideTypeFields();
	SettingsCtrlsUI* topCntrlsPreview;
	QLineEdit* label;
	QCheckBox* hideLabel;
	QCheckBox* hideField;
	QCheckBox* initData;
	QCheckBox* indexField;
	QCheckBox* showInIdexView;
	QStringList getFieldsType();
	StructureVieweditSubFeild * getTableFeild();
private:
	QHBoxLayout *layout;
	//ERPComboBox* typeSelect;
	QWidget* labelWidget;
	FeildUI* previewField;
	QWidget* typeFields;
	QHBoxLayout *typeFieldsLayout;
	QList<StructureVieweditSubFeild *> sVSFs;
	QWidget* preview;
	QHBoxLayout *previewLayout;
	SettingsCtrlsUI* sctrlUI;
	QJsonObject structureView;
	void fill(QJsonObject structureView);
	void clearTypeFields();
	bool setHidden(bool hidden);
	SettingsCtrlsUI* topCntrls;
	QWidget* arrayWidget;
	QCheckBox* array;
signals:
	void changed();
protected:
	//void showEvent(QShowEvent *);
	void paintEvent(QPaintEvent*event);
	QStringList restrictedTypes;
	QString document_id;

public slots:
	void updatePreview(bool oldStrct = false);
	void controller_Clicked(QString btn);
	void addField();
	void removeField(QWidget* field);
};

#endif // STRUCTUREVIEWEDIT_H
