#ifndef FEILDUI_H
#define FEILDUI_H

#include<subfeildui.h>
#include <QDataWidgetMapper>



class FeildUI : public QWidget
{
	Q_OBJECT
public:
	explicit FeildUI(QWidget *parent = 0,QString strID = ""
			, QJsonObject structureView = QJsonObject(),QDataWidgetMapper *mapper = new QDataWidgetMapper());
//	void clear();
	void save(QPair<QString, QString>* insertQuery, bool newDocument);
	QLabel * label;
	QList<SubFieldUI*> subFields;
	QString checkMandatory();
private:
	QLabel* btnRemove;
	QHBoxLayout * layout;
	QList<QWidget* > arrySubFields;
	QString strID;
	QJsonObject structureView;
	QVBoxLayout* fieldsWidgetLayout;
	QDataWidgetMapper *mapper;
signals:

protected:
	void mousePressEvent(QMouseEvent *event);

public slots:
	void btnRemovePressed();
	void addsubFields(QJsonArray arrDataSubFields = QJsonArray());
	void removsubFields(QWidget* subField);
};

#endif // FEILDUI_H
