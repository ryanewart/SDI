#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <iostream>
#include <list>
#include <QMessageBox>

int clicks = 0;
int x1;
int y1;
int Awidth;
int Aheight;
int type;

std::vector<int> allCoords;
std::vector<coords> PolyPoints;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("");
    int w = ui->labelMainPic->width();
    int h = ui->labelMainPic->height();
    ui->labelMainPic->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMessageBox PolyBox;
    int count = 0;
    QPainter painter(this);
    painter.setBrush(Qt::DiagCrossPattern);

    QPen pen;

    pen.setColor(Qt::green);
    pen.setWidth(5);

    painter.setPen(pen);
    if (type == 1) {
        painter.drawRect(QRect(x1,y1,-Awidth,-Aheight));
        if (clicks == 3) {
            painter.drawRect(QRect(x1,y1,-Awidth,-Aheight));
            allCoords.push_back(x1);
            allCoords.push_back(y1);
            allCoords.push_back(Awidth);
            allCoords.push_back(Aheight);
            clicks = 0;
        }
    }
    if (allCoords.empty() == false) {
        for (int i = 0; i<allCoords.size(); i = i+4)
        painter.drawRect(QRect(allCoords[i],allCoords[i+1],-allCoords[i+2],-allCoords[i+3]));
    }

    if (type == 3) {
        int xDiff = PolyPoints[PolyPoints.size()-1].x -PolyPoints[0].x;
        int yDiff = PolyPoints[PolyPoints.size()-1].y -PolyPoints[0].y;
        if ((xDiff < 5 && xDiff >-5) && (yDiff < 5 && yDiff >-5)) {
            type = 0;
        }
    }
    if (PolyPoints.size() > 1) {
        for (int j = 1; j < (PolyPoints.size()); j++) {
            painter.drawLine(PolyPoints[j-1].x, PolyPoints[j-1].y, PolyPoints[j].x, PolyPoints[j].y);
        }
    }
    if (PolyPoints.size() == 9) {
        PolyBox.setText("This shape can only have a maximum of 8 points");
        PolyBox.exec();
        PolyPoints.clear();
        type = 0;
    }
}



void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    QPoint coords = QCursor::pos();
    mapFromGlobal(QCursor::pos());
    if (clicks != 0) {
    //std::cout<<"x:"<<(coords.x())<<std::endl;
    //std::cout<<"y:"<<(coords.y())<<std::endl;
    Awidth = Awidth = x1 - (coords.x()-130);
    Aheight = y1 - (coords.y()-120);
    if (type ==3) {
    PolyPoints[PolyPoints.size()-1] = {coords.x()-130,coords.y()-120};
    }
    repaint();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    QPoint coords = QCursor::pos();
    //std::cout<<"x:"<<(coords.x())<<std::endl;
    //std::cout<<"y:"<<(coords.y())<<std::endl;

    //square
    if (type == 1) {
        if (clicks == 2) {
            mapFromGlobal(QCursor::pos());
            Awidth = x1 - (coords.x()-130);
            Aheight = y1 - (coords.y()-120);
            clicks = clicks+1;
        }

        if (clicks == 1){
            mapFromGlobal(QCursor::pos());
            x1 = coords.x()-130;
            y1 = coords.y()-120;
            clicks++;
        }
    }

    //Polygon
    if  (type == 3) {
        //clicks = clicks+1;

        PolyPoints.push_back({coords.x()-130,coords.y()-120});

        }
    repaint();
}


void MainWindow::on_pushButton_2_clicked()
{
    clicks = 1;
    type = 1;

}

void MainWindow::on_pushButton_clicked()
{
    //clicks = 1;

    std::cout<<"Button Test"<<std::endl;
}

void MainWindow::on_pushButton_5_clicked()
{
    type = 0;
    allCoords.clear();
    PolyPoints.clear();
    repaint();
}

void MainWindow::on_pushButton_4_clicked()
{
    clicks = 1;     //temporary, change to method in class
    type = 3;
}
