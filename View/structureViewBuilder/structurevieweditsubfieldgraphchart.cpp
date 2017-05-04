#include "structurevieweditsubfieldgraphchart.h"
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QHBoxLayout>
#include <QPieSeries>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QPercentBarSeries>
#include <QHorizontalBarSeries>
#include <QValueAxis>
#include <QHorizontalPercentBarSeries>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
StructureViewEditSubFieldGraphChart::StructureViewEditSubFieldGraphChart()
{
    graphMap = QMap<double,double>();
    graphMap.insert(0,6);
    graphMap.insert(2,4);
    graphMap.insert(3,8);
    graphMap.insert(7,4);
    graphMap.insert(10,5);
    graphName = "Graph Test";
    addData(graphMap,graphName);
}


QChartView* StructureViewEditSubFieldGraphChart::getGraphChart()
{

    QChartView* graphChartView = new QChartView();
    graphChartView->setChart(structure);
    graphChartView->setRenderHint(QPainter::Antialiasing);
    return graphChartView;
}

QChart* StructureViewEditSubFieldGraphChart::addData(QMap<double,double> chartDataSent,QString chartNameSent)
{
    this->graphMap = chartDataSent;
    this->graphName = chartNameSent;
    QChart* chart = new QChart();
    QLineSeries *series = new QLineSeries();
    QMapIterator<double,double> mapInidicator(graphMap);
    while(mapInidicator.hasNext())
    {
        mapInidicator.next();
        series->append(mapInidicator.key(),mapInidicator.value());
    }
    chart->addSeries(series);
    QBrush *brush = new QBrush(QColor("Black"));
    chart->setTitle(graphName);
    chart->setTitleBrush(*brush);
    chart->createDefaultAxes();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setAlignment(Qt::AlignLeft);
    this->structure = chart;
    return chart;

}

QJsonObject StructureViewEditSubFieldGraphChart :: save()
{
    QJsonObject saveObject;

    saveObject.insert("ChartType","Graph Chart");
    saveObject.insert("ChartName",graphName);
    //qDebug() <<chartMap;
    QMapIterator<double,double> mapIndicator(graphMap);
    QJsonArray xAxisArray;
    QJsonArray yAxisArray;
    while (mapIndicator.hasNext())
    {
        mapIndicator.next();
        xAxisArray.append(mapIndicator.key());
        yAxisArray.append(mapIndicator.value());
    }
    saveObject.insert("xAxis",xAxisArray);
    saveObject.insert("yAxis",yAxisArray);
    //qDebug() << saveObject;
    fill(saveObject);
    return saveObject;
}

QChartView* StructureViewEditSubFieldGraphChart:: fill (QJsonObject DataSaved)
{
    graphName = DataSaved.value("ChartName").toString();
    //qDebug() << chartName;
    QList <double> xAxis;
    //int count = 0 ;
    QList<double> yAxis;
    QJsonArray xAxisArray = DataSaved.value("xAxis").toArray();
    QJsonArray yAxisArray = DataSaved.value("yAxis").toArray();
    int count = 0 ;
    foreach(QJsonValue sliceName,xAxisArray)
    {
        xAxis.push_back(xAxisArray[count].toDouble());
        count++;
    }
    count = 0 ;
    foreach (QJsonValue sliceValue,yAxisArray)
    {
        yAxis.push_back(yAxisArray[count].toDouble());
        count ++ ;
    }
    for(int i =0;i<xAxisArray.count();i++)
    {
        graphMap.insert(xAxis[i],yAxis[i]);
    }

   this->structure = addData(graphMap,graphName);
   return getGraphChart() ;
}

