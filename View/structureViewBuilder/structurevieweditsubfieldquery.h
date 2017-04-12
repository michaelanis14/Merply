#ifndef STRUCTUREVIEWEDITSUBFIELDQUERY_H
#define STRUCTUREVIEWEDITSUBFIELDQUERY_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QJsonObject>
#include "erpcombobox.h"
class StructureVieweditSubFieldQuery : public QWidget
{
    Q_OBJECT
public:
    explicit StructureVieweditSubFieldQuery(QWidget *parent = 0);
    StructureVieweditSubFieldQuery(QWidget *parent, QString entitiesReference, QString keyString);
    QLineEdit* key;
    QWidget* queryWidget;
    QHBoxLayout*queryWidgetLayout;
    QList<QLineEdit*> queryList;
    QLabel* keyLabel;
    QLabel* valueLabel;
    QJsonObject save();
    ERPComboBox* entities;
    void fill(QString Replacment, QString Key);

public :
    QWidget*  getFields();


signals:

public slots:
    void setFieldsNames(QStringList queryListNames);

};

#endif // STRUCTUREVIEWEDITSUBFIELDQUERY_H
