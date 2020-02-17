#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <iostream>

bool drawShape = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("/Users/jamiehaywood/testAnnotation.jpg");
    int w = ui->labelMainPic->width();
    int h = ui->labelMainPic->height();
    ui->labelMainPic->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (drawShape == true){
        std::cout<<"Test"<<std::endl;
        drawShape = false;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    drawShape = true;
    std::cout<<"Button Test"<<std::endl;

}
