#include "Tree.h"
#include <iostream>

using namespace std;

Tree::Tree() : root(nullptr) {} // Constructor for Tree class, initializes root pointer to nullptr

Tree::~Tree()
{
    delete deleteTree(root); // Destructor for Tree class, deletes the tree by calling deleteTree() function on the root node
}

Node *Tree::deleteTree(Node *currNode)
{
    if (currNode)
    {
        delete deleteTree(currNode->left);   // Recursively delete the left subtree
        delete deleteTree(currNode->middle); // Recursively delete the middle subtree
        delete deleteTree(currNode->right);  // Recursively delete the right subtree
    }

    return currNode; // Return the current node after deleting its subtrees
}

Tree::Tree(const Tree &copy)
{
    root = copyTree(copy.root, nullptr); // Copy constructor for Tree class, creates a deep copy of the tree by calling copyTree() function on the root node
}

Node *Tree::copyTree(const Node *currNode, Node *parentNode)
{
    if (currNode == nullptr)
    {
        return nullptr; // If the current node is nullptr, return nullptr
    }

    Node *newNode = new Node();       // Create a new node
    newNode->small = currNode->small; // Copy the small value from the current node
    newNode->large = currNode->large; // Copy the large value from the current node
    newNode->parent = parentNode;     // Set the parent of the new node to the specified parent node

    newNode->left = copyTree(currNode->left, newNode);     // Recursively copy the left subtree, setting the parent as the new node
    newNode->middle = copyTree(currNode->middle, newNode); // Recursively copy the middle subtree, setting the parent as the new node
    newNode->right = copyTree(currNode->right, newNode);   // Recursively copy the right subtree, setting the parent as the new node

    return newNode; // Return the newly created node
}

Tree &Tree::operator=(const Tree &copy)
{
    if (this != &copy)
    {
        deleteTree(root);
        root = copyTree(copy.root, nullptr);
    }

    return *this;
}

void Tree::preOrder() const
{
    preOrderHelper(root);
    cout << endl;
}

void Tree::preOrderHelper(Node *currNode) const
{
    if (currNode != nullptr)
    {
        cout << currNode->small << ", "; // Print the small value

        preOrderHelper(currNode->left); // Recursively traverse the left subtree

        if (currNode->twoStringCheck())
        {
            cout << currNode->large << ", ";  // If the node has a large value, print it
            preOrderHelper(currNode->middle); // Recursively traverse the middle subtree
            preOrderHelper(currNode->right);  // Recursively traverse the right subtree
        }
        else
        {
            preOrderHelper(currNode->middle); // Recursively traverse the middle subtree
        }
    }
}

void Tree::postOrder() const
{
    postOrderHelper(root);
    cout << endl;
}

// Helper Function print postOrder
void Tree::postOrderHelper(Node *currNode) const
{
    if (currNode == nullptr)
    {
        return; // Base case: Exit the function if the current node is null.
    }

    if (currNode)
    {
        if (currNode->twoStringCheck()) // If the current node satisfies the condition for two strings
        {
            postOrderHelper(currNode->left);   // Traverse the left subtree
            postOrderHelper(currNode->middle); // Traverse the middle subtree
            cout << currNode->small << ", ";   // Print the value of the smaller string
            postOrderHelper(currNode->right);  // Traverse the right subtree
            cout << currNode->large << ", ";   // Print the value of the larger string
        }
        else // If the current node does not satisfy the condition for two strings
        {
            postOrderHelper(currNode->left);   // Traverse the left subtree
            postOrderHelper(currNode->middle); // Traverse the middle subtree
            cout << currNode->small << ", ";   // Print the value of the small string
        }
    }
}

void Tree::inOrder() const
{
    inOrderHelper(root);
    cout << endl;
}

void Tree::inOrderHelper(Node *currNode) const
{
    if (currNode != nullptr)
    {
        inOrderHelper(currNode->left); // Recursively traverse the left subtree

        cout << currNode->small << ", "; // Print the small value

        inOrderHelper(currNode->middle); // Recursively traverse the middle subtree

        if (currNode->twoStringCheck())
        {
            cout << currNode->large << ", "; // If the node has a large value, print it
            inOrderHelper(currNode->right);  // Recursively traverse the right subtree
        }
    }
}

