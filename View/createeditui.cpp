

#include "createeditui.h"
#include "mainform.h"
#include "hcontrollers.h"
#include "controller.h"
#include "indexui.h"
#include "printcontroller.h"
#include <QMessageBox>




CreateEditUI::CreateEditUI(QWidget* parent ) : MainDisplay(parent)
{
	this->init = false;
	this->fieldsgroups = QHash<QString,FeildUI*>();
}

CreateEditUI::CreateEditUI(QWidget* parent, QJsonObject viewStructure,SQLTabelModel* model) : MainDisplay(parent)
{

	this->setContentsMargins(0,0,0,0);
	this->layout = new QVBoxLayout(formPanel);
	this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	this->layout->setContentsMargins(0,0,0,0);
	//this->layout->setSpacing(0);
	fieldsgroups = QHash<QString,FeildUI*>();
	this->model = model;


	QStringList btnsList;
	btnsList << "طباعه->Print"<<"حفظ->Save"<< "إلغاء->Cancel";

	HControllers* contrls = new HControllers(0,btnsList);
	connect(contrls, SIGNAL(btnClicked(const QString&)), this, SLOT(controller_Clicked(QString)));
	contrls->setObjectName("ViewGroup");
	this->layout->addWidget(contrls);

	errorsWidget = new QWidget();
	errorsWidget->setObjectName("errorsWidget");
	errorsWidget->setContentsMargins(0,0,0,0);
	errorsWidgetLayout = new QVBoxLayout(errorsWidget);
	errorsWidgetLayout->setContentsMargins(0,0,0,0);
	errorsWidgetLayout->setSpacing(0);
	this->layout->addWidget(errorsWidget);

	QObject::disconnect(Controller::Get(),SIGNAL(savedQJson(QJsonDocument)),this,SLOT(printAfterSaved(QJsonDocument)));
	printAfterSave(viewStructure);

	createEditWidget = new QWidget();
	createEditWidget->setContentsMargins(0,0,0,0);
	createEditWidgetLayout = new QVBoxLayout(createEditWidget);
	createEditWidgetLayout->setContentsMargins(0,0,0,0);
	createEditWidgetLayout->setSpacing(0);
	this->layout->addWidget(createEditWidget);

	HControllers* ndcontrls = new HControllers(0,btnsList);
	ndcontrls->setObjectName("ViewGroup");
	connect(ndcontrls, SIGNAL(btnClicked(const QString&)), this, SLOT(controller_Clicked(QString)));
	this->layout->addWidget(ndcontrls);



	fill(viewStructure);

	cancelShortCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this, SLOT(cancel()));
	cancelShortCut = new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(cancel()));
	saveShortCut =new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(saveEntity()));
	printShortCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P), this, SLOT(printEntity()));
	this->init = true;
}

void CreateEditUI::showUI( bool create)
{
	MainForm::Get()->ShowDisplay(this);
	if(create)
		mapper->toLast();
	else mapper->toFirst();
}

//CreateEditUI* CreateEditUI::this = 0;
/*
CreateEditUI* CreateEditUI::ShowUI(QJsonObject viewStructure, QJsonObject data,bool create) {

	//CreateEditUI* this;
	QString key = viewStructure.value("document_id").toString().split("::").count() > 1?viewStructure.value("document_id").toString().split("::")[1]:"";


	if(!key.isEmpty())
		{
		if(create ){
			CreateEditUI* p =  new CreateEditUI(0,viewStructure, data);

			//qDebug() << __FILE__ << __LINE__ << "insertCachedCreateEditUI"<<key<< &this;
			//Controller::Get()->insertCachedCreateEditUI(key,p);
			this = p;
			}
		else{

			this = (CreateEditUI*)(Controller::Get()->getStructure(key));

			//	this = (CreateEditUI*)(Controller::Get()->getCachedCreateEditUI(key));
			}
		}
	else if(!data.isEmpty()){
		QStringList tbls =this->getTabelsFieldNames(this->viewStructure);
		if(tbls.count() == 0){
			this->clear();
			this->fill(QJsonObject(), data);
			}
		else{

			this->data = data;
			//qDebug()<<"INITTT" << this->data;
			QObject::connect(Controller::Get(),SIGNAL(gotReportData(QVector<QJsonDocument>)),this,SLOT(gotTabelsData(QVector<QJsonDocument>)));
			Controller::Get()->getTabelsData(data.value("document_id").toString(),tbls);
		//	return;
			}
		//	return; //TODO: PREVENT MULITPE LOADS with fill
		}
	else {
		qDebug() << __FILE__ << __LINE__ << __FILE__ << __LINE__ << "ERRLOG" << viewStructure.value("document_id").toString() << "SPLIT COUNT";
//		return;
		}
	this->saveShortCut->setEnabled(true);
	this->cancelShortCut->setEnabled(true);
	this->printShortCut->setEnabled(true);

	if(!create)
		MainForm::Get()->ShowDisplay(this);

	return this;
}
*/

