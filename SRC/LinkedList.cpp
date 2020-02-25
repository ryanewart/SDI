#include <iostream>
#include <assert.h>
#include "LinkedList.h"

using namespace std;

List::List(coords input) {
    node* TestNode = new node;
    *TestNode = CreateNode(input, NULL);
    head = TestNode;
    tail = TestNode;
}

node List::CreateNode(coords input, node * prev) {
    node testnode;
    testnode.values = input;
    testnode.previous = prev;
    testnode.next = NULL;
    return testnode;
}
/*
bool List:: searchList(coords input) {
    node* firstNode = new node;
    firstNode = head;
    node Test = *firstNode;
    while((Test.previous != NULL) and (Test.value != input)) {
        firstNode = Test.previous;
        Test = *firstNode;
        cout<<Test.value<<endl;
    }

    if (Test.value == input)
        return 1;
    else return 0;
}
*/

/*
void List:: displayList() {
    node* firstNode = new node;
    firstNode = head;
    node Test = *firstNode;
    cout<<Test.value<<endl;
    while(Test.previous != NULL) {
        firstNode = Test.previous;
        Test = *firstNode;
        cout<<Test.value<<endl;
    }
}
*/

void List:: addNode(coords input) {
    node* OldHead = new node;
    OldHead = head;
    node Test = *OldHead;
    node* NewHead = new node;
    *NewHead = CreateNode(input, OldHead);
    Test.next= NewHead;
    head = NewHead;
}

coords List:: getHead() {
    node* NodeHead = new node;
    NodeHead = head;
    node Test = *NodeHead;
    coords value = Test.values;
    //cout<<value<<endl;
    return value;
}

coords List:: popHead() {
    node* NodeHead = new node;
    node* NewHead = new node;
    NodeHead = head;
    node Test = *NodeHead;
    coords value = Test.values;
    NewHead = NodeHead->previous;
    NodeHead->previous = NULL;
    head = NewHead;
    return value;
}

coords List :: getTail() {
    node* NodeTail = new node;
    NodeTail= tail;
    node Test = *NodeTail;
    coords value = Test.values;
    return value;
}

int List:: size() {
    int count = 1;
    node* firstNode = new node;
    firstNode = head;
    node Test = *firstNode;
    while(Test.previous != NULL) {
        count++;
        firstNode = Test.previous;
        Test = *firstNode;
    }
    return count;
}
