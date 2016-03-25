#ifndef HEADERLABEL_H
#define HEADERLABEL_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPalette>
#include <QPainter>

class HeaderLabel : public QWidget
{
	Q_OBJECT
public:
	explicit HeaderLabel(QWidget *parent = 0);
	QString getTitle() const;
	void setTitle(QString value);
private:
	QHBoxLayout* layout;
	QLineEdit *title;
	void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // HEADERLABEL_H
