#include "graphwidget.h"
#include <QDebug>
#include <QFile>
#include <QPainter>
#include <QTextStream>
#include <QDateTime>
#include <math.h>

GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent)
{
    regime = 2;
    if (regime == 0)
        depth = 12;
    else
        //depth = 12;
        depth = 35;
    lineLength   = 70;
    angle        = 22;
    koef         = 0.667;
    probability1 = 1;
    probability2 = 1;
    withLeafs    = true;
    leafsColorR  = 220;
    leafsColorG  = 200;
    leafsColorB  = 0;
    leafsColor   = QColor(leafsColorR, leafsColorG, leafsColorB);
    stemColor    = QColor(  0,   0,   0);

    leafSize1 = 7;
    leafSize2 = 7;

    qsrand(time(NULL));
}

int GraphWidget::randomColorDeviation()
{
    return 50 * (qrand() / float(RAND_MAX)) -
           std::min(std::min(leafsColorR, leafsColorG), leafsColorB) / 2;
}

QColor GraphWidget::getNewLeafsColor()
{
    if (regime == 2)
    {
        QColor newLeafsColor(std::min(int(leafsColorR + 0), 255),
                             std::min(int(leafsColorG + randomColorDeviation()), 255),
                             std::min(int(leafsColorB + randomColorDeviation()), 255));
        return newLeafsColor;
    }
    else
        return leafsColor;
}

void GraphWidget::recursiveFuction(QPointF currentPoint, int currentDepth,
                                   int currentAngle, int currentLength, bool wasOne)
{
    QPainter painter1(this);
    if (currentDepth >= depth)
    {
        if (withLeafs == true)
        {
            painter1.setBrush(QBrush(getNewLeafsColor()));
            painter1.drawRect(std::max(int(currentPoint.x() - leafSize1 / 2), 0),
                              std::max(int(currentPoint.y() - leafSize2 / 2), 0),
                              leafSize1,
                              leafSize2);
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
            leafSize1 = int(fmax(abs(qrand() / float(RAND_MAX)) * 30, 10));
            leafSize2 = int(fmax(abs(qrand() / float(RAND_MAX)) * 30, 10));
            painter1.setBrush(QBrush(getNewLeafsColor()));
            painter1.drawRect(std::max(int(angleline1.p2().x() - leafSize1 / 2), 0),
                              std::max(int(angleline1.p2().y() - leafSize2 / 2), 0),
                              leafSize1,
                              leafSize2);
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
                             currentAngle - (0.5 - currentProb4) * 3,
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
    QPointF startPoint(this->width() / 2, this->height() * 95 / 100);
    bool wasOne = false;
    recursiveFuction(startPoint, 0, 90, lineLength, wasOne);
}
