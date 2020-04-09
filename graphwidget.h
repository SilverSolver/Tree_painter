#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QFile>
#include <QSet>
#include <QPointF>
#include <qpainter.h>

class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    int randomColorDeviation();
    QColor getNewLeafsColor();
    void recursiveFuction(QPointF currentPoint, int currentDepth, int currentAngle, int currentLength, bool wasOne);

    int regime;
    int depth;
    int angle;

    double lineLength;
    double koef;
    double probability1;
    double probability2;

    bool withLeafs;
    QColor leafsColor;
    QColor stemColor;

    QPainter painter1;

private:
    //QVector<QPointF> currentPoints;
    //QVector<double> currentData;
    //QFile* currentFile;
    uint leafsColorR;
    uint leafsColorG;
    uint leafsColorB;

    int leafSize1;
    int leafSize2;
signals:

public slots:
};

#endif // GRAPHWIDGET_H
