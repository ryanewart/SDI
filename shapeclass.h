#ifndef SHAPECLASS_H
#define SHAPECLASS_H
#include <vector>
using namespace std;

struct cord{
    double x;
    double y;
};

enum shapeType {square, triangle, trapezium, polygon};

class shapeClass
{
public:
    shapeClass();
    void DrawShape(); //Should probably pass the view object
    void removeShape(); //Should probably pass the view object
    void alterShape();

private:
    vector<cord> coordinates;
    shapeType shape;
};



#endif // SHAPECLASS_H
