#include "structurevieweditsubfeildtable.h"



#include "QPushButton"
#include "removebtn.h"

StructureVieweditSubFeildTable::StructureVieweditSubFeildTable(QWidget *parent) : QWidget(parent)
{
	this->setContentsMargins(0,0,5,0);
	this->setObjectName("StructureVieweditSubFeildTable");
	this->clmns = QList<StructureVieweditSubFeildTableColumn*>();
	/*
	layout = new QFormLayout(this);
	layout->setContentsMargins(0,0,5,0);
	layout->setSpacing(1);
	layout->setAlignment(Qt::AlignLeft);
	layout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
	layout->setLabelAlignment(Qt::AlignLeft);
*/

	mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(0,0,0,0);
	mainLayout->setSpacing(0);
	mainLayout->setMargin(0);

	QWidget* subFieldTableWidget = new QWidget(this);
	layout = new QHBoxLayout(subFieldTableWidget);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setMargin(0);

	addEnable = new QCheckBox;
	layout->addWidget(new QLabel(tr("Add ")));
	layout->addWidget( addEnable);
	removeEnable = new QCheckBox;
	layout->addWidget(new QLabel(tr("Remove ")));
	layout->addWidget( removeEnable);
	editEnable = new QCheckBox;
	layout->addWidget(new QLabel(tr("Edit ")));
	layout->addWidget( editEnable);

	queryUI = new StructureVieweditSubFeildTableColumnQueryUI(this);

	mainLayout->addWidget(subFieldTableWidget);
	mainLayout->addWidget(queryUI);

	//////
	///
	/// //layout->addRow();
}

QJsonObject StructureVieweditSubFeildTable::save()
{
	QJsonObject saveTable;
	saveTable.insert("Type","Table");
	saveTable.insert("Add",addEnable->isChecked());
	saveTable.insert("Edit",editEnable->isChecked());
	saveTable.insert("Remove",removeEnable->isChecked());

	QJsonObject querySave = queryUI->save();
	if(!querySave.isEmpty())
		saveTable.insert("QueryUI",querySave);
	//
	QJsonArray clmnsArray;
	if(!clmns.isEmpty()){
		foreach(StructureVieweditSubFeildTableColumn* clmn,clmns){
			clmnsArray << clmn->save();
			}
		saveTable.insert("Columns",clmnsArray);
		}
	return saveTable;
}

QVector<QJsonDocument> StructureVieweditSubFeildTable::getClmnsSources(ERPComboBox* excludeSource)
{
	QVector<QJsonDocument> sourcesList;
	if(clmns.first() && !clmns.isEmpty()){
		foreach(StructureVieweditSubFeildTableColumn* clmn,clmns){
			if(clmn->getSource() != (excludeSource)){
				QJsonDocument doc = clmn->getSource()->getCurrentJsonItem();
				QJsonObject objWHeader= doc.object();
				objWHeader.insert("clmnHeader",clmn->header->text());
				sourcesList.append(QJsonDocument(objWHeader));
				}
			}
		}
	return sourcesList;
}

void StructureVieweditSubFeildTable::fill(QJsonObject tblStractureView)
{
	this->tblStractureView = tblStractureView;
	if(tblStractureView.value("Add") == QJsonValue::Undefined)
		this->addEnable->setChecked(true);
	else this->addEnable->setChecked(tblStractureView.value("Add").toBool());
	if(tblStractureView.value("Edit") == QJsonValue::Undefined)
		this->editEnable->setChecked(true);
	else this->editEnable->setChecked(tblStractureView.value("Edit").toBool());
	if(tblStractureView.value("Remove") == QJsonValue::Undefined)
		this->removeEnable->setChecked(true);
	else this->removeEnable->setChecked(tblStractureView.value("Remove").toBool());

	if(tblStractureView.value("QueryUI") != QJsonValue::Undefined)
		queryUI->fill(tblStractureView.value("QueryUI").toObject());
	//
	clmns.clear();
	StructureVieweditSubFeildTableColumn * clmnWidget;
	if(!tblStractureView.isEmpty() && tblStractureView.value("Columns").isArray()){
		foreach(QJsonValue clmn,tblStractureView.value("Columns").toArray()){
			clmnWidget = new StructureVieweditSubFeildTableColumn(this,clmn.toObject());
			clmnWidget->fill(clmn.toObject());
			QObject::disconnect(clmnWidget,SIGNAL(columnChanged()),this,SIGNAL(tableChanged()));
			QObject::connect(clmnWidget,SIGNAL(columnChanged()),this,SIGNAL(tableChanged()));
			clmns << clmnWidget;
			RemoveBtn* removeClmnBtn = new RemoveBtn(this,clmnWidget);
			QObject::connect(removeClmnBtn,SIGNAL(remove(QWidget*)),this,SLOT(removColumn(QWidget*)));

			layout->addWidget(removeClmnBtn);
			}
		}
	else{
		clmnWidget = new StructureVieweditSubFeildTableColumn(this,QJsonObject());
		clmns << clmnWidget;
		QObject::disconnect(clmnWidget,SIGNAL(columnChanged()),this,SIGNAL(tableChanged()));
		QObject::connect(clmnWidget,SIGNAL(columnChanged()),this,SIGNAL(tableChanged()));
		RemoveBtn* removeClmnBtn = new RemoveBtn(this,clmnWidget);
		QObject::connect(removeClmnBtn,SIGNAL(remove(QWidget*)),this,SLOT(removColumn(QWidget*)));

		layout->addWidget(removeClmnBtn);

		}
	QPushButton* addColumn = new QPushButton("+");
	QObject::connect(addColumn,SIGNAL(pressed()),this,SLOT(addColumn()));
	QObject::disconnect(addColumn,SIGNAL(pressed()),this,SIGNAL(tableChanged()));
	QObject::connect(addColumn,SIGNAL(pressed()),this,SIGNAL(tableChanged()));

	layout->addWidget(addColumn);
}

QStringList StructureVieweditSubFeildTable::getHeaders()
{
	QStringList headers;
	if(!tblStractureView.isEmpty() && tblStractureView.value("Columns").isArray()){
		foreach(QJsonValue clmn,tblStractureView.value("Columns").toArray()){
			headers << clmn.toObject().value("Header").toString();
			}
		}
	return headers;
}

void StructureVieweditSubFeildTable::addColumn()
{
	StructureVieweditSubFeildTableColumn *clmnWidget = new StructureVieweditSubFeildTableColumn(this,QJsonObject());
	clmns << clmnWidget;
	QObject::disconnect(clmnWidget,SIGNAL(columnChanged()),this,SIGNAL(tableChanged()));
	QObject::connect(clmnWidget,SIGNAL(columnChanged()),this,SIGNAL(tableChanged()));
	RemoveBtn* removeClmnBtn = new RemoveBtn(this,clmnWidget);
	QObject::connect(removeClmnBtn,SIGNAL(remove(QWidget*)),this,SLOT(removColumn(QWidget*)));
	layout->addWidget(removeClmnBtn);

}

void StructureVieweditSubFeildTable::removColumn(QWidget* clmn)
{
	clmns.removeOne((StructureVieweditSubFeildTableColumn*)clmn);
}



