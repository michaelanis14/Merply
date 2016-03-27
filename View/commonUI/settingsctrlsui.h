#ifndef SETTINGSCTRLSUI_H
#define SETTINGSCTRLSUI_H

//#include "qpainter.h"

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPalette>
#include <QPainter>

class SettingsCtrlsUI : public QWidget
{
	Q_OBJECT
public:
	explicit SettingsCtrlsUI(QWidget *parent = 0);
	void addbtn(QString name,QString icon,QString action);
	QString getTitle() const;
	void setTitle(QString value);
	QHBoxLayout* layout;
	void clear();
private:

	QLabel *title;
	void paintEvent(QPaintEvent *);
signals:
	void btnClicked(const QString&);
	void removeClicked();
public slots:
	void btn_Clicked();
public slots:

};

#endif // SETTINGSCTRLSUI_H
