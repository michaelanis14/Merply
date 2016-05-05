#ifndef STRUCTUREVIEWGROUPSUI_H
#define STRUCTUREVIEWGROUPSUI_H

#include "maindisplay.h"
#include "viewgroup.h"
#include "structureviewseditui.h"
#include "mainform.h"
#include "headerlabel.h"

#include <QObject>
#include <QWidget>

class StructureViewGroupsUI : public MainDisplay
{
	Q_OBJECT
public:
	explicit StructureViewGroupsUI(QWidget *parent = 0,QJsonObject structureView = QJsonObject(),bool links = false);
	static void ShowUI(QJsonObject structureView);
	void fill(QJsonObject structureView);
	static StructureViewGroupsUI* GetUI();
	QJsonObject save();
	HeaderLabel* headerlbl;
	SettingsCtrlsUI* sctrlUI;
private:
	QVBoxLayout *layout;

	QList<StructureViewsEditUI*> sVSFUIs;

	bool init;
	//QWidget* preview;
	static StructureViewGroupsUI* p_instance;
	//QHBoxLayout *previewLayout;
	QJsonObject structureView;
	QList<ViewGroup*> viewgroups;
	QHash<QString,QWidget*>HViewGroups;
	void paintEvent(QPaintEvent *event);
	QWidget * viewGroups;
	QVBoxLayout *viewGroupsLayout;
	void addViewgroup();
protected:

	bool links;


signals:
	void cancel();

public slots:
	void btn_Clicked(QString btn);
	void viewGroupStyleChanged();
	void updateLayout();
	void removeViewgroup(QWidget* field);
	void editControllerCancelPressed();
	void editControllerSavePressed();

protected:
	void mousePressEvent(QMouseEvent *event);

};

#endif // STRUCTUREVIEWGROUPSUI_H