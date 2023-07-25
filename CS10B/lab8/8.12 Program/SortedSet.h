#ifndef SORTEDSET_H
#define SORTEDSET_H

#include <iostream>
#include "IntList.h"
using namespace std;

class SortedSet : public IntList{

    public:

    SortedSet();
    SortedSet(const SortedSet &);
    SortedSet(const IntList &);
    ~SortedSet();

    bool in(int);
    SortedSet operator|(const SortedSet &rhs) const;
    SortedSet operator&(const SortedSet &rhs) const;

    void add(int);
    void push_front(int);
    void push_back(int);
    void insert_ordered(int);
    SortedSet operator|=(SortedSet& rhs);
    SortedSet operator&=(SortedSet &rhs);

};

#endif