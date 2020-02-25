#ifndef SHAPECLASS_H
#define SHAPECLASS_H
#include <vector>
using namespace std;

struct cord{
    int x;
    int y;
};

enum shapeType {square = 1, triangle, trapezium, polygon};

class Shape
{
public:
    Shape();
    void DrawShape(); //Should probably pass the view object
    void removeShape(); //Should probably pass the view object
    void alterShape();
    void addCord(int, int);
    shapeType getShapeType();
    double getCord(char, int);
    int getNoVertecies();

private:
    vector<cord> coordinates;
    shapeType shape; //Should probably rename
    int noVertices;
};



#endif // SHAPECLASS_H