void Tree::insert(const string &newData)
{
    // If the tree is empty, create a new node and make it the root
    if (root == nullptr)
    {
        root = new Node(newData);
    }

    // If the tree is not empty and the newData is not already present in the tree
    else if (!search(newData))
    {
        insertHelper(root, newData); // Call the helper function to insert newData
    }
}

void Tree::insertHelper(Node *currentNode, const string &newData)
{
    // Traverse down the tree until reaching a leaf node
    while (currentNode->left)
    {
        // Check if the current node has three leaves
        if (currentNode->twoStringCheck())
        {
            // If the entry is smaller, move to the left leaf
            if (currentNode->small > newData)
            {
                currentNode = currentNode->left;
            }
            // If the entry is larger, move to the right leaf
            else if (currentNode->large < newData)
            {
                currentNode = currentNode->right;
            }
            // If the entry is in the middle range, move to the middle leaf
            else
            {
                currentNode = currentNode->middle;
            }
        }
        // If the current node has two leaves
        else
        {
            // If the entry is smaller, move to the left leaf
            if (currentNode->small > newData)
            {
                currentNode = currentNode->left;
            }
            // If the entry is in the middle range, move to the middle leaf
            else
            {
                currentNode = currentNode->middle;
            }
        }
    }

    // If the current node has three leaves
    if (currentNode->twoStringCheck())
    {
        string smallerValue, middleValue, largerValue;

        // Determine the correct position for the entry
        if (currentNode->small > newData)
        {
            smallerValue = newData;
            middleValue = currentNode->small;
            largerValue = currentNode->large;
        }
        else if (currentNode->large < newData)
        {
            smallerValue = currentNode->small;
            middleValue = currentNode->large;
            largerValue = newData;
        }
        else
        {
            smallerValue = currentNode->small;
            middleValue = newData;
            largerValue = currentNode->large;
        }

        // Create two children nodes
        Node *smallerNode = new Node(smallerValue);
        Node *largerNode = new Node(largerValue);

        // Update the current node with the middle value and set pointers to the smaller and larger nodes
        currentNode->small = middleValue;
        currentNode->large = "";
        currentNode->left = smallerNode;
        currentNode->middle = largerNode;
        currentNode->right = nullptr;

        // Link the parent nodes
        smallerNode->parent = currentNode;
        largerNode->parent = currentNode;

        // Rebalance the tree
        balance(currentNode);
    }
    // If the current node has only two leaves
    else
    {
        // If the entry is smaller than the current node
        if (currentNode->small > newData)
        {
            currentNode->large = currentNode->small;
            currentNode->small = newData;
        }
        // If the entry is larger than the current node
        else
        {
            currentNode->large = newData;
        }
    }
}

bool Tree::search(const string &key) const
{
    if (root == nullptr)
    {
        return false;
    }

    Node *currentNode = root;

    while (currentNode)
    {
        // Check if the key matches the small value of the current node
        // or if it matches the large value and the node has two strings
        if (currentNode->small == key || (currentNode->large == key && currentNode->twoStringCheck()))
        {
            return true; // Key found, return true
        }
        else
        {
            if (currentNode->small > key)
            {
                currentNode = currentNode->left; // Move to the left child
            }
            else
            {
                if (currentNode->large < key && currentNode->twoStringCheck())
                {
                    currentNode = currentNode->right; // Move to the right child
                }
                else
                {
                    currentNode = currentNode->middle; // Move to the middle child
                }
            }
        }
    }

    return false; // Key not found, return false
}

