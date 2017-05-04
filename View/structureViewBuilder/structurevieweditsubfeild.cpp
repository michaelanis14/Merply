

#include "structureviewgroupsui.h"
#include "structurevieweditsubfeild.h"
#include "structureviewedit.h"
#include "controller.h"
#include "prsistance.h"
#include "removebtn.h"
#include "structurevieweditsubfieldquery.h"
#include "structurevieweditsubfieldpiechart.h"
#include "structurevieweditsubfieldgraphchart.h"
#include "structurevieweditsubfieldbargraph.h"
#include "structurevieweditsubfieldpercentagegraph.h"

StructureVieweditSubFeild::StructureVieweditSubFeild(QWidget *parent) : QWidget(parent)
{
	//this->setFixedWidth(150);


	this->setContentsMargins(0,0,0,0);
	this->setObjectName("StructureVieweditSubFeild");
	this->setStyleSheet("QWidget2#StructureVieweditSubFeild{ border: 1px solid gray; border-top : 1px solid blue;}");
	this->filledLocalfilter = false;
	layout = new QFormLayout(this);
	layout->setContentsMargins(0,0,5,0);
	layout->setSpacing(1);
	//layout->setMargin(0);
	layout->setAlignment(Qt::AlignLeft);
	//layout->setHorizontalSpacing(1);
	//layout->setRowWrapPolicy();
	//this->setAutoFillBackground(true);
	//layout->setRowWrapPolicy(QFormLayout::DontWrapRows);
	//layout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
	layout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
	layout->setLabelAlignment(Qt::AlignLeft);
	this->filled = false;

	preview = new QWidget();
	preview->setContentsMargins(0,0,0,0);
	//preview->setMinimumHeight(35);
	preview->setObjectName("preview");
	previewLayout = new QHBoxLayout(preview);
	previewLayout->setContentsMargins(0,0,0,0);
	previewLayout->setSpacing(0);
	previewLayout->setMargin(1);
	//this->setStyleSheet();
	layout->addRow(preview);


	typeSelect = new ERPComboBox(0);
}


