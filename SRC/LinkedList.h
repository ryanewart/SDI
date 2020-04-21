#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "mainwindow.h"

struct coords {
    int x,y;
};

struct node {
    coords values;
    node * next;
    node * previous;
};

class List {
private:
    node * tail;
public:
    void set(int pos, coords data);
    coords popTail();
    List(coords input);
    node CreateNode(coords input, node * prev);
    void push_back(coords input);
    coords getHead();
    coords getTail();
    coords popHead();
    void displayList();
    bool searchList(coords input);
    int size();
    coords At(int pos);
    coords* copy(int size);
    node * head;    
    void clear();

};


#endif // LINKEDLIST_H
