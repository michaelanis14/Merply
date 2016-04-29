#ifndef EXPANDBUTTON_H
#define EXPANDBUTTON_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>


class ExpandButton : public QWidget
{
	Q_OBJECT
public:
	explicit ExpandButton(QWidget *parent = 0,QString title = "");
private:
	QHBoxLayout* layout;
	QLabel * description;
	QPushButton* btnArroW;
	bool hidden;
	QString title;
signals:
	void hide();
	void show();

public slots:
	void btnArroW_Clicked();
	void updateDescription(QString text);
};

#endif // EXPANDBUTTON_H
