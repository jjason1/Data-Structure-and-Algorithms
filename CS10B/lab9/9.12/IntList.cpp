#include "IntList.h"

#include <ostream>

using namespace std;

IntList::IntList() : head(nullptr) {}


void IntList::push_front(int val) {
   if (!head) {
      head = new IntNode(val);
   } else {
      IntNode *temp = new IntNode(val);
      temp->next = head;
      head = temp;
   }
}

ostream &operator<<(ostream &out, IntNode* node){
   if(node == nullptr){
      return out;
   }
   else{
      out << " ";
   }

   out << node->value;
   return operator<<(out, node->next);
}

ostream &operator<<(ostream &out, const IntList &list){
   IntNode *cur = list.head;

   if(cur == nullptr){
      return out;
   }

   out << cur->value;
   return operator<<(out, list.head->next);
}

bool IntList::exists(IntNode* node, int val) const{

   if(node->value == val){
      return true;
   }
   else{
      if(node->next == nullptr){
         return false;
      }
      else{
         return exists(node->next, val);
      }
   }
}

bool IntList::exists(int n) const{
   if(head == nullptr){
      return false;
   }

   return exists(head, n);
}
