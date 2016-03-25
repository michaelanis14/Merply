#ifndef HCONTROLLERS_H
#define HCONTROLLERS_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QPainter>
#include <QStyleOption>

class HControllers : public QWidget
{
	Q_OBJECT
public:
	explicit HControllers(QWidget *parent = 0, QStringList btns = QStringList());
	QHBoxLayout* layout;
	void fill(QStringList btns);
	void clear();
private:

signals:
	void btnClicked(const QString&);
public slots:
	void btn_Clicked();
protected:
	//void showEvent(QShowEvent *);
	void paintEvent(QPaintEvent*event);
};

#endif // HCONTROLLERS_H
