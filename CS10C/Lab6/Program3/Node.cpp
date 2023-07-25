#include "Node.h"

Node::Node() : left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {}

Node::Node(const string &copy) : left(nullptr), middle(nullptr), right(nullptr), parent(nullptr)
{
    large = "";
    small = copy;
}

// Checks if the node has two strings or not
bool Node::twoStringCheck() const
{
    return !large.empty();
}