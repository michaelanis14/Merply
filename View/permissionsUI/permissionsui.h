#ifndef PERMISSIONSUI_H
#define PERMISSIONSUI_H
#include "permissionfieldui.h"
#include "expandbutton.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QObject>
#include <QWidget>



class PermissionsUI : public QWidget
{
	Q_OBJECT
public:
	explicit PermissionsUI(QWidget *parent = 0,bool read = false,bool write = false);
	QGroupBox *permissionsBox ;
	QVBoxLayout *layout;
	QJsonObject save();
	PermissionFieldUI *pfRead;
	PermissionFieldUI *pfWrite;
	void load(QJsonObject saved);
	ExpandButton* btnExpand;
private:
	bool read;
	bool write;
	void updateDescription();
signals:

public slots:
	void showPermissions();
	void hidePermissions();
};

#endif // PERMISSIONSUI_H
