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
	void save(bool updateDataBase);
	static NavigationPageEditUI* Get();

private:
	QVBoxLayout *layout;
	QScrollArea *scrollAreaPageEdit;
	HeaderLabel* headerlbl;
	static NavigationPageEditUI* p_instance;
	QGroupBox *viewBox ;
	QGroupBox *newCardDetails ;
	QGroupBox *cardDetails ;
	QGroupBox *pageDetails ;
	QGroupBox *preview ;
	QHBoxLayout* previewLayout;
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
	QString currentCardKey;
	void clearPreview();
	QJsonObject saveObject;
signals:
	void editControllerSavePressed();
	void editControllerCancelPressed();
	void saved(QJsonObject saved);


public slots:
	void btn_Clicked(QString btn);
	void newCardToggled(bool state);
	void cardToggled(bool state);
	void pageToggled(bool state);
	void getCardData(QList<QJsonDocument> items);
	void getPageData(QJsonDocument page);
	void updatePagePreview();
	void deleteCard();
	void updateNewCardPreview();
	void updateCardPreview();
	void loadCard(QJsonDocument document);
	void gotLastKeyData(QString key);
};

#endif // NAVIGATIONPAGEEDITUI_H
