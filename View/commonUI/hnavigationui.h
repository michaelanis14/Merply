#ifndef VNAVIGATIONUI_H
#define VNAVIGATIONUI_H


#include "qpainter.h"

#include <QWidget>
#include <QLabel>
#include <QButtonGroup>
#include <QDebug>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPalette>

class HNavigationTab:public QWidget
{
public:
	 HNavigationTab(QWidget *parent = 0, QWidget * display = 0, QString title= "NA");

	 QLabel *getTab() const;
	 void setTab(QLabel *value);
	 QWidget *getDisplay() const;
	 void setDisplay(QWidget *value);

private:
	 QLabel *tab;
	 QWidget *display;
	 QHBoxLayout* layout;
	 void paintEvent(QPaintEvent *);
};

class HNavigationUI : public QWidget
{
	Q_OBJECT
public:
	static HNavigationUI* Get();
	void addTab(QWidget* widget,QString title);
	QWidget* getDisplayByTabName(QString tabName);
	QList<HNavigationTab *> getTabs() const;
	void setTabs(const QList<HNavigationTab *> &value);
	void tabChanged(HNavigationTab* selectedTab);
	void clearTabs();
	void addWidget(QWidget* widget);

	void resizeEvent(QResizeEvent* event);
private:
	explicit HNavigationUI(QWidget *parent = 0);
	static HNavigationUI* p_instance;
	QHBoxLayout* layout;
	QList<HNavigationTab*> tabs;
	void paintEvent(QPaintEvent *);

protected:
	void mousePressEvent(QMouseEvent *event);


};

#endif // VNAVIGATIONUI_H
