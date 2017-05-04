#ifndef STRUCTUREVIEWEDITSUBFIELDBARGRAPH_H
#define STRUCTUREVIEWEDITSUBFIELDBARGRAPH_H

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
class StructureViewEditSubFieldBarGraph: public QChartView
{
public:
    StructureViewEditSubFieldBarGraph(QString vhType);
    QString type;
    int barsCount;
    QString barGraphName;
    QChart* structure;
    QList<QString>axisNames;
    QList<QPair<QString,QList<double> >* >barGraphPairs;
    QChart* addData(QList<QPair<QString,QList<double> >* > chartDataSent, QList<QString> axisNamesSent, QString chartNameSent);
    QChart* addDataHorizontal(QList<QPair<QString,QList<double> >* > chartDataSent, QList<QString> axisNamesSent, QString chartNameSent);

    QChartView *getGraphChart();
    QJsonObject save();
    QChartView* fill (QJsonObject DataSaved);

};

#endif // STRUCTUREVIEWEDITSUBFIELDBARGRAPH_H
