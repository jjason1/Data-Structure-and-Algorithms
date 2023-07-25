#pragma once

#include <iostream>
using namespace std;

struct IntNode
{
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

class IntList 
{
private:
    IntNode *dummyHead;
    IntNode *dummyTail;

public:
    IntList();
    ~IntList();
    //Copy constructor
    IntList(const IntList &);
    //Assignment operator
	IntList & operator=(const IntList &); 
    void push_front(const int &);
    void pop_front();
    void push_back(const int &);
    void pop_back();
    bool empty() const;
    void printReverse() const;
    friend ostream &operator<<(ostream &, const IntList &);

};