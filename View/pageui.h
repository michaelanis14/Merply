#ifndef PAGEUI_H
#define PAGEUI_H

#include "headerlabel.h"

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
	HeaderLabel* headerlbl;
private:
	static PageUI* p_instance;
	HControllers* controllers ;
	void fill(QJsonObject viewStructure);
	void clear();
	//QWidget* createEditWidget;
	//QVBoxLayout *createEditWidgetLayout;
	QVBoxLayout *layout;
	ViewGroups * viewGroups;
	QString document_id;

signals:

public slots:
	void controller_Clicked(QString nameAction);
};

#endif // PAGEUI_H
