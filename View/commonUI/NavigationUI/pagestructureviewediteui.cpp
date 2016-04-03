#include "pagestructureviewediteui.h"

PageStructureViewEditeUI::PageStructureViewEditeUI(QWidget *) : StructureViewGroupsUI(0,QJsonObject(),true)
{
	this->sctrlUI->clear();
	sctrlUI->addbtn("Add",":/resources/icons/add.png","add");
	headerlbl->hide();
}
