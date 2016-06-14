#include "pagestructureviewediteui.h"

PageStructureViewEditeUI::PageStructureViewEditeUI(QWidget *parent) : StructureViewGroupsUI(parent,QJsonObject(),true)
{
	this->sctrlUI->clear();
	sctrlUI->addbtn("Add",":/resources/icons/add.png","add");
	headerlbl->hide();
}
