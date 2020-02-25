#ifndef ANNOTATION_H
#define ANNOTATION_H
#include <string>
#include <QColor>
#include "shapeclass.h"
#include <fstream>

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
    void saveAnnotation();
    void LoadAnnotation(); //Unsure on return type
    Annotation copyShape();
    string getImgPath();

private:
    string caption;
    vector<Shape> annShapes;
    QColor annColour;
    int noOfAnnotations;
    string fileName;
    string imgPath;
    bool fileExists(string);
};

#endif // ANNOTATION_H
