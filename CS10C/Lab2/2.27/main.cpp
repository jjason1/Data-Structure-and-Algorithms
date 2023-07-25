#include <iostream>
#include "IntList.h"
using namespace std;

int main()
{

    //Testing copy constructor
    cout << "Testing the copy constructor" << endl; 

    IntList list1;
    list1.push_back(4);
    list1.push_back(9);
    list1.push_back(3);

    IntList list2(list1);
    cout << "List 1: " << list1 << endl;
    cout << "List 2: " << list2 << endl;

    cout << "-------------------------------" << endl;

    //Testing assignment operator
    cout << "Testing assignment operator" << endl;

    IntList list3;
    list3.push_back(1);
    list3.push_back(2);
    list3.push_back(3);
    
    cout << "Before the assignment operator" << endl;
    cout << "List 3: " << list3 << endl;

    cout << "After the assignment operator" << endl;
    list3 = list1;

    cout << "List 1: " << list1 << endl;
    cout << "List 3: " << list3 << endl;

    cout << "-------------------------------" << endl;
    // Makes a new list that has default values
    cout << "Making a new list" << endl;
    IntList *list = new IntList();

    cout << "-------------------------------" << endl;

    // Testing the push front operator, expecting 4,3,2,1
    cout << "push front operator(1,2,3,4)" << endl;
    list->push_front(1);
    list->push_front(2);
    list->push_front(3);
    list->push_front(4);
    cout << *list << endl;

    cout << "-------------------------------" << endl;
    // Testing the push back operator, expecting 4,3,2,1,0,-1,-2,-3,-4
    cout << "Testing push_back operator(0, -1, -2, -3, -4)" << endl;
    list->push_back(0);
    list->push_back(-1);
    list->push_back(-2);
    list->push_back(-3);
    list->push_back(-4);
    cout << *list << endl;

    cout << "-------------------------------" << endl;
    // Testing the print in reverse, expecting -4,-3,-2,-1,0,1,2,3,4
    cout << "Testing print in reverse" << endl;
    list->printReverse();
    cout << endl;

    cout << "-------------------------------" << endl;
    

    // Testing the pop front function
    cout << "Testing pop front function(4,3,2,1)" << endl;
    list->pop_front();
    list->pop_front();
    list->pop_front();
    list->pop_front();
    cout << *list << endl;

    cout << "-------------------------------" << endl;

    cout << "Testing pop back function(-4,-3,-2,-1)" << endl;
    list->pop_back();
    list->pop_back();
    list->pop_back();
    list->pop_back();
    cout << *list << endl;

    cout << "-------------------------------" << endl;

    cout << "Testing empty function" << endl;
    if (list->empty())
    {
        cout << "The list is empty" << endl;
    }
    else
    {
        cout << "The list is not empty" << endl;
    }

    cout << "-------------------------------" << endl;

    cout << "Testing desctructor" << endl;
    delete list;

    return 0;
}