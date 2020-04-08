#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <iostream>
#include <list>
#include <QMessageBox>
#include <QFileDialog>
#include <QPolygon>



QLabel *annotationLabel = NULL;
coords triangle[3];
coords trap[4];
bool drawing;
bool moving;
std:: vector<coords> tempShape;

std:: vector<QPolygon> Trapeziums;
int editingI,editingJ;
std::string editingType;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
<<<<<<< HEAD
    QPixmap pix("");
    int w = ui->labelMainPic->width();
    int h = ui->labelMainPic->height();
    ui->labelMainPic->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
    annotationLabel = new QLabel(this);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ShowContextMenu(const QPoint &)));
=======

    dirModel = new QFileSystemModel(this);
    dirModel->setRootPath(QDir::homePath());
    ui->treeView->setModel(dirModel);
    ui->treeView->setSortingEnabled(true);
    ui->treeView->setAnimated(true);
    ui->treeView->setColumnWidth(0, ui->treeView->width()/2);

>>>>>>> 85fb838bda6699be036e0a4d1ceefe53b340ce85
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //QPixmap myPix ("/Users/jamiehaywood/testAnnotation.jpg");
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
    if (type == 1) { //rectangle
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

    if(Trapeziums.empty() == false) {
        for (int i = 0; i< Trapeziums.size(); i++) {
                painter.drawPolygon(Trapeziums[i]);
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

    if (type == 3) { //polygon
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
         QPolygon polyLines;
        if (clicks == 4) {
            polyLines << QPoint(trap[0].x,trap[0].y);
            polyLines << QPoint(trap[2].x,trap[2].y);
            polyLines << QPoint(trap[1].x,trap[1].y);
            polyLines << QPoint(trap[3].x,trap[3].y);
            painter.drawPolygon(polyLines);
            Trapeziums.push_back(polyLines);
            polyLines.clear();
            clicks = 5;
            type = 0;
        }
        if (clicks == 3) {
            polyLines << QPoint(trap[0].x,trap[0].y);
            polyLines << QPoint(trap[2].x,trap[2].y);
            polyLines << QPoint(trap[1].x,trap[1].y);
            polyLines << QPoint(trap[3].x,trap[3].y);
            painter.drawPolygon(polyLines);
            clicks++;
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

     //ui->labelMainPic->setPixmap(myPix);
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
        if ((type == 4) && (clicks > 1)){
            std::cout<<"running"<<std::endl;
            trap[1] = {coords.x()-130,coords.y()-120};
            trap[2] = {(trap[0].x+(trap[0].x/5)),trap[1].y};
            trap[3] = {(trap[1].x+(trap[1].x/5)),trap[0].y};
        }
    }
        if (type == 0) {
            if (drawing == true) {
                annotationLabel->setGeometry(coords.x()-120,coords.y()-120,100,20);
                if (editingType == "Polygon") {
                    if (editingJ != allPolys[editingI].size()) {
                        allPolys[editingI][editingJ] = {coords.x()-130,coords.y()-120};
                      }
                    else {
                        allPolys[editingI][editingJ] = {coords.x()-130,coords.y()-120};
                        //allPolys[editingI][0] = {coords.x()-130,coords.y()-120};
                    }
                }
                if (editingType == "Triangle") {
                    Triangles[editingI][editingJ] = {coords.x()-130,coords.y()-120};
                }
                if (editingType == "Trap") {
                    Trapeziums[editingI][editingJ] = {coords.x()-130,coords.y()-120};
                }
            }

            if (moving == true){
                if (editingType == "Polygon") {
                    int xDiff = allPolys[editingI][editingJ].x;
                    int yDiff = allPolys[editingI][editingJ].y;
                    for (int i = 0; i<allPolys[editingI].size(); i++) {
                        allPolys[editingI][i] = {(coords.x()-130)+(xDiff-allPolys[editingI][i].x),(coords.y()-120)+(yDiff-allPolys[editingI][i].y)};

                    }
                }
                if (editingType == "Triangle") {
                    QPolygon temp = moveItem(Triangles,coords.x()-130,coords.y()-120);
                    Triangles[editingI] = temp;
                    }
                if (editingType =="Trap") {
                    QPolygon temp = moveItem(Trapeziums,coords.x()-130,coords.y()-120);
                    Trapeziums[editingI] = temp;
                }
            }
        }



    repaint();
}

void MainWindow::setMoving() {
    moving = true;
    drawing = false;
}

QPolygon MainWindow::moveItem(std::vector<QPolygon> Shape,int x, int y){
    QPolygon movingShape;
    int xDiff = Shape[editingI][editingJ].x();
    int yDiff = Shape[editingI][editingJ].y();
    for (int i = 0; i<Shape[editingI].size(); i++) {
        movingShape << QPoint({x+(xDiff-Shape[editingI][i].x()),y+(yDiff-Shape[editingI][i].y())});
    }
    return movingShape;
}


void MainWindow::checkShape(std::vector<QPolygon> Shape, int x, int y) {
    for (int i = 0; i<Shape.size();i++) {
        for (int j = 0; j<Shape[i].size(); j++){
            if (((Shape[i][j].x() < (x-130)+10) && (Shape[i][j].x() > (x-130)-10)) && ((Shape[i][j].y() < (y-120)+10) && (Shape[i][j].y() > (y-120)-10))) {
                if (Shape[i].size() == 3) {
                    editShapes(i,j,"Triangle",x-130,y-120);
                }
                if (Shape[i].size() == 4) {
                    editShapes(i,j,"Trap",x-130,y-120);
                }
            }
        }
    }
}

void MainWindow::editShapes(int index1,int index2,std::string type,int x, int y) {
    std::cout<<"Polygon Clicked"<<std::endl;
    drawing = true;
    editingI = index1;
    editingJ = index2;
    editingType = type;
    annotationLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    annotationLabel->setText("Annotation Test");
    annotationLabel->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    annotationLabel->setGeometry(x-120,y-120,50,20);
    annotationLabel->show();
}

void MainWindow::copyItem(){
        tempShape.clear();
        if (editingType == "Polygon"){
            int tempX = 0;
            int tempY = 0;
            tempShape.push_back({allPolys[editingI][0].x,allPolys[editingI][0].y});
            for (int count = 1; count< allPolys[editingI].size()+1;count++){
                tempShape.push_back({allPolys[editingI][count].x-allPolys[editingI][count-1].x,allPolys[editingI][count].y-allPolys[editingI][count-1].y});
            }
        }
        if (editingType == "Triangle") {
            tempShape.push_back({Triangles[editingI][0].x(),Triangles[editingI][0].y()});
            for (int count = 1; count< 3;count++){
                tempShape.push_back({Triangles[editingI][count].x()-Triangles[editingI][count-1].x(),Triangles[editingI][count].y()-Triangles[editingI][count-1].y()});
            }
        }
}



void MainWindow::pasteItem(){
    std::vector<coords> pushShape;
    QPoint coords = QCursor::pos();
    if (editingType == "Polygon") {
        mapFromGlobal(QCursor::pos());
        pushShape.push_back({coords.x()-130,coords.y()-120});
        for (int i = 1; i<tempShape.size()-1; i++) {
            pushShape.push_back({tempShape[i].x+pushShape[i-1].x,tempShape[i].y+pushShape[i-1].y});
        }
        allPolys.push_back(pushShape);
    }
    if (editingType == "Triangle") {
        QPolygon triangleLines;
        pushShape.push_back({coords.x()-130,coords.y()-120});
        triangleLines << QPoint{coords.x()-130,coords.y()-120};
        for (int i = 1; i<tempShape.size(); i++) {
            triangleLines << QPoint({tempShape[i].x+pushShape[i-1].x,tempShape[i].y+pushShape[i-1].y});
            pushShape.push_back({tempShape[i].x+pushShape[i-1].x,tempShape[i].y+pushShape[i-1].y});
        }
        Triangles.push_back(triangleLines);
        triangleLines.clear();
    }
    repaint();
}

void MainWindow::deleteItem(){
    if (editingType == "Polygon"){
        allPolys.erase(allPolys.begin()+editingI);
    }
    if (editingType == "Triangle"){
        Triangles.erase(Triangles.begin()+editingI);
    }
    if (editingType == "Trap"){
        Trapeziums.erase(Trapeziums.begin()+editingI);
    }
}

void MainWindow::drawItem(){
    moving = false;
    drawing = true;
}

void MainWindow::ShowContextMenu(const QPoint &pos) // this is a slot
{
    QMenu myMenu(tr("Edit Menu"), this);
    if (drawing or moving) {
    myMenu.addAction("Copy",this,SLOT(copyItem()));
    }
    if (!moving) {
    myMenu.addAction("Move",this,SLOT(setMoving()));
    }
    else {
        myMenu.addAction("Draw",this,SLOT(drawItem()));
    }
    //myMenu.addAction("Resize",this,SLOT(resizeItem()));
    if (tempShape.size() >0) {
        myMenu.addAction("Paste",this,SLOT(pasteItem()));
    }
    myMenu.addAction("Delete",this,SLOT(deleteItem()));
    QAction* selectedItem = myMenu.exec(mapToGlobal(pos));
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    QPoint coords = QCursor::pos();
    mapFromGlobal(QCursor::pos());
    if (drawing == true) {
        drawing = false;
        annotationLabel->hide();
       // moving = false;
    }

    if (type == 0) {
        for (int i = 0; i<allPolys.size();i++) {
            for (int j = 0; j<allPolys[i].size();j++) {
                if (((allPolys[i][j].x < (coords.x()-130)+10) && (allPolys[i][j].x > (coords.x()-130)-10)) && ((allPolys[i][j].y < (coords.y()-120)+10) && (allPolys[i][j].y > (coords.y()-120)-10))) {
                    editShapes(i,j,"Polygon",coords.x(),coords.y());
                }
            }
        }
        checkShape(Triangles,coords.x(),coords.y());
        checkShape(Trapeziums,coords.x(),coords.y());
   }

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
            mapFromGlobal(QCursor::pos());
            x1 = coords.x()-130;
            y1 = coords.y()-120;

            if(clicks == 4) {
                clicks = 5;
            }

            if(clicks == 3) {
                clicks = 4;
            }

            if (clicks == 2) {
                trap[1] = {x1,y1};
                trap[2] = {(trap[0].x+(trap[0].x/5)),trap[1].y};
                trap[3] = {(trap[1].x+(trap[1].x/5)),trap[0].y};
                clicks = 3;

            }
            if (clicks ==1) {
                trap[0] = {x1,y1};
                clicks = 2;
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

    ui->labelMainPic->setPixmap(pix.scaled(w,h, Qt::IgnoreAspectRatio));
    } catch(const std::runtime_error& e) {

    }
}


void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString path = dirModel->fileInfo(index).absoluteFilePath();
    try {
        QPixmap image(path);
        ui->labelMainPic->setPixmap(path);
        ui->labelMainPic->setScaledContents(true);
     } catch (...) {
        ui->labelMainPic->setText("Invalid file format");
     }
}
