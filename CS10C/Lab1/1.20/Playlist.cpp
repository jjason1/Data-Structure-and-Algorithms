#include <iostream>
#include <string>
#include "Playlist.h"
using namespace std;

/*This is the constructor for the PlaylistNode class and intializes each of private variables to default values such as none or 0 or nullptr*/
PlaylistNode::PlaylistNode()
    : uniqueId("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr) {}

/*This is the constructor for the PlaylistNode class that allows the user to create their PlaylistNode through the parameters.
It sets the private variables with the parameters the user inputs.*/
PlaylistNode::PlaylistNode(const string &_uniqueID, const string &_songName, const string &_artistName, int _songLength)
    : uniqueId(_uniqueID), songName(_songName), artistName(_artistName), songLength(_songLength) {}

void PlaylistNode::InsertAfter(PlaylistNode *node) // Function to insert a node after the current n
{
    PlaylistNode *nextNode = nextNodePtr; // Store the pointer to the next node in a temporary variable
    nextNodePtr = node;               // Set the pointer to the next node to the new node being inserted
    node->SetNext(nextNode);              // Set the pointer of the new node to the previous next node
}

void PlaylistNode::SetNext(PlaylistNode *node) // Function to set the next node pointer
{
    nextNodePtr = node; // Set the pointer to the next node to the given node pointer
}

const string &PlaylistNode::GetID() const // Function to get the unique ID of the node. Does not change any data
{
    return uniqueId; // Return a constant reference to the unique ID member variable
}

const string &PlaylistNode::GetSongName() const // Function to get the song name of the node
{
    return songName; // Return a constant reference to the song name member variable
}

const string &PlaylistNode::GetArtistName() const // Function to get the artist name of the node
{
    return artistName; // Return a constant reference to the artist name member variable
}

int PlaylistNode::GetSongLength() const // Function to get the song length of the node
{
    return songLength; // Return the song length member variable
}

PlaylistNode *PlaylistNode::GetNext() const // Function to get the pointer to the next node in the list
{
    return nextNodePtr; // Return the pointer to the next node member variable
}

void PlaylistNode::PrintPlaylistNode() const // Function to print the details of a playlist node
{
    cout << "Unique ID: " << uniqueId << endl;                  // Print the unique ID of the node
    cout << "Song Name: " << songName << endl;                  // Print the name of the song in the node
    cout << "Artist Name: " << artistName << endl;              // Print the name of the artist of the song
    cout << "Song Length (in seconds): " << songLength << endl; // Print the length of the song in seconds
}

Playlist::Playlist() : head(nullptr), tail(nullptr) {} // Constructor for the playlist class and sets head and taill pointers to nullptr

Playlist::~Playlist(){
    PlaylistNode *currentNode = head;

    while(currentNode != nullptr){
        PlaylistNode *prevNode = currentNode;
        currentNode = currentNode->GetNext();
        delete prevNode;
    }

    head = tail = nullptr;
}

Playlist::Playlist(const Playlist& copy)
{
    // Initialize head and tail to null pointers
    head = nullptr;
    tail = nullptr;

    // Traverse the other list and copy each node
    PlaylistNode* currNode = copy.head;
    while (currNode != nullptr) {
        PlaylistNode* newNode = new PlaylistNode(*currNode);
        addSong(newNode);
        currNode = currNode->GetNext();
    }
}

Playlist& Playlist::operator=(const Playlist& copy) {
    if (this == &copy) {
        return *this; // self-assignment guard
    }
    
    // Delete existing list
    while (head != nullptr) {
        PlaylistNode* temp = head;
        head = head->GetNext();
        delete temp;
    }
    tail = nullptr;

    // Copy nodes from other list
    PlaylistNode* currNode = copy.head;
    while (currNode != nullptr) {
        PlaylistNode* newNode = new PlaylistNode(*currNode);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->InsertAfter(newNode);
            tail = newNode;
        }
        currNode = currNode->GetNext();
    }

    return *this;
}