//Dapricated
void CreateEditUI::fill(QJsonObject viewStructure)
{
	QString documentid = viewStructure.value("document_id").toString();

	//	model = new QSqlRelationalTableModel(0,Controller::Get()->getDatabase()->getDatabase());
	//	model->setTable("`"+documentid+"`");
	//	model->setEditStrategy(QSqlTableModel::OnManualSubmit);


	//	model->select();
	mapper = new QDataWidgetMapper(this);
	mapper->setModel(this->model);
	mapper->setItemDelegate(new QSqlRelationalDelegate(this));

	if(!viewStructure.isEmpty()){
		this->viewStructure = viewStructure;
		}

	viewGroups = new ViewGroups(0,this->viewStructure,&this->fieldsgroups,mapper) ;
	createEditWidgetLayout->addWidget(viewGroups);
	mapper->toFirst();
	//this->layout->addWidget(createEditWidget);
}

//Dapricated
void CreateEditUI::clear()
{

	QList<QWidget *> Widgets = this->createEditWidget->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		if(child != NULL){
			this->createEditWidgetLayout->removeWidget(child);
			child->setHidden(true);
			//child->setParent(0);
			child->deleteLater();
			}
		}
}

void CreateEditUI::clearErrorsWidget()
{
	QList<QWidget *> Widgets = this->errorsWidget->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		this->errorsWidgetLayout->removeWidget(child);
		child->setHidden(true);
		child->setParent(0);
		child->deleteLater();  // TODO : check the stability of the app
		}
}

QStringList CreateEditUI::getTabelsFieldNames(QJsonObject viewStructure)
{
	QStringList tbls;
	foreach (QJsonValue vg, viewStructure.value("Viewgroups").toArray()) {
		foreach (QJsonValue fields, vg.toObject().value("Viewgroup").toObject().value("Fields").toArray()) {
			foreach (QJsonValue subfields, fields.toObject().value("SubFields").toArray()) {
				if(subfields.toObject().value("Type").toString().compare("Table") == 0)
					tbls.append(fields.toObject().value("Label").toString());
				}
			}
		}
	return tbls;
}

void CreateEditUI::printAfterSave(QJsonObject strct)
{
	this->toInvoiceFlag = false;
	if(strct.value("document_id").toString().compare("ViewStructure::PriceQutation") == 0)
		this->toInvoiceFlag = true;

	printAfterSaveWidget = new QWidget();
	//printAfterSaveWidget->setContentsMargins(0,0,0,0);
	printAfterSaveWidgetLayout = new QHBoxLayout(printAfterSaveWidget);
	//printAfterSaveWidgetLayout->setContentsMargins(0,0,0,0);
	//printAfterSaveWidgetLayout->setSpacing(0);
	this->layout->addWidget(printAfterSaveWidget);
	printAfter = new QCheckBox(tr("طباعه فورى"));
	connect(printAfter, SIGNAL(toggled(bool)), this, SLOT(printAfterCheckBoxChanged(bool)));
	printAfter->setChecked(true);
	printAfterSaveWidgetLayout->addWidget(printAfter);
	showPrintDialog =new QCheckBox(tr("عرض نموزج الطباعه"));
	printAfterSaveWidgetLayout->addWidget(showPrintDialog);

	if(this->toInvoiceFlag){
		toInvoice =new QCheckBox(tr("تحويل لفاتوره"));
		printAfterSaveWidgetLayout->addWidget(toInvoice);
		}
	/*
	 *
	 * //TODO : EACH ENTITY A CHECK
	if(strct.value("Viewgroups").isArray()){
		foreach (QJsonValue item, strct.value("Viewgroups").toArray()) {
			QJsonObject viewGroupObject = item.toObject().value("Viewgroup").toObject();
			if(viewGroupObject.value("RefrenceFields") != QJsonValue::Undefined){
				foreach(QJsonValue refrenceFields,viewGroupObject.value("RefrenceFields").toArray()){
					refrenceFields.toObject().value("Source").toString().split("::")[1];
					}
				}

			}
		}
		*/
}

