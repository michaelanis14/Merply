#ifndef REMOVEBTN_H
#define REMOVEBTN_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

#include "settingsctrlsui.h"

class RemoveBtn : public QWidget
{
	Q_OBJECT
public:
	explicit RemoveBtn(QWidget *parent = 0,QWidget *widget = 0);
	void hideRemovebtn(bool hidden);
private:
	QHBoxLayout *layout;
	SettingsCtrlsUI * rmvbtn;
	QLabel* lblCancel;
	QWidget* widget;
	QLabel* lblDelete;
	void removeAll();
signals:
	void remove(QWidget* widget);
public slots:
	void remove();


protected:
	void mousePressEvent(QMouseEvent *event);

};

#endif // REMOVEBTN_H
