#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include "Node.h"
#include <string>

using namespace std;

class AVLTree
{
public:
    AVLTree();
    ~AVLTree();
    AVLTree(const AVLTree &);
    AVLTree &operator=(const AVLTree &);

    void insert(const string &);
    int balanceFactor(Node *);
    void printBalanceFactors();
    void visualizeTree(const string &);

private:
    Node *root;

    void destroyTree(Node *);
    Node *copyTree(const Node *);

    void rotate(Node *);
    void rotateLeft(Node *);
    void rotateRight(Node *);
    void setChild(Node *, string, Node *);
    void replaceChild(Node *, Node *, Node *);
    void printBalanceFactorsHelper(Node *);
    void visualizeTree(ofstream &, Node *);
    int findHeight(Node *) const;
};

#endif