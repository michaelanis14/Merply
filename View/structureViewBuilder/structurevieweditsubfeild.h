#ifndef STRUCTUREVIEWEDITSUBFEILD_H
#define STRUCTUREVIEWEDITSUBFEILD_H

#include "subfeildui.h"

#include "structurevieweditsubfeildtable.h"

#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QFormLayout>


class StructureVieweditSubFeild : public QWidget
{
	Q_OBJECT
public:
	explicit StructureVieweditSubFeild(QWidget *parent = 0);
	void fillTypeFields(QString type, QJsonValue fieldVS, bool links);
	QJsonObject save();
	QFormLayout *layout;
private:
	StructureVieweditSubFeildTable* tableEdit;
	ERPComboBox* Source;
	ERPComboBox* Select;
	QCheckBox* Editable;
	QLineEdit* defaultValue;
	QLineEdit* title;
	QString type;
	QJsonValue fieldVS;
	bool filled;
	QWidget* preview;
	QHBoxLayout* previewLayout;
	bool links;
	void paintEvent(QPaintEvent *event);
signals:
	void changed();

public slots:
	void updateFields(QString type);
	void updateSelect(QString title);
	void updateSelectData(QList<QString> fields);
	void gotSourceData(QList<QJsonDocument> items);
};

#endif // STRUCTUREVIEWEDITSUBFEILD_H
