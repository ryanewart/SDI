#ifndef ANNOTATION_H
#define ANNOTATION_H
#include <string>
#include <QColor>
using namespace std;

class Annotation
{
public:
    Annotation();

private:
    string caption;
    //Shape of type shape
    QColor annColour;
    int noOfAnnotations;
    string fileName;

};

#endif // ANNOTATION_H
