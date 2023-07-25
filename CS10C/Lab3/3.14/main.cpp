#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

// Function declarations with template
template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index);

template <typename T>
void selection_sort(vector<T> &vals);

template <typename T>
T getElement(vector<T> vals, int index);

// Creates vectors, given from zybooks
vector<char> createVector()
{
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for (int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main()
{
    // Creating a integer vector and tests all the functions using ints
    vector<int> intVector{4, 1, 6, 123, 4234, 535, 12355};
    cout << "Before calling selection sort" << endl;
    for (unsigned int i = 0; i < intVector.size(); ++i)
    {
        cout << intVector[i] << " ";
    }

    cout << endl
         << "After calling selection sort (ints):" << endl;
    selection_sort(intVector);
    for (unsigned int i = 0; i < intVector.size(); ++i)
    {
        cout << intVector[i] << " ";
    }

    cout << endl
         << "-------------------------------------------------" << endl;

    // Creates a double vector and tests all the function using doubles

    vector<double> doubleVector{1.2, 323.32, 100.11, 3990.3132};
    cout << "Before calling selection sort (doubles)" << endl;
    for (unsigned int i = 0; i < doubleVector.size(); ++i)
    {
        cout << doubleVector[i] << " ";
    }

    cout << endl
         << "After calling selection sort:" << endl;
    selection_sort(doubleVector);
    for (unsigned int i = 0; i < doubleVector.size(); ++i)
    {
        cout << doubleVector[i] << " ";
    }

    cout << endl
         << "-------------------------------------------------" << endl;

    // Creates a vector of strings and tests all the functions using strings
    vector<string> stringVector{"hi", "bye", "jason", "love", "computer", "science"};
    cout << "Before calling selection sort (string)" << endl;
    for (unsigned int i = 0; i < stringVector.size(); ++i)
    {
        cout << stringVector[i] << " ";
    }

    cout << endl
         << "After calling selection sort:" << endl;
    selection_sort(stringVector);
    for (unsigned int i = 0; i < stringVector.size(); ++i)
    {
        cout << stringVector[i] << " ";
    }

    cout << endl
         << "-------------------------------------------------" << endl;

    // Creates a vector for character values only and tests all the functions using char
    vector<char> charVector{'g', 'v', 'q', 'f', 'l'};

    cout << "Before calling selection sort (char)" << endl;
    for (unsigned int i = 0; i < charVector.size(); ++i)
    {
        cout << charVector[i] << " ";
    }

    cout << endl
         << "After calling selection sort:" << endl;
    selection_sort(charVector);
    for (unsigned int i = 0; i < charVector.size(); ++i)
    {
        cout << charVector[i] << " ";
    }

    // Part B
    try
    {
        srand(time(0));
        vector<char> vals = createVector();
        char curChar;
        int index;
        int numOfRuns = 10;
        while (--numOfRuns >= 0)
        {
            cout << "Enter a number: " << endl;
            cin >> index;
            curChar = getElement(vals, index);
            cout << "Element located at " << index << ": is " << curChar << endl;
        }
    }
    catch (out_of_range &excpt)
    {
        cout << excpt.what() << endl;
    }

    return 0;
}

template <typename T>

// Finds the smallest index in a vector passed in. Uses a for loop to traverse through the
// list and returns minIndex
unsigned min_index(const vector<T> &vals, unsigned index)
{
    unsigned smallestIndex = index;

    for (unsigned int i = index; i < vals.size(); ++i)
    {
        if (vals.at(smallestIndex) > vals.at(i))
        {
            smallestIndex = i;
        }
    }

    return smallestIndex;
}

// Sorts the vector from smallest to greatest. Utilizes a for loop and the min_index functions
// to find the smallest index, then swaps it.

template <typename T>
void selection_sort(vector<T> &vals)
{

    for (unsigned int i = 0; i < vals.size(); ++i)
    {
        unsigned smallestIndex = min_index(vals, i);
        T currentIndex = vals.at(i);

        vals.at(i) = vals.at(smallestIndex);
        vals.at(smallestIndex) = currentIndex;
    }
}

template <typename T>

// This function takes in a vector and index. Returns the element that is stored at that index.
// If the index does not exist in the vector, then it throws out of range error.
T getElement(vector<T> vals, int index)
{
    unsigned _index = index;

    if (index < 0 || _index >= vals.size())
    {
        throw out_of_range("out of range exception occured");
        cout << endl;
    }

    return vals.at(index);
}