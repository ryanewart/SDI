#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <iostream>
#include <list>
#include <QMessageBox>
#include <QFileDialog>
#include <QPolygon>


coords triangle[3];
coords trap[4];

std:: vector<QPolygon> Triangles;

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
    QImage tmp(ui->labelMainPic->pixmap()->toImage());
    QMessageBox PolyBox;
    int count = 0;
    QPainter painter(this);
    painter.setBrush(Qt::DiagCrossPattern);

    QPen pen;

    pen.setColor(Qt::green);
    pen.setWidth(5);

    painter.setPen(pen);
    if (allCoords.empty() == false) {
        for (int i = 0; i<allCoords.size(); i = i+4)
        painter.drawRect(QRect(allCoords[i],allCoords[i+1],-allCoords[i+2],-allCoords[i+3]));
    }
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
    if(allPolys.size() > 0) {
        for (int count = 0; count<allPolys.size();count++) {
            for (int j = 1; j < allPolys[count].size(); j++) {
                painter.drawLine(allPolys[count][j-1].x, allPolys[count][j-1].y, allPolys[count][j].x, allPolys[count][j].y);
            }
        }

    }
    if (Triangles.empty() == false) {
        for (int i = 0; i< Triangles.size(); i++) {
                painter.drawPolygon(Triangles[i]);
            }
    }

    if (type == 2) {
        QPolygon polyLines;
        if (clicks == 4) {
            polyLines << QPoint(triangle[0].x,triangle[0].y);
            polyLines << QPoint(triangle[1].x,triangle[1].y);
            polyLines << QPoint(triangle[2].x,triangle[2].y);
            painter.drawPolygon(polyLines);
            Triangles.push_back(polyLines);
            clicks = 5;
            type = 0;
            polyLines.clear();
        }
        if (clicks == 3) {//Triangle
            polyLines << QPoint(triangle[0].x,triangle[0].y);
            polyLines << QPoint(triangle[1].x,triangle[1].y);
            polyLines << QPoint(triangle[2].x,triangle[2].y);
            painter.drawPolygon(polyLines);


        }
    }

    if (type == 3) {
        if (PolyPoints.size() > 2) {
            int xDiff = PolyPoints[PolyPoints.size()-1].x -PolyPoints[0].x;
            int yDiff = PolyPoints[PolyPoints.size()-1].y -PolyPoints[0].y;
            if (((xDiff < 5 && xDiff >-5) && (yDiff < 5 && yDiff >-5)) && (PolyPoints.size()>2)) {
                PolyPoints[PolyPoints.size()-1] = PolyPoints[0];
                type = 0;
                allPolys.push_back(PolyPoints);
                PolyPoints.clear();
        }
    }
    }

    if (type == 4) { //trapezium
        if (clicks = 2) {
            trap[2] = {(trap[0].x+(trap[0].x/5)),trap[1].y};
            trap[3] = {(trap[1].x+(trap[1].x/5)),trap[0].y};
            QPolygon polyLines;
            polyLines << QPoint(trap[0].x,trap[0].y);
            polyLines << QPoint(trap[2].x,trap[2].y);
            polyLines << QPoint(trap[1].x,trap[1].y);
            polyLines << QPoint(trap[3].x,trap[3].y);
            painter.drawPolygon(polyLines);
        }
    }

    if (PolyPoints.size() > 0) {
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

    ui->labelMainPic->setPixmap(QPixmap::fromImage(tmp));
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    QPoint coords = QCursor::pos();
    mapFromGlobal(QCursor::pos());
    if (clicks != 0) {
    Awidth = Awidth = x1 - (coords.x()-130);
    Aheight = y1 - (coords.y()-120);
    if (type ==3 && clicks > 1) {
        PolyPoints[PolyPoints.size()-1] = {coords.x()-130,coords.y()-120};
    }
    if ((type == 2) && (clicks > 1)) {
        triangle[1] = {coords.x()-130,coords.y()-120};
        triangle[2] = {(triangle[0].x),(triangle[1].y)};
    }
    if (type == 4 && clicks >1){

    }

    repaint();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    QPoint coords = QCursor::pos();

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

    //triangle
    if (type == 2) {
        mapFromGlobal(QCursor::pos());
        x1 = coords.x()-130;
        y1 = coords.y()-120;

        if(clicks == 3) {
            clicks = 4;
        }

        if (clicks == 2) {
            triangle[1] = {x1,y1};
            triangle[2] = {(triangle[0].x),(triangle[1].y)};
            clicks = 3;

        }
        if (clicks ==1) {
            triangle[0] = {x1,y1};
            clicks = 2;
        }

    }

    //Polygon
    if  (type == 3) {
        clicks = clicks+1;
        PolyPoints.push_back({coords.x()-130,coords.y()-120});
        }

    //trap
    if (type == 4) {
        if (clicks == 2) {
            mapFromGlobal(QCursor::pos());
            x1 = coords.x()-130;
            y1 = coords.y()-120;
            trap[1] = {x1,y1};


        }
        if ( clicks == 1) {
            mapFromGlobal(QCursor::pos());
            x1 = coords.x()-130;
            y1 = coords.y()-120;
            clicks = clicks+1;
            trap[0] = {x1,y1};
        }
    }
    repaint();
}


void MainWindow::on_pushButton_2_clicked() //square button
{
    clicks = 1;
    type = 1;

}

void MainWindow::on_pushButton_clicked() //triangle button
{
    type = 2;
    clicks = 1;

}

void MainWindow::on_pushButton_5_clicked() //clear Button
{
    type = 0;
    allCoords.clear();
    PolyPoints.clear();
    allPolys.clear();
    repaint();
}

void MainWindow::on_pushButton_4_clicked() //polygon Button
{
    clicks = 1;     //temporary, change to method in class
    type = 3;
}

void MainWindow::on_pushButton_3_clicked() //trap
{
    clicks = 1;
    type = 4;
}


void MainWindow::on_actionOpen_triggered()
{
    try {

    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open file"),
                "/",
                "Images (*.png *.jpg *.jpeg)");

    if (!filename.isEmpty()){
        QString msg = "You chose the file:\n";
        QMessageBox::information(this, tr("File name"), msg.append(filename));
    }

    QPixmap pix(filename);
    int w = ui->labelMainPic->width();
    int h = ui->labelMainPic->height();

    ui->labelMainPic->setPixmap(pix.scaled(w,h, Qt::IgnoreAspectRatio));}
    catch(const std::runtime_error& e) {

    }
}

