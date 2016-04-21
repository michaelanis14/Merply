#ifndef NAVIGATIONPAGEEDITUI_H
#define NAVIGATIONPAGEEDITUI_H

#include "maindisplay.h"
#include "mainform.h"
#include "headerlabel.h"
#include "pagestructureviewediteui.h"
#include "structureviewgroupsui.h"
#include "permissionsui.h"

#include <QGroupBox>
#include <QRadioButton>

#include <QObject>
#include <QWidget>

class NavigationPageEditUI : public MainDisplay
{
	Q_OBJECT
public:
	explicit NavigationPageEditUI(QWidget *parent = 0);
	static void ShowUI(QJsonObject structureView);
	void fill(QJsonObject structureView);
	QJsonObject save();
	static NavigationPageEditUI* Get();
private:
	QVBoxLayout *layout;
	HeaderLabel* headerlbl;
	static NavigationPageEditUI* p_instance;
	QGroupBox *newCardDetails ;
	QGroupBox *cardDetails ;
	QGroupBox *pageDetails ;
	QJsonObject structureView;
	//QStringList cardsItems;
	QStringList viewList;
	PageStructureViewEditeUI* pageEdit;
	StructureViewGroupsUI * newCardStructure;
	QRadioButton *newCard ;
	QRadioButton *card ;
	QRadioButton *page;
	ERPComboBox* cards;
	ERPComboBox* view;
	PermissionsUI* permissions;
signals:
	void editControllerSavePressed();
	void editControllerCancelPressed();


public slots:
	void btn_Clicked(QString btn);
	void newCardToggled(bool state);
	void cardToggled(bool state);
	void pageToggled(bool state);
	void getCardData(QList<QJsonDocument> items);
};

#endif // NAVIGATIONPAGEEDITUI_H
