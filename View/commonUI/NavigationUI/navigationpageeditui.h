#ifndef NAVIGATIONPAGEEDITUI_H
#define NAVIGATIONPAGEEDITUI_H

#include "maindisplay.h"
#include "mainform.h"
#include "headerlabel.h"
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
private:
	QVBoxLayout *layout;
	HeaderLabel* headerlbl;
	static NavigationPageEditUI* p_instance;
	QGroupBox *createFirstExclusiveGroup();
signals:

public slots:
	void btn_Clicked(QString btn);
};

#endif // NAVIGATIONPAGEEDITUI_H
