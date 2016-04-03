#ifndef STRUCTUREVIEWSEDITUI_H
#define STRUCTUREVIEWSEDITUI_H
#include "feildui.h"
#include "structureviewedit.h"
#include <QWidget>

class StructureViewsEditUI : public QWidget
{
	Q_OBJECT
public:
	explicit StructureViewsEditUI(QWidget *parent = 0, QJsonObject structureView = QJsonObject(),bool links = false);
	QJsonObject save();
	QComboBox* group;
	QLineEdit* groupName;
	ERPComboBox* Style;
	QCheckBox* joinCheck;
	SettingsCtrlsUI* topCntrlsPreview;
	void loadGroup();
private:
	QVBoxLayout *layout;
	QList<StructureViewEdit *> sVSFs;
	QJsonObject structureView;
	QWidget* groupSelect;
	QWidget* joinGroup ;
	bool init;
	QLabel* imgExplain;
	QPixmap imgVertical;
	QPixmap imgHorizontal;
	QWidget* layoutPreview;
	QHBoxLayout* layoutPreviewLayout;
	SettingsCtrlsUI* topCntrls;

	bool hidePreview(bool hide);
	void updateLayoutPreview();
	QWidget* styleSelect;
	QStringList styles;
	void loadStyle();
	void addStrField(QJsonValue fieldVS);

protected:
	bool links;
signals:
	void changed();
	void styleChanged();
	void updateLayout();

public slots:
	//void updatePreview(bool oldStrct = false);
	void controller_Clicked(QString btn);
	void styleChanged(QString layout);
	void joinGroupChanged(bool join);
	void groupActivated(int);

	void removeField(QWidget* field);
};

#endif // STRUCTUREVIEWSEDITUI_H
