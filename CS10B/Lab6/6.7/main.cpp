#include <iostream>
#include "IntVector.h"
using namespace std;

void display(const IntVector&);

int main()
{

    IntVector vector(10);

    display(vector);

    // vector.insert(3, 5);
    // // vector.insert(11, 5);
    // display(vector);

    // vector.erase(3);
    // // vector.erase(13);
    // display(vector);

    // vector.push_back(6);
    // display(vector);

    // vector.pop_back();
    // display(vector);

    // vector.resize(5, 3);
    // display(vector);

    // vector.reserve(6);
    // display(vector);

    // vector.assign(2, 3);
    // display(vector);

    // vector.push_back(3);
    // display(vector);

    vector.resize(15,4);
    display(vector);




    return 0;
}

void display(const IntVector& vector){

    for(unsigned int i = 0; i < vector.size(); ++i){
        cout << vector.at(i) << " ";
    }
    cout << endl;
}
