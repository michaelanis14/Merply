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



//Q_IMPORT_PLUGIN(PrinterSupportPlugin)

merplyTabelView::merplyTabelView(QWidget *parent,QString propertyName) :
	QWidget(parent)
{
	this->setObjectName("merplyTabelView");
	this->setContentsMargins(0,0,0,0);
	this->propertyName = propertyName;
	//	this->model = new QStandardItemModel(this);


	layout = new QVBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);

	tabel = new QTableWidget(this);


	tabel->setContentsMargins(0,0,0,0);


	//tabel->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//tabel->hideColumn(0); // don't show the ID
	//tabel->sortByColumn(0,Qt::DescendingOrder);
	tabel->setSortingEnabled(true);
	//tabel->resizeColumnsToContents();
	//tabel->resizeRowsToContents();
	//	tabel->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	//tabel->setSelectionBehavior(QAbstractItemView::SelectRows);
	//tabel->setSelectionMode(QAbstractItemView::SingleSelection);

	//tabel->setItemDelegate(new QSqlRelationalDelegate(tabel));

	lblLayout = new QHBoxLayout();
	lblLayout->setContentsMargins(0,0,0,0);
	lblLayout->setContentsMargins(0,2,0,0);


	print = new QLabel("print",this);
	print->setObjectName("print");
	lblLayout->addWidget(print);

	layout->addItem(lblLayout);
	layout->addWidget(tabel);



	tableView= new QTableView;
	layout->addWidget(tableView);
	tableView->setHidden(true);
	this->setAutoFillBackground(true);

	report = new QtRPT(this);




}

QString merplyTabelView::save(QString propertyName)
{
	QString list;

	int rowCount = this->tabel->model()->rowCount();
	int cloumnCount = this->tabel->model()->columnCount();
	/*
	for(int i = 0; i < rowCount; i++){
	list += this->tabel->model()->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
	//if(i<rowCount-1)
		list +="->';
		}
		*/
	for(int i = 0; i < rowCount; i++){
		list+=propertyName;
		list+="->";
		for(int j = 0; j < cloumnCount;j++){

			//qDebug() <<this->tabel->model()->data(this->tabel->model()->index(i,j)).toString();
			list +=this->tabel->model()->data(this->tabel->model()->index(i,j)).toString();
			if(j<cloumnCount-1)
				list +="->";
			}
		if(i<rowCount-1)
			list +="->";
		}
	return list;
}

