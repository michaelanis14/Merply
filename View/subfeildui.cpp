#include "subfeildui.h"
#include "controller.h"

#include<QDateTimeEdit>
#include <cmath>
#include <cstdlib>


SubFieldUI::SubFieldUI(QWidget *parent,QString strID, QJsonObject structureView, QJsonValue data) : QWidget(parent)
{

	this->structureView = QJsonObject();
	this->structureView = structureView;
	layout = new QHBoxLayout(this);
	this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setMargin(0);
	this->strID = strID;
	this->combox = 0;
	QString type = structureView.value("Type").toString();

	searchShortCut = new QShortcut(QKeySequence(Qt::Key_F8), this, SLOT(btnSearch_Clicked()));
	this->searchShortCut->setEnabled(true);

	if(type.compare("Refrence") == 0){
		combox = new ERPComboBox(this,false);
		if(structureView.value("Editable").toString().compare("false") == 0)
			combox->setEditable(false);

		sctrlUI = new SettingsCtrlsUI();
		sctrlUI->addbtn("Search",":/resources/icons/search.png","search");
		QObject::connect(sctrlUI, SIGNAL(btnClicked(QString)),this, SLOT(btnSearch_Clicked()));
		layout->addWidget(combox);
		layout->addWidget(sctrlUI);
		field = combox;

		if(structureView.value("LocalFilter") != QJsonValue::Undefined && structureView.value("LocalFilter").toBool()){
			qDebug() << __FILE__ << __LINE__  << Controller::Get()->getFirstSubField(structureView.value("Local").toString());
			SubFieldUI* localFilter = Controller::Get()->getFirstSubField(structureView.value("Local").toString());
			if(localFilter->combox){
				qDebug() << __FILE__ << __LINE__  << "COMBO";
				QObject::connect(localFilter->combox,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateFilter(QString)));
				this->updateFilter(localFilter->combox->currentText());
				//emit localFilter->combox->currentIndexChanged(localFilter->combox->currentIndex());
				}
			else{
				qDebug() << __FILE__ << __LINE__  <<"Not Init" << structureView.value("Local").toString() << structureView;
				}
			}
		else{
			if(!structureView.value("Source").toString().isEmpty() && structureView.value("Source").toString().compare("_") != 0){
				QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QVector<QJsonDocument>)),this,SLOT(refrenceData(QVector<QJsonDocument>)));
				Controller::Get()->getJsonEntityFieldsList(structureView.value("Source").toString(),structureView.value("Select").toString(),structureView.value("Condition").toString());
				//qDebug() << __FILE__ << __LINE__  << "currentText"<<structureView.value("Source").toString()<<structureView.value("Select").toString()<<structureView.value("Condition").toString();
				}
			}
		QJsonObject dataObj = data.toObject();
		if(!dataObj.isEmpty()){
			combox->setCurrentIndex(combox->findText(dataObj.value("Value").toString()));
			}
		}
	else if(type.compare("Text") == 0){

		QLineEdit* lineEdit = new QLineEdit();
		lineEdit->setContentsMargins(0,0,0,0);
		if(structureView.value("Default") != QJsonValue::Undefined){
			lineEdit->setText(structureView.value("Default").toString());
			}
		lineEdit->setText(Controller::Get()->toString("",data));
		if(structureView.value("CharCount") != QJsonValue::Undefined && structureView.value("CharCount").toInt() > 0)
			lineEdit->setMaxLength(structureView.value("CharCount").toInt());
		if(structureView.value("InputDataType").toString().compare("IntToMillion") == 0)
			lineEdit->setValidator( new QIntValidator(0, 1000000, this) );
		else if(structureView.value("InputDataType").toString().compare("DoubleToMillion")== 0)
			lineEdit->setValidator( new QDoubleValidator(0, 1000000,2, this) );
		layout->addWidget(lineEdit);
		field = lineEdit;
		}
	else if(type.compare("TextArea") == 0){

		QTextEdit* lineEdit = new QTextEdit();
		lineEdit->setContentsMargins(0,0,0,0);
		if(structureView.value("Default") != QJsonValue::Undefined){
			lineEdit->setText(structureView.value("Default").toString());
			}
		lineEdit->setText(data.toString());
		layout->addWidget(lineEdit);
		field = lineEdit;
		}
	else if(type.compare("Fixed") == 0){
		QLineEdit* lineEdit = new QLineEdit();
		lineEdit->setContentsMargins(0,0,0,0);
		if(structureView.value("Default") != QJsonValue::Undefined){
			lineEdit->setText(structureView.value("Default").toString());
			}
		lineEdit->setEnabled(false);
		lineEdit->setStyleSheet("QLineEdit{background: white; color:black; border:0;}");

		layout->addWidget(lineEdit);
		field = lineEdit;
		}
	else if(type.compare("Index") == 0){
		combox = new ERPComboBox(0,true);
		combox->setEditable(true);
		QObject::connect(combox,SIGNAL(indexedFillEvent(QString)),this,SLOT(indexedFillEvent(QString)));
		layout->addWidget(combox);
		field = combox;

		QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QVector<QJsonDocument>)),this,SLOT(refrenceData(QVector<QJsonDocument>)));
		Controller::Get()->getJsonList(structureView.value("Source").toString(),structureView.value("Select").toString());
		QString dataString = data.toString();
		if(!dataString.isEmpty()){
			combox->setCurrentIndex(combox->findText(dataString));
			}
		}
	else if(type.compare("Table") == 0){
		table = new merplyTabelView(this,true,false);
		//	qDebug() << __FILE__ << __LINE__ <<"Table" << data.toObject() << structureView;
		//Controller::Get()->getReportTableData(structureView);
		QJsonObject firstclmn = structureView.value("Columns").toArray().first().toObject();
		if(firstclmn.value("SourceLocalFilter") != QJsonValue::Undefined &&firstclmn.value("LocalSource").toBool()){
			//	qDebug() << __FILE__ << __LINE__  << "local Field"<< firstclmn.value("SourceLocalFilter").toString();
			//	qDebug() << __FILE__ << __LINE__  << Controller::Get()->getFirstSubField(firstclmn.value("SourceLocalFilter").toString());
			SubFieldUI* localFilter = Controller::Get()->getFirstSubField(firstclmn.value("SourceLocalFilter").toString());
			localFilterCombobox = localFilter->combox;
			if(localFilterCombobox){
				//	qDebug() << __FILE__ << __LINE__  << "COMBO" << localFilter->combox->currentText();
				QObject::connect(localFilter->combox,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateTable(QString)));
				this->updateTable(localFilter->combox->currentText());
				//emit localFilter->combox->currentIndexChanged(localFilter->combox->currentIndex());
				}
			else{
				qDebug() << __FILE__ << __LINE__  <<"Not Init ComboFilter for table init";
				}
			}
		else {
			table->fill(structureView);
			}


		QJsonObject dataObj = data.toObject();
		if(!dataObj.isEmpty()){
			table->fillText(dataObj);
			}
		else if(structureView.value("initData") != QJsonValue::Undefined){
			table->fillText(structureView.value("initData").toObject());
			}


		else if(structureView.value("Query") == QJsonValue::Undefined){
			table->fillText(QJsonObject());
			}
		layout->addWidget(table);
		field = table;
		}
	else if(type.compare("Link") == 0){
		QPushButton* btn  = new QPushButton(structureView.value("Title").toString(),this);
		QObject::connect(btn,SIGNAL(pressed()),this,SLOT(linkPressed()));
		layout->addWidget(btn);
		field = btn;
		}
	else if(type.compare("Serial") == 0){
		QLineEdit* lineEdit = new QLineEdit();
		field = lineEdit;
		lineEdit->setContentsMargins(0,0,0,0);
		//lineEdit->setEnabled(false);

		QString dataString = Controller::Get()->toString("",data);
		if(!dataString.isEmpty()){
			lineEdit->setText(dataString);
			}
		///TODO: INCREMENT BASED ON YEAR !!!!
		else{
			if(structureView.value("startNum") != QJsonValue::Undefined){
				lineEdit->setText(QString::number(structureView.value("startNum").toInt()));
				}
			QStringList id = this->strID.split("ViewStructure::");
			if(id.count() > 1){
				QObject::connect(Controller::Get(),SIGNAL(gotValue(QString)),this,SLOT(serialData(QString)));
				Controller::Get()->getValue(id[1]);
				}
			}
		layout->addWidget(lineEdit);

		}
	else if(type.compare("Date") == 0){
		QDateTimeEdit *date = new QDateTimeEdit(this);

		//qDebug() << data.toString();
		if(data.toString().isEmpty())
			date->setDateTime(QDateTime::currentDateTime());
		//else date->setDateTime(QDateTime::fromString(data.toString(),Qt::DefaultLocaleShortDate));
		else date->setDateTime(QDateTime::fromString(data.toString(),Qt::ISODate));


		//qDebug() << QDateTime::fromMSecsSinceEpoch(data.toString().toDouble());
		date->setDisplayFormat("dd/MM/yyyy");
		layout->addWidget(date);
		field = date;
		}
	else if(type.compare("Equation") == 0){
		QLineEdit* lineEdit = new QLineEdit();
		field = lineEdit;
		lineEdit->setContentsMargins(0,0,0,0);
		lineEdit->setEnabled(false);
		updateEquationField();
		layout->addWidget(lineEdit);

		//QString dataString = data.toString();
		//if(!dataString.isEmpty()){
		//	lineEdit->setText(dataString);
		//	}

		}
	else field  = new QWidget();
}