void StructureVieweditSubFeild::fillTypeFields(QString type,QJsonValue fieldVS,QStringList restrictedTypes)
{
	//qDebug() << __FILE__ << __LINE__  << "fffield" << fieldVS;
	this->filled = true;
	this->type = type;
	this->restrictedTypes = restrictedTypes;
	if(fieldVS.isObject())
		this->fieldVS = fieldVS;

	QStringList types;
	if(!restrictedTypes.isEmpty()){
		types << restrictedTypes;
		}else
        types << "Index"<<"Text"<< "Refrence" <<"Date"<< "Fixed" <<"Serial" << "Table" <<"TextArea" <<"Equation" <<"Query" << "Charts";
	typeSelect->addItems(types);
	typeSelect->setCurrentIndex(types.indexOf(type));
	//if(restrictedTypes.isEmpty())
	layout->addRow(new QLabel(tr("Data Type")), typeSelect);


	QObject::connect(typeSelect,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateFields(QString)));




	if(type.compare("Link") == 0){
		title = new QLineEdit;

		if(!fieldVS.toObject().value("Title").toString().isEmpty())
			title->setText(fieldVS.toObject().value("Title").toString());
		else title->setText(tr("New"));

		layout->addRow(new QLabel(tr("Title")), title);

		Source = new ERPComboBox(0);

		if(!fieldVS.toObject().value("Source").toString().isEmpty())
			Source->setCurrentText(fieldVS.toObject().value("Source").toString());
		layout->addRow(new QLabel(tr("Source ")), Source);
		QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QVector<QJsonDocument>)),this,SLOT(gotSourceData(QVector<QJsonDocument>)));
		Controller::Get()->getJsonList("ViewStructure","Title","`"+QString(DATABASE).append("`.Type =\"Entity\""));


		Select = new ERPComboBox(0);
		Select->addItems(QStringList() << "Index" <<"New");
		if(!fieldVS.toObject().value("Select").toString().isEmpty())
			Select->setCurrentText(fieldVS.toObject().value("Select").toString());
		layout->addRow(new QLabel(tr("Action ")), Select);


		//QObject::connect(Source,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateSelect(QString)));
		//QObject::connect(Select,SIGNAL(currentIndexChanged(QString)),this,SIGNAL(changed()));
		//QObject::connect(title,SIGNAL(textChanged(QString)),this,SIGNAL(changed()));

		}
	else if(type.compare("Refrence") == 0){
		loadData = true;
		Source = new ERPComboBox(0);
		Select = new ERPComboBox(0);
		layout->addRow(new QLabel(tr("Source ")), Source);
		QObject::connect(Controller::Get(),SIGNAL(gotJsonListData(QVector<QJsonDocument>)),this,SLOT(gotSourceData(QVector<QJsonDocument>)));
		Controller::Get()->getJsonList("ViewStructure","Title","`"+QString(DATABASE).append("`.Type =\"Entity\""));
		layout->addRow(new QLabel(tr("Select ")), Select);
		condition = new QTextEdit;
		condition->setText(fieldVS.toObject().value("Condition").toString());
		layout->addRow(new QLabel(tr("Condition ")), condition);
		Editable = new QCheckBox(0);
		Editable->setChecked(fieldVS.toObject().value("Editable").toString().compare("true") ==0);
		layout->addRow(new QLabel(tr("Editable ")), Editable);
		initFilterWidget();
		if(fieldVS.toObject().value("LocalFilter") != QJsonValue::Undefined && fieldVS.toObject().value("LocalFilter").toBool()){
			filterOn->setCurrentIndex(1);
			this->filledLocalfilter = false;
			//	filterOn->currentIndexChanged(filterOn->currentIndex());

			//	qDebug() << __FILE__ << __LINE__  << fieldVS.toObject().value("Local").toString();
			//localFilter->currentIndexChanged(localFilter->currentIndex());

			//	qDebug() << __FILE__ << __LINE__  << fieldVS.toObject().value("Entity").toString();

			//entityFilter->currentIndexChanged(entityFilter->currentIndex());
			//entityFilter->setCurrentText();
			}
		defaultValue = new QLineEdit(0);
		defaultValue->setText(fieldVS.toObject().value("Default").toString());
		defaultValue->setValidator( new QIntValidator(0, 1000000, this) );
		layout->addRow(new QLabel(tr("Default ")), defaultValue);
		}
	else if(type.compare("Text") == 0){

		defaultValue = new QLineEdit(0);
		defaultValue->setText(fieldVS.toObject().value("Default").toString());
		layout->addRow(new QLabel(tr("Default ")), defaultValue);

		QStringList inputDTList;
		inputDTList <<"Text" <<"IntToMillion"<<"DoubleToMillion";
		inputDataType = new ERPComboBox(0);
		inputDataType->addItems(inputDTList);
		if(fieldVS.toObject().value("InputDataType") != QJsonValue::Undefined)
			inputDataType->setCurrentText(fieldVS.toObject().value("InputDataType").toString());
		layout->addRow(new QLabel(tr("Input Type ")), inputDataType);

		charCount = new QLineEdit(0);
		if(fieldVS.toObject().value("CharCount") != QJsonValue::Undefined)
			charCount->setText(fieldVS.toObject().value("CharCount").toString());
		else charCount->setText("-1");

		layout->addRow(new QLabel(tr("Count Limit ")), charCount);

		}
	else if(type.compare("TextArea") == 0){

		textEdit = new QTextEdit;
		textEdit->setText(fieldVS.toObject().value("Default").toString());
		layout->addRow(new QLabel(tr("Default ")), textEdit);
		}
	else if(type.compare("Fixed") == 0){

		defaultValue = new QLineEdit(0);
		defaultValue->setText(fieldVS.toObject().value("Default").toString());
		layout->addRow(new QLabel(tr("Default ")), defaultValue);
		}
	else if(type.compare("Index") == 0){
		Source = new ERPComboBox(0);
		//Source->setText(fieldVS.toObject().value("Source").toString());
		layout->addRow(new QLabel(tr("Source ")), Source);
		Select = new ERPComboBox(0);
		//	Select->setText(fieldVS.toObject().value("Select").toString());
		layout->addRow(new QLabel(tr("Select ")), Select);
		}
	else if(type.compare("Table") == 0){
		tableEdit = new StructureVieweditSubFeildTable(this);
		//qDebug() << __FILE__ << __LINE__  << "TABEL STCT"<< fieldVS.toObject();
		tableEdit->fill(fieldVS.toObject());

		QObject::disconnect(tableEdit,SIGNAL(tableChanged()),this,SIGNAL(changed()));
		QObject::connect(tableEdit,SIGNAL(tableChanged()),this,SIGNAL(changed()));
		layout->addRow("Tabel",tableEdit);
		}
	else if(type.compare("Serial") == 0){
		defaultValue = new QLineEdit;
		if(fieldVS.toObject().value("startNum").toInt() > 0)
			defaultValue->setText(QString::number(fieldVS.toObject().value("startNum").toInt()));
		else defaultValue->setText(QString::number(1));
		layout->addRow(new QLabel(tr("Start Number")), defaultValue);
		}
	else if(type.compare("Date") == 0){
		date = new QDateEdit(this);
		date->setDate(QDate::fromString(fieldVS.toObject().value("date").toString(),"dd-MMM-yyyy"));
		layout->addRow("Date", date);
		}
	else if(type.compare("Equation") == 0){
		initEquationWidget();
		QJsonArray equationTerms =  fieldVS.toObject().value("EquationTerms").toArray();
		foreach(QJsonValue equationTerm,equationTerms){
			addEquationWidget(equationTerm.toObject());
			}
		}
    else if (type.compare("Query") == 0){
        // qDebug() << fieldVS.toObject();


        QPushButton* addQuery = new QPushButton("Add Query");
        QObject::connect(addQuery,SIGNAL(pressed()),this,SLOT(addNewQuery()));
        queryList.clear();
        if(fieldVS.toObject().value("QueryText")!= QJsonValue::Undefined)
        {
            query = new QTextEdit(fieldVS.toObject().value("QueryText").toString());
            layout->addRow(new QLabel(tr("Query")),query);
            layout->addRow(addQuery);
            //StructureViewEdit Q = new StructureViewEdit(this,fieldVS,QStringList());
            //QObject::connect(this,SIGNAL(StructureViewEdit::updateQueryList()),this,SLOT(addQueryWidgetData()));
            QJsonArray queryListSaved = fieldVS.toObject().value("QueriesReplacments").toArray();
            foreach(QJsonValue querySaved,queryListSaved){
                StructureVieweditSubFieldQuery* queryWidget = new StructureVieweditSubFieldQuery();
                QObject::connect(StructureViewGroupsUI::GetUI(),SIGNAL(gotFieldsNames(QStringList)),queryWidget,SLOT(setFieldsNames(QStringList)));
                StructureViewGroupsUI::GetUI()->getFeildsNames();
                queryWidget->fill(querySaved.toObject().value("EntityReference").toString(),querySaved.toObject().value("Keyword").toString());
                queryList.push_back(queryWidget);
                RemoveBtn* removeQuery = new RemoveBtn(this,queryWidget);
                QObject::connect(removeQuery,SIGNAL(remove(QWidget*)),this,SLOT(removeQuery(QWidget*)));
                layout->addRow(removeQuery);
            }

        }
        else{

            query = new QTextEdit();
            layout->addRow(new QLabel(tr("Query")),query);
            layout->addRow(addQuery);
        }

    }
    //emit changed();
    else if (type.compare("Charts") == 0)
    {
        QList<QString> choices;
        choices << "Graph Chart" << "Pie Chart" <<"Vertical Bar Graph" <<"Horizontal Bar Graph" <<"Vertical Percentage Graph" << "Horizontal Percentage Graph";
        charts = new ERPComboBox();
        charts->addItems(choices);
        layout->addRow("Choose which Graph",charts);
        if(fieldVS.toObject().value("ChartType")!= QJsonValue::Undefined)
        {
            charts->setCurrentText(fieldVS.toObject().value("ChartType").toString());
            if(fieldVS.toObject().value("ChartType").toString() == "Pie Chart")
            {
                StructureViewEditSubFieldPieChart* pieChart = new StructureViewEditSubFieldPieChart();
                pieChart->fill(fieldVS.toObject());
                layout->addWidget(pieChart->getPieChart());
            }

            else if(fieldVS.toObject().value("ChartType").toString() == "Graph Chart")
            {
                StructureViewEditSubFieldGraphChart* graphChart = new StructureViewEditSubFieldGraphChart();
                graphChart->fill(fieldVS.toObject());
                layout->addWidget(graphChart->getGraphChart());
            }
            else if(fieldVS.toObject().value("ChartType").toString() == "Vertical Bar Graph")
            {
                StructureViewEditSubFieldBarGraph* graphChart = new StructureViewEditSubFieldBarGraph("Vertical");
                graphChart->fill(fieldVS.toObject());
                layout->addWidget(graphChart->getGraphChart());
            }
            else if(fieldVS.toObject().value("ChartType").toString() == "Horizontal Bar Graph")
            {
                StructureViewEditSubFieldBarGraph* graphChart = new StructureViewEditSubFieldBarGraph("Horizontal");
                graphChart->fill(fieldVS.toObject());
                layout->addWidget(graphChart->getGraphChart());
            }
            else if(fieldVS.toObject().value("ChartType").toString() == "Vertical Percentage Graph")
            {
                StructureViewEditSubFieldPercentageGraph* graphChart = new StructureViewEditSubFieldPercentageGraph("Vertical");
                graphChart->fill(fieldVS.toObject());
                layout->addWidget(graphChart->getGraphChart());
            }
            else if(fieldVS.toObject().value("ChartType").toString() == "Horizontal Percentage Graph")
            {
                StructureViewEditSubFieldPercentageGraph* graphChart = new StructureViewEditSubFieldPercentageGraph("Horizontal");
                graphChart->fill(fieldVS.toObject());
                layout->addWidget(graphChart->getGraphChart());
            }
        }

    }
    //QObject::connect(this,SIGNAL(changed()),SubFieldUI,SLOT(updateQueryField()));
	mandatory = new QCheckBox(this);
	if(fieldVS.toObject().value("Mandatory").toBool())
		mandatory->setChecked(true);
	layout->addRow("Mandatory", mandatory);
	//previewLayout->addWidget(new SubFieldUI(0,"V",this->save()));
	//	qDebug() << __FILE__ << __LINE__  <<this->save();
}


