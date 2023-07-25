#include "AVLTree.h"
#include <fstream>

using namespace std;

AVLTree::AVLTree() : root(nullptr) {} // Constructor for AVLTree class. Initializes the root pointer to nullptr.

AVLTree::~AVLTree()
{
    destroyTree(root); // Destructor for AVLTree class. Calls the destroyTree() function passing the root node for recursive destruction of the entire tree.
}

void AVLTree::destroyTree(Node *currNode)
{
    if (currNode != nullptr)
    {
        destroyTree(currNode->left);  // Recursively destroy the left subtree of the current node.
        destroyTree(currNode->right); // Recursively destroy the right subtree of the current node.

        delete currNode; // Delete the current node.
    }
}

AVLTree::AVLTree(const AVLTree &copy)
{
    // Copy constructor for AVLTree class. Performs a deep copy of the AVL tree.
    root = copyTree(copy.root); // Calls the copyTree() function to create a new tree that is a copy of the provided AVL tree.
}

Node *AVLTree::copyTree(const Node *currNode)
{
    if (!currNode)
    {
        return nullptr; // If the current node is nullptr, return nullptr.
    }

    // Create a new node with the same data as the current node.
    Node *newNode = new Node(currNode->data);
    newNode->count = currNode->count;

    // Recursively copy the left and right subtrees of the current node.
    newNode->left = copyTree(currNode->left);
    newNode->right = copyTree(currNode->right);

    return newNode; // Return the newly created node.
}

AVLTree &AVLTree::operator=(const AVLTree &rhs)
{
    if (this == &rhs)
    {
        // Self-assignment, no need to perform any operation
        return *this;
    }

    // Call a helper function to perform a deep copy of the AVL tree
    Node *newRoot = copyTree(rhs.root);

    // Call a helper function to delete the current tree
    destroyTree(root);

    // Assign the new root to the AVL tree
    root = newRoot;

    return *this;
}

void AVLTree::insert(const string &newData)
{
    Node *newNode = new Node(newData); // Create a new node with the given data
    Node *currNode = root;             // Start traversing the tree from the root node

    if (root == nullptr)
    {
        // If the tree is empty, set the new node as the root and return
        root = newNode;
        root->parent = nullptr;
        return;
    }

    while (currNode != nullptr)
    {
        if (newData == currNode->data)
        {
            // If the new data matches the current node's data, increment the count and exit the loop
            currNode->count++;
            currNode = nullptr; // Set currNode to nullptr to exit the loop
        }
        else if (newData > currNode->data)
        {
            if (currNode->right == nullptr)
            {
                // If the new data is greater than the current node's data and there is no right child,
                // insert the new node as the right child and exit the loop
                currNode->right = newNode;
                newNode->parent = currNode;
                currNode = nullptr; // Set currNode to nullptr to exit the loop
            }
            else
            {
                // Move to the right child and continue traversing
                currNode = currNode->right;
            }
        }
        else
        {
            if (currNode->left == nullptr)
            {
                // If the new data is less than the current node's data and there is no left child,
                // insert the new node as the left child and exit the loop
                currNode->left = newNode;
                newNode->parent = currNode;
                currNode = nullptr; // Set currNode to nullptr to exit the loop
            }
            else
            {
                // Move to the left child and continue traversing
                currNode = currNode->left;
            }
        }
    }

    newNode = newNode->parent; // Move up to the parent of the new node

    // Perform rotations to balance the tree starting from the new node's parent
    while (newNode)
    {
        rotate(newNode);
        newNode = newNode->parent;
    }
}

int AVLTree::balanceFactor(Node *key)
{
    int leftHeight = 0;
    int rightHeight = 0;

    if (key == nullptr)
    {
        return -1; // If the key node is nullptr, return -1 indicating an empty subtree.
    }

    if (key->left)
    {
        leftHeight = findHeight(key->left); // Calculate the height of the left subtree.
    }
    else
    {
        leftHeight = -1; // If the left child is nullptr, set the height to -1.
    }

    if (key->right)
    {
        rightHeight = findHeight(key->right); // Calculate the height of the right subtree.
    }
    else
    {
        rightHeight = -1; // If the right child is nullptr, set the height to -1.
    }

    return leftHeight - rightHeight; // Calculate and return the balance factor of the node.
}

