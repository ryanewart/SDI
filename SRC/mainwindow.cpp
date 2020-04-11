#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <iostream>
#include <list>
#include <QMessageBox>
#include <QFileDialog>
#include <QPolygon>
#include <QInputDialog>
#include <QTextStream>
#include <QStandardPaths>



QLabel *annotationLabel = NULL;

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


QPolygon MainWindow::assignShape(coords Shape[]) {
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
        reloadImage(path);
        QPixmap test;
        int count = 0;
        QImage tmp(ui->labelMainPic->pixmap()->toImage());
        QPainter painter(&tmp);


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

        if (type == 2) { //Polygon
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
    //mapFromParent(QCursor::pos());
    if (clicks >1) {
        //addCoordData(square,4,1,1);
        if ((type == 1)) {
            square[1] = {coords.x(),coords.y()};
            square[2] = {square[0].x,square[1].y};
            square[3] = {square[1].x,square[0].y};
        }

        if ((type == 2)) {
            triangle[1] = {coords.x(),coords.y()};
            triangle[2] = {(triangle[0].x),(triangle[1].y)};
        }
        if ((type == 4)){
            trap[1] = {coords.x(),coords.y()};
            trap[2] = {(trap[0].x+(trap[0].x/5)),trap[1].y};
            trap[3] = {(trap[1].x+(trap[1].x/5)),trap[0].y};
        }

        if (type ==3) {
            PolyPoints[PolyPoints.size()-1] = {coords.x()-130,coords.y()-120};
        }
    }
        if (type == 0) {
            if (drawing == true) {
                annotationLabel->setGeometry(coords.x(),coords.y(),100,20);
                if (editingType == "Polygon") {
                    if (editingJ != allPolys[editingI].size()-1) {
                        allPolys[editingI][editingJ] = {coords.x(),coords.y()};
                      }
                    else {
                        allPolys[editingI][editingJ] = {coords.x(),coords.y()};
                        allPolys[editingI][0] = {coords.x(),coords.y()};
                    }
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
                    int xDiff = allPolys[editingI][editingJ].x;
                    int yDiff = allPolys[editingI][editingJ].y;
                    for (int i = 0; i<allPolys[editingI].size(); i++) {
                        allPolys[editingI][i] = {(coords.x())+(xDiff-allPolys[editingI][i].x),(coords.y())+(yDiff-allPolys[editingI][i].y)};

                    }
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
        //resizing = false;
        //annotationLabel->hide();
    }

    if (type == 0) {
        for (int i = 0; i<allPolys.size();i++) {
            for (int j = 0; j<allPolys[i].size();j++) {
                if (((allPolys[i][j].x < (coords.x())+10) && (allPolys[i][j].x > (coords.x())-10)) && ((allPolys[i][j].y < (coords.y())+10) && (allPolys[i][j].y > (coords.y())-10))) {
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
        x1 = coords.x();//-130;
        y1 = coords.y();//-120;

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
        clicks = clicks+1;
        PolyPoints.push_back({coords.x(),coords.y()});
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

void MainWindow::on_actionSave_triggered() {
    QString shapes[] = {"Triangle","Square","Trapeze"};
    int noOfImages = 1; //Change to incorporate more images.
    int noOfAnnotations = Triangles.size() + Squares.size() + Trapeziums.size();
    std:: vector<std::vector<QPolygon>> totalShapes;
    totalShapes.push_back(Triangles);
    totalShapes.push_back(Squares);
    totalShapes.push_back(Trapeziums);

    QString fileLocation = QInputDialog::getText(this, QObject::tr("Input name of file"), QObject::tr("File name:"), QLineEdit::Normal);
    if (fileLocation != ""){
        //dialog to ask if they want to override
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "File Exists", "Override?", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes){
            QFile file(fileLocation);
            file.open(QIODevice::Append);

            if (!file.isOpen()){
                QMessageBox::information(this, "error", file.errorString());
            }
            else {
                QTextStream outputStream(&file);

                outputStream << noOfImages;
                for (int i=0; i < noOfImages; i++){
                    outputStream << ", " << path;
                    }
                outputStream << "\n";
                //New line in file
                outputStream << noOfAnnotations;
                outputStream << "\n";

                for (int j=0; j < noOfAnnotations; j++){
                    outputStream << shapes[j]<< ", ";
                    for (int k=0; k<totalShapes[j].size(); k++){
                        for (int sides = 0; sides < totalShapes[j][k].size(); sides++) {
                            QPoint point  = totalShapes[j][k][sides];
                            outputStream << point.x() << "," <<point.y()<< "," ;
                        }
                    }
                     outputStream << "\n";
                }
                file.close();
            }

         } else {
            qDebug() << "Save cancelled";
         }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    try {
        int count = 1;
        QString File;
        QString imageName;
        QString filename = QFileDialog::getOpenFileName(
                    this,
                    tr("Open file"),
                    "/",
                    "Text Files (*.txt)");

        if (!filename.isEmpty()){
            QString msg = "You chose the file:\n";
            QMessageBox::information(this, tr("File name"), msg.append(filename));
        }
        QFile loadFile(filename);
        QTextStream in(&loadFile);
        std::cout<<"Test"<<std::endl;

        while(!in.atEnd()){
            for(int lineNo = 1; !in.atEnd(); ++lineNo){
                QString line = in.readLine();
                QStringList data = line.split(",");
                if (lineNo == 1){
                    QString noImages = data.at(0);
                    for(int i = 1; i < data.size(); ++i){
                        QStringList filepathList;
                        File = data.at(i);
                        filepathList.insert(i, File);
                        std::string dispFile = File.toLocal8Bit().constData();
                        std::cout<<dispFile<<std::endl;
                    }
                }
                if (lineNo == 2){
                    QString noShapes = data.at(0);
                }
                else{
                    std::string shapeType = data.at(0).toLocal8Bit().constData();
                    while (count < data.size()){
                        if (shapeType == "Square") {
                            coords Shape[] ={{data.at(count).toInt(),data.at(count+1).toInt()},{data.at(count+2).toInt(),data.at(count+3).toInt()},{data.at(count+4).toInt(),data.at(count+5).toInt()},{data.at(count+6).toInt(),data.at(count+7).toInt()}};
                            QPolygon polygonShape = assignShape(Shape);
                            Squares.push_back(polygonShape);
                            count = count + 8;
                        }
                        if (shapeType == "Trapeze") {
                            coords Shape[] ={{data.at(count).toInt(),data.at(count+1).toInt()},{data.at(count+2).toInt(),data.at(count+3).toInt()},{data.at(count+4).toInt(),data.at(count+5).toInt()},{data.at(count+6).toInt(),data.at(count+7).toInt()}};
                            QPolygon polygonShape = assignShape(Shape);
                            Trapeziums.push_back(polygonShape);
                            count = count + 8;
                        }
                        if (shapeType == "Triangle") {
                            coords Shape[] ={{data.at(count).toInt(),data.at(count+1).toInt()},{data.at(count+2).toInt(),data.at(count+3).toInt()},{data.at(count+4).toInt(),data.at(count+5).toInt()}};
                            QPolygon polygonShape = assignShape(Shape);
                            Trapeziums.push_back(polygonShape);
                            count = count + 6;
                        }
                    }
                }
            }
         }
    loadFile.close();


    reloadImage(File);
    } catch(const std::runtime_error& e) {

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
     } catch (...) {
        ui->labelMainPic->setText("Invalid file format");
     }
}

void MainWindow::on_btn_OpenClass_clicked()
{
    classFilePath = QFileDialog::getOpenFileName(this, tr("Open file"), "/", tr("Name Files (*.names)"));
    QStringList newListObjects;
    try {

        QFile file(classFilePath);
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, "error", file.errorString());
        }
        QTextStream in(&file);

        while(!in.atEnd()) {
            newListObjects.append(in.readLine());
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

void MainWindow::addClassToLW(){

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
    selectedItem[0]->setText(renamedClass);
    //UpdateFile
    updateFile();
}

bool sorted(QStringList array,int high) {
    for (int i = 0; i< high; i++) {
        if (array[i] > array[i+1]) {
            return false;
        }
    }
    return true;
}

QStringList quickSort(QStringList array,int pivot, int low){
     QString temp;
     int l = low;
     int r = pivot -1;
     while (r > l) {
         if ((array[r] < array[pivot]) and (array[l] > array[pivot])) {
             temp = array[r];
             array[r] = array[l];
             array[l] = temp;
         }
         else if (array[l] < array[pivot]) {
             l = l + 1;
             if (array[r] > array[pivot]) {
                 r = r - 1;
             }
         }
         else if (array[r] > array[pivot]) {
             r = r - 1;
             if (array[l] < array[pivot]) {
                 l = l + 1;
             }
         }
     }
     if (array[pivot] < array[l]) {
         temp = array[pivot];
         array[pivot] = array[l];
         array[l] = temp;
     }
     if (sorted(array,pivot) != true) {
         quickSort(array, l-1, 0);
         quickSort(array, pivot, l+1);
     }
    return array;
}

void MainWindow::on_btn_SortList_clicked() //Sorts the classes into alphabetical order.
{
    int itemCount = ui->listWidget->count();
    if (itemCount > 1) {
        QStringList items;
        //std::string items[itemCount];
        QString temp;
        for (int i = 0; i< ui->listWidget->count(); i++) {
            temp = ui->listWidget->item(i)->text();
            items.append(temp);
        }
       items = quickSort(items,itemCount-1,0);
       ui->listWidget->clear();
       ui->listWidget->addItems(items);
    }
    else {
        QMessageBox::information(this, "error", tr("No classes to sort"));
    }

}


