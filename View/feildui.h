#ifndef FEILDUI_H
#define FEILDUI_H

#include<subfeildui.h>




class FeildUI : public QWidget
{
	Q_OBJECT
public:
	explicit FeildUI(QWidget *parent = 0,QString strID = ""
			, QJsonObject structureView = QJsonObject(), QJsonObject data = QJsonObject());
//	void clear();
	QJsonObject save();

private:
	QLabel* btnRemove;
	QHBoxLayout * layout;
	QList<SubFieldUI*> subFields;
	QLabel * label;
	QString strID;
signals:

protected:
	void mousePressEvent(QMouseEvent *event);

public slots:
	void btnRemovePressed();
};

#endif // FEILDUI_H