QJsonObject StructureVieweditSubFeild::save()
{
	QJsonObject saveObject;
	if(!this->type.isEmpty() && filled)
		{
		//qDebug() << __FILE__ << __LINE__  << this->type << filled << Link;
		saveObject.insert("Type",type);
		saveObject.insert("Mandatory",mandatory->isChecked());
		if(type.compare("Link") == 0){
			saveObject.insert("Select",Select->currentText());
			saveObject.insert("Source",Source->getKey());
			saveObject.insert("Title",title->text());
			}

		else if(type.compare("Refrence") == 0){
			//qDebug() << __FILE__ << __LINE__  <<"Save Refrence subfield:213"<< Select->getKey() << Source->getKey();
			saveObject.insert("Select",Select->currentText());
			saveObject.insert("Source",Source->getKey());
			saveObject.insert("Condition",condition->toPlainText());
			saveObject.insert("Editable",Editable->isChecked());
			if(!defaultValue->text().isEmpty())
				saveObject.insert("Default",defaultValue->text());
			if(filterOn->currentIndex() == 1){
				saveObject.insert("LocalFilter",true);
				saveObject.insert("Local",localFilter->currentText());
				saveObject.insert("Entity",entityFilter->currentText());
				}
			}
		else if(type.compare("Text") == 0){
			if(!defaultValue->text().isEmpty())
				saveObject.insert("Default",defaultValue->text());
			saveObject.insert("InputDataType",inputDataType->currentText());
			saveObject.insert("CharCount",charCount->text());
			}
		else if(type.compare("TextArea") == 0){
			if(!textEdit->toPlainText().isEmpty())
				saveObject.insert("Default",textEdit->toPlainText());
			}
		else  if(type.compare("Fixed") == 0){
			if(!defaultValue->text().isEmpty())
				saveObject.insert("Default",defaultValue->text());
			}
		else  if(type.compare("Index") == 0){
			saveObject.insert("Select",Select->currentText());
			saveObject.insert("Source",Source->getKey());
			}
		else if(type.compare("Table") == 0){
			//qDebug() << __FILE__ << __LINE__  << tableEdit->save();
			saveObject = tableEdit->save();
			}
		else  if(type.compare("Serial") == 0){
			if(!defaultValue->text().isEmpty())
				saveObject.insert("startNum",defaultValue->text().toInt());
			else saveObject.insert("startNum",1);
			}
		else if(type.compare("Date") == 0){
			//qDebug() << __FILE__ << __LINE__  << date->date().toString(Qt::DefaultLocaleShortDate);
			//	saveObject.insert("date",date->date().toString(Qt::DefaultLocaleShortDate));
			}
		else if(type.compare("Equation") == 0){
			QJsonArray equationTerms;
			foreach(StructureVieweditSubFeildEquation* eqTerm,equationElements){
				equationTerms << eqTerm->save();
				}
			saveObject.insert("EquationTerms",equationTerms);
			}
        else if(type.compare("Query") == 0)
        {
            saveObject.insert("QueryText",query->toPlainText());
              //              qDebug() << __FILE__ << __LINE__  <<queryList.count();
            QJsonArray queriesArray;
            foreach(StructureVieweditSubFieldQuery* list,queryList){
                queriesArray.append(list->save());
               // qDebug() << __FILE__ << __LINE__  << "SAVE QUERY/replace"<< list->save();
            }
            //qDebug() << queryList;
            saveObject.insert("QueriesReplacments",queriesArray);
        }
        else if (type.compare("Charts")==0)
        {
            if(charts->currentText().compare("Pie Chart")==0){
            StructureViewEditSubFieldPieChart* pieChart = new StructureViewEditSubFieldPieChart();
            saveObject = pieChart->save();
            //qDebug() << saveObject;
            }
            else if(charts->currentText().compare("Graph Chart")==0){
            StructureViewEditSubFieldGraphChart* graphChart = new StructureViewEditSubFieldGraphChart();
            saveObject = graphChart->save();
            //qDebug() << saveObject;
            }
            else if(charts->currentText().compare("Vertical Bar Graph")==0){
            StructureViewEditSubFieldBarGraph* graphChart = new StructureViewEditSubFieldBarGraph("Vertical");
            saveObject = graphChart->save();
            //qDebug() << saveObject;
            }
            else if(charts->currentText().compare("Horizontal Bar Graph")==0){
            StructureViewEditSubFieldBarGraph* graphChart = new StructureViewEditSubFieldBarGraph("Horizontal");
            saveObject = graphChart->save();
            //qDebug() << saveObject;
            }
            else if(charts->currentText().compare("Vertical Percentage Graph")==0){
            StructureViewEditSubFieldPercentageGraph* graphChart = new StructureViewEditSubFieldPercentageGraph("Vertical");
            saveObject = graphChart->save();
            //qDebug() << saveObject;
            }
            else if(charts->currentText().compare("Horizontal Percentage Graph")==0){
            StructureViewEditSubFieldPercentageGraph* graphChart = new StructureViewEditSubFieldPercentageGraph("Horizontal");
            saveObject = graphChart->save();
            //qDebug() << saveObject;
            }
            saveObject.insert("Type","Charts");
        }


    }
	return saveObject;
}

