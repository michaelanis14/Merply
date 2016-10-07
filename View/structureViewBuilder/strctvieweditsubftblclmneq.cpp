#include "strctvieweditsubftblclmneq.h"
#include"structureviewgroupsui.h"

StructureVieweditSubFeildTableColumnEquation::StructureVieweditSubFeildTableColumnEquation(QWidget *parent,bool firstOperand) : QWidget(parent)
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
	if(firstOperand){
		firstOperation = new ERPComboBox(0);
		firstOperation->addItems(ops);
		equationElementLayout->addRow((tr("Operation")), firstOperation);
		}
	columnOne = new ERPComboBox(0);
	equationElementLayout->addRow((tr("First Term")), columnOne);

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

	numbers  = new QLineEdit;
	equationElementLayout->addRow((tr("Number")), numbers);


	QObject::connect(StructureViewGroupsUI::GetUI(),SIGNAL(gotSourcesJson(QList<QJsonDocument>)),this,SLOT(gotclmnsData(QList<QJsonDocument>)));
	StructureViewGroupsUI::GetUI()->getTableFields(new ERPComboBox);
	secondTerm->addItems(secondTermList);
}

QJsonObject StructureVieweditSubFeildTableColumnEquation::save()
{
	QJsonObject save;
	if(firstOperand)
		save.insert("FirstOperation",firstOperation->currentIndex());
	save.insert("FirstColumn",columnOne->currentIndex());
	save.insert("Operation",operation->currentIndex());
	if(secondTerm->currentIndex() == 0){
		save.insert("SecondColmn",columnTwo->currentIndex());
		}
	else {
		save.insert("Number",numbers->text());
		}


	return save;
}

void StructureVieweditSubFeildTableColumnEquation::fill(QJsonObject data)
{
	//qDebug() << data;
	//if(data.value("SecondColmn") != QJsonValue::Undefined){
	if(firstOperand)
		firstOperation->setCurrentIndex(data.value("FirstOperation").toInt());
	if(data.value("FirstColumn") != QJsonValue::Undefined)
		columnOne->setCurrentIndex(data.value("FirstColumn").toInt());
	if(data.value("Operation") != QJsonValue::Undefined)
		operation->setCurrentIndex(data.value("Operation").toInt());
	if(data.value("SecondColmn") != QJsonValue::Undefined){
		secondTerm->setCurrentIndex(0);
		//qDebug() << data.value("SecondColmn").toInt();
		columnTwo->setCurrentIndex(data.value("SecondColmn").toInt());
		}
	else {
		secondTerm->setCurrentIndex(1);
		if(data.value("Number") != QJsonValue::Undefined)
			numbers->setText(data.value("Number").toString().trimmed());
		}
}

void StructureVieweditSubFeildTableColumnEquation::gotclmnsData(QList<QJsonDocument> list)
{
	int oldClmnOneIndex = columnOne->currentIndex();
	int oldClmnTwoIndex = columnTwo->currentIndex();
	columnOne->clear();
	columnTwo->clear();
	int i = 0;
	foreach (QJsonDocument doc, list) {
		QString item = QString(tr("Column:")).append(QString::number(i)).append(" ").append(doc.object().value("clmnHeader").toString());
		columnOne->addItem(item);
		columnTwo->addItem(item);
		i++;
		}
	columnOne->setCurrentIndex(oldClmnOneIndex);
	columnTwo->setCurrentIndex(oldClmnTwoIndex);
}

void StructureVieweditSubFeildTableColumnEquation::updateColmnTwo(int index)
{
	if(index == 0){
		numbers->setHidden(true);
		equationElementLayout->labelForField(numbers)->setHidden(true);
		columnTwo->setHidden(false);
		equationElementLayout->labelForField(columnTwo)->setHidden(false);

		}
	else{
		numbers->setHidden(false);
		equationElementLayout->labelForField(numbers)->setHidden(false);
		columnTwo->setHidden(true);
		equationElementLayout->labelForField(columnTwo)->setHidden(true);
		}
}
