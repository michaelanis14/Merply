/**************************************************************************
** File: MainForm.h
** Created on: Wed Feb 18 2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/


#ifndef MAINFORM_H
#define MAINFORM_H
#include "qpainter.h"

#include "timelineui.h"
#include "navigationui.h"
#include "hnavigationui.h"

#include <QDateTime>
#include <QWidget>
#include <QPaintEvent>
#include <QStyleOption>

class MainDisplay;
class QVBoxLayout;


class MainForm : public QWidget
{
	Q_OBJECT

public:
	static MainForm* Get();
	static void ShowDisplay(MainDisplay *display);
	MainDisplay* GetCurrentDisplay() const;
	MainForm* GetMainDisplay() const;
	static QDateTime lastEvent;

private:
	explicit MainForm();

	timelineUI* timeline;
	navigationUI* navigation;
	HNavigationUI* hnavigation;
	static MainForm* p_instance;
	class MainDisplay* currentDisplay;
	class QVBoxLayout* boxLayout;

	void resizeEvent(QResizeEvent* event);
	void paintEvent(QPaintEvent *);
};

#endif // MAINFORM_H
