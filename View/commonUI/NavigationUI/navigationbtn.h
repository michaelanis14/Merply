#ifndef NAVIGATIONBTN_H
#define NAVIGATIONBTN_H

#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include <QJsonObject>

class NavigationBtn : public QWidget
{
	Q_OBJECT
public:
	explicit NavigationBtn(QWidget *parent = 0,QString title = "");
	void addChild(QString title, QJsonObject);
private:
	QTreeWidgetItem* root;
signals:

public slots:
};

#endif // NAVIGATIONBTN_H