void SubFieldUI::clear()
{

}

QJsonValue SubFieldUI::save()
{
	QJsonValue save = QJsonValue::Null;
	if(QString(field->metaObject()->className()).compare("ERPComboBox") == 0 ){
		//	save += component.name;
		QString value = ((QComboBox*)field)->currentText();
		if(!value.trimmed().isEmpty()){
			QJsonObject comboFields;
			comboFields.insert("Value", ((QComboBox*)field)->currentText());
			comboFields.insert("Key", ((ERPComboBox*)field)->getKey());
			save = comboFields;
			}
		else save = QJsonValue::Null;
		//save +=" ";
		}
	else if(QString(field->metaObject()->className()).compare("QLineEdit") == 0 ){
		//	save += component.name;
		if(!((QLineEdit*)field)->text().trimmed().isEmpty()){
			bool tonum = false ;
			int number = ((QLineEdit*)field)->text().trimmed().toInt(&tonum);
			if(tonum)
				save = number;
			else save =((QLineEdit*)field)->text().trimmed();

			}
		else save = QJsonValue::Null;
		//	save =" ";
		}
	else if(QString(field->metaObject()->className()).compare("QTextEdit") == 0 ){
		if(!((QTextEdit*)field)->toPlainText().trimmed().isEmpty())
			save =((QTextEdit*)field)->toPlainText();
		else save = QJsonValue::Null;
		}
	else if(QString(field->metaObject()->className()).compare("QCheckBox") == 0 ){
		//	save = component.name;
		save =((QCheckBox*)field)->isChecked();
		//	save =" ";
		}
	else if(QString(field->metaObject()->className()).compare("merplyTabelView") == 0){
		//	save = component.name;
		//		save =((merplyTabelView*)field)->save("this->key");
		QJsonObject tblSave = ((merplyTabelView*)field)->save();
		if(!tblSave.isEmpty())
			save = tblSave;
		else save = QJsonValue::Null;
		//	save =" ";
		}
	else if(QString(field->metaObject()->className()).compare("QDateTimeEdit") == 0){

		//save =((QDateTimeEdit*)field)->dateTime().toString(Qt::DefaultLocaleShortDate);
		save = QString(((QDateTimeEdit*)field)->dateTime().toString(Qt::ISODate));
		//qDebug() << save;
		}


	return save;
}

