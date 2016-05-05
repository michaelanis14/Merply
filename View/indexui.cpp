#include "indexui.h"

#include "controller.h"
#include "createeditui.h"

IndexUI::IndexUI(QWidget *parent) : MainDisplay(parent)
{

	layout = new QVBoxLayout(this);
	layout->setContentsMargins(2,2,2,2);
	layout->setSpacing(0);
	this->setContentsMargins(2,2,2,2);
	this->setObjectName("IndexUI");


	btnCreatNew = new QPushButton("Create New");
	connect(btnCreatNew, SIGNAL(pressed()), this, SLOT(createNew()));
	layout->addWidget(btnCreatNew);

	table = new merplyTabelView(this);

	//QDomNode columns = nodek.namedItem("Columns");

	//table->fill(columns,data);


	layout->addWidget(table);


}
IndexUI* IndexUI::p_instance = 0;
void IndexUI::ShowUI(QString id) {
	//qDebug() << id;
	if(id.isEmpty())
		return;
	if(p_instance == 0)
		p_instance = new IndexUI();
	p_instance->clear();
	p_instance->fill(id);
	MainForm::Get()->ShowDisplay(p_instance);
}

void IndexUI::clear()
{
	this->table->tabel->clear();
}

void IndexUI::fill(QString id)
{
	this->id = id;
	QStringList idNumber = id.split("::");
	if(idNumber.count() > 1)
		this->id = idNumber.first();
/*
	xmlNode = Controller::Get()->addStyle(this->id);
	QList<QJsonDocument> all = Controller::Get()->getAll(this->id,"");

	if(!Database::Get()->getLastKeyID().isEmpty()){
		Controller::Get()->getDoc(Database::Get()->getLastKeyID());

		///////Lazy loading
		int MAX_COUNTER = 14;
		int i = 0;
		while(i < MAX_COUNTER && !Controller::Get()->documentInList(all,Database::Get()->getLastKeyID())){
			all = Controller::Get()->getAll(this->id,"");
			i++;
			//qDebug() << "LazyLoading" << Database::Get()->getLastKeyID();
			}
		//qDebug() << Database::Get()->getDocument();
		table->indexTable(xmlNode,all,true,true);
		Database::Get()->setLastKeyID("");
		}
	else{
		table->indexTable(xmlNode,all,true,true);
		}

*/
}

void IndexUI::createNew()
{
	if(!this->id.isEmpty()){

		//CreateEditUI::ShowUI(this->id);
		}
}