bool merplyTabelView::fill(QJsonObject columns)
{

	tabel->setHidden(true);
	tableView->setHidden(false);
	model = new MerplyReportTableModel(columns);
	QObject::connect(this,SIGNAL(updateModel(QList<QJsonDocument>)),model,SLOT(fill(QList<QJsonDocument>)));

	tableView->setModel(model);


	QObject::connect(Controller::Get(),SIGNAL(gotReportData(QList<QJsonDocument>)),this,SLOT(gotReportData(QList<QJsonDocument>)));
	Controller::Get()->getReport(columns);

	return true;
	/*
	if(columns.value("Columns").isArray()){
		QJsonArray arr = (columns.value("Columns").toArray());
		tabel->setColumnCount(arr.count());
		int i = 0;
		foreach(QJsonValue clmn,columns.value("Columns").toArray()){

			tabel->setHorizontalHeaderItem(i, new QTableWidgetItem(QString(clmn.toObject().value("Header").toString())));
			//QStandardItem *data = new QStandardItem(QString(column.namedItem("Value").namedItem("ValueType").firstChild().nodeValue()));
			//model->setItem(i,0,data);
			if(clmn.toObject().value("Type").toString().compare("Database") == 0){
				QList<QString> columnData;

				//TODO :: commented to ease the transition to the new database slots
				//			columnData << Controller::Get()->getListItems(clmn.toObject().value("Source").toString(),clmn.toObject().value("Select").toString());
				if(tabel->rowCount()<columnData.count())
					tabel->setRowCount(columnData.count());



				//qDebug() << columnData;
				if(columnData.count() > 0){
					for (int j = 0; j <columnData.count(); j++) {
						//qDebug() << columnData.at(j);
						QTableWidgetItem *item = new QTableWidgetItem( QString(columnData.at(j)));
						//           tw.setItem( i, j, item );

						//QLabel *value = new QLabel(columnData.at(j));
						//qDebug() << value->text();
						item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
						tabel->setItem(j,i,item);
						}

					//qDebug() <<"dQWDSDF"<<  << ;
					}

				}
			i++;
			}
		}



	if(!data.isEmpty() && data.value(propertyName).isArray()){
		//	tabel->setRowCount(data.value(propertyName).toArray().count());
		//qDebug() <<"AA"<< data.value(propertyName).toArray();
		if(tabel->rowCount() <  data.value(propertyName).toArray().count())
			tabel->setRowCount( data.value(propertyName).toArray().count());
		qDebug() << "clmn DATA " <<data.value(propertyName);
		for(int i = 0; i < data.value(propertyName).toArray().count(); i++){

			//qDebug() <<"I"<< data.value(propertyName).toArray()[i];
			if(data.value(propertyName).toArray()[i].isArray())
				//	tabel->setColumnCount(data.value(propertyName).toArray()[i].toArray().count());
				if(tabel->columnCount() < data.value(propertyName).toArray()[i].toArray().count())
					tabel->setColumnCount(data.value(propertyName).toArray()[i].toArray().count());
			for(int j = 0; j < data.value(propertyName).toArray()[i].toArray().count(); j++){
				//qDebug() <<"JJ"<< data.value(propertyName).toArray()[i].toArray()[j] ;
				QLabel *item = new QLabel(QString(data.value(propertyName).toArray()[i].toArray()[j].toString()));
				//QLable *value = new QStandardItem(QString(data.value(propertyName).toArray()[i].toArray()[j].toString()));
				//model->setItem(i,j,value);
				this->tabel->setCellWidget(i,j,item);
				}
			}
		//qDebug() << data.value(propertyName) << propertyName;
		}

	//this->tabel->setMaximumHeight(this->tabel);
	//	this->tabel->viewh;
	//this->tabel->showRow();
	//this->tabel->showRow(model->rowCount());

	//this->tabel->setC(model);

	return true;
	*/

}

void merplyTabelView::indexTable(const QString document_id,const QList<QJsonDocument> items, const bool , const bool )
{
	//model->setHorizontalHeaderItem(i, new QStandardItem(QString(column.namedItem("Title").firstChild().nodeValue())));
	this->items = items;
	QObject::connect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateHeaderData(QList<QString>)));
	//QString documentid = items.first().object().value("document_id").toString().split("::")[0];
	//qDebug() << documentid;
	Controller::Get()->getFields(document_id);

}

void merplyTabelView::clear()
{
	this->tabel->model()->removeRows(0,this->tabel->model()->rowCount());

}


void merplyTabelView::mousePressEvent(QMouseEvent *event){

	QLabel * child = static_cast<QLabel*>(childAt(event->pos()));
	if(!child)
		return;
	else {
		if(child->objectName() == "print"){
			printTabel();
			}
		else if(child->objectName() == "remove"){
			}
		else if(child->objectName() == "remove"){

			}
		}
	QWidget::mousePressEvent(event);

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


	qDebug() <<"print" <<id << indexedTable.value(id);
	currenctPrintID = id;
	QString fileName = ":/example4.xml";

	report->loadReport(fileName);
	report->recordCount << tabel->rowCount();
	if(this->model)
		QObject::disconnect(report, SIGNAL(setValue(const int, const QString, QVariant&, const int)),
							this->model, SLOT(setValue(const int, const QString, QVariant&, const int)));
	QObject::connect(report, SIGNAL(setValue(const int, const QString, QVariant&, const int)),
					 this, SLOT(setValue(const int, const QString, QVariant&, const int)));
	report->printExec();
}

void merplyTabelView::editEntity(const QString& id)
{
	qDebug() <<"editEntity" <<id;
	Controller::Get()->showCreateEditeStrUI("ViewStructure::"+id.split("::")[0]);
	Controller::Get()->showCreateEditeValueUI(id);
	//CreateEditUI* create = new CreateEditUI(0,id);
	//	CreateEditUI::ShowUI(id);
}

void merplyTabelView::deleteEntity(const QString& id)
{
	if(Controller::Get()->ShowQuestion(tr("Are you sure you want to delete?")))
		if(Controller::Get()->deleteDocument(id))
			Controller::Get()->queryIndexView("ViewStructure::"+id.split("::")[0]);
}

