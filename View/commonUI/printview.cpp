/*************************************
**   Created on:  12/4/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/

#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif
#include <QStyleOptionViewItem>

#include "printview.h"

PrintView::PrintView()
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void PrintView::print(QPrinter *printer)
{
#ifndef QT_NO_PRINTER
	resize(printer->width(), printer->height());
	render(printer);
#endif
}