bool SubFieldUI::checkMandatory()
{

	if(!structureView.isEmpty()
			&& structureView.value("Mandatory") != QJsonValue::Undefined
			&& structureView.value("Mandatory").toBool()){
		QJsonValue saved = this->save();

		if(saved.isObject()){
			if(saved.toObject().value("Value").toString().isEmpty()){
				field->setObjectName("error");
				field->style()->unpolish(field);
				field->style()->polish(field);
				field->update();
				return false;
				}

			}
		else if(this->save().toString().isEmpty()){
			//	qDebug()<< this->save().isNull() << this->save().toString() << field;
			field->setObjectName("error");
			field->style()->unpolish(field);
			field->style()->polish(field);
			field->update();
			return false;
			}
		else{
			field->setObjectName("NotError");
			field->style()->unpolish(field);
			field->style()->polish(field);
			field->update();
			}

		}
	return true;
}

void SubFieldUI::indexedFillEvent(QString completion)
{
	qDebug() << __FILE__ << __LINE__  << completion;

}

void SubFieldUI::linkPressed()
{
	Controller::Get()->linkPressed(this->structureView);
}

void SubFieldUI::btnSearch_Clicked()
{
	searchShortCut->setEnabled(false);
	SearchUI::ShowUI(structureView.value("Source").toString(),QVector<QJsonDocument>(),strID);
	QObject::connect(SearchUI::Get()->getTable(),SIGNAL(gotRowData(QVector<QString>)),this,SLOT(editComboxText(QVector<QString>)));
}

