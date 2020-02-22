#ifndef SHAPECLASS_H
#define SHAPECLASS_H
#include <vector>
using namespace std;

struct cord{
    double x;
    double y;
};

enum shapeType {square, triangle, trapezium, polygon};

class Shape
{
public:
    Shape();
    void DrawShape(); //Should probably pass the view object
    void removeShape(); //Should probably pass the view object
    void alterShape();
    shapeType getShapeType();
    double getCord(char, int);

private:
    vector<cord> coordinates;
    shapeType shape; //Should probably rename
};



#endif // SHAPECLASS_H
