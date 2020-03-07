#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <iostream>
#include<QPainter>
#include<vector>
#include<list>
#include "LinkedList.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    struct coords {
        int x,y;
    };

    std::vector<coords> PolyPoints;

    std::vector<std::vector<coords>> allPolys;

    std::vector<int> allCoords;


    int clicks = 0;

    int x1;

    int y1;

    int Awidth;

    int Aheight;

    int type;

private slots:

    void mouseMoveEvent(QMouseEvent *event)Q_DECL_OVERRIDE;


    virtual void paintEvent(QPaintEvent *event)Q_DECL_OVERRIDE;

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_actionOpen_triggered();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

