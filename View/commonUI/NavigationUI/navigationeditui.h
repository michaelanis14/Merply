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
	void addMainNavTopItem(QString title = "", int key = -1);
	void fillSubNavigation(int key);
	int idCount;
	QJsonObject page;
	int currentSubNav;
	void savePage();
	QTreeWidgetItem* oldItemSubNavSelected;
public slots:
	void mainNavPressed(QTreeWidgetItem* item, int column);
	void subNavPressed(QTreeWidgetItem* item, int column);
	void btn_Clicked(QString btn);
	void btn_ClickedDataReturned(QJsonDocument document);

signals:
	void subNavPressed(QJsonObject view);
};

#endif // NAVIGATIONEDITUI_H
