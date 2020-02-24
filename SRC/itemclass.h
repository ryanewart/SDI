#ifndef ITEMCLASS_H
#define ITEMCLASS_H
#include <string>
#include "annotation.h"

using namespace std;

class ItemClass
{

public:
    ItemClass();
    void SelectClass();
    void AddClass();
    void RemoveClass();
    void SaveClass();

private:
    string className;
    string classType;
    Annotation label;
};

#endif // ITEMCLASS_H
