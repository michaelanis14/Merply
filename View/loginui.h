#ifndef LOGINUI_H
#define LOGINUI_H

#include "maindisplay.h"
#include <QObject>
#include <QWidget>
#include <QJsonObject>
#include <QFormLayout>
#include <QPushButton>

class LoginUI : public MainDisplay
{
	Q_OBJECT
public:
	explicit LoginUI(QWidget *parent = 0);
	static void ShowUI();
private:
	static LoginUI* p_instance;
	QLineEdit* usrname;
	QLineEdit* password;
	QPushButton* submit;
	void clear();
	QFormLayout *layout;
	QJsonObject viewStructure;
signals:

public slots:
	void submitUser();
	void successLogin();
	void faildLogin();
};

#endif // LOGINUI_H
