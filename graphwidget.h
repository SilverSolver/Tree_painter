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

signals:

public slots:
};

#endif // GRAPHWIDGET_H
