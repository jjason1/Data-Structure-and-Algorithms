#include <iostream>
#include "Node.h"

using namespace std;

// Node constructor that sets data to default values
Node::Node(const string &data) : count(1), data(data), left(nullptr), right(nullptr) {}

// // Deconstrctor that recursivly deletes the left and right
// Node::~Node()
// {
//     delete left;
//     delete right;
// }

// // Copy constructor that makes a copy of the parameter passed in

// Node::Node(const Node &copy)
// {
//     count = copy.count;
//     data = copy.data;
//     right = nullptr;
//     left = nullptr;

//     if (copy.left != nullptr)
//     {
//         left = new Node(*copy.left);
//     }

//     if (copy.right != nullptr)
//     {
//         right = new Node(*copy.right);
//     }
// }

// // Assignment operator that sets the node objects to another node object
// Node &Node::operator=(const Node &copy)
// {
//     if (this != &copy)
//     {
//         count = copy.count;
//         data = copy.data;

//         delete left;
//         left = nullptr;
//         if (copy.left != nullptr)
//         {
//             left = new Node(*copy.left);
//         }

//         delete right;
//         right = nullptr;
//         if (copy.right != nullptr)
//         {
//             right = new Node(*copy.right);
//         }
//     }

//     return *this;
// }
