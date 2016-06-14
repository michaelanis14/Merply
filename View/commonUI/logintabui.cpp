#include "logintabui.h"
#include "accesscontroller.h"
#include "controller.h"

LoginTabUI::LoginTabUI(QWidget *parent) : QWidget(parent)
{
	this->setContentsMargins(0,0,0,0);
	this->setObjectName("LoginTabUI");
	this->layout = new QVBoxLayout(this);
	this->layout->setContentsMargins(0,0,0,0);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



	user = new QPushButton(tr("Helloo!"));
	user->setObjectName("user");
	//user->setFixedHeight(40);
	user->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	user->setFlat(true);
	user->setStyleSheet("QPushButton::menu-indicator {image:;}"
						"QPushButton{background-color: white;border-style: outset;border-top: 0px;border-bottom: 0px;border-width: 1px; border-color: white;font: 12px; min-width: 7em;}");
	this->layout->addWidget(user);


	menu = new QMenu("Menu");

	menu->addSeparator();
	user->setMenu(menu);

	logout = new QAction(tr("&Logout"), this);
	//logout->setShortcuts(QKeySequence::New);
	logout->setStatusTip(tr("Logout of the system"));
	QObject::connect(logout, SIGNAL(triggered(bool)), this, SLOT(logoutSlot()));
	menu->addAction(logout);

	//this->layout->addWidget(menu);



	QObject::connect(AccessController::Get(),SIGNAL(successLogin()),this,SLOT(update()));
	//	/this->setAutoFillBackground(true);


}
LoginTabUI* LoginTabUI::p_instance = 0;
LoginTabUI*LoginTabUI::Get()
{
	if (p_instance == 0){
		p_instance = new LoginTabUI();
		}
	return p_instance;
}

void LoginTabUI::update()
{
	user->setText(tr("Welcome, ")+ AccessController::Get()->getUserName());
}

void LoginTabUI::logoutSlot()
{
	AccessController::Get()->logout();

}
