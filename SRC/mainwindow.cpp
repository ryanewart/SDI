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
bool setup = false;
coords square[4];
coords trap[4];
int prevX;
bool imageFound = false;
bool resizing = false;
bool drawing;
bool moving;
std:: vector<coords> tempShape;
std:: vector<QPolygon> Squares;
std:: vector<QPolygon> Trapeziums;
int editingI,editingJ;
std::string editingType;
QString path;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("");

    int w = ui->labelMainPic->width();
    int h = ui->labelMainPic->height();
    ui->labelMainPic->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
    annotationLabel = new QLabel(this);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ShowContextMenu(const QPoint &)));


    dirModel = new QFileSystemModel(this);
    dirModel->setRootPath(QDir::homePath());
    ui->treeView->setModel(dirModel);
    ui->treeView->setSortingEnabled(true);
    ui->treeView->setAnimated(true);
    ui->treeView->setColumnWidth(0, ui->treeView->width()/2);

}

MainWindow::~MainWindow()
{
    delete ui;
}


QPolygon assignShape(coords Shape[]) {
    QPolygon polyLines;
    polyLines << QPoint(Shape[0].x,Shape[0].y);
    polyLines << QPoint(Shape[2].x,Shape[2].y);
    polyLines << QPoint(Shape[1].x,Shape[1].y);
    polyLines << QPoint(Shape[3].x,Shape[3].y);
    return polyLines;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    if (imageFound == true){
        reloadImage();
        QPixmap test;
        QMessageBox PolyBox;
        int count = 0;
        //QImage tmp2(ui->labelMainPic->pixmap()->toImage());
        QImage tmp(ui->labelMainPic->pixmap()->toImage());
        QPainter painter(&tmp);

        //QPainter painter(this);

        painter.setBrush(Qt::DiagCrossPattern);


        QPen pen;

        pen.setColor(Qt::green);
        pen.setWidth(5);

        painter.setPen(pen);


        if (Squares.empty() == false) {
            for (int i = 0; i<Squares.size(); i++)
           painter.drawPolygon(Squares[i]);
        }

        if (type == 1) { //rectangle
            QPolygon squareLines;
            if (clicks == 4) {
                squareLines = assignShape(square);
                painter.drawPolygon(squareLines);
                Squares.push_back(squareLines);
                squareLines.clear();
                clicks = 5;
                type = 0;
            }
            if (clicks == 3) {
                std::cout<<clicks<<std::endl;
                squareLines = assignShape(square);
                painter.drawPolygon(squareLines);
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
                ui->labelMainPic->setPixmap(QPixmap::fromImage(tmp));
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
             QPolygon trapLines;
            if (clicks == 4) {
                trapLines = assignShape(trap);
                painter.drawPolygon(trapLines);
                Trapeziums.push_back(trapLines);
                trapLines.clear();
                clicks = 5;
                type = 0;
            }
            if (clicks == 3) {
                trapLines = assignShape(trap);
                painter.drawPolygon(trapLines);
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
}


coords& addCoordData(coords Shape[], int Size,  int x, int y, int addition = 0) {
    Shape[1] = {x,y};
    int ones = 1, zeros = 0, temp;
    for (int i = 2; i<Size;i++) {
        Shape[i] = {Shape[zeros].x,Shape[ones].y};
        temp = ones;
        ones = zeros;
        zeros = ones;
    }
    return *Shape;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    QPoint coords = QCursor::pos();
    mapFromGlobal(QCursor::pos());
    if (clicks >1) {
        addCoordData(square,4,1,1);
        if ((type == 1)) {
            square[1] = {coords.x()-130,coords.y()-120};
            square[2] = {square[0].x,square[1].y};
            square[3] = {square[1].x,square[0].y};
        }

        if ((type == 2)) {
            triangle[1] = {coords.x()-130,coords.y()-120};
            triangle[2] = {(triangle[0].x),(triangle[1].y)};
        }
        if ((type == 4)){
            trap[1] = {coords.x()-130,coords.y()-120};
            trap[2] = {(trap[0].x+(trap[0].x/5)),trap[1].y};
            trap[3] = {(trap[1].x+(trap[1].x/5)),trap[0].y};
        }

        if (type ==3) {
            PolyPoints[PolyPoints.size()-1] = {coords.x()-130,coords.y()-120};
        }
    }
        if (type == 0) {
            if (drawing == true) {
                annotationLabel->setGeometry(coords.x()-120,coords.y()-120,100,20);
                if (editingType == "Polygon") {
                    if (editingJ != allPolys[editingI].size()-1) {
                        allPolys[editingI][editingJ] = {coords.x()-130,coords.y()-120};
                      }
                    else {
                        allPolys[editingI][editingJ] = {coords.x()-130,coords.y()-120};
                        allPolys[editingI][0] = {coords.x()-130,coords.y()-120};
                    }
                }
                if (editingType == "Triangle") {
                    Triangles[editingI][editingJ] = {coords.x()-130,coords.y()-120};
                }
                if (editingType == "Trap") {
                    Trapeziums[editingI][editingJ] = {coords.x()-130,coords.y()-120};
                }
                if (editingType == "Square") {
                    Squares[editingI][editingJ] = {coords.x()-130,coords.y()-120};
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
                if (editingType =="Square") {
                    QPolygon temp = moveItem(Squares,coords.x()-130,coords.y()-120);
                    Squares[editingI] = temp;
                }
            }
            if (resizing == true) {
                if (editingType == "Triangle") {
                    if (coords.x() > prevX) {
                        Triangles[editingI] = resizeShape(Triangles[editingI],0.01);
                    }
                    else if(coords.x() < prevX) {
                        Triangles[editingI] = resizeShape(Triangles[editingI],-0.01);
                    }
                }
                if (editingType == "Square") {
                        Squares[editingI] = resizeShape(Squares[editingI],0.01);
                }

                if (editingType == "Trap") {
                        Trapeziums[editingI] = resizeShape(Trapeziums[editingI],0.01);

                }
            }
        }


    prevX = coords.x()-130;
    repaint();
}

QPolygon MainWindow::moveItem(std::vector<QPolygon> Shape,int x=1, int y =1){
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
                    break;
                }
                if (Shape[i].size() == 4 && (Shape[i][0].x() !=Shape[i][1].x())) {
                    editShapes(i,j,"Trap",x-130,y-120);
                    std::cout<<"trap"<<std::endl;
                    break;
                }
                else{ editShapes(i,j,"Square",x-130,y-120);
                std::cout<<"Square"<<std::endl;
                break;
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
           copyShape(Triangles);
        }
        if (editingType == "Trap") {
            copyShape(Trapeziums);
        }
        if (editingType == "Square") {
            copyShape(Squares);
        }
}


void MainWindow::copyShape(std:: vector<QPolygon> Shape) {
    tempShape.push_back({Shape[editingI][0].x(),Shape[editingI][0].y()});
    for (int count = 1; count< Shape[editingI].size();count++){
        tempShape.push_back({Shape[editingI][count].x()-Shape[editingI][count-1].x(),Shape[editingI][count].y()-Shape[editingI][count-1].y()});
    }
}

QPolygon pasteShape(int x,int y) {
    std::vector<coords> storedShape;
    QPolygon shapeLines;
    storedShape.push_back({x,y});
    shapeLines << QPoint{x,y};
    for (int i = 1; i<tempShape.size(); i++) {
        shapeLines << QPoint({tempShape[i].x+storedShape[i-1].x,tempShape[i].y+storedShape[i-1].y});
        storedShape.push_back({tempShape[i].x+storedShape[i-1].x,tempShape[i].y+storedShape[i-1].y});
    }
    return shapeLines;
}

void MainWindow::pasteItem(){
    QPoint clickedCoords = QCursor::pos();
    std::vector<coords> pushShape;
    if (editingType == "Polygon") {
        pushShape.push_back({clickedCoords.x()-130,clickedCoords.y()-120});
        for (int i = 1; i<tempShape.size()-1; i++) {
            pushShape.push_back({tempShape[i].x+pushShape[i-1].x,tempShape[i].y+pushShape[i-1].y});
        }
        allPolys.push_back(pushShape);
    }
    if (editingType == "Triangle") {
        Triangles.push_back(pasteShape(clickedCoords.x()-130,clickedCoords.y()-120));
    }
    if (editingType == "Trap") {
        Trapeziums.push_back(pasteShape(clickedCoords.x()-130,clickedCoords.y()-120));
    }
    if (editingType == "Square") {
        Squares.push_back(pasteShape(clickedCoords.x()-130,clickedCoords.y()-120));
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
    if(editingType == "Square") {
        Squares.erase(Squares.begin()+editingI);
    }
}

void MainWindow::drawItem(){
    moving = false;
    drawing = true;
    resizing = false;
}

void MainWindow::setResize() {
    moving = false;
    drawing = false;
    resizing = true;
}

void MainWindow::setMoving() {
    moving = true;
    drawing = false;
    resizing = false;

}

QPolygon MainWindow::resizeShape(QPolygon Shape,double diff){
    coords Centre;
    int centX = 0, centY = 0;
    int diffX, diffY;
    for (int i = 0; i<Shape.size();i++) {
        centX = centX + Shape[i].x();
        centY = centY + Shape[i].y();
    }
    centX = centX/Shape.size();
    centY = centY/Shape.size();
    //std::cout<<centX<<", "<<centY<<std::endl;
    //QPoint origin = Shape[1];

    for (int side = 0; side<Shape.size(); side++){
        diffX = centX - Shape[side].x();
        diffY = centY - Shape[side].y();
        std::cout<<diffX<<", "<<diffY<<std::endl;
        diffX = diffX*(1+diff);
        diffY = diffY*(1+diff);
        Shape[side] = {centX + diffX,centY+diffY};

    }
    //Shape[1] = origin;

    return Shape;
}

void MainWindow::ShowContextMenu(const QPoint &pos) // this is a slot
{
    QMenu myMenu(tr("Edit Menu"), this);
    if (drawing or moving) {
    myMenu.addAction("Copy",this,SLOT(copyItem()));
    if (!moving) {
    myMenu.addAction("Move",this,SLOT(setMoving()));
    }
}
    else {
        myMenu.addAction("Draw",this,SLOT(drawItem()));
    }
    myMenu.addAction("Resize",this,SLOT(setResize()));
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

    }
    if (resizing == true) {
        //resizing = false;
        //annotationLabel->hide();
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
        checkShape(Squares,coords.x(),coords.y());
   }

    //square
    if (type == 1) {
        mapFromGlobal(QCursor::pos());
        x1 = coords.x()-130;
        y1 = coords.y()-120;

        if(clicks == 4) {
            clicks = 5;
        }

        if (clicks == 3) {
            clicks = 4;
        }
        if (clicks == 2) {
            square[1] = {x1,y1};
            square[2] = {(square[0].x),(square[1].y)};
            square[3] = {(square[1].x),square[0].y};
            clicks = 3;
        }

        if (clicks == 1){
            square[0] = {x1,y1};
            clicks = 2;
        }
    }

    //triangle
    if (type == 2) {
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
            triangle[1] = {coords.x()-130,coords.y()-120};
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


void MainWindow::reloadImage(){
    QPixmap image(path);
    ui->labelMainPic->setPixmap(path);
    ui->labelMainPic->setScaledContents(true);
    imageFound = true;
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    path = dirModel->fileInfo(index).absoluteFilePath();
    try {
        reloadImage();
     } catch (...) {
        ui->labelMainPic->setText("Invalid file format");
     }
}
