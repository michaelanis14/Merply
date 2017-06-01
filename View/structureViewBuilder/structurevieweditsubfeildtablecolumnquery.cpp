#include "structurevieweditsubfeildtablecolumnquery.h"
#include "controller.h"

StructureVieweditSubFeildTableColumnQuery::StructureVieweditSubFeildTableColumnQuery(QWidget *parent) : QWidget(parent)
{
	//this->firstOperand = firstOperand;
	this->setContentsMargins(0,0,0,0);
	layout =  new QFormLayout(this);
	layout->setContentsMargins(0,0,5,0);
	layout->setSpacing(1);

	label = new QLineEdit;
	entity = new QLineEdit;
	beforeCondition = new QTextEdit;
	source = new ERPComboBox;
	select = new ERPComboBox;
	afterCondition = new QTextEdit;
	editabel = new QCheckBox;
	matchID = new QCheckBox;
	//QObject::connect(Controller::Get(),SIGNAL(gotSelectListData(QVector<QSqlRecord>)),this,SLOT(gotSourceData(QVector<QJsonDocument>)));

	gotSourceData();
	//Controller::Get()->getSelectList("ViewStructure","Title","`"+QString(DATABASE).append("`.Type =\"Entity\""));



	//if(firstOperand){
	//		firstOperation = new ERPComboBox;
	//		layout->addRow(tr("First OP"),firstOperation);
	//		}
	layout->addRow(tr("Label"),label);
	layout->addRow(tr("Entity"),entity);
	layout->addRow(tr("Before Filter"),beforeCondition);
	layout->addRow(tr("Source"),source);
	layout->addRow(tr("Select"),select);
	layout->addRow(tr("Editabel"),editabel);
	layout->addRow(tr("matchID"),matchID);
	layout->addRow(tr("After Filter"),afterCondition);
}

void StructureVieweditSubFeildTableColumnQuery::fill(QJsonObject strct)
{
	this->strct = strct;
	//if(strct.value("FirstOP") != QJsonValue::Undefined)
	//	firstOperation->setCurrentText(strct.value("FirstOP").toString());
	if(strct.value("Label") != QJsonValue::Undefined)
		label->setText(strct.value("Label").toString());
	else label->setText("Search");
	if(strct.value("BeforFilter") != QJsonValue::Undefined)
		beforeCondition->setText(strct.value("BeforFilter").toString());
	if(strct.value("Entity") != QJsonValue::Undefined)
		entity->setText(strct.value("Entity").toString());
	if(strct.value("Source") != QJsonValue::Undefined){
		QString sour = strct.value("Source").toString().split("::").count() > 1 ?strct.value("Source").toString().split("::")[1]:strct.value("Source").toString();
qDebug() << __FILE__ << __LINE__<< __func__ <<"DATABASE ERR";
		//		source->setCurrentIndex(source->keys.indexOf(QString("ViewStructure::"+sour)));
		}
	if(strct.value("Select") != QJsonValue::Undefined)
		select->setCurrentText(strct.value("Select").toString());
	if(strct.value("Editabel") != QJsonValue::Undefined)
		editabel->setChecked(true);
	if(strct.value("matchID") != QJsonValue::Undefined)
		matchID->setChecked(true);
	if(strct.value("AfterFilter")!= QJsonValue::Undefined)
		afterCondition->setText(strct.value("AfterFilter").toString());
}

QJsonObject StructureVieweditSubFeildTableColumnQuery::save()
{
	QJsonObject save;
	save.insert("Label",label->text());
	if(!entity->text().isEmpty())
		save.insert("Entity",entity->text());
	if(!beforeCondition->toPlainText().trimmed().isEmpty())
		save.insert("BeforFilter",beforeCondition->toPlainText().trimmed());
	save.insert("Source",source->getKey());
	save.insert("Select",select->currentText());
	if(editabel->isChecked())
		save.insert("Editabel",editabel->isChecked());
	if(matchID->isChecked())
		save.insert("matchID",matchID->isChecked());
	if(!afterCondition->toPlainText().trimmed().isEmpty())
		save.insert("AfterFilter",afterCondition->toPlainText().trimmed());

	return save;
}

void StructureVieweditSubFeildTableColumnQuery::updateSelect(QString)
{
//	QObject::disconnect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateSelectData(QList<QString>)));
//	QObject::connect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateSelectData(QList<QString>)));

	updateSelectData(Controller::Get()->getCachedViewStructureSubFields(source->currentText().toInt()).keys());
	//Controller::Get()->getFields(source->getKey());
}

void StructureVieweditSubFeildTableColumnQuery::updateSelectData(QList<int> fields)
{
	//QObject::disconnect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateSelectData(QList<QString>)));
	select->clear();
	select->addItem("ALL");
	//select->addItem("ID");
	foreach(int i, fields){
		select->addItem(QString::number(i));
		}
	if(strct.value("Select") != QJsonValue::Undefined){
		select->setCurrentIndex(select->getItemsText().indexOf(strct.value("Select").toString()));
		//	qDebug() << __FILE__ << __LINE__  << "select" << strct.value("select").toString() << fields << select->getItemsText() << select->getItemsText().indexOf(strct.value("select").toString()) << select->currentIndex();
		//	select->currentIndexChanged(select->currentIndex());
		}
}

void StructureVieweditSubFeildTableColumnQuery::gotSourceData()
{
	//qDebug() << __FILE__ << __LINE__<< "gotsourceData" << items;
//	QObject::disconnect(Controller::Get(),SIGNAL(gotSelectListData(QVector<QSqlRecord>)),this,SLOT(gotSourceData(QVector<QJsonDocument>)));
	source->clear();

	source->addItems(Controller::Get()->getCachedViewStructureNames());

	QObject::disconnect(source,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateSelect(QString)));
	QObject::connect(source,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateSelect(QString)));

	if(strct.value("source") != QJsonValue::Undefined){
		QString sour = strct.value("source").toString().split("::").count() > 1 ?strct.value("Source").toString().split("::")[1]:strct.value("Source").toString();
qDebug() << __FILE__ << __LINE__<< __func__ <<"DATABASE ERR";
		//		source->setCurrentIndex(source->keys.indexOf(QString("ViewStructure::"+sour)));
		//	source->currentIndexChanged(source->currentIndex());
		}
}
