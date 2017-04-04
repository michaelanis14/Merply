#ifndef SEARCHUI_H
#define SEARCHUI_H

#include "maindisplay.h"
#include "mainform.h"
#include "merplytabelview.h"

#include <QObject>
#include <QWidget>

#include <QDebug>
#include <QVBoxLayout>
class SearchUI : public MainDisplay
{
	//Q_OBJECT
public:
	explicit SearchUI(QWidget* parent = 0);
	static void ShowUI(const QString document_id,const QVector<QJsonDocument> documents);
private:
	QVBoxLayout * layout;
	QString document_id;
	static SearchUI* p_instance;
	merplyTabelView * table;

	void fill(const QString document_id,const QVector<QJsonDocument> items);

};

#endif // SEARCHUI_H
