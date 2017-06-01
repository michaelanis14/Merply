#ifndef INDEXUI_H
#define INDEXUI_H

#include "maindisplay.h"
#include "mainform.h"
#include "merplytabelview.h"

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
	explicit IndexUI(QWidget *parent = 0);
	static void ShowUI(const int document_id, const QVector<QJsonDocument> documents);
	void fill(const int document_id, const QVector<QJsonDocument> items);

private:
	QVBoxLayout * layout;
		static IndexUI* p_instance;
	merplyTabelView * table ;
	QPushButton* btnCreatNew;
	int document_id;
signals:

public slots:
	void createNew();
};

#endif // INDEXUI_H
