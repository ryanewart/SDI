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
    outputFile.open(fileName, ios::app);
    if (outputFile.is_open()){
        outputFile << noOfAnnotations << "\n";
        //For each image with this annotation
        for (int i=0; i < annShapes.size(); i++){
            outputFile << annShapes[i].
        }

    }

}

void Annotation::LoadAnnotation(){

}

Annotation Annotation::copyShape(){
    return * new Annotation(annShapes, noOfAnnotations, fileName, caption, annColour); //Return itself
}

bool Annotation::fileExists(string _fileName){
    ifstream existingFile(_fileName);
    return existingFile.good();
}
