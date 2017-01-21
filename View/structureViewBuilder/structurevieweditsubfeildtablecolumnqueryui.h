#ifndef STRUCTUREVIEWEDITSUBFEILDTABLECOLUMNQUERYUI_H
#define STRUCTUREVIEWEDITSUBFEILDTABLECOLUMNQUERYUI_H


#include <structurevieweditsubfeildtablecolumnquery.h>

#include <QObject>
#include <QWidget>
#include <QPushButton>

class StructureVieweditSubFeildTableColumnQueryUI : public QWidget
{
	Q_OBJECT
public:
	explicit StructureVieweditSubFeildTableColumnQueryUI(QWidget *parent = 0);
	QJsonObject save();
	void fill(QJsonObject strct);
private:
	QTextEdit* queryBox;
	QHBoxLayout* layout;
	QPushButton* add;
	QVector<StructureVieweditSubFeildTableColumnQuery*> entityFilter;

signals:

public slots:
	void addEntityFilter(QJsonObject strct = QJsonObject());
	void removeField(QWidget* field);
};

#endif // STRUCTUREVIEWEDITSUBFEILDTABLECOLUMNQUERYUI_H
