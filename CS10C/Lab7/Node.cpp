#include "Node.h"

// Default Constructor
Node::Node(const string &data) : data(data), count(1), left(nullptr), right(nullptr), parent(nullptr){}