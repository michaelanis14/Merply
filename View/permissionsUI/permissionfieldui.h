#ifndef PERMISSIONFIELDUI_H
#define PERMISSIONFIELDUI_H

#include "erpcombobox.h"

#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include <QFormLayout>
#include <QGroupBox>

class PermissionFieldUI : public QWidget
{
	Q_OBJECT
public:
	explicit PermissionFieldUI(QWidget *parent = 0, QString name = "Field");
private:
	ERPComboBox* readPermissons;
	QGroupBox* allowGroupBox;
	QTreeWidget *allowGroup;
	QTreeWidget *denyGroup;
	QFormLayout* layout;
signals:

public slots:
	void showSpcfic(int field);
	void allowGroupPressed(QTreeWidgetItem* item, int column);
	void denyGroupPressed(QTreeWidgetItem* item, int column);
};

#endif // PERMISSIONFIELDUI_H
