#include "structurevieweditsubfieldpercentagegraph.h"

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


StructureViewEditSubFieldPercentageGraph::StructureViewEditSubFieldPercentageGraph(QString vhType)
{
    this->type = vhType;
        //this->barsCount = numberOfBars;

        QList<double>randomNumbers;
        QList<double>randomNumbers1;
        QList<double>randomNumbers2;
        QList<double>randomNumbers3;
        QList<double>randomNumbers4;


        randomNumbers << 1 << 2 << 3 << 4 << 5 << 6;
        randomNumbers1 << 5 << 0 << 0 << 4 << 0 << 7;
        randomNumbers2 << 3 << 5 << 8 << 13 << 8 << 5;
        randomNumbers3 << 5 << 6 << 7 << 3 << 4 << 5;
        randomNumbers4<< 9 << 7 << 5 << 3 << 1 << 2;

        QPair<QString,QList<double> >*RandomPair = new QPair<QString,QList<double> > ("Firstone",randomNumbers);
        QPair<QString,QList<double> >*RandomPair1 = new QPair<QString,QList<double> > ("Secondone",randomNumbers1);
        QPair<QString,QList<double> >*RandomPair2 = new QPair<QString,QList<double> > ("Thirdone",randomNumbers2);
        QPair<QString,QList<double> >*RandomPair3 = new QPair<QString,QList<double> > ("Forthone",randomNumbers3);
        QPair<QString,QList<double> >*RandomPair4 = new QPair<QString,QList<double> > ("Fifthone",randomNumbers4);

        percentageGraphPairs << RandomPair;
        percentageGraphPairs << RandomPair1;
        percentageGraphPairs << RandomPair2;
        percentageGraphPairs << RandomPair3;
        percentageGraphPairs << RandomPair4;

        QList<QString> randomNames;
        randomNames << "2010" << "2011" << "2012" << "2013" << "2014" << "2015";

        if(this->type == "Vertical")
            addData(percentageGraphPairs,randomNames,"Test Vertical PercentageGraph");
        else if (this->type == "Horizontal")
            addDataHorizontal(percentageGraphPairs,randomNames,"Test Vertical PercentageGraph");
}


QChartView* StructureViewEditSubFieldPercentageGraph::getGraphChart()
{
    QChartView* graphChartView = new QChartView();
    graphChartView->setChart(structure);
    graphChartView->setRenderHint(QPainter::Antialiasing);
    return graphChartView;
}


QChart* StructureViewEditSubFieldPercentageGraph::addData( QList<QPair<QString,QList<double> >* > chartDataSent,QList<QString> axisNamesSent, QString chartNameSent)
{
    this->percentageGraphPairs = chartDataSent;
    this->percentageGraphName = chartNameSent;
    this->axisNames = axisNamesSent;
    QChart* chart = new QChart();
    QList<QBarSet*> barSets;
    QPercentBarSeries *barSeries = new QPercentBarSeries();
    for(int i = 0 ; i < percentageGraphPairs.count();i++)
    {
        QBarSet *tempSet = new QBarSet(percentageGraphPairs[i]->first);
        //qDebug() << mapIndicatorTemp.key();
        for(int j = 0 ; j < percentageGraphPairs[i]->second.count();j++)
        {
            *tempSet << percentageGraphPairs[i]->second [j];
        }
        barSets << tempSet;
    }
    for(int i = 0 ; i < barSets.count();i++)
    {
        barSeries->append(barSets[i]);
    }
    chart->addSeries(barSeries);
    QBrush *brush = new QBrush(QColor("Black"));
    chart->setTitle(percentageGraphName);
    chart->setTitleBrush(*brush);
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(axisNames);
    chart->createDefaultAxes();
    chart->setAxisX(axis, barSeries);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setAlignment(Qt::AlignBottom);
    return chart;
}

