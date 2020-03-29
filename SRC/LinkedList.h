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
    node * head;
    node * tail;
public:
    coords popTail();
    List(coords input);
    node CreateNode(coords input, node * prev);
    void addNode(coords input);
    coords getHead();
    coords getTail();
    coords popHead();
    void displayList();
    bool searchList(coords input);
    int size();

};


#endif // LINKEDLIST_H
