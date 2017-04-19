#ifndef SUBFIELDUI_H
#define SUBFIELDUI_H

#include "rangevalidator.h"
#include "erpcombobox.h"
#include "merplytabelview.h"
#include "settingsctrlsui.h"
#include "searchui.h"

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QJsonObject>
#include <QMouseEvent>
#include <QDebug>
#include <QShortcut>
#include <QJsonArray>





class SubFieldUI : public QWidget
{
	Q_OBJECT
public:
	explicit SubFieldUI(QWidget *parent = 0,QString strID = "", QJsonObject structureView = QJsonObject(), QJsonValue data = QJsonValue());
	void clear();
	QJsonValue save();
	bool checkMandatory();
private:
	QHBoxLayout *layout;
	QWidget* field;
	QJsonObject structureView;
	ERPComboBox* combox;
	QString strID;
	merplyTabelView * table;
	ERPComboBox* localFilterCombobox;
	SettingsCtrlsUI* sctrlUI;
	QShortcut* searchShortCut;

protected:
signals:
	void btnClicked(QString);
public slots:
	void indexedFillEvent(QString completion);
	void linkPressed();
	void btnSearch_Clicked();
	void refrenceData(QVector<QJsonDocument> items);
	void serialData(QString serial);
	void updateFilter(QString filter);
	void updateTable(QString);
	void updateEquationField();
	double getClmnDataCount(QString strct);
	double evalEquationCondition(int condition,double col1,double col2);
	void editComboxText(QVector<QString> rowData);
};

#endif // SUBFIELDUI_H
