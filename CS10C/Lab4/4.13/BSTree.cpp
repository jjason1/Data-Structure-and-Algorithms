#include "BSTree.h"
#include "Node.h"
#include <iostream>
#include <string>
using namespace std;

// Sets the root to nullptr
BSTree::BSTree() : root(nullptr) {}

// The deconstructor that calls a recrusive function to delete all the nodes
BSTree::~BSTree()
{
    deleteTreeHelper(root);
}

// A recursive function that starts at the leafs and deletes all the node up to the root
void BSTree::deleteTreeHelper(Node *currNode)
{
    if (currNode == nullptr)
    {
        return;
    }
    else
    {
        deleteTreeHelper(currNode->left);  // Deletes nodes in the left
        deleteTreeHelper(currNode->right); // Deletes nodes in the right
        delete currNode;
    }
}

BSTree::BSTree(const BSTree &copy)
{
    // If the other tree is empty, set the root to nullptr and return
    if (copy.root == nullptr)
    {
        root = nullptr;
        return;
    }

    // Create a new root node and copy the data from the other root node
    root = new Node(copy.root->data);
    root->count = copy.root->count;

    // Recursively copy the left and right subtrees
    if (copy.root->left != nullptr)
    {
        root->left = new Node(*copy.root->left);
    }
    if (copy.root->right != nullptr)
    {
        root->right = new Node(*copy.root->right);
    }
}

BSTree &BSTree::operator=(const BSTree &copy)
{
    // Check for self-assignment
    if (this == &copy)
    {
        return *this;
    }

    // Create a temporary copy of the other tree
    BSTree copyTree(copy);

    // Swap the root pointers of the two trees
    swap(root, copyTree.root);

    // Return this object
    return *this;
}

// First checks if the root is null, if it is then the root becomes the new node
void BSTree::insert(const string &newString)
{
    Node *newNode = new Node(newString);

    if (root != nullptr)
    {
        insertHelper(root, newNode);
    }
    else
    {
        root = newNode;
    }


}
// Recursively moves down the binary tree to find the positon to insert the new node
void BSTree::insertHelper(Node *parentNode, Node *currNode)
{
    if (currNode->data < parentNode->data)
    {
        if (parentNode->left == nullptr)
        {
            parentNode->left = currNode;
        }
        else
        {
            insertHelper(parentNode->left, currNode);
        }
    }
    else if (currNode->data > parentNode->data)
    {
        if (parentNode->right == nullptr)
        {
            parentNode->right = currNode;
        }
        else
        {
            insertHelper(parentNode->right, currNode);
        }
    }
    else
    {
        // deletes duplicate node
        parentNode->count++;
        delete currNode;
    }
}

// This function removes a node with a given key from a binary search tree.
void BSTree::remove(const string &key)
{
    // If the node with the given key is not found in the tree, return.
    if (!search(key))
    {
        return;
    }
    else
    {
        // Find the node with the given key and its parent node.
        Node *currNode = searchHelper(key, root);
        Node *parentNode = getParentNode(currNode);

        removeHelper(parentNode, currNode);
    }
}
// This function removes a node from a binary search tree, with the help of its parent node.
void BSTree::removeHelper(Node *parent_node, Node *current_node)
{
    if (current_node->count > 1) // if the current node has a count greater than 1, decrement it and return
    {
        --current_node->count;
        return;
    }

    if (current_node->left == nullptr && current_node->right == nullptr) // if the current node has no children
    {
        if (parent_node != nullptr) // if the current node has a parent
        {
            if (current_node->data < parent_node->data) // if the current node is the left child of the parent
            {
                parent_node->left = nullptr; // set the parent's left child to null
                delete current_node;         // delete the current node
            }
            else // if the current node is the right child of the parent
            {
                parent_node->right = nullptr; // set the parent's right child to null
                delete current_node;          // delete the current node
            }
        }
        else // if the current node is the root node
        {
            root = nullptr;      // set the root to null
            delete current_node; // delete the current node
        }
    }
    else // if the current node has one or two children
    {
        Node *successor_node = nullptr;             // initialize a pointer to the successor node
        Node *successor_node_parent = current_node; // initialize a pointer to the parent of the successor node

        if (successor_node_parent->left != nullptr) // if the current node has a left child
        {
            successor_node = largestHelper(current_node->left);    // find the largest node in the left subtree of the current node
            successor_node_parent = getParentNode(successor_node); // find the parent of the successor node
        }
        else // if the current node does not have a left child (i.e., it has a right child)
        {
            successor_node = smallestHelper(current_node->right);  // find the smallest node in the right subtree of the current node
            successor_node_parent = getParentNode(successor_node); // find the parent of the successor node
        }

        Node successor_node_cpy = *successor_node; // create a copy of the successor node
        successor_node->count = 1;                 // set the count of the successor node to 1

        removeHelper(successor_node_parent, successor_node); // recursively remove the successor node

        current_node->data = successor_node_cpy.data;   // set the data of the current node to the data of the successor node
        current_node->count = successor_node_cpy.count; // set the count of the current node to the count of the successor node
    }
}