void Tree::balance(Node *key)
{
    // Only if the node has a parent
    if (key->parent)
    {
        Node *parent = key->parent;

        // Check if the parent has two strings
        if (parent->twoStringCheck())
        {
            // If the parent is larger than the current node
            if (parent->small > key->small)
            {
                Node *largeNode = new Node(parent->large);

                // Adjust pointers for the new largeNode
                largeNode->left = parent->middle;
                largeNode->left->parent = largeNode;
                largeNode->middle = parent->right;
                largeNode->middle->parent = largeNode;

                // Update parent node with key as left child and largeNode as middle child
                parent->left = key;
                parent->middle = largeNode;
                parent->right = nullptr;
                parent->large = "";

                // Update parent pointer for the largeNode
                largeNode->parent = parent;
            }
            // If the parent is smaller than the current node
            else if (parent->large < key->small)
            {
                Node *smallNode = new Node(parent->small);

                // Adjust pointers for the new smallNode
                smallNode->left = parent->left;
                smallNode->left->parent = smallNode;
                smallNode->middle = parent->middle;
                smallNode->middle->parent = smallNode;

                // Update parent node with smallNode as left child and key as middle child
                parent->left = smallNode;
                parent->middle = key;
                parent->right = nullptr;
                parent->small = parent->large;
                parent->large = "";

                // Update parent pointer for the smallNode
                smallNode->parent = parent;
            }
            else
            {
                Node *smallNode = new Node(parent->small);
                smallNode->left = parent->left;
                smallNode->left->parent = smallNode;
                smallNode->middle = key->left;
                smallNode->middle->parent = smallNode;

                Node *largeNode = new Node(parent->large);
                largeNode->left = key->middle;
                largeNode->left->parent = largeNode;
                largeNode->middle = parent->middle;
                largeNode->middle->parent = largeNode;

                parent->left = smallNode;
                parent->middle = largeNode;
                parent->right = nullptr;
                parent->small = key->small;
                parent->large = "";

                smallNode->parent = parent;
                largeNode->parent = parent;

                delete key;
            }

            balance(parent);
        }
        else
        {
            if (parent->small > key->small)
            {
                parent->large = parent->small;
                parent->small = key->small;

                // Adjust pointers for the parent node
                parent->left = key->left;
                parent->right = parent->middle;
                parent->middle = key->middle;
            }
            else
            {
                parent->large = key->small;

                // Adjust pointers for the parent node
                parent->middle = key->left;
                key->left->parent = parent;
                parent->right = key->middle;
                key->middle->parent = parent;
            }

            // Update parent pointers for the children nodes and delete the current node
            key->left->parent = parent;
            key->middle->parent = parent;
            delete key;
        }
    }
}

void Tree::remove(const string &key)
{
    // returns if tree is empty
    if (root == nullptr)
    {
        return;
    }

    else
    {
        Node *currentNode = root;

        // finds the node with the entry
        while (currentNode)
        {
            // if the entry is found
            if (currentNode->small == key || (currentNode->large == key && currentNode->twoStringCheck()))
            {
                break;
            }

            else
            {
                // if current node is smaller move left
                if (currentNode->small > key)
                {
                    currentNode = currentNode->left;
                }

                // if current node is smaller that larger and only two leaves move right
                else if (currentNode->twoStringCheck() && currentNode->large < key)
                {
                    currentNode = currentNode->right;
                }

                // otherwise move to the middle
                else
                {
                    currentNode = currentNode->middle;
                }
            }
        }

        if (currentNode)
        {
            // if the node has three leaves
            if (currentNode->twoStringCheck())
            {
                // if the entry is the small value
                if (currentNode->small == key)
                {
                    currentNode->small = currentNode->large;
                    currentNode->large = "";
                }

                // if the entry is the large value
                else
                {
                    currentNode->large = "";
                }
            }

            // if the node only has two leaves
            else
            {
                Node *parentNode = currentNode->parent;

                // if the node has a parent
                if (parentNode)
                {
                    if (parentNode->small > key)
                    {
                        parentNode->left = nullptr;
                        parentNode->large = parentNode->middle->small;
                        parentNode->middle = nullptr;
                    }

                    else
                    {
                        parentNode->middle = nullptr;
                        parentNode->large = parentNode->small;
                        parentNode->small = parentNode->left->small;
                        parentNode->left = nullptr;
                    }
                }

                // if the node has no parent
                else
                {
                    Node *childNode = new Node();

                    if (root->left)
                    {
                        childNode->small = root->left->small;
                        childNode->large = root->middle->small;
                        root = childNode;
                    }

                    else
                    {
                        root = nullptr;
                    }
                }
            }
        }
    }
}