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
	explicit StructureVieweditSubFeildTable(QWidget *parent = 0);
	QJsonObject save();
	QList<QJsonDocument> getClmnsSources(ERPComboBox* excludeSource);
	void fill(QJsonObject tblStractureView);
	QStringList getHeaders();
private:
	QHBoxLayout *layout;
	QHBoxLayout *clmnsLayout;
	QList<StructureVieweditSubFeildTableColumn*> clmns;
	QCheckBox* addEnable;
	QCheckBox* removeEnable;
	QCheckBox* editEnable;
	QJsonObject tblStractureView;
signals:

	void tableChanged();



public slots:
	void addColumn();
	void removColumn(QWidget* clmn);
};

#endif // STRUCTUREVIEWEDITSUBFEILDTABLE_H
