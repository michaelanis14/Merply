#include "structurevieweditsubfeildequation.h"
#include"structureviewgroupsui.h"

StructureVieweditSubFeildEquation::StructureVieweditSubFeildEquation(QWidget *parent,bool firstOperand) : QWidget(parent)
{
	this->firstOperand  = firstOperand;
	this->setContentsMargins(0,0,0,0);
	this->setAutoFillBackground(true);
	this->setObjectName("equationElementWidget");
	equationElementLayout = new QFormLayout(this);
	this->setLayout(equationElementLayout);
	equationElementLayout->setFormAlignment(Qt::AlignLeft);
	equationElementLayout->setLabelAlignment(Qt::AlignLeft);
	equationElementLayout->setSpacing(0);
	equationElementLayout->setMargin(0);


	ops<<"+"<<"-"<<"*"<<"/";
	conditions <<"No Condition"<<">"<<"<";
	if(firstOperand){
		firstOperation = new ERPComboBox(0);
		firstOperation->addItems(ops);
		equationElementLayout->addRow((tr("Operation")), firstOperation);
		}
	columnOne = new ERPComboBox(0);
	equationElementLayout->addRow((tr("First Term")), columnOne);

	conditionOnOne = new ERPComboBox(0);
	conditionOnOne->addItems(conditions);
	equationElementLayout->addRow((tr("Condition")), conditionOnOne);

	conditionColumnOne = new ERPComboBox(0);
	conditionColumnOne->setHidden(true);
	equationElementLayout->addRow((tr("Condition Column")), conditionColumnOne);
	QObject::connect(conditionOnOne,SIGNAL(currentIndexChanged(int)),this,SLOT(updateConditionColmnOne(int)));


	operation = new ERPComboBox(0);
	operation->addItems(ops);
	equationElementLayout->addRow((tr("Operation")), operation);

	secondTerm = new ERPComboBox(0);
	QStringList secondTermList ;
	secondTermList<<tr("Column")<<tr("Number");

	equationElementLayout->addRow((tr("Second Term Type")), secondTerm);
	QObject::connect(secondTerm,SIGNAL(currentIndexChanged(int)),this,SLOT(updateColmnTwo(int)));


	columnTwo = new ERPComboBox(0);
	equationElementLayout->addRow((tr("Second Term")), columnTwo);

	conditionOnTwo = new ERPComboBox(0);
	conditionOnTwo->addItems(conditions);
	equationElementLayout->addRow((tr("Condition")), conditionOnTwo);

	conditionColumnTwo = new ERPComboBox(0);
	conditionColumnTwo->setHidden(true);
	equationElementLayout->addRow((tr("Condition Column")), conditionColumnTwo);
	QObject::connect(conditionOnTwo,SIGNAL(currentIndexChanged(int)),this,SLOT(updateConditionColmnTwo(int)));

	numbers  = new QLineEdit;
	equationElementLayout->addRow((tr("Number")), numbers);


	QObject::connect(StructureViewGroupsUI::GetUI(),SIGNAL(gotFieldsNames(QStringList)),this,SLOT(gotFields(QStringList)));
	StructureViewGroupsUI::GetUI()->getFeildsNames();
	secondTerm->addItems(secondTermList);
}

QJsonObject StructureVieweditSubFeildEquation::save()
{
	QJsonObject save;
	if(firstOperand)
		save.insert("FirstOperation",firstOperation->currentIndex());
	save.insert("FirstColumn",columnOne->currentText());
	save.insert("Operation",operation->currentIndex());
	if(secondTerm->currentIndex() == 0){
		save.insert("SecondColmn",columnTwo->currentText());
		}
	else {
		save.insert("Number",numbers->text());
		}
	if(conditionOnOne->currentIndex() !=0){
		save.insert("ConditionOnOne",conditionOnOne->currentText());
		save.insert("ConditionColumnOne",conditionColumnOne->currentText());
		}
	if(conditionOnTwo->currentIndex() !=0){
		save.insert("ConditionOnTwo",conditionOnTwo->currentText());
		save.insert("ConditionColumnTwo",conditionColumnTwo->currentText());
		}

	qDebug() << save;
	return save;
}

