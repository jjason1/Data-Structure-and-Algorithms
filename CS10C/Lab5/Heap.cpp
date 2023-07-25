#include <iostream>
#include "Heap.h"
using namespace std;

Heap::Heap()
{
    numItems = 0;
}

// Utilizes a for loop to go through the array and delete the items
Heap::~Heap()
{
    for (int i = 0; i < numItems; ++i)
    {
        delete arr[i];
    }
}
// Copy constructor
Heap::Heap(const Heap &copy)
{

    numItems = copy.numItems;

    for (int i = 0; i < numItems; ++i)
    {
        arr[i] = new PrintJob(*(copy.arr[i]));
    }
}
// Assignment operator
Heap &Heap::operator=(const Heap &copy)
{
    if (this != &copy)
    {
        for (int i = 0; i < numItems; ++i)
        {
            delete arr[i];
        }
    }

    numItems = copy.numItems;

    for (int i = 0; i < numItems; ++i)
    {
        arr[i] = new PrintJob(*(copy.arr[i]));
    }

    return *this;
}

void Heap::enqueue(PrintJob *newItem)
{
    // Check if there's still space in the heap
    if (numItems != MAX_HEAP_SIZE)
    {
        // Check if there's already an item in the heap
        if (numItems != 0)
        {
            // Find the correct position to insert the new item
            int currIndex = numItems;
            while (currIndex > 0 && arr[(currIndex - 1) / 2]->getPriority() < newItem->getPriority())
            {
                // Move parent down if its priority is lower than the new item's priority
                arr[currIndex] = arr[(currIndex - 1) / 2];
                currIndex = (currIndex - 1) / 2;
            }

            // Insert new item at the correct position
            arr[currIndex] = newItem;
            numItems++;
        }
        else // If there are no items in the heap, add the new item at the first position
        {
            arr[numItems] = newItem;
            numItems++;
        }
    }
}

void Heap::trickleDown(int index)
{
    // Base case: If there are no children
    if (numItems < index * 2 + 2)
    {
        return;
    }
    // Base case: If there is only one child
    else if (numItems == index * 2 + 2)
    {
        // Check if parent's priority is less than child's priority
        if (arr[index]->getPriority() < arr[numItems - 1]->getPriority())
        {
            // Swap parent and child
            PrintJob *currIndex = arr[index];
            arr[index] = arr[numItems - 1];
            arr[numItems - 1] = currIndex;
        }
    }
    else // General case: If there are two children
    {
        // Get the left and right children
        PrintJob *leftBranch = arr[index * 2 + 1];
        PrintJob *rightBranch = arr[index * 2 + 2];

        // Compare the priorities of the two children
        if (rightBranch->getPriority() > leftBranch->getPriority())
        {
            // If the right child's priority is higher, compare with parent
            if (arr[index]->getPriority() < arr[index * 2 + 2]->getPriority())
            {
                // Swap parent and right child
                PrintJob *currentIndex = arr[index];
                arr[index] = arr[index * 2 + 2];
                arr[index * 2 + 2] = currentIndex;
            }

            // Recursive call on right child
            trickleDown(index * 2 + 2);
        }
        else
        {
            // If the left child's priority is higher or equal, compare with parent
            if (arr[index]->getPriority() < arr[index * 2 + 1]->getPriority())
            {
                // Swap parent and left child
                PrintJob *currentIndex = arr[index];
                arr[index] = arr[index * 2 + 1];
                arr[index * 2 + 1] = currentIndex;
            }

            // Recursive call on left child
            trickleDown(index * 2 + 1);
        }
    }
}
void Heap::dequeue()
{
    // Check if heap is not empty
    if (numItems != 0)
    {
        // If there is more than 1 item, swap first and last item
        if (numItems != 1)
        {
            arr[0] = arr[numItems - 1];
        }

        // Decrease the number of items in the heap
        --numItems;

        // Restore the heap order starting from the root
        trickleDown(0);
    }
}

PrintJob *Heap::highest() const
{
    PrintJob *highest;

    // If heap is empty, return nullptr
    if (numItems == 0)
    {
        highest = nullptr;
    }
    else
    {
        // Otherwise, return the highest priority item which is the root of the heap
        highest = arr[0];
    }

    return highest;
}

void Heap::print() const
{
    // If heap is not empty, print the highest priority item
    if (numItems != 0)
    {
        cout << "Priority: " << highest()->getPriority()
             << ", Job Number: " << highest()->getJobNumber()
             << ", Number of Pages: " << highest()->getPages();
    }

    // Always print a new line at the end
    cout << endl;
}
