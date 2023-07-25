#include <iostream>
#include "IntVector.h"
using namespace std;

int main()
{
    IntVector vector;
    IntVector(10);
    IntVector(10,10);

    /*Testing*/

    cout << "Testing size() function. Expected to return 10" << endl;
    cout << "Result of size(): " << vector.size() << endl;
    cout << "----------------------------------------------" << endl;

    cout << "Testing capacity() function. Expected to return 10" << endl;
    cout << "Result of capacity(): " << vector.capacity() << endl;
    cout << "----------------------------------------------" << endl;

    cout << "Testing empty() function. Expected to return false (0)" << endl;
    cout << "Result of empty(): " << vector.empty() << endl;
    cout << "----------------------------------------------" << endl;

    cout << "Testing at() function. Expected to return 10" << endl;
    cout << "Result of at(): " << vector.at(4) << endl;
    cout << "----------------------------------------------" << endl;

    cout << "Testing front() function. Expected to return 10" << endl;
    cout << "Result of front(): " << vector.front() << endl;
    cout << "----------------------------------------------" << endl;
    
    cout << "Testing back() function. Expected to return 10" << endl;
    cout << "Result of back(): " << vector.back() << endl;
    cout << "----------------------------------------------" << endl;

    cout << "Testing at() function. Expected to return index of out bound error" << endl;
    cout << "Result of at(): " << vector.at(10) << endl;
    cout << "----------------------------------------------" << endl;

    



    

    


    return 0;
}