// Prints Out All Balance Factors
void AVLTree::printBalanceFactors()
{
    printBalanceFactorsHelper(root);
    cout << endl;
}

// Prints Out Balance Factors of a Node
void AVLTree::printBalanceFactorsHelper(Node *key)
{
    if (key != nullptr)
    {
        printBalanceFactorsHelper(key->left);
        cout << key->data << "(" << balanceFactor(key) << "), ";
        printBalanceFactorsHelper(key->right);
    }
}

// Creates a Dot File for GraphViz
void AVLTree::visualizeTree(const string &outputFilename)
{
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open())
    {
        cout << "Error opening " << outputFilename << endl;
        return;
    }
    outFS << "digraph G {" << endl;
    visualizeTree(outFS, root);
    outFS << "}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

// Prints Out the Tree in GraphViz Format
void AVLTree::visualizeTree(ofstream &outFS, Node *targetNode)
{
    if (targetNode)
    {
        if (targetNode->left)
        {
            visualizeTree(outFS, targetNode->left);
            outFS << targetNode->data << " -> " << targetNode->left->data << ";" << endl;
        }

        if (targetNode->right)
        {
            visualizeTree(outFS, targetNode->right);
            outFS << targetNode->data << " -> " << targetNode->right->data << ";" << endl;
        }
    }
}

void AVLTree::rotate(Node *key)
{
    if (balanceFactor(key) == -2)
    {
        // Perform right rotation
        if (balanceFactor(key->right) == 1)
        {
            rotateRight(key->right); // Perform a right rotation on the right child of the key
        }
        rotateLeft(key); // Perform a left rotation on the key itself
    }
    else if (balanceFactor(key) == 2)
    {
        // Perform left rotation
        if (balanceFactor(key->left) == -1)
        {
            rotateLeft(key->left); // Perform a left rotation on the left child of the key
        }
        rotateRight(key); // Perform a right rotation on the key itself
    }
}

void AVLTree::rotateRight(Node *key)
{
    Node *rotatingNode = key->left->right;

    // if target node has a parent
    if (key->parent)
    {
        replaceChild(key->parent, key, key->left);
    }

    // otherwise set root to target node's left
    else
    {
        root = key->left;
        root->parent = 0;
    }

    // sets the child of the target node's left to the target node
    setChild(key->left, "right", key);
    setChild(key, "left", rotatingNode);
}

void AVLTree::rotateLeft(Node *key)
{
    Node *rotatingNode = key->right->left;

    // if target node has a parent
    if (key->parent)
    {
        replaceChild(key->parent, key, key->right);
    }

    // otherwise set root to target node's right
    else
    {
        root = key->right;
        root->parent = 0;
    }

    // sets the child of the target node's right to the target node
    setChild(key->right, "left", key);
    setChild(key, "right", rotatingNode);
}

void AVLTree::setChild(Node *parentNode, string location, Node *childNode)
{
    if (location == "left")
    {
        parentNode->left = childNode; // Set the left child of the parentNode to the childNode.
    }
    else
    {
        parentNode->right = childNode; // Set the right child of the parentNode to the childNode.
    }
    if (childNode)
    {
        childNode->parent = parentNode; // Set the parent of the childNode to the parentNode.
    }
}

void AVLTree::replaceChild(Node *parentNode, Node *key, Node *childNode)
{

    // if parent's left is the target node
    if (parentNode->left == key)
    {
        setChild(parentNode, "left", childNode);
    }

    // if parent's right is the target node
    else if (parentNode->right == key)
    {
        setChild(parentNode, "right", childNode);
    }
}

int AVLTree::findHeight(Node *currNode) const
{

    // if node doesn't exist
    if (currNode == nullptr)
    {
        return -1;
    }

    // if node is a leaf
    else if (currNode->left == nullptr && currNode->right == nullptr)
    {
        return 0;
    }

    int leftHeight = findHeight(currNode->left);
    int rightHeight = findHeight(currNode->right);

    // returns the height of the node
    if (leftHeight > rightHeight)
    {
        return leftHeight + 1;
    }

    else
    {
        return rightHeight + 1;
    }

    return 0;
}
