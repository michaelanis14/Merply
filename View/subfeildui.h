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

class SubFieldUI : public QWidget
{
	Q_OBJECT
public:
	explicit SubFieldUI(QWidget *parent = 0, QJsonObject structureView = QJsonObject(), QJsonObject data = QJsonObject());
	void clear();
	QString save();
private:
	QHBoxLayout *layout;
	QWidget* field;
	QJsonObject structureView;
	ERPComboBox* combox;
signals:

public slots:
		void indexedFillEvent(QString completion);
		void linkPressed();

		void refrenceData(QList<QJsonDocument> items);
};

#endif // SUBFIELDUI_H