void merplyTabelView::gotReportData(QList<QJsonDocument> documents)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotReportData(QList<QJsonDocument>)),this,SLOT(gotReportData(QList<QJsonDocument>)));
	emit updateModel(documents);
	//model->fill(documents);
}

void merplyTabelView::updateHeaderData(QList<QString> headerItems)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotFieldsData(QList<QString>)),this,SLOT(updateHeaderData(QList<QString>)));
	indexedTable.clear();
	tabel->setColumnCount(headerItems.count()+1);
	tabel->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("controls")));
	bool edit = true;
	bool remove = true;
	int k = 1;
	foreach(QString key,headerItems){
		tabel->setHorizontalHeaderItem(k, new QTableWidgetItem(QString(key)));
		k++;
		}
	tabel->setRowCount(items.count());
	int i = 0;
	foreach(QJsonDocument item,items){
		int j = 0;
		merplyTableControllers* controller = new merplyTableControllers(0,item.object().value("document_id").toString(),edit,remove);
		connect(controller, SIGNAL(printClicked(QString)), this, SLOT(printEntity(QString)));
		if(edit)
			connect(controller, SIGNAL(editClicked(const QString&)), this, SLOT(editEntity(QString)));
		if(remove)
			connect(controller, SIGNAL(deleteClicked(QString)), this, SLOT(deleteEntity(QString)));

		tabel->setCellWidget(i, j, controller);

		//qDebug() << item;
		QJsonObject simplifiedItem = QJsonObject();
		foreach(QJsonValue value, item.object().value("Fields").toArray()){
			foreach(QJsonValue viewGroup, value.toArray()){
				QString valueString;
				if(headerItems.count() -1 > j)
					valueString = Controller::Get()->toString(viewGroup.toObject().value(headerItems.at(j)).toArray());
				simplifiedItem.insert(headerItems.at(j), valueString);
				//QStandardItem *value = new QStandardItem(valueString);
				//	tabel->setItem(i,k,value);
				QLabel *value = new QLabel(valueString);
				//QLable *value = new QStandardItem(QString(data.value(propertyName).toArray()[i].toArray()[j].toString()));
				//model->setItem(i,j,value);
				tabel->setCellWidget(i,j+1,value);
				j++;
				}
			}
		indexedTable.insert(item.object().value("document_id").toString(),simplifiedItem);
		i++;
		}
	//qDebug() <<indexedTable;
	tabel->resizeColumnsToContents();
	/*


	foreach(QJsonDocument item,items){

		foreach(QString key,headerItems){

			foreach(QJsonValue value, item.object().value("Fields").toArray()){

				foreach(QJsonValue viewGroup, value.toArray()){
					//qDebug() << viewGroup.toObject().value("key");
					}
				}


			if(item.object().value(key).isArray()){
				QString valueString = Controller::Get()->toString(item.object().value(key).toArray());
				//qDebug()  << valueString;
					//QStandardItem *value = new QStandardItem(valueString);
				//	tabel->setItem(i,k,value);

				QLabel *value = new QLabel(valueString);
				//QLable *value = new QStandardItem(QString(data.value(propertyName).toArray()[i].toArray()[j].toString()));
				//model->setItem(i,j,value);
				tabel->setCellWidget(i,k,value);
				}
			else{
				//QStandardItem *value = new QStandardItem();
				//tabel->setItem(i,k,value);
				QLabel *value = new QLabel(QString(item.object().value(key).toString()));
				//QLable *value = new QStandardItem(QString(data.value(propertyName).toArray()[i].toArray()[j].toString()));
				//model->setItem(i,j,value);
				////	item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				tabel->setCellWidget(i,k,value);

				}


			}
		i++;
		}
	//	this->tabel->setModel(model);
	this->tabel->resizeColumnsToContents();

	//this->tabel->hideColumn(headerItems.indexOf("document_id"));
	//this->tabel->hideColumn(headerItems.indexOf("cas"));

	//return true;
	*/
}

void merplyTabelView::setValue(const int , const QString paramName, QVariant& paramValue, const int )
{
	qDebug() << paramName;
	QJsonValue value = indexedTable.value(currenctPrintID).value(paramName);
	if(value != QJsonValue::Undefined)
		paramValue = value.toVariant();
	else return;
}
