#include "structurevieweditsubfieldbargraph.h"
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


StructureViewEditSubFieldBarGraph::StructureViewEditSubFieldBarGraph(QString vhType)
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

    barGraphPairs << RandomPair;
    barGraphPairs << RandomPair1;
    barGraphPairs << RandomPair2;
    barGraphPairs << RandomPair3;
    barGraphPairs << RandomPair4;

    QList<QString> randomNames;
    randomNames << "2010" << "2011" << "2012" << "2013" << "2014" << "2015";

    if(type == "Vertical")
        addData(barGraphPairs,randomNames,"Test Vertical BarsGraph");
    else if (type == "Horizontal")
        addDataHorizontal(barGraphPairs,randomNames,"Test Horizontal BarsGraph");

    qDebug()<<"Tamaam ";
}

QChartView* StructureViewEditSubFieldBarGraph::getGraphChart()
{
    QChartView* graphChartView = new QChartView();
    graphChartView->setChart(structure);
    graphChartView->setRenderHint(QPainter::Antialiasing);
    return graphChartView;
}


QChart* StructureViewEditSubFieldBarGraph::addData( QList<QPair<QString,QList<double> >* > chartDataSent,QList<QString> axisNamesSent, QString chartNameSent)
{
    this->barGraphPairs = chartDataSent;
    this->barGraphName = chartNameSent;
    this->axisNames = axisNamesSent;
    QChart* chart = new QChart();
    QList<QBarSet*> barSets;
    QBarSeries *barSeries = new QBarSeries();
    for(int i = 0 ; i < barGraphPairs.count();i++)
    {
       QBarSet *tempSet = new QBarSet(barGraphPairs[i]->first);
       //qDebug() << mapIndicatorTemp.key();
        for(int j = 0 ; j < barGraphPairs[i]->second.count();j++)
         {
            *tempSet << barGraphPairs[i]->second [j];
         }
        barSets << tempSet;
     }
    for(int i = 0 ; i < barSets.count();i++)
    {
        barSeries->append(barSets[i]);
    }
    //qDebug()<<"BAr Graph zeft";
    chart->addSeries(barSeries);
    QBrush *brush = new QBrush(QColor("Black"));
    chart->setTitle(barGraphName);
    chart->setTitleBrush(*brush);
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(axisNames);
    chart->createDefaultAxes();
    chart->setAxisX(axis, barSeries);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setAlignment(Qt::AlignBottom);
    qDebug() << "ELMAFROOD MAGIISH HENA !!!!";
    return chart;
}
QChart* StructureViewEditSubFieldBarGraph::addDataHorizontal( QList<QPair<QString,QList<double> >* > chartDataSent,QList<QString> axisNamesSent, QString chartNameSent)
{
    this->barGraphPairs = chartDataSent;
    this->barGraphName = chartNameSent;
    this->axisNames = axisNamesSent;
    QList<QBarSet*> barSets;
    QHorizontalBarSeries *barSeries = new QHorizontalBarSeries();
    for(int i = 0 ; i < barGraphPairs.count();i++)
    {
        QBarSet *tempSet = new QBarSet(barGraphPairs[i]->first);
        //qDebug() << mapIndicatorTemp.key();
        for(int j = 0 ; j < barGraphPairs[i]->second.count();j++)
        {
            *tempSet << barGraphPairs[i]->second [j];
        }
        barSets << tempSet;
    }
    for(int i = 0 ; i < barGraphPairs.count();i++)
    {
        barSeries->append(barSets[i]);
    }
    QChart *chart = new QChart();
    chart->addSeries(barSeries);
    QBrush *brush = new QBrush(QColor("Black"));
    chart->setTitle(barGraphName);
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


QJsonObject StructureViewEditSubFieldBarGraph :: save()
{
    QJsonObject saveObject;
    if(this->type =="Vertical")
        saveObject.insert("ChartType","Vertical Bar Graph");
    else if (this->type == "Horizontal")
        saveObject.insert("ChartType","Horizontal Bar Graph");
    saveObject.insert("TypeOfChart",type);
    saveObject.insert("ChartName",barGraphName);
    //qDebug() <<chartMap;
    QJsonArray namesArray;
    QList<QJsonArray> ValuesArray;
    QJsonArray axisNamesArray;
    for(int i = 0 ; i < axisNames.count();i++)
    {
        axisNamesArray.append(axisNames[i]);
    }
    for(int i = 0 ; i < barGraphPairs.count();i++)
    {
        namesArray.append(barGraphPairs[i]->first);
        QJsonArray temp;
        for(int j = 0 ; j < barGraphPairs[i]->second.count();j++)
        {
            temp.append(barGraphPairs[i]->second [j]);
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

    qDebug() << saveObject;
    fill(saveObject);
    return saveObject;
}

QChartView* StructureViewEditSubFieldBarGraph:: fill (QJsonObject DataSaved)
{
    barGraphName = DataSaved.value("ChartName").toString();
    type = DataSaved.value("TypeOfChart").toString();
    //qDebug() << chartName;
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
        barGraphPairs << randomPair;
    }
    if(this->type == "Vertical")
       this->structure = addData(barGraphPairs,axisNames,barGraphName);
    else
        this->structure = addDataHorizontal(barGraphPairs,axisNames,barGraphName);
    return getGraphChart() ;
}
