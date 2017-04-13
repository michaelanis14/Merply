#ifndef SEARCHUI_H
#define SEARCHUI_H

#include "maindisplay.h"
#include "mainform.h"
#include "merplytabelview.h"
#include "settingsctrlsui.h"

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QVBoxLayout>

class SearchUI : public MainDisplay
{
	Q_OBJECT
public:
	explicit SearchUI(QWidget* parent = 0);
	static void ShowUI(const QString document_id, const QVector<QJsonDocument> documents, QString strID);
	merplyTabelView* getTable();
	static SearchUI* Get();

private:
	QVBoxLayout * layout;
	QString document_id;
	static SearchUI* p_instance;
	merplyTabelView * table;
	QString strID;
	void fill(const QString document_id,const QVector<QJsonDocument> items);
	SettingsCtrlsUI* sctrlUI;
signals:
	void btnClicked(QString);
public slots:
	void showEditUI();

};

#endif // SEARCHUI_H
