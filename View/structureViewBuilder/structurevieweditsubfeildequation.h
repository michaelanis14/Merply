#ifndef STRUCTUREVIEWEDITSUBFEILDEQUATION_H
#define STRUCTUREVIEWEDITSUBFEILDEQUATION_H

#include <erpcombobox.h>

#include <QObject>
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>

class StructureVieweditSubFeildEquation : public QWidget
{
	Q_OBJECT
public:
	explicit StructureVieweditSubFeildEquation(QWidget *parent = 0, bool firstOperand = false);
	QJsonObject save();
	void fill(QJsonObject data);
private:
	QFormLayout *equationElementLayout;
	ERPComboBox* firstOperation;
	ERPComboBox* columnOne;
	ERPComboBox* conditionOnOne;
	ERPComboBox* conditionColumnOne;
	ERPComboBox* operation;
	ERPComboBox* secondTerm;
	ERPComboBox* columnTwo;
	ERPComboBox* conditionOnTwo;
	ERPComboBox* conditionColumnTwo;
	QLineEdit* numbers;
	bool firstOperand;
	QStringList ops ;
	QStringList conditions ;
signals:

public slots:
	void gotclmnsData(QList<QVector<QJsonDocument> > list);
	void gotFields(QStringList fields);
	void updateColmnTwo(int index);
	void updateConditionColmnOne(int index);
	void updateConditionColmnTwo(int index);
};

#endif // STRUCTUREVIEWEDITSUBFEILDEQUATION_H