QChart* StructureViewEditSubFieldPercentageGraph::addDataHorizontal( QList<QPair<QString,QList<double> >* > chartDataSent,QList<QString> axisNamesSent, QString chartNameSent)
{
    this->percentageGraphPairs = chartDataSent;
    this->percentageGraphName = chartNameSent;
    this->axisNames = axisNamesSent;
    QChart* chart = new QChart();
    QList<QBarSet*> barSets;
    QHorizontalPercentBarSeries *barSeries = new QHorizontalPercentBarSeries();
    for(int i = 0 ; i < percentageGraphPairs.count();i++)
    {
        QBarSet *tempSet = new QBarSet(percentageGraphPairs[i]->first);
        //qDebug() << mapIndicatorTemp.key();
        for(int j = 0 ; j < percentageGraphPairs[i]->second.count();j++)
        {
            *tempSet << percentageGraphPairs[i]->second [j];
        }
        barSets << tempSet;
    }
    for(int i = 0 ; i < barSets.count();i++)
    {
        barSeries->append(barSets[i]);
    }
    chart->addSeries(barSeries);
    QBrush *brush = new QBrush(QColor("Black"));
    chart->setTitle(percentageGraphName);
    chart->setTitleBrush(*brush);
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    QValueAxis *axisX = new QValueAxis();
    chart->setAxisX(axisX, barSeries);
    axisX->applyNiceNumbers();
    axis->append(axisNames);
    chart->createDefaultAxes();
    chart->setAxisY(axis, barSeries);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setAlignment(Qt::AlignBottom);
    return chart;
}
QJsonObject StructureViewEditSubFieldPercentageGraph :: save()
{
    QJsonObject saveObject;
    if(this->type =="Vertical")
        saveObject.insert("ChartType","Vertical Percentage Graph");
    else if (this->type == "Horizontal")
        saveObject.insert("ChartType","Horizontal Percentage Graph");

    saveObject.insert("TypeOfChart",type);
    saveObject.insert("ChartName",percentageGraphName);
    //qDebug() <<chartMap;
    QJsonArray namesArray;
    QList<QJsonArray> ValuesArray;
    QJsonArray axisNamesArray;
    for(int i = 0 ; i < axisNames.count();i++)
    {
        axisNamesArray.append(axisNames[i]);
    }
    for(int i = 0 ; i < percentageGraphPairs.count();i++)
    {
        namesArray.append(percentageGraphPairs[i]->first);
        QJsonArray temp;
        for(int j = 0 ; j < percentageGraphPairs[i]->second.count();j++)
        {
            temp.append(percentageGraphPairs[i]->second [j]);
        }
        ValuesArray << temp;
    }
    saveObject.insert("AxisNames",axisNamesArray);
    saveObject.insert("BarNames",namesArray);
    saveObject.insert("Number",ValuesArray.count());
    for(int i = 0 ; i < ValuesArray.count();i++)
    {
        saveObject.insert("BarValues" + QString::number(i),ValuesArray[i]);
    }

    //qDebug() << saveObject;
    fill(saveObject);
    return saveObject;
}

QChartView* StructureViewEditSubFieldPercentageGraph:: fill (QJsonObject DataSaved)
{
    percentageGraphName = DataSaved.value("ChartName").toString();
    //qDebug() << chartName;
    type = DataSaved.value("TypeOfChart").toString();
    QList <QString> BarNames;
    //int count = 0 ;
    QList<QList<double>> Values;
    QJsonArray BarNameArray = DataSaved.value("BarNames").toArray();
    QList<QJsonArray> valueArray ;
    int count = 0;
    foreach(QJsonValue axisNamesValues,DataSaved.value("AxisNames").toArray())
    {
        axisNames<<DataSaved.value("AxisNames").toArray()[count].toString();
        count++;
    }

    int tempCounter = 0;
    int numberOfBars = DataSaved.value("Number").toInt();
    for(int i = 0 ; i < numberOfBars;i++)
    {
       valueArray << DataSaved.value("BarValues" + QString::number(i)).toArray();
       tempCounter++;
    }


    count = 0 ;
    foreach(QJsonValue BarName,BarNameArray)
    {
        BarNames<< BarNameArray[count].toString();
        count++;
    }
    for(int i = 0 ; i < valueArray.count();i++)
    {
        QList<double> temp;
        count =0;
        foreach (QJsonValue value, valueArray[i]) {
            temp.append(valueArray[i][count].toDouble());
            count++;
        }
        Values.append(temp);
    }
    for(int i =0;i<Values.count();i++)
    {
        QPair<QString,QList<double> >*randomPair = new QPair<QString,QList<double> > (BarNames[i],Values[i]);
        percentageGraphPairs << randomPair;
    }
    if(this->type == "Vertical")
        this->structure = addData(percentageGraphPairs,axisNames,percentageGraphName);

    else
        this->structure = addDataHorizontal(percentageGraphPairs,axisNames,percentageGraphName);

   return getGraphChart() ;
}

