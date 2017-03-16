/**************************************************************************
** File: MainForm.cpp
** Created on: Wed Feb 18 2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/


#include "mainform.h"
#include "maindisplay.h"
#include "model.h"
#include "controller.h"


#include "logintabui.h"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QLinearGradient>


/**
* @author Michael Bishara
* @date   18 February, 2015
* @brief  constructor.
*
* Main class constructor: init the style sheets, load specific settings for each operating system
* set the minimum window size and intialize the display's stack layout.
*/
MainForm::MainForm(): QWidget()
{
	/*
#ifndef Q_OS_WIN332
#endif

#ifdef Q_OS_WIN32
	QApplication::setStyle(new QCleanlooksStyle);
#endif
*/
	//border-right: 1px solid rgb(255, 170, 0);
	this->setWindowTitle("Merply[*]");
	this->setWindowModified(false);
	this->setStyleSheet(
				// make background white
				"timelineUI { border: 1px solid gray;background-color: white;}"
				"navigationUI { background-color: white;}"
				"QLabel#Tab {  background: #4B6884; color: white; padding: 5px; font-size: 10pt;font-weight: bold;text-align:center;}"
				"QLabel#mandatory {  color: red; padding: 0px; font-size: 10pt;}"
				//"QWidget{background-color: white; color:black;}"
				"QScrollArea #formPanel {background-color: white;}"
				//"QScrollArea {background-color: black;background: black;}"
				"StructureViewsEditUI {background-color: black; border:11px } "
				//"MainForm {  background-color: white; background-image: url(:/resources/Background.png);} "
				"QLabel#TabSelected { color: black;background: white;padding: 5px; font-size: 10pt;font-weight: bold;text-align:center; } "
				//	"QTabWidget::pane { border: 0; } "
				//	  "QWidget { background: lightgray; } "
				//"QWidget { outline: 0; }"  // removing dotted-border in all controls
				//"QWidget:focus { outline: 0; }"  // removing dotted-border in all controls
				"StructureViewEdit#preview{ border: 11px solid gray;}"
				"QWidget#ViewGroups{ border: 1px solid gray;}"

				"QWidget#errorsWidget{ background: red;}"
				"QWidget#errorsWidget#QLabel{ color: red;}"

				"QWidget#ViewGroup{ border: 2px solid gray;}"
				"QCheckBox {spacing: 5px;}"
				"QCheckBox::indicator {width: 13px;height: 13px;}"
				"QComboBox#ERPComboBoxIndexed {  border:1px solid gray; border-color:  gray gray  gray gray;  } "
				"QComboBox#ERPComboBoxIndexed::down-arrow {image: url(noimg); border: 0px;}"
				"QComboBox#ERPComboBoxIndexed::drop-down {border-width: 0px; border:  0;}"
				"QComboBox#ERPComboBoxIndexed::drop-down:disabled{border:  0;}"

				"QTreeWidget{outline:0; border-style: none; outline: none; background: #4B6384; color: white; border-width:0px; selection-background-color: transparent;}"
				"QTreeWidget::item{ background: #4B6384; color: white; padding: 3px; font-weight: normal;text-align:center;"
				"font: 400 6.0pt;}"
				"QTreeWidget::item:has-children{ background: #4B6384; border-right: 0px solid rgb(255, 0, 255);}"
				"QTreeView::item:selected {background: rgba(255, 0, 0, 50%);}"
				"QTreeView::branch:has-children:!has-siblings:closed,QTreeView::branch:closed:has-children:has-siblings "
				"{ margin: 0px 0px 0px 0px;}"
				"QTreeView::branch:open:has-children:!has-siblings,"
				"QTreeView::branch:open:has-children:has-siblings  {"
				"     margin: 0px 0px 0px 0px; }"
				"QLineEdit {"
				//"background-color: gray;"
				"border-style: outset;"
				"border-width: 0.5px;"
				"border-radius: 5px;"
				"border-color: grey;"
				"font: 14px;"
				//"min-width: 10em;"
				//"padding: 6px;"
				"}"

				"QLineEdit:focus {"
				//"background-color: rgb(76, 200, 98);"
				"border-style: inset;"
				"}"
				"QLineEdit#error { border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: red;}"
				//"QPushButton {border: 1px solid rgb(100, 100, 100);min-width: 70px;min-height: 30px;}"
				"QLineEdit { border: 1px solid rgb(100, 100, 100);min-width: 150px;min-height: 30px;}"
				"QComboBox{  border: 1px solid rgb(100, 100, 100);min-width: 150px;min-height: 30px; } "
				"QGroupBox::title	{subcontrol-origin: margin;subcontrol-position: top left;padding: 5 5px;font-size: 18px;font-weight: bold;border-radius: 5px; background:gray;min-width: 100px;}"
				);
	this->setMinimumSize(Controller::GetWindowWidth(),Controller::GetWindowHeight());


	boxLayout = new QVBoxLayout(this);
	//	boxLayout->setContentsMargins(0, 0, 0, 0);
	boxLayout->setContentsMargins(NAVIGATION_WIDTH, NAVIGATION_HEIGHT, 0, 0);

	//timeline = timelineUI::Get();
	//timeline->setParent(this);
	//timeline->move(0,0);

	navigation =  navigationUI::Get();
	navigation->setParent(this);
	//navigation->setFixedHeight(this->width()- Controller::GetTimeLineWidth());
	navigation->move(0,0);
	// navigationUI::Get()->raise();

	hnavigation =  HNavigationUI::Get();
	hnavigation->setParent(this);
	hnavigation->move(NAVIGATION_WIDTH,0);
	hnavigation->addWidget(LoginTabUI::Get());
	currentDisplay = 0;

}


