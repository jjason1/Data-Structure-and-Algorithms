#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree
{
private:
    Node *root;

public:
    Tree();
    ~Tree();
    Tree(const Tree &);
    Tree &operator=(const Tree &);
    void preOrder() const;
    void postOrder() const;
    void inOrder() const;
    void insert(const string &);
    bool search (const string &) const;
     void remove(const string &);

private:
    // Add additional functions/variables here

    Node *deleteTree(Node *);
    Node *copyTree(const Node *, Node *);
    void preOrderHelper(Node *) const;
    void postOrderHelper(Node *) const;
    void inOrderHelper(Node *) const;
    void insertHelper(Node *, const string &);
    void balance(Node *);
};


#endif