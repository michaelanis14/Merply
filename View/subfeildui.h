#ifndef SUBFIELDUI_H
#define SUBFIELDUI_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QJsonObject>
#include <QMouseEvent>
#include <QDebug>
#include <QJsonArray>

#include "rangevalidator.h"
#include "erpcombobox.h"
#include "merplytabelview.h"


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
signals:

public slots:
	void indexedFillEvent(QString completion);
	void linkPressed();
	void refrenceData(QVector<QJsonDocument> items);
	void serialData(QString serial);
	void updateFilter(QString filter);
	void updateTable(QString);
	void updateEquationField();
	double getClmnDataCount(QString strct);
	double evalEquationCondition(int condition,double col1,double col2);


};

#endif // SUBFIELDUI_H
