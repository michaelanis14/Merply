#ifndef DATEFILTERUI_H
#define DATEFILTERUI_H

#include <QWidget>
#include <QFormLayout>
#include <QDateTimeEdit>

class DateFilterUI : public QWidget
{
	Q_OBJECT
public:
	explicit DateFilterUI(QWidget *parent = 0);
	QString getToDateTime();
	QString getFromDateTime();
	QDateTimeEdit* from;
	QDateTimeEdit* to;
private:
	QFormLayout *layout;

signals:

public slots:
};

#endif // DATEFILTERUI_H
