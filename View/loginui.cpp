#include "loginui.h"
#include "mainform.h"
#include "controller.h"

LoginUI::LoginUI(QWidget *parent) : MainDisplay(parent)
{
	//this->setContentsMargins(0,0,0,0);
	this->layout = new QFormLayout(this);
	//this->layout->setContentsMargins(0,0,0,0);
	//layout->setAlignment(Qt::AlignVCenter);
	layout->setAlignment(Qt::AlignHCenter);
	//this->layout->setSpacing(0);

	usrname = new QLineEdit;
	password = new QLineEdit;
	password->setEchoMode(QLineEdit::Password);
	submit = new QPushButton(tr("submit"));
	QObject::connect(submit,SIGNAL(clicked(bool)),this,SLOT(submitUser()));
	this->layout->addRow(tr("Username"),usrname);
	this->layout->addRow(tr("Password"),password);
	this->layout->addWidget(submit);

	QObject::connect(AccessController::Get(),SIGNAL(successLogin()),this,SLOT(successLogin()));
	QObject::connect(AccessController::Get(),SIGNAL(faildLogin()),this,SLOT(faildLogin()));
}

LoginUI* LoginUI::p_instance = 0;
void LoginUI::ShowUI()
{
	if(p_instance == 0){
		p_instance = new LoginUI();
		}
	else{
		p_instance->clear();
		}
	navigationUI::Get()->hide();
	HNavigationUI::Get()->hide();
	MainForm::Get()->ShowDisplay(p_instance);
}

void LoginUI::clear()
{
	usrname->clear();
	password->clear();
}

void LoginUI::submitUser()
{
	if(usrname->text().isEmpty())
		Controller::Get()->showWarning(tr("Username can not be empty !"));
	else if(password->text().isEmpty())
		Controller::Get()->showWarning(tr("Password can not be empty !"));
	else {
		AccessController::Get()->login(usrname->text(),password->text());

		}

}

void LoginUI::successLogin()
{
	navigationUI::Get()->setHidden(false);
	HNavigationUI::Get()->setHidden(false);
}

void LoginUI::faildLogin()
{
	Controller::Get()->showWarning(tr("Wrong Username or Password"));
}