QHash<QString, FeildUI*> CreateEditUI::getFieldsgroups() const
{

	if(init &&!fieldsgroups.isEmpty())
		return fieldsgroups;
	else return QHash<QString, FeildUI*>();
}

void CreateEditUI::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void CreateEditUI::controller_Clicked(QString nameAction)
{
	QStringList nActon = nameAction.split("->");
	if(nActon.count() > 1){
		if(nActon.at(1).compare("Print") == 0){
			printEntity();
			}
		else if(nActon.at(1).compare("Cancel") == 0){
			cancel();
			}
		else if(nActon.at(1).compare("Save") == 0){
			//saveEntity();
			sqlSubmit();
			}

		}


}

void CreateEditUI::gotTabelsData(QVector<QJsonDocument> tblsData)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotReportData(QVector<QJsonDocument>)),this,SLOT(gotTabelsData(QVector<QJsonDocument>)));

	//qDebug() <<"gotTabelsData"<< tblsData.first();
	//qDebug()<<"BEFOREEEE" << this->data;

	QStringList keys ;
	if(tblsData.count() > 0)
		keys= tblsData.first().object().keys();
	foreach(QString key,keys){
		QJsonObject row;
		row.insert("merplyTabel",tblsData.first().object().value(key).toArray());
		}
	this->clear();
	//qDebug() << this->data;
	//	this->fill(QJsonObject());
	//MainForm::Get()->ShowDisplay(this);
}

void CreateEditUI::printEntity()
{
	this->clearErrorsWidget();
	QString errs = viewGroups->checkMandatory();
	if(errs.isEmpty()){
		//	qDebug() << __FILE__ << __LINE__ <<"Controller Clicked to save" << this->cas;

		QJsonObject vgsSave;
		qDebug() << __FILE__ << __LINE__ <<"TODO PRINTING";
		//= viewGroups->save();
		QString documentID ;
		if(this->viewStructure.value("SaveAs") != QJsonValue::Undefined){
			documentID = this->viewStructure.value("SaveAs").toString();
			}
		else{
			documentID = this->viewStructure.value("document_id").toString();
			}
		vgsSave.insert("document_id",documentID.split("::")[1]);
		PrintController::Get()->gotPrintEntity(QJsonDocument(vgsSave));



		}
}

