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
	ERPComboBox* operation;
	ERPComboBox* secondTerm;
	ERPComboBox* columnTwo;
	QLineEdit* numbers;
	bool firstOperand;
	QStringList ops ;
signals:

public slots:
	void gotclmnsData(QList<QJsonDocument> list);
	void updateColmnTwo(int index);
};

#endif // STRUCTUREVIEWEDITSUBFEILDTABLECOLUMNEQUATION_H
