#ifndef __NODE_H__
#define __NODE_H__

#include <string>

using namespace std;

struct Node
{
    int count;
    string data;
    Node *left;
    Node *right;
    
    Node(const string &data);
    // ~Node();
    // Node(const Node &);
    // Node &operator=(const Node &);
};

#endif