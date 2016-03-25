#ifndef FILEPATHUI_H
#define FILEPATHUI_H

#include <QWidget>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

class filepathUI : public QWidget
{
	Q_OBJECT
public:
	explicit filepathUI(QWidget *parent = 0);

	QLineEdit* getLineEdit() const;
	void setLineEdit(QLineEdit* value);

private:
	QHBoxLayout* filepathLayout;
	QLabel * open;
	QLineEdit* lineEdit;

signals:


protected:
	void mousePressEvent(QMouseEvent *event);

public slots:
};

#endif // FILEPATHUI_H
