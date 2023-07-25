#include <iostream>
#include "IntList.h"
using namespace std;

IntList::IntList() : head(nullptr), tail(nullptr){}

IntList::~IntList()
{
    while (this->head != nullptr)
    {
        pop_front();
    }
}

void IntList::push_front(int value)
{
    IntNode *temp = new IntNode(value);
    temp->next = this->head;
    this->head = temp;

    if (tail == nullptr)
    {
        tail = head;
    }
}

void IntList::pop_front()
{

    if (head == nullptr)
    {
        return;
    }
    else if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        IntNode *temp = head->next;
        delete head;
        head = temp;
    }
}

bool IntList::empty() const
{
    return (head == nullptr);
}

const int &IntList::front() const
{
    return head->value;
}

const int &IntList::back() const
{
    return tail->value;
}

ostream &operator<<(ostream &out, const IntList &list)
{
    IntNode *cur = list.head;

    if(cur){
        out << cur->value;
        cur = cur->next;
    }
    while(cur){
        out << " " << cur->value;
        cur = cur->next;
    }

    return out;
}

IntList::IntList(const IntList &cpy) : head(nullptr), tail(nullptr){
    if(!cpy.empty()){
        IntNode *temp = cpy.head;
        while(temp != nullptr){
            push_back(temp->value);
            temp = temp->next;
        }
    }
}

IntList & IntList::operator=(const IntList &rhs){
    if(rhs.empty()){
        head = nullptr;
        tail = nullptr;
    }
    else if(this == &rhs){
        return *this;
    }
    else{
        clear();
        if(!rhs.empty()){
            for(IntNode *temp = rhs.head; temp != nullptr; temp = temp->next){
                push_back(temp->value);
            }
        }
    }

    return *this;
}


void IntList::push_back(int value){
    if (head == nullptr){
        IntNode *temp = new IntNode(value);
        head = temp;
        tail = head;
    }

    else{
        IntNode *temp = new IntNode(value);
        tail -> next = temp;
        tail = temp;
    }
}

void IntList::clear(){
    while(head != nullptr){
        pop_front();
    }

    head = nullptr;
    tail = nullptr;

}

void IntList::selection_sort(){
    for(IntNode *i = head; i != nullptr; i = i->next){
        IntNode *min = i;
        for(IntNode *j = i; j != nullptr; j = j->next){
            if(min->value > j->value){
                min = j;
            }
        }

        int tempVal = i->value;
        i->value = min->value;
        min->value = tempVal;
        
    }
}

// void IntList::selection_sort(){
//     IntNode *currNode = nullptr;
//     IntNode *tempNode = nullptr;
//     IntNode *smallestNode = nullptr;

//     for(currNode = head; currNode != nullptr; currNode = currNode->next){
//         smallestNode = currNode;
//         for(tempNode = currNode; tempNode != nullptr; tempNode = tempNode->next){
//             if(smallestNode->value > tempNode->value){
//                 smallestNode = tempNode;
//             }
//         }

//         int temp = currNode->value;
//         currNode->value = smallestNode->value;
//         smallestNode->value = temp;
//     }
// }


void IntList::insert_ordered(int value){

    if (empty()){
        push_back(value);
    }

    else if (value <= head->value){
        push_front(value);
    }

    else if (value >= tail-> value){
        push_back(value);
    }
    else{
        IntNode *temp = new IntNode(value);
        IntNode *prev = head;
        IntNode *curr = head->next;

        while(curr != nullptr){
            if(prev->value <= value && value < curr->value){
                prev->next = temp;
                temp->next = curr;
                return;
            }
            curr = curr->next;
            prev = prev->next;
        }
    }
}

// void IntList::insert_ordered(int value){
//     if (empty()){
//         push_back(value);
//     }

//     else if (value <= head->value){
//         push_front(value);
//     }

//     else if (value >= tail-> value){
//         push_back(value);
//     }
//     else{
//         IntNode *newNode = new IntNode(value);
//         IntNode *currNode = head;
//         IntNode *nextNode = head->next;

//         while(nextNode != nullptr){
//             if(newNode->value < nextNode->value){
//                 currNode->next = newNode;
//                 newNode->next = nextNode;

//                 return;
//             }

//             nextNode = nextNode->next;
//             currNode = currNode->next;
//         }
//     }
// }

void IntList::remove_duplicates(){

    IntNode *temp = nullptr;
    if (empty()){
        return;
    }
    else{
        for(IntNode *i = head; i != nullptr; i = i->next){
            temp = i;
            for(IntNode *j = i->next; j != nullptr; j = temp->next){
                if(i->value == j->value){
                    if(j == tail){
                        delete j;
                        tail = temp;
                        tail->next = nullptr;
                    }
                    else{
                        temp->next = j->next;
                        delete j;
                    }
                }
                else{
                    temp = temp -> next;
                }
            }
        }
    } 
}

