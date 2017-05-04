#ifndef STRUCTUREVIEWEDITSUBFIELDGRAPHCHART_H
#define STRUCTUREVIEWEDITSUBFIELDGRAPHCHART_H

#include <QObject>
#include <QWidget>
#include <QChartView>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <QHBoxLayout>
#include  <QPieSeries>
#include <QFormLayout>

using namespace QtCharts;
class StructureViewEditSubFieldGraphChart : public QChartView
{
public:
    StructureViewEditSubFieldGraphChart();
    QMap<double,double> graphMap;
    QString graphName;
    QChart* structure;
    QChart* addData(QMap<double, double> chartDataSent, QString chartNameSent);

    QChartView *getGraphChart();
    QJsonObject save();
    QChartView* fill (QJsonObject DataSaved);

};

#endif // STRUCTUREVIEWEDITSUBFIELDGRAPHCHART_H
