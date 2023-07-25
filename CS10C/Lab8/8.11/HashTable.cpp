#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
 *  input s is the size of the array
 *  set s to be size
 *  initialize array of lists of WordEntry
 */
HashTable::HashTable(int s) : size(s)
{
    // Allocate memory for an array of lists of WordEntry objects
    hashTable = new list<WordEntry>[size]; // Creating an array of lists for the hash table
}

HashTable::~HashTable()
{
    // Deallocate the memory used by the hashTable array
    delete[] hashTable; // Deleting the dynamically allocated array
}

HashTable::HashTable(const HashTable &copy)
{
    // Copy the size from the original hash table
    size = copy.size;

    // Allocate memory for a new hash table array
    hashTable = new list<WordEntry>[size];

    // Copy each element from the original hash table to the new hash table
    for (int i = 0; i < size; ++i)
    {
        hashTable[i] = copy.hashTable[i];
    }
}

HashTable &HashTable::operator=(const HashTable &copy)
{
    // Check for self-assignment
    if (this == &copy)
    {
        return *this; // Return the current object if it's the same as the assigned object
    }

    // Deallocate existing memory
    delete[] hashTable;

    // Copy the size from the assigned object
    size = copy.size;

    // Allocate memory for a new hash table array
    hashTable = new list<WordEntry>[size];

    // Copy each element from the assigned object's hash table to the new hash table
    for (int i = 0; i < size; ++i)
    {
        hashTable[i] = copy.hashTable[i];
    }

    return *this; // Return the updated object
}

/* computeHash
 *  return an integer based on the input string
 *  used for index into the array in hash table
 *  be sure to use the size of the array to
 *  ensure array index doesn't go out of bounds
 */
int HashTable::computeHash(const string &s)
{
    // Compute the hash value based on the size of the string and the size of the hash table
    return s.size() % size; // Modulo operation to ensure the hash value is within the range of the hash table size
}

/* put
 *  input: string word and int score to be inserted
 *  First, look to see if word already exists in hash table
 *   if so, addNewAppearence with the score to the WordEntry
 *   if not, create a new Entry and push it on the list at the
 *   appropriate array index
 */
void HashTable::put(const string &s, int score)
{
    // Check if the word is already in the hash table
    if (contains(s))
    {
        // Find the word in the hash table
        for (list<WordEntry>::iterator i = hashTable[computeHash(s)].begin(); i != hashTable[computeHash(s)].end(); ++i)
        {
            if (i->getWord() == s)
            {
                // Add a new appearance with the given score to the existing word entry
                i->addNewAppearance(score);
            }
        }
    }
    else // If the word is not in the hash table
    {
        // Create a new WordEntry object with the given word and score
        WordEntry newEntry(s, score);

        // Add the new WordEntry object to the end of the linked list at the computed hash index
        hashTable[computeHash(s)].push_back(newEntry);
    }
}

/* getAverage
 *  input: string word
 *  output: the result of a call to getAverage()
 *          from the WordEntry
 *  Must first find the WordEntry in the hash table
 *  then return the average
 *  If not found, return the value 2.0 (neutral result)
 */

double HashTable::getAverage(const string &s)
{
    // Check if the word is in the hash table
    if (contains(s))
    {
        // Find the word in the hash table
        for (list<WordEntry>::iterator i = hashTable[computeHash(s)].begin(); i != hashTable[computeHash(s)].end(); ++i)
        {
            if (i->getWord() == s)
            {
                // Return the average score for the found word entry
                return i->getAverage();
            }
        }
    }

    // If the word is not found, return a default value of 2.0
    return 2.0;
}

/* contains
 * input: string word
 * output: true if word is in the hash table
 *         false if word is not in the hash table
 */
bool HashTable::contains(const string &s)
{
    for (list<WordEntry>::iterator i = hashTable[computeHash(s)].begin(); i != hashTable[computeHash(s)].end(); ++i)
    {
        if (i->getWord() == s)
        {
            return true; // The word is found in the hash table
        }
    }

    return false; // The word is not found in the hash table
}

// Main program for testing the HashTable class
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main()
{
    // declare a few needed variables for inputing the data
    string line;
    int score;
    string message = " ";

    // open input file
    ifstream myfile("movieReviews.txt");
    if (myfile.fail())
    {
        cout << "could not open file" << endl;
        exit(1);
    }

    // create hash table
    HashTable table(20071);

    while (!myfile.eof())
    {
        myfile >> score; // get score
        myfile.get();    // get blank space
        getline(myfile, line);
        int len = line.size();
        while (len > 0)
        { // identify all individual strings
            string sub;
            len = line.find(" ");
            if (len > 0)
            {
                sub = line.substr(0, len);
                line = line.substr(len + 1, line.size());
            }
            else
            {
                sub = line.substr(0, line.size() - 1);
            }
            table.put(sub, score); // insert string with the score
        }
    }

    // after data is entered in hash function
    // prompt user for a new movie review
    while (message.length() > 0)
    {
        cout << "enter a review -- Press return to exit: " << endl;
        getline(cin, message);

        // used for calculating the average
        double sum = 0;
        int count = 0;

        double sentiment = 0.0;

        size_t len = message.size();
        // get each individual word from the input
        while (len != string::npos)
        {
            string sub;
            len = message.find(" ");
            if (len != string::npos)
            {
                sub = message.substr(0, len);
                message = message.substr(len + 1, message.size());
            }
            else
            {
                sub = message;
            }
            // calculate the score of each word
            sum += table.getAverage(sub);
            ++count;
        }

        if (message.size() > 0)
        {
            sentiment = sum / count;
            cout << "The review has an average value of " << sentiment << endl;
            if (sentiment >= 3.0)
            {
                cout << "Positive Sentiment" << endl;
            }
            else if (sentiment >= 2.0)
            {
                cout << "Somewhat Positive Sentiment" << endl;
            }
            else if (sentiment >= 1.0)
            {
                cout << "Somewhat Negative Sentiment" << endl;
            }
            else
            {
                cout << "Negative Sentiment" << endl;
            }
            cout << endl;
        }
    }

    return 0;
}