#ifndef STRUCTUREVIEWGROUPSUI_H
#define STRUCTUREVIEWGROUPSUI_H

#include "maindisplay.h"
#include "viewgroups.h"
#include "structureviewseditui.h"
#include "mainform.h"
#include "headerlabel.h"

#include <QObject>
#include <QWidget>

class StructureViewGroupsUI : public MainDisplay
{
	Q_OBJECT
public:
	explicit StructureViewGroupsUI(QWidget *parent = 0, QJsonObject structureView = QJsonObject(), QStringList restrictedTypes = QStringList());
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
	QString cas_value;
	QString document_id;
protected:

	QStringList restrictedTypes;


signals:
	void cancel();
	void gotFieldsNames(QStringList names);
public slots:
	void btn_Clicked(QString btn);
	void viewGroupStyleChanged();
	void updateLayout();
	void removeViewgroup(QWidget* field);
	void editControllerCancelPressed();
	void editControllerSavePressed();
	void getFeildsNames();


protected:
	void mousePressEvent(QMouseEvent *event);

};

#endif // STRUCTUREVIEWGROUPSUI_H
