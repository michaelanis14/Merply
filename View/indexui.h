#ifndef INDEXUI_H
#define INDEXUI_H

#include "maindisplay.h"
#include "mainform.h"
#include "merplytabelview.h"
#include "createeditui.h"

#include <QObject>
#include <QWidget>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDebug>
#include <QPaintEvent>

#include <QJsonObject>

class IndexUI : public MainDisplay
{
	Q_OBJECT
public:
	explicit IndexUI(QWidget *parent = 0, const QString document_id = 0);
	void showUI();
private:
	QVBoxLayout * layout;
	merplyTabelView * table ;
	CreateEditUI* createEditUI;
	QPushButton* btnCreatNew;
	QString document_id;
signals:

public slots:
	void createNew();
	void editEntity(int tbl,int id);
};

#endif // INDEXUI_H
