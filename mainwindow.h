#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent* event);
    ~MainWindow();

private slots:
    void on_actionSave_picture_triggered();

private:
    Ui::MainWindow *ui;
    QMessageBox* helpBox;
};

#endif // MAINWINDOW_H
