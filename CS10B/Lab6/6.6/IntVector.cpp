#include <stdexcept>
#include "IntVector.h"
using namespace std;


IntVector::IntVector(unsigned capacity, int value){

    if(capacity == 0){
        _capacity = 0;
        _size = 0;
        _data = nullptr;
    }
    else{
        _data = new int[capacity];
        _capacity = capacity;
        _size = capacity;

        for(unsigned int i = 0; i < capacity; ++i){
            _data[i] = value;
        }
    }
}

IntVector:: ~IntVector(){
    delete[] _data;
    _data = nullptr;
}

unsigned IntVector::size() const{
    return _size;
}

unsigned IntVector::capacity() const{
    return _capacity;
}

bool IntVector::empty() const{
    return (_size == 0);
}

const int & IntVector::at(unsigned index) const{
    if(index >= _size || _size == 0){
        throw out_of_range("IntVector::at_range_check");
    }
    else{
        return _data[index];
    }
}

const int & IntVector::front() const{
    return at(0);
}

const int & IntVector::back() const{
    return at(_size-1);
}