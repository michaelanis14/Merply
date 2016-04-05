#ifndef PAGEUI_H
#define PAGEUI_H

#include "maindisplay.h"
#include "viewgroups.h"


#include <QObject>
#include <QWidget>
#include <QJsonObject>
#include <QVBoxLayout>

class PageUI : public MainDisplay
{
	Q_OBJECT
public:
	explicit PageUI(QWidget *parent = 0, QJsonObject viewStructure = QJsonObject());
	static void ShowUI(QJsonObject viewStructure);
private:
	static PageUI* p_instance;
	void fill(QJsonObject viewStructure);
	void clear();
	//QWidget* createEditWidget;
	//QVBoxLayout *createEditWidgetLayout;
	QVBoxLayout *layout;
	ViewGroups * viewGroups;
signals:

public slots:
};

#endif // PAGEUI_H
