#ifndef NAVIGATIONPAGEEDITUI_H
#define NAVIGATIONPAGEEDITUI_H

#include "maindisplay.h"
#include "mainform.h"
#include "headerlabel.h"
#include "pagestructureviewediteui.h"
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
private:
	QVBoxLayout *layout;
	HeaderLabel* headerlbl;
	static NavigationPageEditUI* p_instance;
	QGroupBox *createFirstExclusiveGroup();
	QGroupBox *cardDetails ;
	QGroupBox *pageDetails ;
	QJsonObject structureView;
signals:

public slots:
	void btn_Clicked(QString btn);
	void cardToggled(bool state);
	void pageToggled(bool state);
};

#endif // NAVIGATIONPAGEEDITUI_H
