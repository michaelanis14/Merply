#ifndef PERMISSIONFIELDUI_H
#define PERMISSIONFIELDUI_H

#include <QObject>
#include <QWidget>
#include "erpcombobox.h"

class PermissionFieldUI : public QWidget
{
	Q_OBJECT
public:
	explicit PermissionFieldUI(QWidget *parent = 0, QString name = "Field");
private:
	ERPComboBox* readPermissons;
signals:

public slots:
	void showSpcfic(int field);
};

#endif // PERMISSIONFIELDUI_H
