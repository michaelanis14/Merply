#ifndef STRUCTUREVIEWEDITSUBFEILDTABLECOLUMNEQUATION_H
#define STRUCTUREVIEWEDITSUBFEILDTABLECOLUMNEQUATION_H


#include <erpcombobox.h>



#include <QObject>
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>


class StructureVieweditSubFeildTableColumnEquation : public QWidget
{
	Q_OBJECT
public:
	explicit StructureVieweditSubFeildTableColumnEquation(QWidget *parent = 0, bool firstOperand = false);
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
	QJsonObject data;
signals:

public slots:
	void gotclmnsData(QList<QVector<QJsonDocument> > list);
	void updateColmnTwo(int index);
	void updateConditionColmnOne(int index);
	void updateConditionColmnTwo(int index);
};

#endif // STRUCTUREVIEWEDITSUBFEILDTABLECOLUMNEQUATION_H
