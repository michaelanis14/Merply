#ifndef CREATEEDITUI_H
#define CREATEEDITUI_H


#include "maindisplay.h"
#include "viewgroups.h"
#include <QObject>
#include <QWidget>
#include <QJsonObject>
#include <QVBoxLayout>

class CreateEditUI : public MainDisplay
{
	Q_OBJECT
public:
	explicit CreateEditUI(QWidget *parent = 0,QJsonObject viewStructure = QJsonObject(),QJsonObject data = QJsonObject());
	static void ShowUI(QJsonObject viewStructure,QJsonObject data);
private:
	static CreateEditUI* p_instance;
	void fill(QJsonObject viewStructure,QJsonObject data);
	void clear();
	QWidget* createEditWidget;
	QVBoxLayout *createEditWidgetLayout;
	QWidget* errorsWidget;
	QVBoxLayout *errorsWidgetLayout;
	QVBoxLayout *layout;
	ViewGroups * viewGroups;
	QJsonObject viewStructure;
	QString cas;
	QJsonObject data;
	void clearErrorsWidget();
signals:
protected:
	//void showEvent(QShowEvent *);
	void paintEvent(QPaintEvent*event);
public slots:
	void controller_Clicked(QString nameAction);
};

#endif // CREATEEDITUI_H