bool BSTree::search(const string &search_key) const
{
    // Call the search helper function to find the node with the given key
    if (searchHelper(search_key, root))
    {
        // If the node is found, return true
        return true;
    }
    return false;
}

Node *BSTree::searchHelper(const string &search_key, Node *current_node) const
{
    // If the current node is null, return null pointer as the key is not found
    if (current_node == nullptr)
    {
        return nullptr;
    }

    // If the search key matches the data of the current node, return the current node pointer
    if (search_key == current_node->data)
    {
        return current_node;
    }
    // If the search key is less than the data of the current node, search in the left subtree
    else if (search_key < current_node->data)
    {
        return searchHelper(search_key, current_node->left);
    }
    // If the search key is greater than the data of the current node, search in the right subtree
    else
    {
        return searchHelper(search_key, current_node->right);
    }
}

// Gets the parent node of a current node
Node *BSTree::getParentNode(Node *key) const
{
    return getParentNodeHelper(root, key);
}

Node *BSTree::getParentNodeHelper(Node *parent_node, Node *target_node) const
{
    // If parent node is null, return null
    if (parent_node == nullptr)
    {
        return nullptr;
    }

    // If either left or right child of the parent node is the target node, return the parent node
    if (parent_node->left == target_node || parent_node->right == target_node)
    {
        return parent_node;
    }

    // If the target node is less than the parent node's data, recursively call the function
    // on the left child of the parent node
    if (parent_node->data > target_node->data)
    {
        return getParentNodeHelper(parent_node->left, target_node);
    }
    // If the target node is greater than or equal to the parent node's data, recursively call
    // the function on the right child of the parent node
    else
    {
        return getParentNodeHelper(parent_node->right, target_node);
    }
}

// Findst the largest value in the BST
string BSTree::largest() const
{

    Node *largestNode = largestHelper(root);

    if (largestNode == nullptr)
    {
        return "";
    }

    return largestNode->data;
}

Node *BSTree::largestHelper(Node *currNode) const
{
    // If the current node is null, return null as it doesn't have a largest node.
    if (currNode == nullptr)
    {
        return nullptr;
    }

    // If the current node doesn't have a right child, it must be the largest node in the subtree.
    if (currNode->right == nullptr)
    {
        return currNode;
    }
    else
    {
        // Otherwise, keep going right to find the largest node.
        return largestHelper(currNode->right);
    }
}

// Finds the smallest value in the BST
string BSTree::smallest() const
{
    Node *smallestNode = smallestHelper(root);

    if (smallestNode == nullptr)
    {
        return "";
    }

    return smallestNode->data;
}