void StructureVieweditSubFeild::addQueryWidgetData()
{
    QJsonArray queryListSaved = fieldVS.toObject().value("QueriesReplacments").toArray();
    int countIndices=0;
    foreach (StructureVieweditSubFieldQuery* queryWidget, queryList) {
       queryWidget->fill(queryListSaved[countIndices].toObject().value("EntityReference").toString(),queryListSaved[countIndices].toObject().value("Keyword").toString());
       countIndices++;
    }

}

QString StructureVieweditSubFeild::getType()
{
	return this->type;
}

StructureVieweditSubFeildTable* StructureVieweditSubFeild::getTableEdit() const
{
	return tableEdit;
}

void StructureVieweditSubFeild::initFilterWidget()
{
	filterWidget = new QWidget(0);
	filterWidget->setContentsMargins(0,0,0,0);
	filterWidget->setObjectName("filterWidget");
	filterWidgetLayout = new QFormLayout(filterWidget);
	filterWidgetLayout->setFormAlignment(Qt::AlignLeft);
	filterWidgetLayout->setLabelAlignment(Qt::AlignLeft);
	filterWidgetLayout->setSpacing(0);
	filterWidgetLayout->setMargin(0);

	filterOn = new ERPComboBox(filterWidget);
	filterWidgetLayout->addRow(new QLabel(tr("Filter on    ")), filterOn);
	QStringList filterItems;
	filterItems <<tr("none")<< tr("local match") << tr("Other");
	filterOn->addItems(filterItems);
	//fieldsWidgetLayout->addWidget(filterWidget);
	QObject::connect(filterOn,SIGNAL(currentIndexChanged(int)),this,SLOT(filterOnChanged(int)));


	localFilterWidget = new QWidget(0);
	localFilterWidget->setAutoFillBackground(true);
	localFilterWidget->setContentsMargins(0,0,0,0);
	localFilterWidget->setObjectName("localFilterWidget");
	localFilterWidgetLayout = new QFormLayout(localFilterWidget);
	localFilterWidgetLayout->setAlignment(Qt::AlignLeft);
	//localFilterWidgetLayout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
	localFilterWidgetLayout->setLabelAlignment(Qt::AlignLeft);
	localFilterWidgetLayout->setSpacing(0);
	localFilterWidgetLayout->setMargin(0);

	localFilter = new ERPComboBox(0);
	localFilterWidgetLayout->addRow(new QLabel(tr("Local Filter")), localFilter);
	entityFilter = new ERPComboBox(0);
	localFilterWidgetLayout->addRow(new QLabel(tr("Entity Filter")), entityFilter);
	//QObject::connect(localFilter,SIGNAL(currentIndexChanged(int)),this,SLOT(filterOnChanged(int)));
	localFilterWidget->setHidden(true);
	filterWidgetLayout->addRow(localFilterWidget);

	layout->addRow(filterWidget);
}

