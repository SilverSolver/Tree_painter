#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileInfo>
#include <QDateTime>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    helpBox = new QMessageBox();
    helpBox->setText("\n\
Left arrow key - decrease angle \n\
Right arrow key - increase angle \n\
Space key - redraw \n\
L key - leafs ON/OFF \n\
                      \n");
    helpBox->move(int(this->width()/2), int(this->height()/2));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
    {
        ui->graphWidget->angle -= 1;
        break;
    }
    case Qt::Key_Right:
    {
        ui->graphWidget->angle += 1;
        break;
    }
    case Qt::Key_L:
    {
        ui->graphWidget->withLeafs = !ui->graphWidget->withLeafs;
        break;
    }
    case Qt::Key_F1:
    {
        helpBox->exec();
        break;
    }
    case Qt::Key_Space:
    {
        ui->graphWidget->repaint();
        break;
    }
    default:
        break;
    }
    repaint();
}

void MainWindow::on_actionSave_picture_triggered()
{
    QString dateTime = QDateTime::currentDateTime().toString();
    int sec = (QDateTime::currentMSecsSinceEpoch() % (60 * 1000)) / 1000;
    int ms  = QDateTime::currentMSecsSinceEpoch() % 1000;
    dateTime.replace(QRegExp("[\\:|\\ |\\.]"), "_");
    dateTime += (QString::number(sec) + "_" + QString::number(ms));

    QString folder = "./picturesGenerated";
    if (!QDir(folder).exists())
        QDir().mkdir(folder);

    QString filePath = folder + "/tree_from_" + dateTime + ".png";
    qDebug() << filePath;
    ui->graphWidget->grab().save(filePath);
}
