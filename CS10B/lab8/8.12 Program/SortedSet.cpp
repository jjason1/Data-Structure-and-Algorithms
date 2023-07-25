#include <iostream>
#include "SortedSet.h"
using namespace std;

SortedSet::SortedSet(): IntList(){};

SortedSet::SortedSet(const SortedSet & cpy) : IntList(cpy){};

SortedSet::SortedSet(const IntList &cpy) : IntList(cpy){
    IntList::remove_duplicates();
    IntList::selection_sort();
}

SortedSet:: ~SortedSet(){
    while(this->head != nullptr){
        IntList::pop_front();
    }
    head = nullptr;
    tail = nullptr;
}

bool SortedSet::in(int value){
    for(IntNode *i = head; i != nullptr; i = i->next){
        if(i->value == value){
            return true;
            break;
        }
    }

    return false;
}

SortedSet SortedSet::operator|(const SortedSet &rhs) const{
    SortedSet sum;

    for(IntNode *j = this->head; j != nullptr; j= j->next){
        sum.push_back(j->value);
    }

    for(IntNode *i = rhs.head; i != nullptr; i = i->next){
        sum.insert_ordered(i->value);
    }

    sum.selection_sort();

    return sum;
}

SortedSet SortedSet::operator&(const SortedSet &rhs) const{
    SortedSet sum;

    for(IntNode *i = this->head; i != nullptr; i = i->next){
        for(IntNode *j = rhs.head; j != nullptr; j = j->next){
            if(i->value == j->value){
                sum.push_back(i->value);
            }
        }
    }

    sum.selection_sort();

    return sum;
}

void SortedSet::add(int value){

    if (empty()){
        IntNode *temp = new IntNode(value);
        head = temp;
        tail = head;
    }
    else if (value <= head->value){
        if(value < head->value){
            IntList::push_front(value);
        }
        else{
            return;
        }
        
    }
    else if (value >= tail-> value){
        if(value > tail->value){
            IntList::push_back(value);
        }
        else{
            return;
        }
    }
    else{
        IntNode* temp = new IntNode(value);
        IntNode* prev = head;
        IntNode* curr = head->next;
        while(prev != nullptr && value >= curr->value){
            curr = curr -> next;
            prev = prev -> next;
        }

        if (prev->value != value){
            prev -> next = temp;
            temp -> next = curr;
        }

        else{
            delete temp;
        }
    }
}

void SortedSet::push_front(int value){
    add(value);
}

void SortedSet::push_back(int value){
    add(value);
}

void SortedSet::insert_ordered(int value){
    add(value);
}

SortedSet SortedSet::operator|=(SortedSet &rhs){
    *this = *this | rhs;
    return *this;
}

SortedSet SortedSet::operator&=(SortedSet &rhs){
    *this = *this & rhs;
    return *this;
}