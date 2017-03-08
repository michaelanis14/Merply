

#include "createeditui.h"
#include "mainform.h"
#include "hcontrollers.h"
#include "controller.h"
#include "indexui.h"
#include "printcontroller.h"




CreateEditUI::CreateEditUI(QWidget* parent ) : MainDisplay(parent)
{

}

CreateEditUI::CreateEditUI(QWidget* parent, QJsonObject viewStructure, QJsonObject data) : MainDisplay(parent)
{

	this->setContentsMargins(0,0,0,0);
	this->layout = new QVBoxLayout(formPanel);
	this->layout->setSizeConstraint(QLayout::SetMaximumSize);
	this->layout->setContentsMargins(0,0,0,0);
	//this->layout->setSpacing(0);
	this->data = data;
	this->cas = "";
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



	fill(viewStructure,data);

	cancelShortCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this, SLOT(cancel()));
	cancelShortCut = new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(cancel()));
	saveShortCut =new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(saveEntity()));
	printShortCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P), this, SLOT(printEntity()));
}

CreateEditUI* CreateEditUI::p_instance = 0;
void CreateEditUI::ShowUI(QJsonObject viewStructure, QJsonObject data,bool create) {

	//CreateEditUI* p_instance;
	QString key = viewStructure.value("document_id").toString().split("::").count() > 1?viewStructure.value("document_id").toString().split("::")[1]:"";
	if(!key.isEmpty())
		{
		//this->viewStructure = viewStructure;
		if( create || !Controller::Get()->isCachedCreateEditUI(key)){
			CreateEditUI* p =  new CreateEditUI(0,viewStructure, data);
			//qDebug() << __FILE__ << __LINE__ << "insertCachedCreateEditUI"<<key<< &p_instance;
			Controller::Get()->insertCachedCreateEditUI(key,p);
			p_instance = p;
			}
		else{
			//qDebug() << __FILE__ << __LINE__ << "getCachedCreateEditUI"<<key;
			p_instance = (CreateEditUI*)(Controller::Get()->getCachedCreateEditUI(key));
			}
		}
	else if(!data.isEmpty()){
		QStringList tbls =p_instance->getTabelsFieldNames(p_instance->viewStructure);
		if(tbls.count() == 0){
			p_instance->clear();
			p_instance->fill(QJsonObject(), data);
			}
		else{

			p_instance->data = data;
			//qDebug()<<"INITTT" << p_instance->data;
			QObject::connect(Controller::Get(),SIGNAL(gotReportData(QVector<QJsonDocument>)),p_instance,SLOT(gotTabelsData(QVector<QJsonDocument>)));
			Controller::Get()->getTabelsData(data.value("document_id").toString(),tbls);
			return;
			}
		//	return; //TODO: PREVENT MULITPE LOADS with fill
		}
	else {
		qDebug() << __FILE__ << __LINE__ << __FILE__ << __LINE__ << "ERRLOG" << viewStructure.value("document_id").toString() << "SPLIT COUNT";
		return;
		}
	p_instance->saveShortCut->setEnabled(true);
	p_instance->cancelShortCut->setEnabled(true);
	p_instance->printShortCut->setEnabled(true);
	MainForm::Get()->ShowDisplay(p_instance);
}

void CreateEditUI::fill(QJsonObject viewStructure, QJsonObject data)
{
	if(!viewStructure.isEmpty()){
		this->viewStructure = viewStructure;
		}

	if(!data.isEmpty()){
		this->data = data;
		this->cas = data.value("cas_value").toString();
		}
	//qDebug() << __FILE__ << __LINE__  <<"Fill"<< this->cas;

	viewGroups = ViewGroups::Create(this->viewStructure,data) ;
	createEditWidgetLayout->addWidget(viewGroups);

	//this->layout->addWidget(createEditWidget);
}

void CreateEditUI::clear()
{
	this->cas = "";
	QList<QWidget *> Widgets = createEditWidget->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		if(child != NULL){
			createEditWidgetLayout->removeWidget(child);
			child->setHidden(true);
			//child->setParent(0);
			child->deleteLater();
			}
		}
}

void CreateEditUI::clearErrorsWidget()
{
	QList<QWidget *> Widgets = errorsWidget->findChildren<QWidget *>();
	foreach(QWidget * child, Widgets)
		{
		errorsWidgetLayout->removeWidget(child);
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

	printAfterSaveWidget = new QWidget();
	//printAfterSaveWidget->setContentsMargins(0,0,0,0);
	printAfterSaveWidgetLayout = new QHBoxLayout(printAfterSaveWidget);
	printAfterSaveWidgetLayout->setContentsMargins(0,0,0,0);
	//printAfterSaveWidgetLayout->setSpacing(0);
	this->layout->addWidget(printAfterSaveWidget);
	printAfter = new QCheckBox(tr("طباعه فورى"));
	connect(printAfter, SIGNAL(toggled(bool)), this, SLOT(printAfterCheckBoxChanged(bool)));
	printAfter->setChecked(true);
	printAfterSaveWidgetLayout->addWidget(printAfter);
	showPrintDialog =new QCheckBox(tr("عرض نموزج الطباعه"));
	printAfterSaveWidgetLayout->addWidget(showPrintDialog);
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
			saveEntity();
			}

		}


}

