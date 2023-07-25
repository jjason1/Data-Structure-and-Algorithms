#include <iostream>
#include <string>
using namespace std;

class IntVector{
    private:
        unsigned _size;
        unsigned _capacity;
        int *_data;

    public:
        IntVector(unsigned capacity = 0, int value = 0);
        ~IntVector();

        unsigned size() const; /*Accessor*/
        unsigned capacity() const; /*Accessor*/
        bool empty() const; /*Accessor*/
        const int & at(unsigned) const; /*Accessor*/
        const int & front() const; /*Accessor*/
        const int & back() const; /*Accessor*/
};