void StructureVieweditSubFeild::initEquationWidget()
{
	equationWidget = new QWidget;
	equationWidget->setContentsMargins(0,0,0,0);
	equationWidget->setAutoFillBackground(true);
	equationWidget->setObjectName("equationWidget");
	equationWidgetLayout = new QFormLayout(equationWidget);
	equationWidget->setLayout(equationWidgetLayout);
	equationWidgetLayout->setFormAlignment(Qt::AlignLeft);
	equationWidgetLayout->setLabelAlignment(Qt::AlignLeft);
	equationWidgetLayout->setSpacing(0);
	equationWidgetLayout->setMargin(0);

	QPushButton* addEqElement = new QPushButton("add Element");
	equationWidgetLayout->addRow(addEqElement);
	QObject::connect(addEqElement,SIGNAL(pressed()),this,SLOT(addEquationWidget()));
	layout->addRow(equationWidget);
}

void StructureVieweditSubFeild::updateFields(QString type)
{
	this->type = type;
	QList<QWidget *> Widgets = this->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		if(child != NULL && child->objectName().compare("preview") !=0 ){
			layout->removeWidget(child);
			child->setHidden(true);
			//child->setParent(0);
			child->deleteLater();
			}
		}

	this->fillTypeFields(type,this->fieldVS,this->restrictedTypes);
	//emit changed();
}

