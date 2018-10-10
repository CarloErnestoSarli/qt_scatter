/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chartview.h"
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>
#include <QCategoryAxis>

ChartView::ChartView(QWidget *parent) :
    QChartView(new QChart(), parent)
{
    //![1]
    QScatterSeries *series0 = new QScatterSeries();
    series0->setName("scatter1");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(10.0);


    //![1]
    std::vector<QChar> letters = readCsv();

    //![2]
    //!
    qDebug() << letters.size();

    for(int i =0; i<letters.size()-1; ++i)
    {
        QChar lX = letters.at(i).toLower();
        QChar lY = letters.at(++i).toLower();
        int x = convertLetterToInt(lX);
        int y = convertLetterToInt(lY);

        *series0 << QPointF(x,y);
    }


    //![2]

    //![3]


    //![3]

    //![4]
    QString alpha = {"abcdefghijklmnopqrstuvwxyz"};

    setRenderHint(QPainter::Antialiasing);
    chart()->addSeries(series0);

    QCategoryAxis *xAxis = new QCategoryAxis();
    xAxis->setRange(0, 25);
    xAxis->setTickCount(26);
    QCategoryAxis *yAxis = new QCategoryAxis();
    yAxis->setRange(0, 25);

    for(int i =0; i < 26; ++i)
    {

        xAxis->append((QString)alpha[i], i+ 0.5);
        yAxis->append((QString)alpha[i], i +0.5);
    }



    chart()->setTitle("Simple scatterchart example");
    chart()->setAxisX(xAxis, series0);
    chart()->setAxisY(yAxis, series0);
    //chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);
    //![4]

    //![5]
    chart()->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
    //![5]
}

int ChartView::convertLetterToInt(QChar l)
{
    return l.toLatin1() - 'a';
}

std::vector<QChar> ChartView::readCsv()
{
    std::vector<QChar> letters;

    QFile file("D:/Users/Carlo/git/C++/Qt/qt_bars/InternetOfEnergy.csv");
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug() << "File does not exists";
        }else
        {
            QTextStream in(&file);
            in.readLine();
            while(!in.atEnd())
            {
                QString line = in.readLine();
                for(int i=0; i < line.length(); ++i )
                {
                    if(line.at(i).isLetter())
                    {
                        letters.push_back(line.at(i));
                    }
                }

            }
            file.close();
        }
    return letters;
}

//void ChartView::populateChart(std::vector<QChar> v)
//{
//    for(int i =0; i<v.size(); ++i)
//    {
//        QChar lX = v.at(i).toLower();
//        QChar lY = v.at(++i).toLower();
//        int x = convertLetterToInt(lX);
//        int y = convertLetterToInt(lY);
//        qDebug() << x;
//        qDebug() << y;



//    }
//}