void CreateEditUI::saveEntity()
{
	this->saveShortCut->setEnabled(false);
	this->clearErrorsWidget();
	bool newDocument = true;
	//qDebug() << "SAVEEE"	 << this->viewStructure;
	QString errs = this->viewGroups->checkMandatory();
	if(errs.isEmpty()){
		//	qDebug() << __FILE__ << __LINE__ <<"Controller Clicked to save" << this->cas;
		QString documentID ;
		QString tbl;
		if(false){
			documentID ;
			//= this->data.value("document_id").toString();
			newDocument = false;
			}
		else if(this->viewStructure.value("SaveAs") != QJsonValue::Undefined){
			tbl = this->viewStructure.value("SaveAs").toString();
			}
		else{
			tbl = this->viewStructure.value("document_id").toString();
			}


		if(newDocument){
			// new
			QPair<QString,QString> insertQuery = this->viewGroups->save(true);
			if(!insertQuery.first.isEmpty())
				insertQuery.first.append(" , ");
			insertQuery.first.append("`Enabled`");
			if(!insertQuery.second.isEmpty())
				insertQuery.second.append(" , ");
			insertQuery.second.append("1");

			if(!insertQuery.first.isEmpty())
				insertQuery.first.append(" , ");
			insertQuery.first.append("`Active`");
			if(!insertQuery.second.isEmpty())
				insertQuery.second.append(" , ");
			insertQuery.second.append("1");

			if(!insertQuery.first.isEmpty())
				insertQuery.first.append(" , ");
			insertQuery.first.append("`ShowOnWebSite`");
			if(!insertQuery.second.isEmpty())
				insertQuery.second.append(" , ");
			insertQuery.second.append("1");

			if(!insertQuery.first.isEmpty())
				insertQuery.first.append(" , ");
			insertQuery.first.append("`CreatedOn`");
			if(!insertQuery.second.isEmpty())
				insertQuery.second.append(" , ");
			insertQuery.second.append(QString("'"+(QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss")+"'"));

			if(!insertQuery.first.isEmpty())
				insertQuery.first.append(" , ");
			insertQuery.first.append("`EditedOn`");
			if(!insertQuery.second.isEmpty())
				insertQuery.second.append(" , ");
			insertQuery.second.append(QString("'"+(QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss")+"'"));

			if(!insertQuery.first.isEmpty())
				insertQuery.first.append(" , ");
			insertQuery.first.append("`CreatedByName`");
			if(!insertQuery.second.isEmpty())
				insertQuery.second.append(" , ");
			insertQuery.second.append(QString("'"+AccessController::Get()->getUserName()+"'"));

			if(!insertQuery.first.isEmpty())
				insertQuery.first.append(" , ");
			insertQuery.first.append("`CreatedByID`");
			if(!insertQuery.second.isEmpty())
				insertQuery.second.append(" , ");
			insertQuery.second.append(AccessController::Get()->getUserID());

			if(!insertQuery.first.isEmpty())
				insertQuery.first.append(" , ");
			insertQuery.first.append("`EditedByName`");
			if(!insertQuery.second.isEmpty())
				insertQuery.second.append(" , ");
			insertQuery.second.append(QString("'"+AccessController::Get()->getUserName()+"'"));

			if(!insertQuery.first.isEmpty())
				insertQuery.first.append(" , ");
			insertQuery.first.append("`EditedByID`");
			if(!insertQuery.second.isEmpty())
				insertQuery.second.append(" , ");
			insertQuery.second.append(AccessController::Get()->getUserID());



			qDebug() << __FILE__ << __LINE__ <<"TODO NEW SAVE";
			//= this->viewGroups->save();
			//vgsSave.insert("cas_value",this->cas);
			//vgsSave.insert("document_id",key);

			QString insertQueryMerged =
					QString("INSERT INTO `").append(tbl).append("` (").append(insertQuery.first.append(" ) VALUES (").append(insertQuery.second.append(" );")));

			QObject::connect(Controller::Get(),SIGNAL(saved(QString)),this,SLOT(saved()));
			Controller::Get()->insertUpdateRow(insertQueryMerged);



			/*
			if(this->toInvoiceFlag){
				if(this->toInvoice->isChecked())

					Controller::Get()->saveRefrenceStructures(this->viewStructure,vgsSave);
				}
			else Controller::Get()->saveRefrenceStructures(this->viewStructure,vgsSave);

			}
		else{

			QJsonObject vgsSave ;

			//= this->viewGroups->save();
			qDebug() << __FILE__ << __LINE__ <<"TODO NEW SAVE";
			//qDebug() << vgsSave;
			vgsSave.insert("cas_value",this->cas);
			vgsSave.insert("document_id",documentID);
			QObject::connect(Controller::Get(),SIGNAL(savedItems(QString)),this,SLOT(saved()));
			Controller::Get()->createEditStore(vgsSave);


			if(this->toInvoiceFlag){
				if(this->toInvoice->isChecked())

					Controller::Get()->saveRefrenceStructures(this->viewStructure,vgsSave);
				}
			else Controller::Get()->saveRefrenceStructures(this->viewStructure,vgsSave);
			//QObject::connect(Controller::Get(),SIGNAL(saved(QString)),this,SLOT(saved()));
			//Controller::Get()->UpdateDoc(QJsonDocument(vgsSave));
			}

*/
			}

		else{
			//update
			QPair<QString,QString> insertQuery = this->viewGroups->save(false);
			if(!insertQuery.first.isEmpty())
				insertQuery.first.append(" , ");
			insertQuery.first.append("`EditedOn`");
			if(!insertQuery.second.isEmpty())
				insertQuery.second.append(" , ");
			insertQuery.second.append(QString("'"+(QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss")+"'"));

			if(!insertQuery.first.isEmpty())
				insertQuery.first.append(" , ");
			insertQuery.first.append("`EditedByName`");
			if(!insertQuery.second.isEmpty())
				insertQuery.second.append(" , ");
			insertQuery.second.append(QString("'"+AccessController::Get()->getUserName()+"'"));

			if(!insertQuery.first.isEmpty())
				insertQuery.first.append(" , ");
			insertQuery.first.append("`EditedByID`");
			if(!insertQuery.second.isEmpty())
				insertQuery.second.append(" , ");
			insertQuery.second.append(AccessController::Get()->getUserID());



			QString insertQueryMerged =
					QString("UPDATE `").append(tbl).append("` SET ").append(insertQuery.first.append(" WHERE `id` = ").append(documentID));

			QObject::connect(Controller::Get(),SIGNAL(saved(QString)),this,SLOT(saved()));
			Controller::Get()->insertUpdateRow(insertQueryMerged);


			}
		}

	else{
		qDebug()<<"ERRORRRR:" << errs;
		foreach(QString err,errs.split(";")){
			this->errorsWidgetLayout->addWidget(new QLabel(err +" can not be empty"));
			}
		this->saveShortCut->setEnabled(true);
		}

}

void CreateEditUI::sqlSubmit()
{
	model->database().transaction();
	if (model->submitAll()) {
		model->database().commit();
		cancel();
		} else {
		model->database().rollback();
		QMessageBox::warning(this, tr("Cached Table"),
							 tr("The database reported an error: %1")
							 .arg(model->lastError().text()));
		}
}

void CreateEditUI::cancel()
{
	saveShortCut->setEnabled(false);
	int documentID  = 0;
	if(this->viewStructure.value("SaveAs") != QJsonValue::Undefined)
		documentID = this->viewStructure.value("SaveAs").toString().toInt();
	else
		documentID = this->viewStructure.value("document_id").toString().toInt();

	((IndexUI*)Controller::Get()->getCachedIndexUI(documentID))->showUI();
}

void CreateEditUI::printAfterCheckBoxChanged(bool checked)
{
	//TODO : BETTER RE GET THE DOCUMENT WITH ITS ID TO MAKE SURE IT IS ALREADY SAVED CORRECTLY
	if(checked){
		QObject::connect(Controller::Get(),SIGNAL(savedQJson(QJsonDocument)),this,SLOT(printAfterSaved(QJsonDocument)));
		//QObject::connect(Controller::Get(),SIGNAL(savedItems(QString)),this,SLOT(printAfterSaved(QString)));
		}
	else {
		QObject::disconnect(Controller::Get(),SIGNAL(savedQJson(QJsonDocument)),this,SLOT(printAfterSaved(QJsonDocument)));
		//QObject::disconnect(Controller::Get(),SIGNAL(savedItems(QString)),this,SLOT(printAfterSaved(QString)));
		}
}

void CreateEditUI::printAfterSaved(QJsonDocument document)
{
	//QObject::disconnect(Controller::Get(),SIGNAL(savedQJson(QJsonDocument)),this,SLOT(printAfterSaved(QJsonDocument)));
	//	qDebug() << "Will PRINTT" << document.object().value("document_id");
	PrintController::Get()->gotPrintEntity(document,this->showPrintDialog->isChecked());
}

//Dapricated
void CreateEditUI::saved()
{
	QObject::disconnect(Controller::Get(),SIGNAL(saved(QString)),this,SLOT(saved()));
	//	this->clear();
	//	this->fill(QJsonObject());
	((IndexUI*)Controller::Get()->getCachedIndexUI(this->viewStructure.value("document_id").toString().toInt()))->showUI();
}
