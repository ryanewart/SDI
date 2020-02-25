#include "shapeclass.h"
#include <iostream>
Shape::Shape()
{

}

shapeType  Shape::getShapeType() { return shape; }

double Shape::getCord(char choice, int index){
    if (choice == 'X' | choice == 'x') { return coordinates[index].x; }
    else if (choice == 'Y' | choice == 'y') {return coordinates[index].y; }
    else {
        throw out_of_range("invalid x/y");
    }
}

int Shape::getNoVertecies() { return noVertices; }

void Shape::addCord(int _x, int _y){
    cord tempCord; tempCord.x = _x; tempCord.y = _y;
    coordinates.push_back(tempCord);
}
