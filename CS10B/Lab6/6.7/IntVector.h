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

        int & at(unsigned int); /*Mutator*/
        void insert(unsigned, int); /*Mutator*/
        void erase(unsigned); /*Mutator*/
        int & front(); /*Mutator*/
        int & back();/*Mutator*/

        void assign(unsigned, int);/*Mutator*/
        void push_back(int);/*Mutator*/
        void pop_back();/*Mutator*/
        void clear();/*Mutator*/
        void resize(unsigned, int value = 0);/*Mutator*/
        // void resize(int);
        void reserve(unsigned);/*Mutator*/

    private:
        void expand();
        void expand(unsigned);
};

