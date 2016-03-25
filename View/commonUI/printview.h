/*************************************
**   Created on:  12/4/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/
#ifndef PRINTVIEW_H
#define PRINTVIEW_H

#include <QTableView>
QT_BEGIN_NAMESPACE
class QPrinter;
QT_END_NAMESPACE

class PrintView : public QTableView
{
	Q_OBJECT

public:
	PrintView();

public Q_SLOTS:
	void print(QPrinter *printer);
};

#endif // PRINTVIEW_H
