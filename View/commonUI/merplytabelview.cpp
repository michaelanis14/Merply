/*************************************
**   Created on:  12/4/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/

#include"merplytabelview.h"
#include "merplytablecontrollers.h"
#include "QPrinter"
#include "QPrintDialog"
#include "controller.h"
#include "printcontroller.h"
#include "qtooltipper.h"


#include <QLabel>
#include <QVariant>


//Q_IMPORT_PLUGIN(PrinterSupportPlugin)

merplyTabelView::merplyTabelView(QWidget *parent, bool add, bool edit) :
	QWidget(parent)
{
	this->add = add;
	this->edit = edit;
	this->setObjectName("merplyTabelView");
	this->setContentsMargins(0,0,0,0);
	//	this->model = new QStandardItemModel(this);

	//this->setFixedHeight(600);
	layout = new QVBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	//layout->setSpacing(0);





	//tabel->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//tabel->hideColumn(0); // don't show the ID
	//tabel->sortByColumn(0,Qt::DescendingOrder);
	//tabel->setSortingEnabled(true);
	//tabel->resizeColumnsToContents();
	//tabel->resizeRowsToContents();
	//	tabel->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	//tabel->setSelectionBehavior(QAbstractItemView::SelectRows);
	//tabel->setSelectionMode(QAbstractItemView::SingleSelection);

	//tabel->setItemDelegate(new QSqlRelationalDelegate(tabel));

	lblLayout = new QHBoxLayout();
	lblLayout->setContentsMargins(0,0,0,0);
	lblLayout->setContentsMargins(0,2,0,0);



	queryUI = new MerplyQueryUI(this,true);
	layout->addWidget(queryUI);

	controllers = new HControllers;
	controllers->setObjectName("controllers");
	layout->addWidget(controllers);


	tableView= new QTableView;
	tableView->setContentsMargins(0,0,0,0);
	if(edit){
		controllers->setEnabled(false);
		}

	connect(controllers, SIGNAL(btnClicked(const QString&)), this, SLOT(controller_Clicked(QString)));
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);

	layout->addWidget(tableView);

	this->setAutoFillBackground(true);

	report = new QtRPT(this);


	initHController(QJsonObject());
	this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//this->tableView->setSortingEnabled(true);

}
void merplyTabelView::controller_Clicked(QString nameAction)
{
	if(tableView){
		QStringList nActon = nameAction.split("->");

		if(nActon.count() > 1){
			if(nActon.at(1).compare("Add") == 0){

				if(model->insertRow(model->rowCount(QModelIndex()))){
					//qDebug() << (model->getRowsCount()-1)<< (model->getRowsCount());
					QModelIndex index = tableView->model()->index((model->getRowsCount()-1),0, QModelIndex());
					tableView->setCurrentIndex(index);
					tableView->edit(index);
					//tableView->e
					}
				//model->rowsInserted(QModelIndex(),);
				return;

				}
			else if(nActon.at(1).compare("Remove") == 0){
				QModelIndexList indexes  = tableView->selectionModel()->selectedRows();
				int countRow = indexes.count();
				for( int i = countRow; i > 0; i--)
					model->removeRow( indexes.at(i-1).row(), QModelIndex());
				// model->removeRows( tableView->selectedIndexes().first().row(), tableView->selectedIndexes().count());
				}
			}
		QItemSelectionModel *select = tableView->selectionModel();
		if(select && select->hasSelection()){
			QString id = 	model->getRowKey(select->currentIndex().row());
			//qDebug() << __FILE__ << __LINE__  << id;
			if(nActon.count() > 1){
				if(nActon.at(1).compare("Print") == 0){
					PrintController::Get()->printEntity(id);
					//////////////				Controller::Get()->queryIndexView(this->viewStructure.value("document_id").toString());
					}
				else if(nActon.at(1).compare("Edit") == 0){

					Controller::Get()->showCreateEditeStrUI("ViewStructure::"+id.split("::")[0],false);
					Controller::Get()->showCreateEditeValueUI(id);
					}
				else if(nActon.at(1).compare("Delete") == 0){
					if(Controller::Get()->ShowQuestion(tr("Are you sure you want to delete?").append(" "+id))){
						Controller::Get()->deleteEntity(id);
						queryUI->generateQuery();
						//Controller::Get()->queryIndexView("ViewStructure::"+id.split("::")[0]);
						}
					}
				}
			}
		}
}

void merplyTabelView::selectionChanged(const QItemSelection& , const QItemSelection& )
{
	controllers->setEnabled(true);
	//qDebug() << __FILE__ << __LINE__  << "SELECTIONN";
}

void merplyTabelView::resizeTabelToContets()
{
	if(this->model->getColmnsCount() > 6 && this->model->getRowsCount() < 100){
		this->tableView->resizeColumnsToContents(); //TODO : BAD PERFORMANCE
		}
	if(this->model->getRowsCount() < 40){
		this->tableView->setMinimumHeight(tableView->rowHeight(1)*this->model->getRowsCount()+40);
		}
}


bool merplyTabelView::fill(QJsonObject columns,QString filter)
{
	//TODO: Better connect to Signals
	//	qDebug() << __FILE__ << __LINE__ << "fill";
	model = new MerplyReportTableModel(columns);

	bool initDelegate = true;
	//	queryUI->fill(columns);
	if(columns.value("QueryUI") != QJsonValue::Undefined){
		//	QObject::connect(this,SIGNAL(updateModel(QVector<QJsonDocument>)),model,SLOT(fillQuery(QVector<QJsonDocument>)));
		//

		//	QObject::disconnect(model,SIGNAL(done()),this,SLOT(modelFinished()));
		QObject::connect(model,SIGNAL(done()),this,SLOT(modelFinished()));

		queryUI->fillEntityQuery(columns.value("QueryUI").toObject());
		QObject::disconnect(queryUI,SIGNAL(queryResults(QVector<QJsonDocument>)),model,SLOT(fillQuery(QVector<QJsonDocument>)));
		QObject::connect(queryUI,SIGNAL(queryResults(QVector<QJsonDocument>)),model,SLOT(fillQuery(QVector<QJsonDocument>)));

		//	}

		}
	else if(columns.value("Add") != QJsonValue::Undefined){
		//qDebug() << "ADD" << columns;
		if(columns.value("Add").toBool()){
			foreach(QJsonValue clmn,columns.value("Columns").toArray()){
				if(clmn.toObject().value("Source") != QJsonValue::Undefined){
					initDelegate = false;
					columns.remove("Add");
					QObject::disconnect(queryUI,SIGNAL(queryResults(QVector<QJsonDocument>)),model,SLOT(fillAddtoTable(QVector<QJsonDocument>)));
					QObject::connect(queryUI,SIGNAL(queryResults(QVector<QJsonDocument>)),model,SLOT(fillAddtoTable(QVector<QJsonDocument>)));
					queryUI->fillAddtoTable(columns.value("Columns").toArray());

					break; //TODO: SEVERAL INPUTS
					}
				}



			}
		}

	else {
		//TODO : Else normal fill
		QObject::disconnect(Controller::Get(),SIGNAL(gotReportData(QVector<QJsonDocument>)),this,SLOT(gotReportData(QVector<QJsonDocument>)));
		QObject::connect(Controller::Get(),SIGNAL(gotReportData(QVector<QJsonDocument>)),this,SLOT(gotReportData(QVector<QJsonDocument>)));
		Controller::Get()->getReport(columns,filter);

		}
	if(initDelegate)
		initDelegateClmns(columns); //TODO: Condition specific to init it.
	initHController(columns);
	return true;
}

bool merplyTabelView::fillLocalSource(QJsonObject columns, QString filter)
{
	//if(model)
	//	model->deleteLater();
	//qDebug() << __FILE__ << __LINE__ << "fillLocalSource";
	model = new MerplyReportTableModel(columns);
	//QObject::disconnect(model,SIGNAL(done()),this,SLOT(modelFinished()));
	//QObject::connect(model,SIGNAL(done()),this,SLOT(modelFinished()));
	QObject::connect(this,SIGNAL(updateModel(QVector<QJsonDocument>)),model,SLOT(fillLocalSource(QVector<QJsonDocument>)));

	QObject::connect(Controller::Get(),SIGNAL(gotReportData(QVector<QJsonDocument>)),this,SLOT(gotReportData(QVector<QJsonDocument>)));
	Controller::Get()->getReport(columns,filter);

	initHController(columns);
	initDelegateClmns(columns);


	return true;
}

//this just adds data to a tabel that already been init
bool merplyTabelView::fillText(QJsonObject data)
{
	//qDebug() << __FILE__ << __LINE__ << data;
	QJsonArray dataArray = data.value("merplyTabel").toArray();
	if(!dataArray.isEmpty()){
		QObject::disconnect(model,SIGNAL(done()),this,SLOT(modelFinished()));
		QObject::connect(model,SIGNAL(done()),this,SLOT(modelFinished()));
		model->fillText(dataArray);
		}
	else modelFinished();

	//initHController(QJsonObject());
	return true;
}

void merplyTabelView::indexTable(const QString document_id,const QVector<QJsonDocument> items)
{
	this->items = items;
	this->indexDocument_id = document_id;
	controllers->setEnabled(false);
	//	if(model){
	//		if(model->rowCount( )== items.count()
	//			&& items.first().object().value("document_id").toString().compare(model->getRowKey(0)) == 0){
	//	//	//qDebug() << __FILE__ << __LINE__  << "Lazyyy" ;
	//	return;
	//		}
	//}
	//qDebug() << __FILE__ << __LINE__  << "Not Lazy"  ;
	//

	//QObject::connect(Controller::Get(),SIGNAL(gotFieldsData(QVector<QJsonDocument>)),this,SLOT(fill(QVector<QJsonDocument>)));
	//qDebug() << __FILE__ << __LINE__  << "indexTable" << document_id ;
	QObject::connect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateHeaderData(QList<QString>)));
	Controller::Get()->getIndexHeader(document_id);


	//	initHController(QJsonObject());

}

QJsonObject merplyTabelView::save()
{
	tableView->setDisabled(true);
	QJsonObject table;
	table.insert("merplyTabel",this->model->getJsonData());
	if(this->model->getRemovedRows().count() > 0)
		table.insert("RemovedRows",this->model->getRemovedRows());
	//qDebug() << __FILE__ << __LINE__  << this->model->getJsonData();
	return table;
}

MerplyReportTableModel* merplyTabelView::getModel() const
{
	return model;
}

QModelIndex merplyTabelView::getIndexAt(QPoint position)
{
	return tableView->indexAt(position);
}

QTableView* merplyTabelView::getTableView() const
{
	return tableView;
}

void merplyTabelView::generateQuery(int limit)
{
	if(this->queryUI){
		this->queryUI->generateQuery(limit);
		}
}

void merplyTabelView::initHController(QJsonObject columns)
{
	QStringList btns;
	if(columns.isEmpty()){
		if(add){
			btns << "أضف->Add" << "Remove->Remove";
			}
		if(edit){
			btns << "طباعه->Print"<< "تعديل->Edit"<< "مسح->Delete";
			}
		}
	else{
		//	qDebug() << __FILE__ << __LINE__  << "CON : "<< add<<edit<<columns;
		if(edit){
			btns << "طباعه->Print";
			}

		if(add && columns.value("Add").toBool())
			btns <<"أضف->Add";
		if(edit && columns.value("Edit").toBool())
			btns <<"تعديل->Edit";
		if(add && columns.value("Remove").toBool())
			btns <<"مسح->Remove";
		}
	controllers->clear();
	controllers->fill(btns);
}

void merplyTabelView::initDelegateClmns(QJsonObject columns)
{
	int i = 0;
	foreach(QJsonValue clmn,columns.value("Columns").toArray()){
		if(clmn.toObject().value("Type").toString().compare("Refrence") == 0){
			MTabelCombobox *comboDelegate = new MTabelCombobox(this,clmn.toObject());
			tableView->setItemDelegateForColumn(i,comboDelegate);
			//delegateItems << comboDelegate;
			//qDebug() << "DEEE";
			}
		i++;
		}
}

void merplyTabelView::printTabel(){
	//tabel->hideColumn(0); // don't show the ID



	QString fileName = ":/example4.xml";

	report->loadReport(fileName);
	report->recordCount << this->model->rowCount();
	QObject::disconnect(report, SIGNAL(setValue(const int, const QString, QVariant&, const int)),
						this->model, SLOT(setValue(const int, const QString, QVariant&, const int)));

	QObject::connect(report, SIGNAL(setValue(const int, const QString, QVariant&, const int)),
					 this->model, SLOT(setValue(const int, const QString, QVariant&, const int)));
	report->printExec();

	/*
	if(tabel->model()->headerData(tabel->model()->columnCount()-2, Qt::Horizontal).toString().contains("Created"))
		tabel->hideColumn(tabel->model()->columnCount()-2); // don't show Created On

	if(tabel->model()->headerData(tabel->model()->columnCount()-1, Qt::Horizontal).toString().contains("Edited"))
		tabel->hideColumn(tabel->model()->columnCount()-1); // don't show Edited On

	QString strStream;
	QTextStream out(&strStream);

	const int rowCount = tabel->model()->rowCount();
	const int columnCount = tabel->model()->columnCount();

	out <<  "<html>\n"
			"<head>\n"
			"<meta Content=\"Text/html; charset=Windows-1251\">\n"
		 <<  QString("<title>%1</title>\n").arg("strTitle")
		  <<  "</head>\n"
			  "<body bgcolor=#ffffff link=#5000A0>\n"
			  "<table border=1 cellspacing=0 cellpadding=2>\n";

	// headers
	out << "<thead><tr bgcolor=#f0f0f0>";
	for (int column = 0; column < columnCount; column++)
		if (!tabel->isColumnHidden(column))
			out << QString("<th>%1</th>").arg(tabel->model()->headerData(column, Qt::Horizontal).toString());
	out << "</tr></thead>\n";

	// data table
	for (int row = 0; row < rowCount; row++) {
		out << "<tr>";
		for (int column = 1; column < columnCount; column++) {
			if (!tabel->isColumnHidden(column)) {
				//	QString data = tabel->model()->data(tabel->model()->index(row, column)).toString().simplified();
				QString data = ((QLabel*)tabel->cellWidget(row,column))->text();
				out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
				}
			}
		out << "</tr>\n";
		}
	out <<  "</table>\n"
			"</body>\n"
			"</html>\n";

	QTextDocument *document = new QTextDocument();
	document->setHtml(strStream);

	//QPrinter printer;
	//printer.setPageSize(printer.A4);
	//printer.setPageMargins(10, 10, 0, 0, printer.Millimeter);
	//document->setPageSize(QSizeF(printer.pageRect().size()));
	//printer.setOutputFormat(QPrinter::NativeFormat);


	QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
	if (dialog->exec() == QDialog::Accepted) {
		document->print(&printer);
		}

	QString filename = QFileDialog::getSaveFileName(0, QString("Save file"),QString(),QString(),0,0);

	QPdfWriter writer(filename);
	QPainter painter(&writer);
	QTransform TPiXEL = QTransform::fromScale(
				painter.device()->physicalDpiX() / 75.400, //25.400
				painter.device()->physicalDpiY() / 75.400);
	painter.setWorldTransform(TPiXEL, false);
	//printer->setFullPage(true);
	document->drawContents(&painter);
	painter.end();

	if(tabel->model()->headerData(tabel->model()->columnCount()-2, Qt::Horizontal).toString().contains("Created"))
		tabel->showColumn(tabel->model()->columnCount()-2); // don't show Created On

	if(tabel->model()->headerData(tabel->model()->columnCount()-1, Qt::Horizontal).toString().contains("Edited"))
		tabel->showColumn(tabel->model()->columnCount()-1); // don't show Edited On


	delete document;*/

}

