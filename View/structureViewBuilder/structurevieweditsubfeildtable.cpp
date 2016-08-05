#include "structurevieweditsubfeildtable.h"
#include "QPushButton"

StructureVieweditSubFeildTable::StructureVieweditSubFeildTable(QWidget *parent,QJsonObject tblStractureView) : QWidget(parent)
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
	layout = new QHBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setMargin(0);
	//layout->addRow();

	StructureVieweditSubFeildTableColumn * clmnWidget;
	if(!tblStractureView.isEmpty() && tblStractureView.value("Columns").isArray()){
		foreach(QJsonValue clmn,tblStractureView.value("Columns").toArray()){
			clmnWidget = new StructureVieweditSubFeildTableColumn(this,clmn.toObject());
			QObject::connect(clmnWidget,SIGNAL(columnChanged()),this,SIGNAL(tableChanged()));
			clmns << clmnWidget;
			layout->addWidget(clmnWidget);
			}
		}
	else{
		clmnWidget = new StructureVieweditSubFeildTableColumn(this,QJsonObject());
		clmns << clmnWidget;
		QObject::connect(clmnWidget,SIGNAL(columnChanged()),this,SIGNAL(tableChanged()));
		layout->addWidget(clmnWidget);

		}

	QPushButton* addColumn = new QPushButton("+");
	QObject::connect(addColumn,SIGNAL(pressed()),this,SLOT(addColumn()));
	QObject::connect(addColumn,SIGNAL(pressed()),this,SIGNAL(tableChanged()));

	layout->addWidget(addColumn);

}

QJsonObject StructureVieweditSubFeildTable::save()
{
	QJsonObject saveTable;
	saveTable.insert("Type","Table");
	QJsonArray clmnsArray;
	if(!clmns.isEmpty()){
		foreach(StructureVieweditSubFeildTableColumn* clmn,clmns){
			clmnsArray << clmn->save();
			}
		saveTable.insert("Columns",clmnsArray);
		}
	return saveTable;
}

QList<QJsonDocument> StructureVieweditSubFeildTable::getClmnsSources()
{
	QList<QJsonDocument> sourcesList;
	if(!clmns.isEmpty()){
		foreach(StructureVieweditSubFeildTableColumn* clmn,clmns){
			sourcesList.append(clmn->getSource()->getCurrentJsonItem());
			}
		}
	return sourcesList;
}

void StructureVieweditSubFeildTable::addColumn()
{
	StructureVieweditSubFeildTableColumn *clmnWidget = new StructureVieweditSubFeildTableColumn(this,QJsonObject());
	clmns << clmnWidget;
	QObject::connect(clmnWidget,SIGNAL(columnChanged()),this,SIGNAL(tableChanged()));
	layout->addWidget(clmnWidget);

}



