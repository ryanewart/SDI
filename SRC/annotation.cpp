#include "annotation.h"
#include "shapeclass.h"

#include <string>
#include <QColor>
#include <fstream>

Annotation::Annotation(vector<Shape>, int, string){

}
Annotation::Annotation(vector<Shape>,int, string, string, QColor){

}

string Annotation::getCaption() { return caption; }
void Annotation::setCaption(string _caption){ this->caption = _caption; }

QColor Annotation::getColour() { return annColour; }
void Annotation::setColour(QColor _colour) { this->annColour = _colour; }

void Annotation::saveAnnotation(){
    if (fileExists(fileName)){
        //Some user dialog to aks if they want to override
    }

    ofstream outputFile;
    outputFile.open(fileName, ios::app); //Number of annotated images (always 1), img path, number of shapes per image, for each shape: shape type, cords of each vertex
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
}

Annotation Annotation::copyShape(){
    return * new Annotation(annShapes, noOfAnnotations, fileName, caption, annColour); //Return itself
}

bool Annotation::fileExists(string _fileName){
    ifstream existingFile(_fileName);
    return existingFile.good();
}

string Annotation::getImgPath() { return imgPath; }
