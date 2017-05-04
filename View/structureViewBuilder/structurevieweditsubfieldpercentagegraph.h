#ifndef STRUCTUREVIEWEDITSUBFIELDPERCENTAGEGRAPH_H
#define STRUCTUREVIEWEDITSUBFIELDPERCENTAGEGRAPH_H

#include <QObject>
#include <QWidget>
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

class StructureViewEditSubFieldPercentageGraph: public QChartView
{
public:
    StructureViewEditSubFieldPercentageGraph(QString vhType);
    QString type;
        int barsCount;
        QString percentageGraphName;
        QChart* structure;
        QList<QString>axisNames;
        QList<QPair<QString,QList<double> >* >percentageGraphPairs;
        QChart* addData( QList<QPair<QString,QList<double> >* > chartDataSent,QList<QString> axisNamesSent, QString chartNameSent);
        QChart* addDataHorizontal( QList<QPair<QString,QList<double> >* > chartDataSent,QList<QString> axisNamesSent, QString chartNameSent);

        QChartView *getGraphChart();
        QJsonObject save();
        QChartView* fill (QJsonObject DataSaved);

};

#endif // STRUCTUREVIEWEDITSUBFIELDPERCENTAGEGRAPH_H
