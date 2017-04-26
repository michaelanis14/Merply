#include "structurevieweditsubfieldpiechart.h"
#include <QLineSeries>
#include <QChart>
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

StructureViewEditSubFieldPieChart::StructureViewEditSubFieldPieChart()
{
    chartMap.insert("Oil",20);
    chartMap.insert("Coal",30);
    chartMap.insert("Natural gas",40);
    chartMap.insert("Peat",10);
    chartName = "Testing Construcotr";
    this->structure = addData(chartMap,chartName);
}

QChartView* StructureViewEditSubFieldPieChart::getPieChart()
{
    QChartView* pieChartView = new QChartView();
    pieChartView->setChart(structure);
    pieChartView->setRenderHint(QPainter::Antialiasing);
    return pieChartView;
}

QChart* StructureViewEditSubFieldPieChart::addData(QMap<QString,double> chartDataSent,QString chartNameSent)
{
    this->chartMap = chartDataSent;
    this->chartName = chartNameSent;
    QChart* chart = new QChart();
    QPieSeries *pieChart = new QPieSeries();
    double percentageTotal = 0;
    QMapIterator<QString,double> mapIndicatorTemp(chartMap);
    while(mapIndicatorTemp.hasNext())
    {
        mapIndicatorTemp.next();
        percentageTotal = percentageTotal + mapIndicatorTemp.value();
    }
    QMapIterator<QString,double> mapIndicator(chartMap);
    while(mapIndicator.hasNext())
    {
        mapIndicator.next();
        pieChart->append(mapIndicator.key()+ "  " + QString::number((mapIndicator.value()/percentageTotal) * 100) + "%" ,mapIndicator.value());
    }
    foreach (QPieSlice *slices, pieChart->slices()) {
        slices->setLabelVisible();
        //slices->setExploded();
    }
    chart->addSeries(pieChart);
    //pieChart->slices()[0]->setExploded();
    chart->setTitle(chartName);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setAlignment(Qt::AlignLeft);
    return chart;
}

QJsonObject StructureViewEditSubFieldPieChart :: save()
{
    QJsonObject saveObject;

    saveObject.insert("ChartType","Pie Chart");
    saveObject.insert("ChartName",chartName);
    //qDebug() <<chartMap;
    QMapIterator<QString,double> mapIndicator(chartMap);
    QJsonArray sliceNameArray;
    QJsonArray sliceValueArray;
    while (mapIndicator.hasNext())
    {
        mapIndicator.next();
        sliceNameArray.append(mapIndicator.key());
        sliceValueArray.append(mapIndicator.value());
    }
    saveObject.insert("SliceNames",sliceNameArray);
    saveObject.insert("SliceValue",sliceValueArray);
    //qDebug() << saveObject;
    fill(saveObject);
    return saveObject;
}

QChartView* StructureViewEditSubFieldPieChart:: fill (QJsonObject DataSaved)
{
    chartName = DataSaved.value("ChartName").toString();
    //qDebug() << chartName;
    QList <QString> sliceNames;
    //int count = 0 ;
    QList<double> sliceValues;
    QJsonArray sliceNameArray = DataSaved.value("SliceNames").toArray();
    QJsonArray sliceValueArray = DataSaved.value("SliceValue").toArray();
    int count = 0 ;
    foreach(QJsonValue sliceName,sliceNameArray)
    {
        sliceNames.push_back(sliceNameArray[count].toString());
        count++;
    }
    count = 0 ;
    foreach (QJsonValue sliceValue,sliceValueArray)
    {
        sliceValues.push_back(sliceValueArray[count].toDouble());
        count ++ ;
    }
    for(int i =0;i<sliceNameArray.count();i++)
    {
        chartMap.insert(sliceNames[i],sliceValues[i]);
    }

   this->structure = addData(chartMap,chartName);
   return getPieChart() ;
}