void StructureVieweditSubFeild::updateSelect(QString)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateSelectData(QList<QString>)));
	QObject::connect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateSelectData(QList<QString>)));
	Controller::Get()->getFields(Source->getKey());

}

void StructureVieweditSubFeild::updateSelectData(QList<QString> fields)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateSelectData(QList<QString>)));
	Select->clear();
	Select->addItems(fields);
	if(loadData && fieldVS.toObject().value("Select") != QJsonValue::Undefined){
		loadData = false;
		Select->setCurrentIndex(Select->getItemsText().indexOf(fieldVS.toObject().value("Select").toString()));
		//	qDebug() << __FILE__ << __LINE__  << "Select" << fieldVS.toObject().value("Select").toString() << fields << Select->getItemsText() << Select->getItemsText().indexOf(fieldVS.toObject().value("Select").toString()) << Select->currentIndex();
		//	Select->currentIndexChanged(Select->currentIndex());
		}
}

void StructureVieweditSubFeild::gotSourceData(QVector<QJsonDocument> items)
{
	//qDebug() << __FILE__ << __LINE__<< "gotSourceData" << items;
	QObject::disconnect(Controller::Get(),SIGNAL(gotJsonListData(QVector<QJsonDocument>)),this,SLOT(gotSourceData(QVector<QJsonDocument>)));
	Source->clear();
	Source->addJsonItems(items);

	QObject::disconnect(Source,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateSelect(QString)));
	QObject::disconnect(Select,SIGNAL(currentIndexChanged(QString)),this,SIGNAL(changed()));
	QObject::connect(Source,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateSelect(QString)));
	QObject::connect(Select,SIGNAL(currentIndexChanged(QString)),this,SIGNAL(changed()));

	if(fieldVS.toObject().value("Source") != QJsonValue::Undefined){
		QString source = fieldVS.toObject().value("Source").toString().split("::").count() > 1 ?fieldVS.toObject().value("Source").toString().split("::")[1]:fieldVS.toObject().value("Source").toString();
		Source->setCurrentIndex(Source->keys.indexOf(QString("ViewStructure::"+source)));
		//	Source->currentIndexChanged(Source->currentIndex());
		}
}