Node *BSTree::smallestHelper(Node *currNode) const
{
    // If the current node is null, there are no nodes in the subtree, so return null
    if (currNode == nullptr)
    {
        return nullptr;
    }

    // If the left child of the current node is null, then the current node has the smallest value in the subtree
    if (currNode->left == nullptr)
    {
        return currNode;
    }

    // Otherwise, continue recursively searching the left subtree
    return smallestHelper(currNode->left);
}
// Finds the height of the bst
int BSTree::height(const string &key) const
{
    if (!search(key)) // if the key doesn't exist in the tree
    {
        return -1; // return -1 to indicate an invalid height
    }

    Node *targetNode = nullptr; // pointer to the node containing the key

    int leftHeight = subtreeHeightHelper(root->left);
    int rightHeight = subtreeHeightHelper(root->right);
    int maxHeight = 0; // maximum height of the tree

    if (rightHeight > leftHeight)
    {
        maxHeight = rightHeight;
    }
    else
    {
        maxHeight = leftHeight;
    }

    targetNode = searchHelper(key, root);
    maxHeight = heightHelper(key, root, maxHeight); // get the height of the subtree rooted at the target node

    if (targetNode->left == nullptr && targetNode->right == nullptr) // if the target node has no children
    {
        return 0; // the height of the target node is 0
    }

    return maxHeight;
}

int BSTree::heightHelper(const string &key, Node *currNode, int heightCount) const
{
    if (currNode == nullptr)
    {
        // if we've reached a leaf node and haven't found the key, return the current height count
        return heightCount;
    }

    if (currNode->data == key)
    {
        // if we've found the node with the key, return the current height count
        return heightCount;
    }
    else if (currNode->data > key)
    {
        // if the current node's data is greater than the key, recursively search the left subtree and decrease the height count
        return heightHelper(key, currNode->left, heightCount - 1);
    }
    else
    {
        // if the current node's data is less than the key, recursively search the right subtree and decrease the height count
        return heightHelper(key, currNode->right, heightCount - 1);
    }
}

int BSTree::subtreeHeightHelper(Node *currNode) const
{
    // Base case: if current node is null, height is 0
    if (currNode == nullptr)
    {
        return 0;
    }

    // Recursively calculate height of left and right subtrees
    int leftSubtreeHeight = subtreeHeightHelper(currNode->left);
    int rightSubtreeHeight = subtreeHeightHelper(currNode->right);

    // Add 1 to the maximum height of the left and right subtrees to get the height of the current node's subtree
    if (leftSubtreeHeight > rightSubtreeHeight)
    {
        return 1 + leftSubtreeHeight;
    }
    else
    {
        return 1 + rightSubtreeHeight;
    }
}

// Preorder the bst, calls the helper function

void BSTree::preOrder() const
{
    preOrderHelper(root);
}

void BSTree::preOrderHelper(Node *currNode) const
{
    // if the current node is null, return
    if (currNode == nullptr)
    {
        return;
    }

    // print the data and count of the current node
    cout << currNode->data << "(" << currNode->count << "), ";

    // recursively traverse the left subtree
    preOrderHelper(currNode->left);

    // recursively traverse the right subtree
    preOrderHelper(currNode->right);
}

// Post order the BST and calls the helper function
void BSTree::postOrder() const
{
    postOrderHelper(root);
}

void BSTree::postOrderHelper(Node *currNode) const
{
    // If current node is null, return
    if (currNode == nullptr)
    {
        return;
    }

    // Traverse left subtree
    postOrderHelper(currNode->left);

    // Traverse right subtree
    postOrderHelper(currNode->right);

    // Print data of current node
    cout << currNode->data << "(" << currNode->count << "), ";
}

// orders the bst by calling the helper function
void BSTree::inOrder() const
{
    inOrderHelper(root);
}

void BSTree::inOrderHelper(Node *currNode) const
{
    // Check if current node is null. If so, return from the function.
    if (currNode == nullptr)
    {
        return;
    }

    // Traverse the left subtree recursively.
    inOrderHelper(currNode->left);

    // Print the current node's data and count.
    cout << currNode->data << "(" << currNode->count << "), ";

    // Traverse the right subtree recursively.
    inOrderHelper(currNode->right);
}