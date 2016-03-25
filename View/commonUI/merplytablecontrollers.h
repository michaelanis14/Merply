#ifndef MERPLYTABLECONTROLLERS_H
#define MERPLYTABLECONTROLLERS_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>

class merplyTableControllers : public QWidget
{
	Q_OBJECT
public:
	explicit merplyTableControllers(QWidget *parent = 0,QString id ="", const bool edit = false, const bool remove = false);
private:
	QPushButton* btn_edit;
	QPushButton* btn_delete;
	QHBoxLayout* layout;
	QString id;

signals:
	void editClicked(const QString&);
	void deleteClicked(const QString&);
public slots:
	void btn_editClicked();
	void btn_deleteClicked();
};

#endif // MERPLYTABLECONTROLLERS_H