void SubFieldUI::refrenceData(QVector<QJsonDocument> items)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotJsonListData(QVector<QJsonDocument>)),this,SLOT(refrenceData(QVector<QJsonDocument>)));

	if(combox){
		combox->clear();
		combox->addJsonItems(items);
		}
	if(structureView.value("Default") != QJsonValue::Undefined){
		combox->setCurrentIndex(structureView.value("Default").toString().toInt());
		}

}


void SubFieldUI::serialData(QString serial)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotValue(QString)),this,SLOT(serialData(QString)));
	int newValue = Controller::Get()->Count((this->strID.split("ViewStructure::")[1] + "::%").trimmed()+"\"") ;
	int oldValue = structureView.value("currentNum").toInt();
	int startNum = structureView.value("startNum").toInt();
	int serializedNum = newValue - oldValue + startNum;

	((QLineEdit*)field)->setText(QString::number(serializedNum));

}

void SubFieldUI::updateFilter(QString filter)
{
	QString source = structureView.value("Source").toString().trimmed();
	QString select = structureView.value("Select").toString().trimmed();
	QString entity = structureView.value("Entity").toString().trimmed();
	if(source.isEmpty() || select.isEmpty() || entity.isEmpty()){
		return;
		}
	else{
		//qDebug() << __FILE__ << __LINE__  <<"filter" << filter << structureView.value("Source").toString()<<structureView.value("Select").toString()<<structureView.value("Entity").toString()+"="+filter;
		QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QVector<QJsonDocument>)),this,SLOT(refrenceData(QVector<QJsonDocument>)));
		//qDebug() <<"Source:" << source <<"SELECT:"<< select<<"Entity:" << entity <<"Filter:"<< filter;
		//QString("`"+entity+"`").append(" = ").append("'").append(filter).append("'");
		Controller::Get()->getJsonEntityFieldsList(source,select,QString("to_string(d.`"+entity+"`)").append("  LIKE  ").append("'").append(filter).append("'"));
		}

}

