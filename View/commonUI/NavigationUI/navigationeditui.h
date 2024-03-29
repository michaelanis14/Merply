#ifndef NAVIGATIONEDITUI_H
#define NAVIGATIONEDITUI_H


#include "navigationbtn.h"
#include "controller.h"
#include "navigationui.h"
#include <QObject>
#include <QWidget>

class NavigationEditUI : public QWidget
{
	Q_OBJECT
public:
	static NavigationEditUI* Get();
	void loadMainNavigation(QJsonDocument navDoc);
	QList<QTreeWidgetItem*> loadSubNavigation(QJsonArray subNav);
	void save();
	explicit NavigationEditUI(QWidget *parent = 0);

private:
	static NavigationEditUI* p_instance;
	QVBoxLayout* layout;

	SettingsCtrlsUI* sctrlUI;
	QTreeWidget *subNavigation;
	QTreeWidget *mainNavigation;
	void paintEvent(QPaintEvent *);
	bool editMode;
	void addSubNavChild(QTreeWidgetItem* parent);
	void addSubNavTopItem();
	void addMainNavTopItem(QString title = "", double key = -1);
	void fillSubNavigation(double key);
	int idCount;
	QJsonObject page;
	int currentSubNav;
	void savePage(bool updateDataBase);
	QTreeWidgetItem* oldItemSubNavSelected;
	bool rootOnly;
	bool updateDataBase;
public slots:
	void mainNavPressed(QTreeWidgetItem* item, int column);
	void mainNavChanged(QTreeWidgetItem* item, int);
	void subNavPressed(QTreeWidgetItem* item, int column);
	void btn_Clicked(QString btn);
//	void btn_ClickedDataReturned(QJsonDocument document);

	void editControllerCancelPressed();
	void editControllerSavePressed();
	void savePageData(QJsonObject savedPage);
signals:
	void subNavPressed(QJsonObject view);
};

#endif // NAVIGATIONEDITUI_H
