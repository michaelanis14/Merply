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
	explicit PermissionsUI(QWidget *parent = 0,QJsonObject saved = QJsonObject());
	QGroupBox *permissionsBox ;
	QVBoxLayout *layout;
	QJsonObject save();
	PermissionFieldUI *pfRead;
	void load(QJsonObject saved);
	ExpandButton* btnExpand;
private:

	void updateDescription();
signals:

public slots:
	void showPermissions();
	void hidePermissions();
};

#endif // PERMISSIONSUI_H
