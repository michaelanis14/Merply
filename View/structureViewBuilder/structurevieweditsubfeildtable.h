#ifndef STRUCTUREVIEWEDITSUBFEILDTABLE_H
#define STRUCTUREVIEWEDITSUBFEILDTABLE_H

#include "feildui.h"
#include "structurevieweditsubfeildtablecolumn.h"

#include <QObject>
#include <QWidget>

class StructureVieweditSubFeildTable : public QWidget
{
	Q_OBJECT
public:
	explicit StructureVieweditSubFeildTable(QWidget *parent = 0, QJsonObject tblStractureView = QJsonObject());
	QJsonObject save();
private:
	QHBoxLayout *layout;
	QHBoxLayout *clmnsLayout;
	QList<StructureVieweditSubFeildTableColumn*> clmns;

signals:
	void tableChanged();



public slots:
	void addColumn();
};

#endif // STRUCTUREVIEWEDITSUBFEILDTABLE_H
