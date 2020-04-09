#include "graphwidget.h"
#include <QDebug>
#include <QFile>
#include <QPainter>
#include <QTextStream>
#include <QDateTime>
#include <math.h>

GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent)
{
    regime = 1;
    if (regime == 0)
        depth = 12;
    else
        depth = 22;
    lineLength   = 60;
    angle        = 20;
    koef         = 0.667;
    probability1 = 0.95;
    probability2 = 0.3;
    //qDebug() << depth;
    //QVector<QPointF> currentPoints;
    withLeafs    = true;
    leafsColor   = QColor( 50, 150, 255);
    stemColor    = QColor(  0,   0,   0);

    qsrand(time(NULL));
}

void GraphWidget::recursiveFuction(QPointF currentPoint, int currentDepth,
                                   int currentAngle, int currentLength, bool wasOne)
{
    QPainter painter1(this);
    if (currentDepth >= depth)
    {
        if (withLeafs == true)
        {
            int leafSize = 7;
            painter1.setBrush(QBrush(leafsColor));
            painter1.drawRect(currentPoint.x(), currentPoint.y(), leafSize, leafSize);
        }
        return;
    }
    else
    {
        /* Create the line object: */
        QLineF angleline1;
        /* Set the origin: */
        angleline1.setP1(QPointF(currentPoint));
        /* Set the angle and length: */
        angleline1.setAngle(currentAngle);
        angleline1.setLength(currentLength);
        /* Draw the line: */
        painter1.drawLine(angleline1);

        double trProb = probability1;

        if (currentAngle < 0 || currentAngle > 180)
            trProb = probability2;

        float currentProb1 = qrand();
              currentProb1 /= RAND_MAX;
              currentProb1 *= currentDepth / 3;
        float currentProb2 = qrand();
              currentProb2 /= RAND_MAX;
              currentProb2 *= currentDepth / 3;
        float currentProb3 = qrand();
              currentProb3 /= RAND_MAX;
              currentProb3 *= 5;
        float currentProb4 = qrand();
              currentProb4 /= RAND_MAX;
              currentProb4 *= 5;

        //qDebug() << wasOne;
        if (regime == 0)
        {
            currentProb1 = 0;
            currentProb2 = 0;
            currentProb3 = 0;
            currentProb4 = 0;
        }
        if (((currentProb1 >= trProb) or (currentProb2 >= trProb))
                and (withLeafs == true) and (currentDepth >= 2))
        {
            int leafSize1 = int(fmax(abs(qrand() / float(RAND_MAX)) * 20, 2));
            int leafSize2 = int(fmax(abs(qrand() / float(RAND_MAX)) * 20, 2));
            painter1.setBrush(QBrush(leafsColor));
            painter1.drawRect(angleline1.p2().x(), angleline1.p2().y(),
                              leafSize1, leafSize2);
        }
        else
            wasOne = false;

        painter1.setBrush(QBrush(stemColor));

        float koefs;
        float addAngle;

        if (regime == 0)
        {
            koefs = koef;
            addAngle = 0;
        }
        else
        {
            koefs = koef * fmin(qrand() / float(RAND_MAX) + 0.9, 1);
            addAngle = (0.5 - currentProb1) * 2;
        }

        if (currentProb1 < trProb)
        {
            //qDebug() << qrand() / float(RAND_MAX) + 0.1;

            recursiveFuction(angleline1.p2(), currentDepth + 1,
                             currentAngle + angle + addAngle,
                             currentLength * std::sqrt(koefs), wasOne);
        }
        if (currentProb2 < trProb)
        {
            recursiveFuction(angleline1.p2(), currentDepth + 1,
                             currentAngle - angle - addAngle,
                             currentLength * std::sqrt(koefs), wasOne);
        }

        if ((currentProb3 < trProb or currentDepth < 2) and (regime >= 1))
        {
            recursiveFuction(angleline1.p2(), currentDepth + 2,
                             currentAngle + (0.5 - currentProb3) * 3,
                             currentLength * std::sqrt(koefs), wasOne);
            recursiveFuction(angleline1.p2(), currentDepth + 2,
                             currentAngle + (0.5 - currentProb4) * 3,
                             currentLength * std::sqrt(koefs), wasOne);
        }

        return;
    }
}

void GraphWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    uint timestamp=QDateTime::currentDateTime().toTime_t();
    qsrand(timestamp);
    QPointF startPoint(this->width() / 2, this->height() * 7 / 8);
    bool wasOne = false;
    recursiveFuction(startPoint, 0, 90, lineLength, wasOne);
}