void StructureVieweditSubFeildEquation::fill(QJsonObject data)
{
//	qDebug() << data;
	//if(data.value("SecondColmn") != QJsonValue::Undefined){
	if(firstOperand)
		firstOperation->setCurrentIndex(data.value("FirstOperation").toInt());
	if(data.value("FirstColumn") != QJsonValue::Undefined)
		columnOne->setCurrentText(data.value("FirstColumn").toString());
	if(data.value("Operation") != QJsonValue::Undefined)
		operation->setCurrentIndex(data.value("Operation").toInt());
	if(data.value("SecondColmn") != QJsonValue::Undefined){
		secondTerm->setCurrentIndex(0);
		//qDebug() << data.value("SecondColmn").toString();
		columnTwo->setCurrentText(data.value("SecondColmn").toString());
		}
	else {
		secondTerm->setCurrentIndex(1);
		if(data.value("Number") != QJsonValue::Undefined)
			numbers->setText(data.value("Number").toString().trimmed());
		}
	if(data.value("ConditionColumnOne") != QJsonValue::Undefined){
		conditionOnOne->setCurrentText(data.value("ConditionOnOne").toString());
		conditionColumnOne->setCurrentText(data.value("ConditionColumnOne").toString());
		}
	if(data.value("ConditionColumnTwo") != QJsonValue::Undefined){
		conditionOnTwo->setCurrentText(data.value("ConditionOnTwo").toString());
		conditionColumnTwo->setCurrentText(data.value("ConditionColumnTwo").toString());
		}
}

void StructureVieweditSubFeildEquation::gotclmnsData(QList<QList<QJsonDocument> > list)
{
	QString oldClmnOneIndex = columnOne->currentText();
	QString oldClmnTwoIndex = columnTwo->currentText();

	columnOne->clear();
	columnTwo->clear();
	foreach(QList<QJsonDocument> table,list){
	int i = 0;
	foreach (QJsonDocument doc, table) {
		QString item = QString(tr("Column:")).append(QString::number(i)).append(" ").append(doc.object().value("clmnHeader").toString());
		columnOne->addItem(item);
		columnTwo->addItem(item);
		conditionColumnOne->addItem(item);
		conditionColumnTwo->addItem(item);
		i++;
		}
		}
	columnOne->setCurrentText(oldClmnOneIndex);
	columnTwo->setCurrentText(oldClmnTwoIndex);
}

void StructureVieweditSubFeildEquation::gotFields(QStringList fields)
{
	QString oldClmnOneIndex = columnOne->currentText();
	QString oldClmnTwoIndex = columnTwo->currentText();
	columnOne->clear();
	columnTwo->clear();

	columnOne->addItems(fields);
	columnTwo->addItems(fields);
	conditionColumnOne->addItems(fields);
	conditionColumnTwo->addItems(fields);

	columnOne->setCurrentText(oldClmnOneIndex);
	columnTwo->setCurrentText(oldClmnTwoIndex);
}

void StructureVieweditSubFeildEquation::updateColmnTwo(int index)
{
	if(index == 0){
		numbers->setHidden(true);
		equationElementLayout->labelForField(numbers)->setHidden(true);
		columnTwo->setHidden(false);
		equationElementLayout->labelForField(columnTwo)->setHidden(false);
		conditionOnTwo->setHidden(false);
		equationElementLayout->labelForField(conditionOnTwo)->setHidden(false);
		}
	else{
		numbers->setHidden(false);
		equationElementLayout->labelForField(numbers)->setHidden(false);
		columnTwo->setHidden(true);
		equationElementLayout->labelForField(columnTwo)->setHidden(true);
		conditionOnTwo->setHidden(true);
		equationElementLayout->labelForField(conditionOnTwo)->setHidden(true);
		}
}

void StructureVieweditSubFeildEquation::updateConditionColmnOne(int index)
{
	if(index == 0){
		conditionColumnOne->setHidden(true);
		equationElementLayout->labelForField(conditionColumnOne)->setHidden(true);
		}
	else{
		conditionColumnOne->setHidden(false);
		equationElementLayout->labelForField(conditionColumnOne)->setHidden(false);
		}
}

void StructureVieweditSubFeildEquation::updateConditionColmnTwo(int index)
{
	if(index == 0){
		conditionColumnTwo->setHidden(true);
		equationElementLayout->labelForField(conditionColumnTwo)->setHidden(true);
		}
	else {
		conditionColumnTwo->setHidden(false);
		equationElementLayout->labelForField(conditionColumnTwo)->setHidden(false);
		}
}
