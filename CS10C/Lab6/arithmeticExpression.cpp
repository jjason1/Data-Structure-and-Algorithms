#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include "arithmeticExpression.h"
using namespace std;

arithmeticExpression::arithmeticExpression(const string &data) : infixExpression(data), root(nullptr)
{
    // cout << "Try to build from: " << infixExpression << endl;

    // cout << "In postfix this is: " << infix_to_postfix() << endl;

    // throw std::runtime_error("Create constructor");
}

arithmeticExpression::~arithmeticExpression()
{
    // Call a helper function to deallocate the nodes recursively, starting from the root
    deleteTree(root);
}

void arithmeticExpression::deleteTree(TreeNode *currNode)
{
    if (currNode) // Check if the current node exists
    {
        deleteTree(currNode->left); // Recursively delete the left subtree

        deleteTree(currNode->right); // Recursively delete the right subtree

        delete currNode; // Delete the current node itself
    }
}

arithmeticExpression::arithmeticExpression(const arithmeticExpression &copy)
{
    infixExpression = copy.infixExpression; // Copy the infix expression from the source object

    if (copy.root) // Check if the source object has a root node
    {
        root = copyTree(copy.root); // Perform a deep copy of the tree starting from the source object's root
    }
    else
    {
        root = nullptr; // If the source object has no root node, set the root of the current object to nullptr
    }
}

TreeNode *arithmeticExpression::copyTree(const TreeNode *currNode)
{
    if (!currNode) // Check if the current node is null
    {
        return nullptr; // If so, return nullptr indicating an empty subtree
    }

    TreeNode *newNode = new TreeNode(currNode->data, currNode->key); // Create a new node with the same data and key as the current node

    newNode->left = copyTree(currNode->left);   // Recursively copy the left subtree
    newNode->right = copyTree(currNode->right); // Recursively copy the right subtree

    return newNode; // Return the new node
}

arithmeticExpression &arithmeticExpression::operator=(const arithmeticExpression &copy)
{
    if (this != &copy) // Check for self-assignment
    {
        infixExpression = copy.infixExpression; // Copy the infix expression from the source object

        TreeNode *newRoot = nullptr;

        if (copy.root) // Check if the source object has a root node
        {
            newRoot = copyTree(copy.root); // Perform a deep copy of the tree starting from the source object's root
        }

        deleteTree(root); // Delete the existing tree in the current object

        root = newRoot; // Assign the new root to the current object
    }

    return *this; // Return a reference to the current object
}

void arithmeticExpression::buildTree()
{
    string postFix = infix_to_postfix(); // Convert infix expression to postfix notation
    char key = 'a';                      // Start assigning keys from 'a'

    root = buildTreeHelper(postFix, key); // Call the buildTreeHelper function to construct the tree
}

TreeNode *arithmeticExpression::buildTreeHelper(string &eq, char &key)
{
    if (!eq.empty()) // Check if the expression is not empty
    {
        char data = eq.back(); // Get the last character of the expression
        eq.pop_back();         // Remove the last character from the expression

        TreeNode *newNode = new TreeNode(data, static_cast<char>(key)); // Create a new node with the character and the current key value
        key++;                                                          // Increment the key value for the next node

        if (priority(newNode->data) > 0)
        {
            newNode->right = buildTreeHelper(eq, key);
            newNode->left = buildTreeHelper(eq, key);
        }

        return newNode; // Return the newly created node
    }

    return nullptr; // Return nullptr when the expression is empty
}

void arithmeticExpression::infix()
{
    infix(root);
}

void arithmeticExpression::infix(TreeNode *currNode)
{
    if (currNode != nullptr) // Check if the current node exists
    {
        if (currNode->left != nullptr) // Check if the current node has a left child
        {
            cout << '('; // Print opening parenthesis if there is a left child
        }

        infix(currNode->left);  // Recursively traverse the left subtree
        cout << currNode->data; // Print the data of the current node
        infix(currNode->right); // Recursively traverse the right subtree

        if (currNode->left != nullptr) // Check if the current node has a left child
        {
            cout << ')'; // Print closing parenthesis if there was a left child
        }
    }
}

void arithmeticExpression::prefix()
{
    prefix(root); // Call the overloaded prefix function with the root node
}

void arithmeticExpression::prefix(TreeNode *node)
{
    if (node != nullptr) // Check if the current node exists
    {
        cout << node->data;  // Print the data of the current node
        prefix(node->left);  // Recursively traverse the left subtree
        prefix(node->right); // Recursively traverse the right subtree
    }
}

void arithmeticExpression::postfix()
{
    postfix(root); // Call the overloaded postfix function with the root node
}

void arithmeticExpression::postfix(TreeNode *node)
{
    if (node != nullptr) // Check if the current node exists
    {
        postfix(node->left);  // Recursively traverse the left subtree
        postfix(node->right); // Recursively traverse the right subtree
        cout << node->data;   // Print the data of the current node
    }
}

int arithmeticExpression::priority(char op)
{
    int priority = 0;
    if (op == '(')
    {
        priority = 3; // Assign a priority value of 3 for '('
    }
    else if (op == '*' || op == '/')
    {
        priority = 2; // Assign a priority value of 2 for '*' and '/'
    }
    else if (op == '+' || op == '-')
    {
        priority = 1; // Assign a priority value of 1 for '+' and '-'
    }
    return priority; // Return the priority value
}

string arithmeticExpression::infix_to_postfix()
{
    stack<char> s;
    ostringstream oss;
    char c;

    for (unsigned i = 0; i < infixExpression.size(); ++i)
    {
        c = infixExpression.at(i);

        if (c == ' ')
        {
            continue; // Skip spaces
        }

        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
        { // c is an operator
            if (c == '(')
            {
                s.push(c); // Push '(' onto the stack
            }
            else if (c == ')')
            {
                while (s.top() != '(')
                {
                    oss << s.top(); // Append top of stack to output
                    s.pop();        // Pop from stack
                }
                s.pop(); // Pop '(' from stack
            }
            else
            {
                while (!s.empty() && priority(c) <= priority(s.top()))
                {
                    if (s.top() == '(')
                    {
                        break;
                    }
                    oss << s.top(); // Append top of stack to output
                    s.pop();        // Pop from stack
                }
                s.push(c); // Push current operator onto the stack
            }
        }
        else
        {             // c is an operand
            oss << c; // Append operand to output
        }
    }

    while (!s.empty())
    {
        oss << s.top(); // Append top of stack to output
        s.pop();        // Pop from stack
    }

    return oss.str(); // Convert output stringstream to string and return
}

// void arithmeticExpression::visualizeTree(const string &outputFilename)
// {
//     ofstream outFS(outputFilename.c_str());
//     if (!outFS.is_open())
//     {
//         cout << "Error opening " << outputFilename << endl;
//         return;
//     }
//     outFS << "digraph G {" << endl;
//     visualizeTree(outFS, root);
//     outFS << "}";
//     outFS.close();
//     string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
//     string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
//     system(command.c_str());
// }
