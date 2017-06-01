#ifndef CREATEEDITUI_H
#define CREATEEDITUI_H


#include "maindisplay.h"
#include "viewgroups.h"
#include <QObject>
#include <QWidget>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QShortcut>
#include <QCheckBox>
class CreateEditUI : public MainDisplay
{
	Q_OBJECT
public:
	CreateEditUI(QWidget *parent = 0);
	explicit CreateEditUI(QWidget *parent = 0,QJsonObject viewStructure = QJsonObject(),QJsonObject data = QJsonObject());
	//static CreateEditUI* ShowUI(QJsonObject viewStructure, QJsonObject data, bool create);


	QJsonObject getViewStructure() const;
	void fillData(QJsonObject data);
	void fill(QJsonObject viewStructure,QJsonObject data);
	QHash<QString, FeildUI*> getFieldsgroups() const;

private:
	//static CreateEditUI* p_instance;

	void clear();
	QWidget* createEditWidget;
	QVBoxLayout *createEditWidgetLayout;
	QWidget* errorsWidget;
	QVBoxLayout *errorsWidgetLayout;
	QVBoxLayout *layout;
	ViewGroups * viewGroups;
	QJsonObject viewStructure;
	QString cas;
	QJsonObject data;
	void clearErrorsWidget();
	QStringList getTabelsFieldNames(QJsonObject viewStructure);
	QShortcut* saveShortCut;
	QShortcut* cancelShortCut;
	QShortcut* printShortCut;
	bool init;
	QWidget* printAfterSaveWidget;
	QHBoxLayout *printAfterSaveWidgetLayout;

	void printAfterSave(QJsonObject strct);
	QCheckBox* printAfter;
	QCheckBox* showPrintDialog;
	QCheckBox* toInvoice;
	bool toInvoiceFlag;

	QHash<QString,FeildUI*> fieldsgroups;
signals:
protected:
	//void showEvent(QShowEvent *);
	void paintEvent(QPaintEvent*event);
public slots:
	void controller_Clicked(QString nameAction);
	void gotTabelsData(QVector<QJsonDocument> tblsData);
	void saved();
	void printEntity();
	void saveEntity();
	void cancel();
	void printAfterCheckBoxChanged(bool checked);
	void printAfterSaved(QJsonDocument document);
};

#endif // CREATEEDITUI_H
