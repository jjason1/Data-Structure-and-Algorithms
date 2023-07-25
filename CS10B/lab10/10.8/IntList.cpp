#include "IntList.h"

bool IntList::bubbleUp() {
    bool swapped = false;

    if(!head || !head->next){
        return swapped;
    }

    swapped = bubbleUp(head->next);

    if(head->value > head->next->value){
        swap(head->value, head->next->value);
        swapped = true;
    }

    return swapped;
}

bool IntList::bubbleUp(IntNode *curr){
    bool swapped = false;

    if(!curr->next){
        return swapped;
    }
    swapped = bubbleUp(curr->next);

    if(curr->value > curr->next->value){
        swap(curr->value, curr->next->value);
        swapped = true;
    }

    return swapped;
}