void StructureVieweditSubFeild::filterOnChanged(int index)
{
	if(filterWidget){
		if(index == 0){
			localFilterWidget->setHidden(true);
			}
		else if(index == 1){
			//entityFilter->clear();
			entityFilter->addItems(Select->getItemsText());
			entityFilter->adjustSize();
			QObject::connect(StructureViewGroupsUI::GetUI(),SIGNAL(gotFieldsNames(QStringList)),this,SLOT(fillLocalFilter(QStringList)));
			StructureViewGroupsUI::GetUI()->getFeildsNames();

			localFilterWidget->setHidden(false);
			}
		else if(index == 2){
			localFilterWidget->setHidden(true);
			}
		}
}

void StructureVieweditSubFeild::fillLocalFilter(QStringList feilds)
{
	QObject::disconnect(StructureViewGroupsUI::GetUI(),SIGNAL(gotFieldsNames(QStringList)),this,SLOT(fillLocalFilter(QStringList)));

	if(localFilterWidget){
		localFilter->clear();
		localFilter->addItems(feilds);
		}
	if(!filledLocalfilter){
		localFilter->setCurrentIndex(localFilter->getItemsText().indexOf(fieldVS.toObject().value("Local").toString()));
		localFilter->setCurrentText(fieldVS.toObject().value("Local").toString());
		localFilter->adjustSize();
		entityFilter->setCurrentIndex(entityFilter->getItemsText().indexOf(fieldVS.toObject().value("Entity").toString()));
		entityFilter->setCurrentText(fieldVS.toObject().value("Entity").toString());
		this->filledLocalfilter = true;
		}

}

void StructureVieweditSubFeild::addEquationWidget(QJsonObject data)
{
	StructureVieweditSubFeildEquation* eqElemnet = new StructureVieweditSubFeildEquation(0,equationElements.count() > 0 ?true:false);
	if(!data.isEmpty()){
		//	qDebug() << __FILE__ << __LINE__  << "Fill addEquationWidget"<< data;
		eqElemnet->fill(data);
		}
	equationElements << eqElemnet;
	RemoveBtn* removeEqElement = new RemoveBtn(this,eqElemnet);
	QObject::connect(removeEqElement,SIGNAL(remove(QWidget*)),this,SLOT(removeEqElement(QWidget*)));
	equationWidgetLayout->addWidget(removeEqElement);
}

void StructureVieweditSubFeild::removeEqElement(QWidget* eqElement)
{
	equationElements.removeOne((StructureVieweditSubFeildEquation*)eqElement);
}


void StructureVieweditSubFeild::addNewQuery()
{
    StructureVieweditSubFieldQuery* queryWidget = new StructureVieweditSubFieldQuery();
    QObject::connect(StructureViewGroupsUI::GetUI(),SIGNAL(gotFieldsNames(QStringList)),queryWidget,SLOT(setFieldsNames(QStringList)));
    StructureViewGroupsUI::GetUI()->getFeildsNames();
    queryList.push_back(queryWidget);
    RemoveBtn* removeQuery = new RemoveBtn(this,queryWidget);
    QObject::connect(removeQuery,SIGNAL(remove(QWidget*)),this,SLOT(removeQuery(QWidget*)));
    layout->addRow(removeQuery);
}



void StructureVieweditSubFeild::removeQuery(QWidget* queryWidget)
{
    queryList.removeOne((StructureVieweditSubFieldQuery*) queryWidget);
}

void StructureVieweditSubFeild::paintEvent(QPaintEvent * event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(event);
}


