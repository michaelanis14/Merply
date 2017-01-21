#include "structurevieweditsubfeildtablecolumnqueryui.h"
#include "removebtn.h"

#include <QJsonArray>

StructureVieweditSubFeildTableColumnQueryUI::StructureVieweditSubFeildTableColumnQueryUI(QWidget *parent) : QWidget(parent)
{
	this->setContentsMargins(0,0,0,0);
	layout =  new QHBoxLayout(this);
	layout->setContentsMargins(0,0,5,0);
	layout->setSpacing(1);

	queryBox = new QTextEdit();
	layout->addWidget(new QLabel(tr("Query ")));
	layout->addWidget( queryBox);

	add = new QPushButton(tr("Add"));
	layout->addWidget(add);
	QObject::connect(add,SIGNAL(clicked(bool)),this,SLOT(addEntityFilter()));


}

QJsonObject StructureVieweditSubFeildTableColumnQueryUI::save()
{
	QJsonObject save;
	if(!(queryBox->toPlainText().trimmed().isEmpty())){
		//	qDebug() << queryBox->toPlainText();
		save.insert("Query",queryBox->toPlainText());
		}
	QJsonArray entityClmnQuery;
	foreach(StructureVieweditSubFeildTableColumnQuery* clmnQ,entityFilter){
		entityClmnQuery << clmnQ->save();
		}
	if(entityClmnQuery.count() > 0)
		save.insert("ColumnsQuery",entityClmnQuery);

	return save;
}

void StructureVieweditSubFeildTableColumnQueryUI::fill(QJsonObject strct)
{
	if(strct.value("Query") != QJsonValue::Undefined)
		this->queryBox->setText(strct.value("Query").toString());
	foreach(QJsonValue clmQ,strct.value("ColumnsQuery").toArray()){
		addEntityFilter(clmQ.toObject());
		}

}

void StructureVieweditSubFeildTableColumnQueryUI::addEntityFilter(QJsonObject strct)
{
	StructureVieweditSubFeildTableColumnQuery* entityColmnFilter = new StructureVieweditSubFeildTableColumnQuery();
	if(!strct.isEmpty())
		entityColmnFilter->fill(strct);
	entityFilter << entityColmnFilter;
	RemoveBtn* rmvtbn =  new RemoveBtn(0,entityColmnFilter);
	//rmvtbn->hideRemovebtn(true);
	QObject::connect(rmvtbn,SIGNAL(remove(QWidget*)),this,SLOT(removeField(QWidget*)));
	layout->addWidget(rmvtbn);
	layout->addStretch(1);
}

void StructureVieweditSubFeildTableColumnQueryUI::removeField(QWidget* field)
{
	field->setHidden(true);
	entityFilter.removeOne((StructureVieweditSubFeildTableColumnQuery*)field);
}