void Playlist::print(string playlistTitle) const
{
    /*If the playlist is empty then prints out that the playlist is empty*/
    if (head == nullptr)
    {
        cout << "Playlist is empty" << endl;
        cout << endl;
    }
    else
    {
        int num = 1; // counter to display the number of each song in the playlist

        /* Loop through each node in the playlist and print its information */
        for (PlaylistNode *i = head; i != nullptr; i = i->GetNext())
        {
            cout << num << "." << endl; // display the number of the song in the playlist
            i->PrintPlaylistNode();     // print the information of the current node
            cout << endl;               // add a blank line for readability
            num++;                      // increment the song counter
        }
    }
}

void Playlist::addSong(PlaylistNode *node) // Add a new song to the end of the playlist
{
    if (head == nullptr) // If the playlist is empty, set both head and tail to the new song
    {
        head = tail = node;
    }
    else // Otherwise, set the next pointer of the tail to the new song, and update the tail to the new song
    {
        tail->SetNext(node);
        tail = node;
    }
}

PlaylistNode *Playlist::removeSong(const string &target) // Removes a song from the playlist
{

    PlaylistNode *curr = head;    // Start with the head node
    PlaylistNode *prev = nullptr; // Keep track of the previous node to curr

    while (curr->GetID() != target) // Iterate until target node is found and sets prev to curr and curr to the target node
    {
        prev = curr;
        curr = curr->GetNext();
    }

    cout << "\"" << curr->GetSongName() << "\"" // Print out confirmation message
         << " removed." << endl;

    if (curr == head) // If target node is the head node then set the next node as the new head
    {
        head = curr->GetNext();
        delete curr;
    }
    else if (curr == nullptr) /*If the current position is the last element in the list, then sets tail point to the previous node by setting the previous node with the node after the target node*/
    {
        tail = prev;
        delete curr;
    }
    else // If the target node is not in head or tail, then it skips over the target node by
    {
        prev->SetNext(curr->GetNext());
        delete curr;
    }
    

    return nullptr;
}

void Playlist::changePos(int currPosition, int newPosition)
{

    int currIndex = 1;
    PlaylistNode *currPositionPtr = head;
    PlaylistNode *prevPositionPtr = nullptr;

    /*Find the position of song that wants to be moved to another position*/
    while (currIndex != currPosition)
    {
        prevPositionPtr = currPositionPtr;
        currPositionPtr = currPositionPtr->GetNext();
        currIndex++;
    }
    // Remove the node at current position
    if (prevPositionPtr != nullptr)
    {
        prevPositionPtr->SetNext(currPositionPtr->GetNext());
    }
    else if (currPositionPtr == tail)
    {
        tail = prevPositionPtr;
    }
    else
    {
        head = currPositionPtr->GetNext();
    }
    // Place the removed node at the new position
    if (newPosition <= 1)
    {
        currPositionPtr->SetNext(head);
        head = currPositionPtr;
        cout << "\"" << currPositionPtr->GetSongName() << "\""
             << " moved to position 1" << endl;
    }
    else
    {
        int newPosIndex = 2;
        PlaylistNode *prev = head;
        PlaylistNode *curr = head->GetNext();

        /*Finds the index of the new location and puts a pointer there*/
        while (newPosIndex != newPosition)
        {
            prev = curr;
            curr = curr->GetNext();
            newPosIndex++;
        }
        // Insert the node at the new position
        prev->InsertAfter(currPositionPtr);

        if (curr != nullptr) // if the index of the new location's node is at the tail then sets tail to the current postion
        {
            tail = currPositionPtr;
        }
        cout << "\"" << currPositionPtr->GetSongName() << "\""
             << " moved to position " << newPosIndex << endl;
    }

}

void Playlist::printByArtist(const string &artistName) const // This method prints all the songs in the playlist that are from a given artist.
{

    int counter = 0;

    for (PlaylistNode *curr = head; curr != nullptr; curr = curr->GetNext())
    {
        counter++;

        if (curr->GetArtistName() == artistName)
        {
            cout << counter << "." << endl;
            curr->PrintPlaylistNode();
            cout << endl;
        }
    }
}

int Playlist::totalTime() const // Calculate the total time of the entire playlist by adding up all the song lengths
{
    int sum = 0;

    for (PlaylistNode *i = head; i != nullptr; i = i->GetNext())
    {
        sum += i->GetSongLength();
    }

    return sum;
}
