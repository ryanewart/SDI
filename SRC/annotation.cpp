#include "annotation.h"
#include "shapeclass.h"

#include <string>
#include <QColor>
#include <fstream>
#include <QMessageBox>
#include <QApplication>
#include <map>

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

string Annotation::getImgPath() { return imgPath; }

void Annotation::saveAnnotation(){
    string fileLocation;
    if (fileExists(fileName)){
        //Some user dialog to aks if they want to override
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "File Exists", "Override?", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes){
            fileLocation = fileName;
        } else {
            //Get new file name ?
        }
    }

    ofstream outputFile;
    outputFile.open(fileLocation, ios::app); //Number of annotated images (always 1), img path, number of shapes per image, for each shape: shape type, cords of each vertex
    if (outputFile.is_open()){
        outputFile << "1" << "\n";
        outputFile << imgPath << "\n";
        outputFile << noOfAnnotations << "\n";
        //For each image with this annotation
        for (int i=0; i < noOfAnnotations; i++){
            outputFile << annShapes[i].getShapeType() << "\n";
            for (int j=0; j<annShapes[i].getNoVertecies(); j++){
                outputFile << "x:" << annShapes[i].getCord('x', j) << "y:" << annShapes[i].getCord('y', j) << "\n";
            }
        }
    }
}

void Annotation::LoadAnnotation(){
    //Load annotation from file .annotation extension
    int noImages;
    int noShapes;
    map<int, int> vertexMapping;
    vertexMapping[1] = 4; vertexMapping[2] = 3; vertexMapping [3] = 4; vertexMapping[4] = 0;
    ifstream inputFile;
    inputFile.open(fileName, ios::in);
    if (inputFile.is_open()){
       inputFile >> noImages;
       inputFile >> imgPath;
       inputFile >> noShapes; //This many shape objects to add to vector
       for (int i = 0; i < noShapes; i++){
           int noVertecies;
           inputFile >> noVertecies;
           for (int j = 0; j < noVertecies; j++){
               //Get each cord and add to a new shape object in the vector
           }
       }
    }

}

Annotation Annotation::copyShape(){
    return * new Annotation(annShapes, noOfAnnotations, fileName, caption, annColour); //Return itself
}

bool Annotation::fileExists(string _fileName){
    ifstream existingFile(_fileName);
    return existingFile.good();
}


