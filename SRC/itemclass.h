#ifndef ITEMCLASS_H
#define ITEMCLASS_H
#include <string>
#include "annotation.h"

using namespace std;

class ItemClass
{

public:
    ItemClass(string);
    void SelectClass();
    void AddClass();
    void RemoveClass();
    void SaveClass();
    void AddAnnotation(Annotation);

private:
    string className;
    string classType;
    vector<Annotation> labels;
};

#endif // ITEMCLASS_H
