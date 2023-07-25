#pragma once

#include <iostream>
#include <stdexcept>
using namespace std;

const int MAX_SIZE = 20;

template <typename T>

class stack
{
private:
    T data[MAX_SIZE]; // The maxiumum capacity of the array is 20
    int size;         // The size of the array

public:
    stack() // Creates an empty stack
    {
        size = 0;
    }

    // Deconstructor
    // Simply sets the size to 0
    ~stack()
    {
        size = 0;
    }

    // Copy constructor
    // Utilizes a for loop to copy the data into the array

    stack(const stack<T> &copy)
    {
        size = copy.size;

        for (int i = 0; i < size; i++)
        {
            data[i] = copy.data[i];
        }
    }

    // Assignment operator
    // Uses for loop to make copy the data

    stack<T> &operator=(const stack<T> &copy)
    {
        if (this != &copy) // checks for self-assignment
        {
            size = copy.size;

            for (int i = 0; i < size; i++)
            {
                data[i] = copy.data[i];
            }
        }
        return *this;
    }

    void push(const T &val) // Adds a value to the end of the stack
    {
        if (size == MAX_SIZE)
        {
            throw overflow_error("Called push on full stack.");
        }
        else
        {
            data[size] = val;
            size++;
        }
    }

    void pop() // Deletes the last value in the array
    {
        if (size == 0) // Makes sure the array is not empty first
        {
            throw overflow_error("Called pop on empty stack.");
        }
        else
        {
            size--;
        }
    }

    void pop_two() // Deletes the last two elements in the array
    {
        if (size == 1 || size == 0)
        {
            throw overflow_error("Called pop_two on a stack of size 1.");
        }
        else
        {
            size -= 2;
        }
    }

    T top() const // Returns the last element in the array
    {
        if (size == 0)
        {
            throw overflow_error("Called top on empty stack.");
        }
        else
        {
            return data[size - 1];
        }
    }

    bool empty() const // Checks to see if the stack is empty or not
    {
        if (size == 0)
        {
            return true;
        }

        return false;
    }
};