void merplyTabelView::printEntity(const QString& id)
{
	QObject::disconnect(report);
	QObject::disconnect(report, SIGNAL(setValue(const int, const QString, QVariant&, const int)),
						this, SLOT(setValue(const int, const QString, QVariant&, const int)));


	qDebug() << __FILE__ << __LINE__  <<"print" <<id;
	currenctPrintID = id;
	QString fileName = ":/example4.xml";

	report->loadReport(fileName);
	//report->recordCount << tabel->rowCount();
	if(this->model)
		QObject::disconnect(report, SIGNAL(setValue(const int, const QString, QVariant&, const int)),
							this->model, SLOT(setValue(const int, const QString, QVariant&, const int)));
	QObject::connect(report, SIGNAL(setValue(const int, const QString, QVariant&, const int)),
					 this, SLOT(setValue(const int, const QString, QVariant&, const int)));
	report->printExec();
}

void merplyTabelView::gotReportData(QVector<QJsonDocument> documents)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotReportData(QVector<QJsonDocument>)),this,SLOT(gotReportData(QVector<QJsonDocument>)));
	emit updateModel(documents);

}

void merplyTabelView::updateHeaderData(QList<QString> headerItems)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateHeaderData(QList<QString>)));

	QJsonObject clmnObj = QJsonObject();
	clmnObj.insert("clmnsHeader",QJsonValue::fromVariant(QVariant(headerItems)));
	model = new MerplyReportTableModel(clmnObj);
	QObject::connect(model,SIGNAL(done()),this,SLOT(modelFinished()));
	model->fillIndexTabel(items);

	if(!indexDocument_id.isEmpty()){
		QObject::disconnect(queryUI,SIGNAL(queryResults(QVector<QJsonDocument>)),model,SLOT(fillIndexTabel(QVector<QJsonDocument>)));
		QObject::connect(queryUI,SIGNAL(queryResults(QVector<QJsonDocument>)),model,SLOT(fillIndexTabel(QVector<QJsonDocument>)));
		queryUI->fillDocumentID(indexDocument_id);
		}




}

void merplyTabelView::setValue(const int , const QString paramName, QVariant& paramValue, const int )
{
	qDebug() << __FILE__ << __LINE__  <<"setValue TabelView"<< paramName;
	QJsonValue value;// = indexedTable.value(currenctPrintID).value(paramName);
	if(value != QJsonValue::Undefined)
		paramValue = value.toVariant();
	else return;
}

void merplyTabelView::modelFinished()
{
	//qDebug() << __FILE__ << __LINE__  << "ModelDone" <<model << model->getRowsCount();
	QObject::disconnect(model,SIGNAL(done()),this,SLOT(modelFinished()));

	tableView->setModel(model);
	tableView->viewport()->installEventFilter(new QToolTipper(tableView));




	QObject::disconnect(
				tableView->selectionModel(),
				SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),this,
				SLOT(selectionChanged(const QItemSelection &, const QItemSelection &))
				);
	QObject::connect(
				tableView->selectionModel(),
				SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),this,
				SLOT(selectionChanged(const QItemSelection &, const QItemSelection &))
				);

	QObject::connect(model,SIGNAL(done()),this,SLOT(resizeTabelToContets()));

	//this->repaint();
}