void CreateEditUI::gotTabelsData(QVector<QJsonDocument> tblsData)
{
	QObject::disconnect(Controller::Get(),SIGNAL(gotReportData(QVector<QJsonDocument>)),p_instance,SLOT(gotTabelsData(QVector<QJsonDocument>)));

	//qDebug() <<"gotTabelsData"<< tblsData.first();
	//qDebug()<<"BEFOREEEE" << p_instance->data;

	QStringList keys ;
	if(tblsData.count() > 0)
		keys= tblsData.first().object().keys();
	foreach(QString key,keys){
		QJsonObject row;
		row.insert("merplyTabel",tblsData.first().object().value(key).toArray());
		p_instance->data.insert(key,row);
		}
	p_instance->clear();
	//qDebug() << p_instance->data;
	p_instance->fill(QJsonObject(), p_instance->data);
	MainForm::Get()->ShowDisplay(p_instance);
}

void CreateEditUI::printEntity()
{
	this->clearErrorsWidget();
	QString errs = viewGroups->checkMandatory();
	if(errs.isEmpty()){
		//	qDebug() << __FILE__ << __LINE__ <<"Controller Clicked to save" << this->cas;

		if(this->cas.isEmpty()){
			}
		else{
			QJsonObject vgsSave = viewGroups->save();
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
}

void CreateEditUI::saveEntity()
{
	saveShortCut->setEnabled(false);
	this->clearErrorsWidget();
	QString errs = viewGroups->checkMandatory();
	if(errs.isEmpty()){
		//	qDebug() << __FILE__ << __LINE__ <<"Controller Clicked to save" << this->cas;
		QString documentID ;
		if(!this->data.isEmpty()){
			documentID = this->data.value("document_id").toString();
			}
		else if(this->viewStructure.value("SaveAs") != QJsonValue::Undefined){
			documentID = this->viewStructure.value("SaveAs").toString();
			}
		else{
			documentID = this->viewStructure.value("document_id").toString();
			}
		if(this->cas.isEmpty()){



			QString key = documentID.replace("ViewStructure::","");

			QJsonObject vgsSave = viewGroups->save();
			//vgsSave.insert("cas_value",this->cas);
			vgsSave.insert("document_id",key);
			QObject::connect(Controller::Get(),SIGNAL(savedItems(QString)),this,SLOT(saved()));
			Controller::Get()->createEditStore(vgsSave);
			Controller::Get()->saveRefrenceStructures(this->viewStructure,vgsSave);


			}
		else{
			QJsonObject vgsSave = viewGroups->save();
			//qDebug() << vgsSave;
			vgsSave.insert("cas_value",this->cas);
			vgsSave.insert("document_id",documentID);
			QObject::connect(Controller::Get(),SIGNAL(savedItems(QString)),this,SLOT(saved()));
			Controller::Get()->createEditStore(vgsSave);
			Controller::Get()->saveRefrenceStructures(this->viewStructure,vgsSave);


			//QObject::connect(Controller::Get(),SIGNAL(saved(QString)),this,SLOT(saved()));
			//Controller::Get()->UpdateDoc(QJsonDocument(vgsSave));
			}


		}
	else{
		foreach(QString err,errs.split(";")){
			errorsWidgetLayout->addWidget(new QLabel(err +" can not be empty"));
			}
		saveShortCut->setEnabled(true);
		}
}

void CreateEditUI::cancel()
{
	saveShortCut->setEnabled(false);
	QString documentID ;
	if(this->viewStructure.value("SaveAs") != QJsonValue::Undefined){
		documentID = this->viewStructure.value("SaveAs").toString();
		}
	else{
		documentID = this->viewStructure.value("document_id").toString();
		}
	IndexUI::ShowUI(documentID,QVector<QJsonDocument>());
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
	//qDebug() << "Will PRINTT" << document;
	PrintController::Get()->gotPrintEntity(document,this->showPrintDialog->isChecked());
}

void CreateEditUI::saved()
{
	QObject::disconnect(Controller::Get(),SIGNAL(saved(QString)),this,SLOT(saved()));

	IndexUI::ShowUI(this->viewStructure.value("document_id").toString(),QVector<QJsonDocument>());
}
