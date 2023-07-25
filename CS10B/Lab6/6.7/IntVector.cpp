#include <stdexcept>
#include "IntVector.h"
using namespace std;

IntVector::IntVector(unsigned capacity, int value)
{

    if (capacity == 0)
    {
        _capacity = 0;
        _size = 0;
        _data = nullptr;
    }
    else
    {
        _data = new int[capacity];
        _capacity = capacity;
        _size = capacity;

        for (unsigned int i = 0; i < capacity; ++i)
        {
            _data[i] = value;
        }
    }
}

IntVector::~IntVector()
{
    delete[] _data;
    _data = nullptr;
}

unsigned IntVector::size() const
{
    return _size;
}

unsigned IntVector::capacity() const
{
    return _capacity;
}

bool IntVector::empty() const
{
    return (_size == 0);
}

const int &IntVector::at(unsigned index) const
{
    if (index >= _size || _size == 0)
    {
        throw out_of_range("IntVector::at_range_check");
    }
    else
    {
        return _data[index];
    }
}

const int &IntVector::front() const
{
    return at(0);
}

const int &IntVector::back() const
{
    return at(_size - 1);
}

void IntVector::expand()
{

    int *temp = _data;

    if (_capacity == 0)
    {
        _capacity = 1;
        _data = new int[_capacity];
    }
    else
    {
        _capacity = _capacity * 2;
        _data = new int[_capacity];
    }

    for (unsigned int i = 0; i < _size; ++i)
    {
        _data[i] = temp[i];
    }

    delete[] temp;
}

void IntVector::expand(unsigned amount)
{

    int *temp = _data;
    _capacity += amount;
    _data = new int[_capacity];

    for (unsigned int i = 0; i < _size; ++i)
    {
        _data[i] = temp[i];
    }

    delete[] temp;
}

void IntVector::insert(unsigned index, int value)
{

    if (_size >= _capacity)
    {
        expand();
        _size++;
    }
    else
    {
        _size++;
    }

    if (index >= _size || _size == 0)
    {
        throw out_of_range("IntVector::insert_range_check");
    }
 
    for (unsigned int i = _size - 1; i > index; --i)
    {
        _data[i] = _data[i - 1];
    }

    _data[index] = value;
}

void IntVector::erase(unsigned index)
{
    if (index >= _size || _size == 0)
    {
        throw out_of_range("IntVector::erase_range_check");
    }
    else
    {
        for (unsigned int i = index; i < _size - 1; ++i)
        {
            _data[i] = _data[i + 1];
        }

        _size--;
    }
}

void IntVector::push_back(int value)
{

    if (_size >= _capacity)
    {
        expand();
        _size++;
    }
    else
    {
        _size++;
    }

    _data[_size - 1] = value;
}

void IntVector::pop_back()
{
    _size--;
}

void IntVector::clear()
{
    _size = 0;
}

void IntVector::resize(unsigned size, int value)
{
    if (size > _capacity)
    {
        expand();
        if (size > _capacity)
        {
            expand(size - _capacity);
        }
    }

    if (_size > size)
    {
        _size = size;
    }
    else
    {
        for (unsigned int i = _size; i < size; i++)
        {
            _data[i] = value;
        }

        _size = size;
    }
}

void IntVector::reserve(unsigned n)
{
    if (n > _capacity)
    {
        expand(n - _capacity);
    }
}

void IntVector::assign(unsigned n, int value)
{
    if (n > _capacity)
    {
        expand();
    }

    if (n > _capacity)
    {
        expand(n - _capacity);
    }

    _size = n;

    for (unsigned int i = 0; i < _size; ++i)
    {
        _data[i] = value;
    }
}

int &IntVector::at(unsigned index)
{
    if (index >= _size || _size == 0)
    {
        throw out_of_range("IntVector::at_range_check");
    }
    else
    {
        return _data[index];
    }
}

int &IntVector::front()
{
    return _data[0];
}

int &IntVector::back()
{
    return _data[_size - 1];
}
