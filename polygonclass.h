#ifndef POLYGONCLASS_H
#define POLYGONCLASS_H
#include "shapeclass.h"

class polygonClass : Shape
{
public:
    polygonClass();
    void addLine();
    bool CheckConnected();
private:
    int noSides;
};

#endif // POLYGONCLASS_H
