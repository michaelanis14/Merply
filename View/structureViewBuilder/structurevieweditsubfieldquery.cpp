/**
@brief this class is made for the Query Choice .. Choosing a Query and Writing it in the Text box . replacing the Keywords with the Entity Reference ..
@author Andrew Assad
*/

#include "structurevieweditsubfieldquery.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "structureviewgroupsui.h"
#include "erpcombobox.h"
#include "controller.h"
StructureVieweditSubFieldQuery::StructureVieweditSubFieldQuery(QWidget *parent) : QWidget(parent)
{

    this->setContentsMargins(0,0,0,0);
    this->setAutoFillBackground(true);
    this->setObjectName("queryWidget");

    key = new QLineEdit();
    keyLabel = new QLabel("#");
    valueLabel = new QLabel("Replace");
    queryWidgetLayout = new QHBoxLayout();
    this->setLayout(queryWidgetLayout);
    entities = new ERPComboBox();


    queryWidgetLayout->addWidget(keyLabel);
    queryWidgetLayout->addWidget(key);
    queryWidgetLayout->addWidget(valueLabel);
    queryWidgetLayout->addWidget(entities);

}


QJsonObject StructureVieweditSubFieldQuery::save()//Saving data inside the Database
{
    QJsonObject save;
    save.insert("Keyword",key->text());
    save.insert("EntityReference",entities->currentText());
    return save;
}

void StructureVieweditSubFieldQuery::fill(QString Replacment,QString Key)//Filling the Choice Saved into the COmbobox and the editline
{
    this->key->setText(Key);
    this->entities->setCurrentText(Replacment);
}

void StructureVieweditSubFieldQuery::setFieldsNames(QStringList queryListNames) // Filling the ERPComboBox with the Fields Names
{
    QObject::disconnect(StructureViewGroupsUI::GetUI(),SIGNAL(gotFieldsNames(QStringList)),this,SLOT(setFieldsNames(QStringList)));
    entities->addItems(queryListNames);
}
