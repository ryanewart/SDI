#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include "BinarySearch.cpp"
#include "QuickSort.cpp"
#include <QPixmap>
#include <iostream>
#include <list>
#include <QMessageBox>
#include <QFileDialog>
#include <QPolygon>
#include <QInputDialog>
#include <QMap>
#include <QTextStream>
#include <QStandardPaths>



QLabel *annotationLabel = NULL;

struct classData {
    int position;
    std::string data;
};
int classIndex[100][1];
int prevX;
bool imageFound = false;
bool resizing = false;
bool drawing;
bool moving;
int editingI,editingJ;
bool setup = false;
std::string editingType;
std:: vector<coords> tempShape;
QString path;
std:: vector<classData> classDataIndex;
std:: vector<QPolygon> Polygons;
coords polygonArray[8];
List PolyPoints = List({NULL,NULL});


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

    autoSaveThread = new saveThread();
    connect(autoSaveThread, SIGNAL(callSave()), this, SLOT(onSaveCalled()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPolygon assignPolygon(coords Shape[], int size) {
    QPolygon polyLines;
    for (int i = 0; i<size;i++) {
        polyLines << QPoint(Shape[i].x,Shape[i].y);
    }
    return polyLines;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    if (imageFound == true){
        reloadImage(path);
        QPixmap test;
        int count = 0;
        QImage tmp(ui->labelMainPic->pixmap()->toImage());
        QPainter painter(&tmp);


        //painter.setBrush(Qt::DiagCrossPattern);


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
                squareLines = assignShape(square,4);
                painter.drawPolygon(squareLines);
                Squares.push_back(squareLines);
                classIndex[type][Squares.size()-1] =  ui->listWidget->currentRow();
                squareLines.clear();
                clicks = 5;
                type = 0;
            }
            if (clicks == 3) {
                squareLines = assignShape(square,4);
                painter.drawPolygon(squareLines);
            }


        }

        if (type == 2) { //Triangle
            QPolygon triangleLines;
            if (clicks == 4) {
                triangleLines = assignShape(triangle,3);
                painter.drawPolygon(triangleLines);
                Triangles.push_back(triangleLines);
                classIndex[type][Triangles.size()-1] =  ui->listWidget->currentRow();
                triangleLines.clear();
                clicks = 5;
                type = 0;
            }

            if (clicks == 3) {
                triangleLines = assignShape(triangle,3);
                painter.drawPolygon(triangleLines);

            }
        }

        if (type == 3) { //polygon

            if (PolyPoints.size() > 2) {
                int xDiff = PolyPoints.At(PolyPoints.size()-1).x -PolyPoints.At(0).x;
                int yDiff = PolyPoints.At(PolyPoints.size()-1).y -PolyPoints.At(0).y;
                if (((xDiff < 5 && xDiff >-5) && (yDiff < 5 && yDiff >-5)) && (PolyPoints.size()>2)) {
                    for (int i = 0; i<PolyPoints.size();i++) {
                        polygonArray[i] = PolyPoints.At(i);
                    }
                    type = 0;
                    Polygons.push_back(assignPolygon(polygonArray,PolyPoints.size()-1));
                    classIndex[type][Polygons.size()-1] =  ui->listWidget->currentRow();
                    PolyPoints.clear();

            }
        }           
        }
        if (type == 4) { //trapezium
             QPolygon trapLines;
            if (clicks == 4) {
                trapLines = assignShape(trap,4);
                painter.drawPolygon(trapLines);
                Trapeziums.push_back(trapLines);
                 classIndex[type][Trapeziums.size()-1] =  ui->listWidget->currentRow();
                trapLines.clear();
                clicks = 5;
                type = 0;
            }
            if (clicks == 3) {
                trapLines = assignShape(trap,4);
                painter.drawPolygon(trapLines);
            }
        }

        if (PolyPoints.size() > 0) {
            for (int j = 1; j < (PolyPoints.size()); j++) {
                painter.drawLine(PolyPoints.At(j-1).x, PolyPoints.At(j-1).y, PolyPoints.At(j).x, PolyPoints.At(j).y);
            }
        }

        if(Polygons.empty() == false) {
            for (int i = 0; i<Polygons.size();i++) {
                 painter.drawPolygon(Polygons[i]);
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

        ui->labelMainPic->setPixmap(QPixmap::fromImage(tmp));
    }
}


QPolygon MainWindow::assignShape(coords Shape[],int size) {
    QPolygon polyLines;
    for (int i = 0; i<size;i++) {
        polyLines << QPoint(Shape[i].x,Shape[i].y);
    }
    return polyLines;
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
    //mapFromParent(QCursor::pos());
    if (clicks >1) {
        //addCoordData(square,4,1,1);
        if ((type == 1)) {
            square[2] = {coords.x(),coords.y()};
            square[1] = {square[0].x,square[2].y};
            square[3] = {square[2].x,square[0].y};
        }

        if ((type == 2)) {
            triangle[1] = {coords.x(),coords.y()};
            triangle[2] = {(triangle[0].x),(triangle[1].y)};
        }
        if ((type == 4)){
            trap[2] = {coords.x(),coords.y()};
            trap[1] = {(trap[0].x+(trap[0].x/5)),trap[2].y};
            trap[3] = {(trap[2].x+(trap[2].x/5)),trap[0].y};
        }

        if (type ==3) {
            PolyPoints.set(0,{coords.x(),coords.y()}); //REVIEW
        }
    }
        if (type == 0) {
            if (drawing == true) {
                annotationLabel->setGeometry(coords.x(),coords.y(),100,20);
                if (editingType == "Polygon") {
                    Polygons[editingI][editingJ] = {coords.x(),coords.y()};
                }
                if (editingType == "Triangle") {
                    Triangles[editingI][editingJ] = {coords.x(),coords.y()};
                }
                if (editingType == "Trap") {
                    Trapeziums[editingI][editingJ] = {coords.x(),coords.y()};
                }
                if (editingType == "Square") {
                    Squares[editingI][editingJ] = {coords.x(),coords.y()};
                }
            }

            if (moving == true){
                if (editingType == "Polygon") {
                    QPolygon temp = moveItem(Polygons,coords.x(),coords.y());
                    Polygons[editingI] = temp;

                }
                if (editingType == "Triangle") {
                    QPolygon temp = moveItem(Triangles,coords.x(),coords.y());
                    Triangles[editingI] = temp;
                    }
                if (editingType =="Trap") {
                    QPolygon temp = moveItem(Trapeziums,coords.x(),coords.y());
                    Trapeziums[editingI] = temp;
                }
                if (editingType =="Square") {
                    QPolygon temp = moveItem(Squares,coords.x(),coords.y());
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
                if (editingType == "Polygon") {
                        Polygons[editingI] = resizeShape(Polygons[editingI],0.01);

                }
            }

        }

        prevX = coords.x();
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
            if (((Shape[i][j].x() < (x)+10) && (Shape[i][j].x() > (x)-10)) && ((Shape[i][j].y() < (y)+10) && (Shape[i][j].y() > (y)-10))) {
                if (Shape[i].size() == 3) {
                    editShapes(i,j,"Triangle",2,x-130,y-120);
                    break;
                }
                else if (Shape[i].size() == 4 && (Shape[i][0].x() !=Shape[i][1].x())) {
                    editShapes(i,j,"Trap",4,x-130,y-120);
                    std::cout<<"trap"<<std::endl;
                    break;
                }
                else if(Shape[i].size() == 4 && (Shape[i][0].x() == Shape[i][1].x())) {
                    editShapes(i,j,"Square",1,x-130,y-120);
                    std::cout<<"Square"<<std::endl;
                    break;
                }
                else {
                    editShapes(i,j,"Polygon",4,x-130,y-120);
                    std::cout<<"Polygon"<<std::endl;
                    break;
                }

            }
        }
    }
}

void MainWindow::editShapes(int index1,int index2,std::string type,int num,int x, int y) {
    drawing = true;
    editingI = index1;
    editingJ = index2;
    editingType = type;
    if (ui->listWidget->count() != 0) {
        int classIndexNumber = classIndex[num][editingI];
        QString classDisplay = ui->listWidget->item(classIndexNumber)->text();
        annotationLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        annotationLabel->setText(classDisplay);
        annotationLabel->setAlignment(Qt::AlignBottom | Qt::AlignRight);
        annotationLabel->setGeometry(x,y,50,20);
        annotationLabel->show();
    }

}

void MainWindow::copyItem(){
        tempShape.clear();

        if (editingType == "Polygon") {
           copyShape(Polygons);
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
        Polygons.push_back(pasteShape(clickedCoords.x()-130,clickedCoords.y()-120));
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
        Polygons.erase(Polygons.begin()+editingI);
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
    if (resizing == false) {
        moving = false;
        drawing = false;
        resizing = true;
    }
    else {
        resizing = false;
    }

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
    //QPoint origin = Shape[1];

    for (int side = 0; side<Shape.size(); side++){
        diffX = centX - Shape[side].x();
        diffY = centY - Shape[side].y();
        //std::cout<<diffX<<", "<<diffY<<std::endl;
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
    //mapFromParent(QCursor::pos());
    if (drawing == true) {
        drawing = false;
        annotationLabel->hide();

    }
    if (resizing == true) {
        if (clicks == 2) {
            resizing = false;
            annotationLabel->hide();
            clicks = 0;
        }
         clicks = 2;
    }

    if (moving == true) {
        if (clicks == 2) {
            moving = false;
            annotationLabel->hide();
            clicks = 0;
        }
        clicks = 2;
    }

    if (type == 0) {

        checkShape(Polygons,coords.x(),coords.y());
        checkShape(Triangles,coords.x(),coords.y());
        checkShape(Trapeziums,coords.x(),coords.y());
        checkShape(Squares,coords.x(),coords.y());
   }

    //square
    if (type == 1) {
        x1 = coords.x();//-130;
        y1 = coords.y();//-120;

        if(clicks == 4) {
            clicks = 5;
        }

        if (clicks == 3) {
            clicks = 4;
        }
        if (clicks == 2) {
            square[2] = {x1,y1};
            square[1] = {(square[0].x),(square[2].y)};
            square[3] = {(square[2].x),square[0].y};
            clicks = 3;
        }

        if (clicks == 1){
            square[0] = {x1,y1};
            clicks = 2;
        }
    }

    //triangle
    if (type == 2) {
        x1 = coords.x();
        y1 = coords.y();

        if(clicks == 4) {
            clicks = 5;
        }

        if(clicks == 3) {
            clicks = 4;
        }

        if (clicks == 2) {
            triangle[1] = {coords.x(),coords.y()};
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
        QMessageBox PolyBox;
        if (clicks  == 1) {
            PolyPoints.set(0,{coords.x(),coords.y()});
            clicks = clicks+1;
        }
        else {
            PolyPoints.push_back({coords.x(),coords.y()});
            clicks = clicks+1;
        }
        if (clicks > 8 ) {
            PolyBox.setText("This shape can only have a maximum of 8 points");
            PolyBox.exec();
            PolyPoints.clear();
            type = 0;
            clicks = 0;
        }
        }

    //trap
    if (type == 4) {
            mapFromGlobal(QCursor::pos());
            x1 = coords.x();
            y1 = coords.y();

            if(clicks == 4) {
                clicks = 5;
            }

            if(clicks == 3) {
                clicks = 4;
            }

            if (clicks == 2) {
                trap[2] = {x1,y1};
                trap[1] = {(trap[0].x+(trap[0].x/5)),trap[2].y};
                trap[3] = {(trap[2].x+(trap[2].x/5)),trap[0].y};
                clicks = 3;

            }
            if (clicks ==1) {
                trap[0] = {x1,y1};
                clicks = 2;
            }



        if ( clicks == 1) {
            mapFromGlobal(QCursor::pos());
            x1 = coords.x();
            y1 = coords.y();
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

void MainWindow::clearShapes(){
    Triangles.clear();
    Squares.clear();
    Trapeziums.clear();
    Polygons.clear();
}

void MainWindow::on_pushButton_5_clicked() //clear Button
{
    type = 0;
    clearShapes();
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

void MainWindow::saveAnnotations() {
    QString shapes[] = {"Triangle","Square","Trapeze","Polygon"};
    int noOfImages = 1; //Change to incorporate more images.

    std:: vector<std::vector<QPolygon>> totalShapes;

    totalShapes.push_back(Triangles);
    totalShapes.push_back(Squares);
    totalShapes.push_back(Trapeziums);
    totalShapes.push_back(Polygons);

    int noOfAnnotations = totalShapes.size();
    QFile file(annotationFilePath);

    file.open(QIODevice::WriteOnly);
    QTextStream outputStream(&file);
    outputStream << noOfImages;
        for (int i=0; i < noOfImages; i++){
            outputStream << "," << path;
        }
                //New line in file
                outputStream << "\n";

                for (int j=0; j < 4; j++){
                    outputStream << shapes[j];
                    for (int k=0; k<totalShapes[j].size(); k++){
                        for (int sides = 0; sides < totalShapes[j][k].size(); sides++) {
                            QPoint point  = totalShapes[j][k][sides];
                            outputStream << ","<< point.x() << "," <<point.y() ;
                        }
                        if (shapes[j] == "Polygon") {
                            outputStream << "\n";
                        }
                    }
                     outputStream << "\n";
                }
                outputStream << "\n";
                outputStream << classFilePath;
                outputStream << "\n";
                file.close();

}

void MainWindow::on_actionSave_triggered() {
        if (annotationFilePath == ""){
            QString newSave = QInputDialog::getText(this, tr("Create a new annotation file"), tr("Annotation file name: "), QLineEdit::Normal);
            QString fileLocation = newSave.trimmed();
            annotationFilePath = QDir::homePath() + "/" + newSave + ".annotations";
        }

        else if (annotationFilePath != ""){
            //dialog to ask if they want to override
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "File Exists", "Override?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::No){
                QString newSave = QInputDialog::getText(this, tr("Create a new annotation file"), tr("Annotation file name: "), QLineEdit::Normal);
                QString fileLocation = newSave.trimmed();
                annotationFilePath = QDir::homePath() + "/" + newSave + ".annotations";
            }
        }

        saveAnnotations();

}

void MainWindow::on_actionSave_As_triggered() {
    if (imageFound) {
        QString newSave = QInputDialog::getText(this, tr("Create a new annotation file"), tr("Annotation file name: "), QLineEdit::Normal);
        QString fileLocation = newSave.trimmed();
        annotationFilePath = QDir::homePath() + "/" + newSave + ".annotations";
        saveAnnotations();
    }
    else {

    }
}

QPolygon MainWindow::loadShapes(QStringList data, int count, int size) {
    coords Shape[size];
    int index = 0;
    for (int i = 0; i<(size*2);i= i+2) {
        Shape[index] = {data.at(count+i).toInt(),data.at(count+i+1).toInt()};
        index++;
    }
    QPolygon polygonShape = assignShape(Shape,size);
    return polygonShape;
}

void MainWindow::on_actionRename_triggered() {
        QString oldname = annotationFilePath;
        oldname = oldname.trimmed();
        QFile file(annotationFilePath);
        qDebug() <<oldname;
        QString newname = QDir::homePath() + "/" +QInputDialog::getText(this, tr("Rename file"), tr("New file name: "), QLineEdit::Normal)+".annotations";
        bool renameCheck = file.rename(oldname,newname);
        if (renameCheck == true){
            QMessageBox::warning(this,"Error","Saved successfully", QMessageBox::Ok);
                    file.close();
        }
        else {
            QMessageBox::warning(this,"Error","Rename unsuccessful! Please try again.", QMessageBox::Ok);
        }
    }


void MainWindow::on_actionOpen_triggered()
{
    try {
        QMessageBox::StandardButton saveAnswer;
        if (imageFound == true) {
            saveAnswer = QMessageBox::question(nullptr, "Save", "Would you like to save before opening?", QMessageBox::Yes|QMessageBox::No);
            if (saveAnswer == QMessageBox::Yes){
                saveAnnotations();
            }
        }
        QStringList filepathList;
        QString File;
        QString imageName;
        QString filename = QFileDialog::getOpenFileName(
                    this,
                    tr("Open file"),
                    "/",
                    "Text Files (*.annotations)");

        if (!filename.isEmpty()){
            QString msg = "You chose the file:\n";
            QMessageBox::information(this, tr("File name"), msg.append(filename));
            clearShapes();
            annotationFilePath = filename;
            QFile loadFile(filename);
            QTextStream in(&loadFile);
            if(!loadFile.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, "error", loadFile.errorString());
            }
            QString line = in.readLine();
            QStringList data = line.split(",");
            File = data.at(1);
            for(int i = 1; i < data.size(); ++i){
                File = data.at(i);
                filepathList.insert(i, File);
            }
            while (!in.atEnd()) {
                int count = 1;
                line = in.readLine();
                data = line.split(",");
                std::string shapeType = data.at(0).toLocal8Bit().constData();
                if (data.size()>2) {
                    if (shapeType == "Square") {
                        while(count<data.size()) {
                            std::cout<<"Loading Square"<<std::endl;
                            Squares.push_back(loadShapes(data,count,4));
                            count = count + 8;
                        }
                    }
                    if (shapeType == "Trapeze") {
                        while(count<data.size()) {
                            std::cout<<"Loading Trapeze"<<std::endl;
                            Trapeziums.push_back(loadShapes(data,count,4));
                            count = count + 8;
                        }
                    }
                    if (shapeType == "Triangle") {
                        while(count<data.size()) {
                            std::cout<<"Loading Triangle"<<std::endl;
                            Triangles.push_back(loadShapes(data,count,3));
                            count = count + 6;
                        }
                    }
                    if (shapeType == "Polygon" or shapeType == "") {
                        while(count<data.size()) {
                            std::cout<<"Loading Polygon"<<std::endl;
                            Polygons.push_back(loadShapes(data,count,(data.size()-1)/2));
                            count = count + data.size()-1;
                        }
                    }
                }
            }
        loadFile.close();
        path = File;
        reloadImage(path);
        imageFound = true;
            loadFile.close();
            path = File;
            reloadImage(path);
            imageFound = true;
        }

    }
    catch(const std::runtime_error& e) {

    }
}

void MainWindow::reloadImage(QString imgPath = path){
    QPixmap image(imgPath);
    ui->labelMainPic->setPixmap(imgPath);
    ui->labelMainPic->setScaledContents(true);
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    path = dirModel->fileInfo(index).absoluteFilePath();
    try {
        reloadImage(path);
        imageFound = true;
        autoSaveThread->start();
        qDebug() << "Autosave thread started";
     } catch (...) {
        ui->labelMainPic->setText("Invalid file format");
     }
}

void MainWindow::on_btn_OpenClass_clicked()
{
    int count = 1;
    classFilePath = QFileDialog::getOpenFileName(this, tr("Open file"), "/", tr("Name Files (*.names)"));
    QString tempItem;
    QStringList newListObjects;
    QMap<QString, int> classIndexMap;

    try {

        QFile file(classFilePath);
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, "error", file.errorString());
        }
        QTextStream in(&file);

        while(!in.atEnd()) {
            tempItem = in.readLine();
            newListObjects.append(tempItem);
            classDataIndex.push_back({count,tempItem.toUtf8().constData()}); //Comment this out when dictionary is implemented.
            classIndexMap[tempItem] = count;
            count++;
        }
        file.close();

       ui->listWidget->clear();
       ui->listWidget->addItems(newListObjects);

    } catch (...) {
        QMessageBox::information(this, "Error", "There has been an error with the file");
    }


}



void MainWindow::on_btn_AddClass_clicked()
{
    if (classFilePath == ""){
        QString renamedClass = QInputDialog::getText(this, tr("Create a new class file"), tr("Class file name: "), QLineEdit::Normal);
        renamedClass = renamedClass.trimmed();
        classFilePath = QDir::homePath() + "/" + renamedClass + ".names";
    }
    if(classFilePath !=""){
        //Ask the user for a class
        QString newClass = QInputDialog::getText(this, tr("Input a New Class"), tr("New Class:"), QLineEdit::Normal);
        //Append to the listWidget
        ui->listWidget->addItem(newClass);
        //Append to the class file (How to parse the path)
        if (classFilePath != ""){
            QFile file(classFilePath);
            file.open(QIODevice::Append);

            if (!file.isOpen()){
                QMessageBox::information(this, "error", file.errorString());
            }

            QTextStream outputStream(&file);

            outputStream << newClass << "\n";
            file.close();
        }
    }
}

void MainWindow::on_btn_RemoveClass_clicked()
{
    //Remove from the list
    qDeleteAll(ui->listWidget->selectedItems());
    QMessageBox::information(this, "error", tr("Removed from class"));
    //Remove from the file -> re write all item - create function
    updateFile();
}

void MainWindow::updateFile(){ //reWrites the current class selection file based on whats in the list widget
    QFile file(classFilePath);
    file.open(QIODevice::WriteOnly);

    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, "error", file.errorString());
    }

    for (int i = 0; i < ui->listWidget->count(); i++) {
         QListWidgetItem * item = ui->listWidget->item(i);
         QString className = item->text();
         QTextStream outStream(&file);
         outStream << className << " \n";
    }

    file.close();
}

void MainWindow::on_btn_ModifyClass_clicked() //Modifiys the name of the selected class
{
    //Get index of selected item
    QList<QListWidgetItem*> selectedItem = ui->listWidget->selectedItems();

    if (selectedItem.count() == 0){
         QMessageBox::information(this, "error", tr("No class selected"));
    }

    //Pop up box to get the new name
    QString renamedClass = QInputDialog::getText(this, tr("Input the modified name"), tr("New Class Name:"), QLineEdit::Normal);
    if (renamedClass != "") {
        selectedItem[0]->setText(renamedClass);
        //UpdateFile
        updateFile();
    }
}

void MainWindow::on_btn_SortList_clicked() //Sorts the classes into alphabetical order.
{
    int itemCount = ui->listWidget->count();
    if (itemCount > 1) {
        QStringList sortedItemList;
        std::string items[itemCount];
        std::string temp;
        for (int i = 0; i< ui->listWidget->count(); i++) {
            items[i] = ui->listWidget->item(i)->text().toLocal8Bit().constData();
        }
       std:: string* sortedItems= quickSort(items,itemCount-1,0);
       for (int i = 0; i< itemCount; i++) {
        sortedItemList.push_back(QString::fromStdString(sortedItems[i]));
       }
       ui->listWidget->clear();
       ui->listWidget->addItems(sortedItemList);


    }
    else {
        QMessageBox::information(this, "error", tr("No classes to sort"));
    }
}

void MainWindow::onSaveCalled(){
    saveAnnotations();
    qDebug() << "Saved";
}




void MainWindow::on_btn_SearchList_clicked()
{
    qDebug() << "Reached";
    int itemCount = ui->listWidget->count();
    std::string temp;
    if (itemCount > 1) {
        std::string items[itemCount];
        for (int i = 0; i< ui->listWidget->count(); i++) {
            temp = ui->listWidget->item(i)->text().toLocal8Bit().constData();
            items[i] = temp;
        }
        std::string * sortedItems = quickSort(items, itemCount-1, 0);
        QString classSearch = QInputDialog::getText(this, tr("What Item do you want to search for?"), tr("Class name: "), QLineEdit::Normal);
        std::string temp = classSearch.toStdString();
        if (temp != "") {
            int pos = binarySearch(sortedItems,temp);
            std::cout<<pos<<std::endl;
            if (pos == -1) {
                std::cout<<"Item Not Found"<<std::endl;
            }
            else {
                ui->listWidget->setCurrentRow(pos);
            }
        }
    }
}


void MainWindow::on_btn_SortList_3_clicked()
{
    int itemCount = ui->listWidget->count();
    if (itemCount > 1) {
        QStringList sortedItemList;
        std::string items[itemCount];
        std::string temp;
        for (int i = 0; i< ui->listWidget->count(); i++) {
            temp = ui->listWidget->item(i)->text().toLocal8Bit().constData();
            items[i] = temp;
        }
       std:: string* sortedItems= quickSort(items,itemCount-1,0);
       for (int i = 0; i < itemCount; i++) {
        sortedItemList.push_front(QString::fromStdString(sortedItems[i]));
       }
       ui->listWidget->clear();
       ui->listWidget->addItems(sortedItemList);
    }
    else {
        QMessageBox::information(this, "error", tr("No classes to sort"));
    }
}


