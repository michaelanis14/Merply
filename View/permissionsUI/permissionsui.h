#ifndef PERMISSIONSUI_H
#define PERMISSIONSUI_H
#include "permissionfieldui.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QObject>
#include <QWidget>


class PermissionsUI : public QWidget
{
	Q_OBJECT
public:
	explicit PermissionsUI(QWidget *parent = 0);
	QGroupBox *permissionsBox ;
	QVBoxLayout *layout;

signals:

public slots:
};

#endif // PERMISSIONSUI_H
