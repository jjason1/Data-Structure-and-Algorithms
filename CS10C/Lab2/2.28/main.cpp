#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node
{
    string payload; // The value held by the node
    Node *next;     // A pointer to the next node in the list
};

// A function that creates a new node
Node *newNode(string payload)
{
    // Create a new Node object and assign it to a pointer variable
    Node *currNode = new Node;
    // Set the "next" pointer of the new node to point to itself
    currNode->next = currNode;
    // Set the payload of the new node to the given payload
    currNode->payload = payload;

    // Return a pointer to the new node
    return currNode;
}

// Function that loads a game with the given number of players and names
Node *loadGame(int n, vector<string> names)
{
    Node *head = nullptr; // Creates pointer variable to hold the head of the linked list
    Node *prev = nullptr; // Create pointer variable to hold the previous node in the linked list
    string name;          // Create a string variable to hold the name of each player

    // Iterate over the names vector and create a new linked list node for each player
    for (int i = 0; i < n; ++i)
    {
        name = names.at(i);
        if (head == nullptr)
        {
            head = newNode(name); // initialize head specially
            prev = head;
        }
        else
        {
            prev->next = newNode(name); // create a new node and link it to the previous node
            prev = prev->next;
        }
    }

    // If the previous node is not null, link it to the head to make the linked list circular
    if (prev != nullptr)
    {
        prev->next = head; // make circular
    }

    return head;
}

// This function takes a pointer to the starting node of a linked list as input and prints the linked list
void print(Node *start)
{ // prints list

    // Declare a pointer to the current node and initialize it to the starting node.
    Node *currNode = start;

    // Traverse the linked list until the current node is null.
    while (currNode != nullptr)
    {
        // Output the payload of the current node.
        cout << currNode->payload << endl;
        // Set the current node to the next node in the list.
        currNode = currNode->next;
        // Exit if reached the start of the circular linked list
        if (currNode == start)
        {
            break; // exit circular list
        }
    }

    delete currNode;
}

Node *runGame(Node *start, int k)
{ // josephus w circular list, k = num skips
    // Declare pointers to the current node and the previous node, and initialize them to the starting node.
    Node *currNode = start;
    Node *prev = currNode;
    // Traverse the circular linked list until only one node remains.
    while (currNode->next != currNode)
    { // exit condition, last person standing
        for (int i = 0; i < k; ++i)
        { // find kth node
            prev = currNode;
            currNode = currNode->next;
        }

        // delete kth node
        prev->next = currNode->next;
        // Free the memory of the kth node.
        delete currNode;
        // Set the current node to the next node in the list.
        currNode = prev->next;
    }

    return currNode; // last person standing
}

/* Driver program to test above functions */
int main()
{
    int n = 1, k = 1; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    while (cin >> name && name != ".")
    {
        names.push_back(name);
    } // EOF or . ends input

    // initialize and run game
    Node *startPerson = loadGame(n, names);
    Node *lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr)
    {
        cout << lastPerson->payload << " wins!" << endl;
    }
    else
    {
        cout << "error: null game" << endl;
    }

    delete lastPerson;

    return 0;
}
