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
    return (head == nullptr && tail == nullptr);
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
    IntNode *temp = list.head;

    if (temp != nullptr)
    {
        out << temp->value;
        temp = temp->next;
    }
    while (temp != nullptr)
    {
        out << " " << temp->value;
        temp = temp->next;
    }

    return out;
}