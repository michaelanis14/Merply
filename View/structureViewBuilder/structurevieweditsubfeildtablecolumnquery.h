#ifndef STRUCTUREVIEWEDITSUBFEILDTABLECOLUMNQUERY_H
#define STRUCTUREVIEWEDITSUBFEILDTABLECOLUMNQUERY_H

#include <erpcombobox.h>

#include <QObject>
#include <QWidget>
#include <QFormLayout>
#include <QTextEdit>
#include <QCheckBox>

class StructureVieweditSubFeildTableColumnQuery : public QWidget
{
	Q_OBJECT
public:
	explicit StructureVieweditSubFeildTableColumnQuery(QWidget *parent = 0);
	void fill(QJsonObject strct);
	QJsonObject save();
private:
	QFormLayout *layout;
	//ERPComboBox* firstOperation;
	QLineEdit* label;
	QLineEdit* entity;
	QTextEdit* beforeCondition;
	ERPComboBox* source;
	ERPComboBox* select;
	QTextEdit* afterCondition;
	QCheckBox* editabel;
	QCheckBox* matchID;
	QJsonObject strct;
	//bool firstOperand;
signals:

public slots:
	void updateSelect(QString);
	void updateSelectData(QList<QString> fields);
	void gotSourceData(QVector<QJsonDocument> items);
};

#endif // STRUCTUREVIEWEDITSUBFEILDTABLECOLUMNQUERY_H
