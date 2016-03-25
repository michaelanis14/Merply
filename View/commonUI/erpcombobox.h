/*************************************
**   Created on:  10/4/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/

#ifndef ERPCOMBOBOX_H
#define ERPCOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QKeyEvent>

class ERPComboBox : public QComboBox
{
	Q_OBJECT
public:
	explicit ERPComboBox(QWidget *parent = 0 ,bool indexedFill = false);
	void addItems(QList<QString >);
	int getKey();
	bool addedItems;
	bool indexedFill;
private:
	QList<QString>  items;
	QString oldCompletion;
signals:
	void refreshModel();
	void indexedFillEvent(QString completion);
public slots:

protected slots:
	void focusOutEvent(QFocusEvent *e);
protected:
	//void mousePressEvent(QMouseEvent *event);
	//virtual void  keyPressEvent(QKeyEvent *event);
	 bool eventFilter(QObject *obj, QEvent *event);


};

#endif // ERPCOMBOBOX_H
