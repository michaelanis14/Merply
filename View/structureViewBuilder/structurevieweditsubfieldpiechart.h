#ifndef STRUCTUREVIEWEDITSUBFIELDPIECHART_H
#define STRUCTUREVIEWEDITSUBFIELDPIECHART_H

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
class StructureViewEditSubFieldPieChart : public QChartView
{
public:
    QMap<QString,double> chartMap = QMap<QString,double>();
    StructureViewEditSubFieldPieChart();
    QChart *addData(QMap<QString, double> chartDataSent, QString chartNameSent);
    QChart* structure;
    QChartView *getPieChart();
    QJsonObject save();
    QString chartName;
    //QChart* fillData(QMap<QString,double> chartData,QString chartName);
    QChartView* fill (QJsonObject DataSaved);
};

#endif // STRUCTUREVIEWEDITSUBFIELDPIECHART_H
