#ifndef ANNOTATION_H
#define ANNOTATION_H
#include <string>
#include <QColor>
#include "shapeclass.h"
#include <fstream>
#include "mainwindow.h"

using namespace std;

class Annotation
{
public:
    Annotation(string);
    Annotation(vector<Shape>, int, string);
    Annotation(vector<Shape>,int, string, string, QColor); //Change class diagram to list of shapes per annotation
    string getCaption();
    void setCaption(string);
    QColor getColour();
    void setColour(QColor);
    void createAnnotationFile();
    void renameAnnotation();
    void saveAnnotation();
    void LoadAnnotation(); //Unsure on return type
    Annotation copyShape();
    string getImgPath();
    int noOfImages;

private:
    string caption;
    vector<Shape> annShapes;
    QColor annColour;
    int noOfAnnotations;
    string fileName;
    QString imgPath;
    bool fileExists(string);
    QString TypeOfShape;

};

#endif // ANNOTATION_H
