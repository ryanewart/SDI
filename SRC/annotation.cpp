#include "annotation.h"
#include "shapeclass.h"

#include <string>
#include <cstdio>
#include <QColor>
#include <fstream>
#include <QMessageBox>
#include <QInputDialog>
#include <QApplication>
#include <map>
#include <QFile>
#include <QDebug>


Annotation::Annotation(string _inputFile){
    fileName = _inputFile;
    LoadAnnotation();
}

Annotation::Annotation(vector<Shape> _annShapes, int _noOfAnnotations, string _fileName){
    annShapes = _annShapes;
    noOfAnnotations = _noOfAnnotations;
    fileName = _fileName;
}
Annotation::Annotation(vector<Shape>,int, string, string, QColor){

}

string Annotation::getCaption() { return caption; }
void Annotation::setCaption(string _caption){ this->caption = _caption; }

QColor Annotation::getColour() { return annColour; }
void Annotation::setColour(QColor _colour) { this->annColour = _colour; }

//string Annotation::getImgPath() { return imgPath; }

void createAnnotationFile(){
    QMessageBox msgBox;

    QString filename = "dogAnnotation.txt";
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite | QFile::Text)) {
        msgBox.setText("File could not be created");
        msgBox.exec();
     } else {
        QTextStream stream(&file);
        stream << "test" << endl;
        msgBox.setText("File created successfully");
        msgBox.setInformativeText("File created in project directory");
        msgBox.exec();
     }
}

//void Annotation::renameAnnotation(){
//    int result;
//    bool ok;
//    //char oldname[] ="";
//    //char newname[] ="";
//    QString oldNameInput = QInputDialog::getText(0, "Input dialog", "Old file name:", QLineEdit::Normal,
//                                         "", &ok);
//    if (ok && !oldNameInput.isEmpty()) {


//         QString newNameInput = QInputDialog::getText(0, "Input dialog", "New file name:", QLineEdit::Normal,
//                                              "", &ok);
//         if (ok && !newNameInput.isEmpty()) {
//              QString qStr = newNameInput;
//              string str = qStr.toStdString();
//              const char *newname = str.c_str();
//              result= rename( *oldname , *newname );  //NEED TO DO THIS WITHOUT CONSTANTS
//              if ( result == 0 )
//                  qDebug( "File successfully renamed" );
//              else
//                  qDebug( "Error renaming file" );
//         }
//    }
//}

/*
void Annotation::saveAnnotation(){
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
                    outputStream << "," << imgPath[i];
                    }
                outputStream << "\n";
                //New line in file
                outputStream << noOfAnnotations;

                for (int j=0; j < noOfAnnotations; j++){
                    outputStream << "\n" << annShapes[j].getShapeType();
                    for (int k=0; k<annShapes[j].getNoVertecies(); j++){
                        outputStream << "," << annShapes[j].getCord('x', k) << "," << annShapes[j].getCord('y', k);
                    }
                }
                file.close();
            }

         } else {
            qDebug() << "Save cancelled";
         }
    }
}
*/


void Annotation::LoadAnnotation(){
    //Load annotation from file .annotation extension


    QFile inputFile("test.txt");
    if(!inputFile.open(QIODevice::ReadOnly)){
        QMessageBox::information(0, "error", inputFile.errorString());
    }

    QTextStream in(&inputFile);
    while(!in.atEnd()){
        for(int lineNo = 1; !in.atEnd(); ++lineNo){
            QString line = in.readLine();
            QStringList data = line.split(",");
            if (lineNo == 1){
                QString noImages = data.at(0).toLocal8Bit().constData();
                for(int i = 0; i < data.size(); ++i){
                    QStringList filepathList;
                    QString File = data.at(i + 1).toLocal8Bit().constData();
                    filepathList.insert(i + 1, File);
                }
            }
            if (lineNo == 2){
                QString noShapes = data.at(0).toLocal8Bit().constData();
            }
            else{
                QString shapeType = data.at(0).toLocal8Bit().constData();
                for(int j = 0; j < data.size(); ++j){
                    QStringList coordinatePointsList;
                    QString coordinate = data.at(j + 1).toLocal8Bit().constData();
                    coordinatePointsList.insert(j + 1, coordinate);
                }
            }
        }
    }
    inputFile.close();
}


Annotation Annotation::copyShape(){
    return * new Annotation(annShapes, noOfAnnotations, fileName, caption, annColour); //Return itself
}

bool Annotation::fileExists(string _fileName){
    ifstream existingFile(_fileName);
    return existingFile.good();
}