void SubFieldUI::updateTable(QString)
{
	if(localFilterCombobox)
		table->fillLocalSource(structureView,localFilterCombobox->getKey());
}

void SubFieldUI::updateEquationField()
{
	double total = 0;

	if(this->structureView.value("EquationTerms").isArray()){
		if(structureView.value("EquationTerms").toArray().first().toObject().value("Editable") == QJsonValue::Undefined)
			((QLineEdit*)field)->setEnabled(false);
		else ((QLineEdit*)field)->setEnabled(true);

		foreach(QJsonValue eq,this->structureView.value("EquationTerms").toArray()){
			double subTotal = 0;
			bool ok = true;
			double firstTerm = 0;
			double secondTerm = 0;
			//qDebug() << __FILE__ << __LINE__  << eq;
			double tempFirstField = -2;

			QString firstClmn = eq.toObject().value("FirstColumn").toString();
			SubFieldUI* firstTermField = Controller::Get()->getFirstSubField(firstClmn);
			if(firstClmn.contains("$")){

				tempFirstField = getClmnDataCount(firstClmn);
				ok = true;
				//TODO : connect table update signal just like text update
				if(tempFirstField < -1){
					qDebug() << __FILE__ << __LINE__  << "ERORR : Table is not Init connceted signal to recalculte!";
					//((QLineEdit*)field)->setText(QString::number(-1));
					//return;
					}
				}
			else{

				if((QString((firstTermField->field)->metaObject()->className()).compare("QLineEdit") == 0 ) &&(QLineEdit*)firstTermField->field){
					if(!((QLineEdit*)firstTermField->field)->text().trimmed().isEmpty())
						tempFirstField = ((QLineEdit*)firstTermField->field)->text().trimmed().toDouble(&ok);
					QObject::disconnect(((QLineEdit*)firstTermField->field),SIGNAL(textChanged(QString)),this,SLOT(updateEquationField()));
					QObject::connect(((QLineEdit*)firstTermField->field),SIGNAL(textChanged(QString)),this,SLOT(updateEquationField()));
					}
				else if((QString((firstTermField->field)->metaObject()->className()).contains("ERPComboBox")) &&(ERPComboBox*)firstTermField->field){
					if(! ((ERPComboBox*)firstTermField->field)->currentText().trimmed().isEmpty())
						tempFirstField = ((ERPComboBox*)firstTermField->field)->currentText().trimmed().toDouble(&ok);
					QObject::disconnect(((ERPComboBox*)firstTermField->field),SIGNAL(currentTextChanged(QString)),this,SLOT(updateEquationField()));
					QObject::connect(((ERPComboBox*)firstTermField->field),SIGNAL(currentTextChanged(QString)),this,SLOT(updateEquationField()));
					}
				}
			double tempSecondField = -2;
			QString secondClmn = eq.toObject().value("SecondColmn").toString();
			SubFieldUI* secondTermField = Controller::Get()->getFirstSubField(secondClmn);
			if(secondClmn.contains("$")){
				tempSecondField = getClmnDataCount(secondClmn);
				if(tempSecondField < -1){
					//tempSecondField = 0;
					//qDebug() << __FILE__ << __LINE__  << "ERORR : Table is not Init connceted signal to recalculte!";
					//((QLineEdit*)field)->setText(QString::number(-1));
					//return;
					}
				}
			else{
				if((QString((secondTermField->field)->metaObject()->className()).compare("QLineEdit") == 0 ) &&  ((QLineEdit*)secondTermField->field)){
					if(!((QLineEdit*)secondTermField->field)->text().trimmed().isEmpty())
						tempSecondField = ((QLineEdit*)secondTermField->field)->text().trimmed().toDouble(&ok);
					QObject::disconnect(((QLineEdit*)secondTermField->field),SIGNAL(textChanged(QString)),this,SLOT(updateEquationField()));
					QObject::connect(((QLineEdit*)secondTermField->field),SIGNAL(textChanged(QString)),this,SLOT(updateEquationField()));
					}
				else if((QString((secondTermField->field)->metaObject()->className()).contains("ERPComboBox")) &&(ERPComboBox*)secondTermField->field){
					if(! ((ERPComboBox*)secondTermField->field)->currentText().trimmed().isEmpty())
						tempSecondField = ((ERPComboBox*)secondTermField->field)->currentText().trimmed().toDouble(&ok);
					QObject::disconnect(((ERPComboBox*)secondTermField->field),SIGNAL(currentTextChanged(QString)),this,SLOT(updateEquationField()));
					QObject::connect(((ERPComboBox*)secondTermField->field),SIGNAL(currentTextChanged(QString)),this,SLOT(updateEquationField()));
					}
				}

			if(eq.toObject().value("ConditionColumnOne") != QJsonValue::Undefined){
				double tempFirstCondField = 0;
				QString condOnColOne = eq.toObject().value("ConditionColumnOne").toString();
				if(condOnColOne.contains("$")){

					tempFirstCondField = getClmnDataCount(condOnColOne);
					ok = true;
					//qDebug() << __FILE__ << __LINE__  << "TABELL" <<tempFirstField;

					//TODO : connect table update signal just like text update
					if(tempFirstField < -1){
						qDebug() << __FILE__ << __LINE__  << "ERORR : Table is not Init connceted signal to recalculte!";
						((QLineEdit*)field)->setText(QString::number(-1));
						return;
						}
					}
				else{
					SubFieldUI* firstTermCondField = Controller::Get()->getFirstSubField(condOnColOne);
					if((QString((firstTermCondField->field)->metaObject()->className()).compare("QLineEdit") == 0 ) && (QLineEdit*)firstTermCondField->field){
						tempFirstCondField = ((QLineEdit*)firstTermCondField->field)->text().trimmed().toDouble(&ok);
						QObject::disconnect(((QLineEdit*)firstTermCondField->field),SIGNAL(textChanged(QString)),this,SLOT(updateEquationField()));

						QObject::connect(((QLineEdit*)firstTermCondField->field),SIGNAL(textChanged(QString)),this,SLOT(updateEquationField()));
						}
					}

				firstTerm = evalEquationCondition(eq.toObject().value("ConditionOnOne").toInt(),tempFirstCondField,tempFirstField);
				}
			//qDebug() << __FILE__ << __LINE__  << eq.toObject().value("FirstColumn").toInt() << j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt() << cells[j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt()].getData();
			else firstTerm = tempFirstField;

			if(eq.toObject().value("SecondColmn") != QJsonValue::Undefined){

				if(eq.toObject().value("ConditionColumnTwo") != QJsonValue::Undefined){
					double tempSecondCondField = 0;
					SubFieldUI* secondTermCondField = Controller::Get()->getFirstSubField(eq.toObject().value("ConditionColumnTwo").toString());
					if((QString((secondTermCondField->field)->metaObject()->className()).compare("QLineEdit") == 0 ) && (QLineEdit*)secondTermCondField->field){
						tempSecondCondField = ((QLineEdit*)secondTermCondField->field)->text().trimmed().toDouble(&ok);
						QObject::disconnect(((QLineEdit*)secondTermCondField->field),SIGNAL(textChanged(QString)),this,SLOT(updateEquationField()));

						QObject::connect(((QLineEdit*)secondTermCondField->field),SIGNAL(textChanged(QString)),this,SLOT(updateEquationField()));
						}

					secondTerm = evalEquationCondition(eq.toObject().value("ConditionOnTwo").toInt(),tempSecondCondField,tempSecondField);
					}else secondTerm = tempSecondField;

				}

			else if(eq.toObject().value("Number") != QJsonValue::Undefined){
				secondTerm = eq.toObject().value("Number").toString().toDouble(&ok);
				}

			if(ok){
				//qDebug() << __FILE__ << __LINE__  << "GetTotal:"<< ok << firstTerm << secondTerm;
				if(eq.toObject().value("Operation").toInt() == 0){
					firstTerm < -1? firstTerm = 0:true;
					secondTerm < -1? secondTerm = 0:true;
					subTotal = firstTerm + secondTerm;
					}
				else if(eq.toObject().value("Operation").toInt() == 1){
					firstTerm < -1? firstTerm = 0:true;
					secondTerm < -1? secondTerm = 0:true;
					subTotal = firstTerm - secondTerm;
					}
				else if(eq.toObject().value("Operation").toInt() == 2){
					firstTerm < -1? firstTerm = 1:true;
					secondTerm < -1? secondTerm = 1:true;
					subTotal = firstTerm * secondTerm;
					}
				else if(eq.toObject().value("Operation").toInt() == 3){
					firstTerm < -1? firstTerm = 1:true;
					secondTerm < -1? secondTerm = 1:true;
					subTotal = firstTerm / secondTerm;
					}

				if(eq.toObject().value("FirstOperation") != QJsonValue::Undefined){
					if(eq.toObject().value("FirstOperation").toInt() == 0){
						total += subTotal;
						}
					else if(eq.toObject().value("FirstOperation").toInt() == 1){
						total -= subTotal;
						}
					else if(eq.toObject().value("FirstOperation").toInt() == 2){
						total *= subTotal;
						}
					else if(eq.toObject().value("FirstOperation").toInt() == 3){
						total /= subTotal;
						}
					//qDebug() << __FILE__ << __LINE__  << subTotal << total;
					}
				else total = subTotal;
				}
			else {
				total = -1;
				}
			}

}
	//qDebug() << __FILE__ << __LINE__  <<total;

	((QLineEdit*)field)->setText(QString::number(total));
}

