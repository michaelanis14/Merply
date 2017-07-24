#include "indexui.h"

#include "controller.h"
#include "createeditui.h"

IndexUI::IndexUI(QWidget *parent,const QString document_id) : MainDisplay(parent)
{

	layout = new QVBoxLayout(formPanel);
	this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	layout->setContentsMargins(2,2,2,2);
	layout->setSpacing(0);
	this->setContentsMargins(2,2,2,2);
	this->setObjectName("IndexUI");


	btnCreatNew = new QPushButton("جديد");
	connect(btnCreatNew, SIGNAL(pressed()), this, SLOT(createNew()));
	layout->addWidget(btnCreatNew);

	table = new merplyTabelView(this,false,true);
	QObject::connect(table,SIGNAL(editEntity(int,int)),this,SLOT(editEntity(int,int)));
	QObject::connect(table,SIGNAL(deleteEntity(int,int)),Controller::Get(),SLOT(deleteEntity(int,int)));

	//QDomNode columns = nodek.namedItem("Columns");

	//table->fill(columns,data);

	this->document_id = document_id;
	table->indexTable(document_id);
	table->hideColumns(Controller::Get()->getCachedViewStructure(this->document_id.toInt()));
	layout->addWidget(table);

	createEditUI = new CreateEditUI(0,Controller::Get()->getCachedViewStructure(this->document_id.toInt()),this->table->getModel());


	new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_N), this, SLOT(createNew()));
	//	qDebug() << __FILE__ << __LINE__  <<"Index";

}

void IndexUI::showUI()
{
	table->getModel()->setFilter("");
	MainForm::Get()->ShowDisplay(this);
}

void IndexUI::createNew()
{
	//	Controller::Get()->showCreateEditeStrUI(this->document_id,false);
	table->getModel()->insertRow(table->getModel()->rowCount(QModelIndex()));
	createEditUI->showUI(true);

}

void IndexUI::editEntity(int tbl, int id)
{
	Q_UNUSED(tbl);
	table->getModel()->setFilter("`id` = "+QString::number(id));
	createEditUI->showUI();
}
