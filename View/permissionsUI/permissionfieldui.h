#ifndef PERMISSIONFIELDUI_H
#define PERMISSIONFIELDUI_H

#include "erpcombobox.h"

#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include <QFormLayout>
#include <QGroupBox>
#include <QPushButton>

class PermissionFieldUI : public QWidget
{
	Q_OBJECT
public:
	explicit PermissionFieldUI(QWidget *parent = 0, QString name = "Field", QJsonObject saved = QJsonObject());
	QJsonObject save();
	void load(QJsonObject saved);
private:
	ERPComboBox* readPermissons;
	QGroupBox* allowGroupBox;
	QTreeWidget *allowGroup;
	QGroupBox* denyGroupBox;
	QTreeWidget *denyGroup;
	QFormLayout* layout;
	ERPComboBox* usersforAllowedList;
	ERPComboBox* usersforDeniedList;
	QPushButton* btnAddDeny ;
	QPushButton* btnAddAllowed;
	QStringList getAllowed();
	QStringList getDenied();
	void addAllowed(QString title,QString key);
	void addDenied(QString title,QString key);

signals:

public slots:
	void showSpcfic(int field);
	void allowGroupPressed(QTreeWidgetItem* item, int column);
	void denyGroupPressed(QTreeWidgetItem* item, int column);
	void addDenied();
	void addAllowed();

	void loadUsers(QList<QJsonDocument> users);
};

#endif // PERMISSIONFIELDUI_H