// initialize static singleton pointer of the MainForm
MainForm* MainForm::p_instance = NULL;
MainForm *MainForm::Get()
{
	if (NULL == p_instance)
		p_instance = new MainForm();

	return p_instance;
}

/**
* @author Michael Bishara
* @date   18 February, 2015
* @brief  function shows a display.
* @param [MainDisplay *]display pointer the the display that will be shown on the main window
*
* A function.
* receives display and add it the main window to be the current display
**/

void MainForm::ShowDisplay(MainDisplay * display) {

	///if(AccessController::hasAccess())
	if (p_instance != NULL)
		p_instance->show();

	if (p_instance->currentDisplay != 0)
		p_instance->currentDisplay->hide();
	p_instance->boxLayout->addWidget((QWidget*)display);
	if (p_instance->currentDisplay != 0)
		display->setGeometry(0,0,p_instance->currentDisplay->width(),p_instance->currentDisplay->height());
	//qDebug() << __FILE__ << __LINE__  << p_instance->currentDisplay->objectName() << p_instance->currentDisplay->height();
	p_instance->currentDisplay = display;
	p_instance->currentDisplay->scrollAreaFormPanel->setGeometry(0,0,display->width(),display->height());

	display->show();
	display->setFocus();
}

/**
* @author Michael Bishara
* @date   18 February, 2015
* @brief  function show a display.
*
* A function.
* returns the current display object
**/
MainDisplay* MainForm::GetCurrentDisplay() const {
	return p_instance->currentDisplay;
}

// Testing the new Keyboard Woooow Hello What is this yayyyywassup people this is michael Anis lkhdjhflhdlfj;da;lkjap

/**
* @author Michael Bishara
* @date   18 February, 2015
* @brief  function show a display.
*
* A function.
* returns the main window object
**/
MainForm* MainForm::GetMainDisplay() const {
	return p_instance;
}
void MainForm::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MainForm::resizeEvent(QResizeEvent* event) {

	navigationUI::Get()->setFixedHeight(event->size().height());
	HNavigationUI::Get()->setFixedWidth(event->size().width() - Controller::GetNavigationWidth() );
	if (p_instance->currentDisplay != 0)
		currentDisplay->scrollAreaFormPanel->setGeometry(0,0,this->width() - NAVIGATION_WIDTH,this->height() - NAVIGATION_HEIGHT);
	this->QWidget::resizeEvent(event);

}

