#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <string>

using namespace std;

class Node
{
    friend class AVLTree;

private:
    string data;
    int count;
    Node *left;
    Node *right;
    Node *parent;

public:
    Node(const string &);
};

#endif