#include <iostream>
#include "IntList.h"
using namespace std;

// Creates an Intlist with all default values and makes a circular list by setting dummyHead and dummyTail to each other

IntList::IntList() : dummyHead(new IntNode(0)), dummyTail(new IntNode(0))
{
    dummyHead->next = dummyTail;
    dummyHead->prev = dummyTail;
    dummyTail->next = dummyHead;
    dummyTail->prev = dummyHead;
}

// This destroys all the instances of IntList
// Uses a while loop to traverse through the IntList and delete
IntList::~IntList()
{
    IntNode *currNode = dummyHead->next;

    while (currNode != dummyTail)
    {
        IntNode *nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}

// Copy constructor
IntList::IntList(const IntList &copy)
{
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    dummyHead->next = dummyTail;
    dummyHead->prev = dummyTail;
    dummyTail->next = dummyHead;
    dummyTail->prev = dummyHead;

    //Uses a for loop to copy the data into list

    for (IntNode *currentNode = copy.dummyHead->next; currentNode != copy.dummyTail; currentNode = currentNode->next)
    {
        push_back(currentNode->data);
    }
}

// Assignment operator
IntList &IntList::operator=(const IntList &copy)
{
    // If the two are the same
    if (this == &copy)
    {
        return *this;
    }

    // Deletes the current list
    while (!empty())
    {
        pop_front();
    }

    // Copy each node from the other list into the 'this' list
    for (IntNode *currentNode = copy.dummyHead->next; currentNode != copy.dummyTail; currentNode = currentNode->next)
    {
        push_back(currentNode->data);
    }

    return *this;
}

// Checks if the Intlist is empty and returns true or false
bool IntList::empty() const
{
    return dummyHead->next == dummyTail;
}

// Adds value to the Front of the Intlist
void IntList::push_front(const int &value)
{ // Creates a new node with the value
    IntNode *newNode = new IntNode(value);
    // Creates a node to store the head value
    IntNode *nextNode = dummyHead->next;

    dummyHead->next = newNode;
    newNode->next = nextNode;
    nextNode->prev = newNode;
    newNode->prev = dummyHead;
}

// This removes the value at the front of the list
void IntList::pop_front()
{
    IntNode *currNode = dummyHead->next;
    IntNode *nextNode = currNode->next;
    delete currNode;

    dummyHead->next = nextNode;
    nextNode->prev = dummyHead;
}

// This adds value to the back of the list.
void IntList::push_back(const int &value)
{
    IntNode *newNode = new IntNode(value);
    IntNode *prevNode = dummyTail->prev;

    prevNode->next = newNode;
    newNode->next = dummyTail;
    dummyTail->prev = newNode;
    newNode->prev = prevNode;
}

// This removes values from the back of the list using dummyTail
void IntList::pop_back()
{
    IntNode *currNode = dummyTail->prev;
    IntNode *prevNode = currNode->prev;

    delete currNode;
    prevNode->next = dummyTail;
    dummyTail->prev = prevNode;
}

// Overloads the output operator so it can cout Intlist values
ostream &operator<<(ostream &out, const IntList &rhs)
{

    IntNode *currNode = rhs.dummyHead->next;

    if (!rhs.empty())
    {
        while (currNode->next != rhs.dummyTail)
        {
            out << currNode->data << " ";
            currNode = currNode->next;
        }

        out << currNode->data;
    }

    return out;
}

// Uses a while loop that starts from the dummyTail and prints the IntList in reverse
void IntList::printReverse() const
{
    IntNode *currNode = dummyTail->prev;

    while (currNode != dummyHead)
    {
        cout << currNode->data << " ";
        currNode = currNode->prev;
    }
}
