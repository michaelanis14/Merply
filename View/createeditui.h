#ifndef CREATEEDITUI_H
#define CREATEEDITUI_H


#include "maindisplay.h"
#include "viewgroups.h"
#include "sqltabelmodel.h"

#include <QObject>
#include <QWidget>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QShortcut>
#include <QCheckBox>

class QSqlRelationalTableModel;
class QStandardItemModel;
class QStringListModel;
class QTextEdit;
class QComboBox;
class QDataWidgetMapper;
class QItemSelectionModel;

class CreateEditUI : public MainDisplay
{
	Q_OBJECT
public:
	CreateEditUI(QWidget *parent = 0);
	explicit CreateEditUI(QWidget *parent = 0,QJsonObject viewStructure = QJsonObject(),SQLTabelModel* model = new SQLTabelModel());
	//static CreateEditUI* ShowUI(QJsonObject viewStructure, QJsonObject data, bool create);
	void showUI(bool create = false);

	QJsonObject getViewStructure() const;
	void fill(QJsonObject viewStructure);
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
	Database* database;
	QHash<QString,FeildUI*> fieldsgroups;

	SQLTabelModel* model;
	QItemSelectionModel *selectionModel;
	QDataWidgetMapper *mapper;
	int typeIndex;
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
	void sqlSubmit();
	void cancel();
	void printAfterCheckBoxChanged(bool checked);
	void printAfterSaved(QJsonDocument document);
};

#endif // CREATEEDITUI_H
