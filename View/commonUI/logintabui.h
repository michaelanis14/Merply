#ifndef LOGINTABUI_H
#define LOGINTABUI_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QMenu>
#include <QPushButton>

class LoginTabUI : public QWidget
{
	Q_OBJECT
public:
	explicit LoginTabUI(QWidget *parent = 0);
	static LoginTabUI* Get();
private:
	static LoginTabUI* p_instance;
	QVBoxLayout* layout;
	QPushButton* user;
	QMenu* menu;
	QAction *logout;
signals:

public slots:
	void update();
	void logoutSlot();
};

#endif // LOGINTABUI_H
