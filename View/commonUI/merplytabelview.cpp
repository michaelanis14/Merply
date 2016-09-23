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

#include <QLabel>
#include <QVariant>


//Q_IMPORT_PLUGIN(PrinterSupportPlugin)

merplyTabelView::merplyTabelView(QWidget *parent,QString propertyName) :
	QWidget(parent)
{
	this->setObjectName("merplyTabelView");
	this->setContentsMargins(0,0,0,0);
	this->propertyName = propertyName;
	//	this->model = new QStandardItemModel(this);

	this->setFixedHeight(600);
	layout = new QVBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);





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

	QStringList btnsList;
	btnsList << "Print->Print"<< "Edit->Edit"<< "Delete->Delete";


	controllers = new HControllers(0,btnsList);
	connect(controllers, SIGNAL(btnClicked(const QString&)), this, SLOT(controller_Clicked(QString)));
	controllers->setObjectName("controllers");
	controllers->setEnabled(false);

	layout->addWidget(controllers);
	tableView= new QTableView;
	tableView->setContentsMargins(0,0,0,0);

	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->setSelectionMode(QAbstractItemView::SingleSelection);


	layout->addWidget(tableView);

	this->setAutoFillBackground(true);

	report = new QtRPT(this);




}
void merplyTabelView::controller_Clicked(QString nameAction)
{
	if(tableView){
		QItemSelectionModel *select = tableView->selectionModel();
		if(select && select->hasSelection()){
			QStringList nActon = nameAction.split("->");
			if(nActon.count() > 1){
				QString id = 	model->getRowKey(select->currentIndex().row());
				if(nActon.at(1).compare("Print") == 0){
					//			Controller::Get()->queryIndexView(this->viewStructure.value("document_id").toString());
					}
				else if(nActon.at(1).compare("Edit") == 0){

					Controller::Get()->showCreateEditeStrUI("ViewStructure::"+id.split("::")[0]);
					Controller::Get()->showCreateEditeValueUI(id);
					}
				else if(nActon.at(1).compare("Delete") == 0){
					if(Controller::Get()->ShowQuestion(tr("Are you sure you want to delete?")))
						if(Controller::Get()->deleteDocument(id))
							Controller::Get()->queryIndexView("ViewStructure::"+id.split("::")[0]);

					}
				}
			}
		}
}

void merplyTabelView::selectionChanged(const QItemSelection& , const QItemSelection& )
{
	controllers->setEnabled(true);
}


bool merplyTabelView::fill(QJsonObject columns)
{

	model = new MerplyReportTableModel(columns);
	QObject::connect(model,SIGNAL(done()),this,SLOT(modelFinished()));
	QObject::connect(this,SIGNAL(updateModel(QList<QJsonDocument>)),model,SLOT(fill(QList<QJsonDocument>)));

	QObject::connect(Controller::Get(),SIGNAL(gotReportData(QList<QJsonDocument>)),this,SLOT(gotReportData(QList<QJsonDocument>)));
	Controller::Get()->getReport(columns);
	return true;
}

void merplyTabelView::indexTable(const QString document_id,const QList<QJsonDocument> items, const bool , const bool )
{
	this->items = items;
	controllers->setEnabled(false);
//	if(model){
//		if(model->rowCount( )== items.count()
	//			&& items.first().object().value("document_id").toString().compare(model->getRowKey(0)) == 0){
	//	//	//qDebug() << "Lazyyy" ;
		//	return;
		//		}
		//}
		//qDebug() << "Not Lazy"  ;
		QObject::connect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateHeaderData(QList<QString>)));
		Controller::Get()->getFields(document_id);



}

void merplyTabelView::printTabel(){
	//tabel->hideColumn(0); // don't show the ID



	QString fileName = ":/example4.xml";

	report->loadReport(fileName);
	report->recordCount << this->model->rowCount();
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


	//	qDebug() <<"print" <<id << indexedTable.value(id);
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

void merplyTabelView::gotReportData(QList<QJsonDocument> documents)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotReportData(QList<QJsonDocument>)),this,SLOT(gotReportData(QList<QJsonDocument>)));
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
}

void merplyTabelView::setValue(const int , const QString paramName, QVariant& paramValue, const int )
{
	qDebug() << paramName;
	QJsonValue value;// = indexedTable.value(currenctPrintID).value(paramName);
	if(value != QJsonValue::Undefined)
		paramValue = value.toVariant();
	else return;
}

void merplyTabelView::modelFinished()
{
	//qDebug() << "ModelDone";
	tableView->setModel(model);
	QObject::connect(
				tableView->selectionModel(),
				SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),this,
				SLOT(selectionChanged(const QItemSelection &, const QItemSelection &))
				);
}