double SubFieldUI::getClmnDataCount(QString strct)
{

	QString fieldName = strct.split("$").count() == 2? strct.split("$")[1]:"";
	QString columnName = strct.split("$").count() == 2?strct.split("$")[0]:"";

	double total = 0;
	SubFieldUI* tableSubField = Controller::Get()->getFirstSubField(fieldName);
	if(((merplyTabelView*)tableSubField->field)->getModel() != NULL && QString( tableSubField->field->metaObject()->className()).compare("merplyTabelView") == 0){
		QObject::disconnect(((merplyTabelView*)tableSubField->field)->getModel(),SIGNAL(changed()),this,SLOT(updateEquationField()));
		QObject::connect(((merplyTabelView*)tableSubField->field)->getModel(),SIGNAL(changed()),this,SLOT(updateEquationField()));
		if( ((merplyTabelView*)tableSubField->field)->getModel()->getRowsCount() == 0 )
			{
			total = -2;
			}
		else {
			total = ((merplyTabelView*)tableSubField->field)->getModel()->getTotalClmn(columnName);

			}
		}
	//qDebug() << __FILE__ << __LINE__  << total << strct << fieldName;
	return total;
}

double SubFieldUI::evalEquationCondition(int condition, double col1, double col2)
{
	//qDebug() << __FILE__ << __LINE__  << condition << col1 << col2;
	if(condition == 1){
		if(col1 > col2)
			return col1;
		else return col2;
		}
	else if(condition ==2){
		if(col1 < col2)
			return col1;
		else return col2;
		}
	return 0;
}
/**
 * @brief SubFieldUI::editComboxText, it sets the text of combox based on the clicked row
 * @param rowData
 * @author Safa Ads
 */
void SubFieldUI::editComboxText(QVector<QString> rowData)
{
	for(int i =0; i<rowData.size();i++){
		QString dataHeader = rowData[i].split(",")[1];
		if(dataHeader.compare(structureView.value("Select").toString())==0)
			combox->setCurrentText(rowData[i].split(",")[0]);
		}
}
