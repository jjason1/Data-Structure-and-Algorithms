#include "SortedSet.h"
#include <iostream>
using namespace std;

int main() {

   /*Testing constructors*/
   SortedSet a;
   SortedSet b;
   SortedSet sum;
   IntList c;
   
   a.push_back(1);
   a.push_back(2);
   a.push_back(3);
   a.push_back(4);
   a.push_back(5);

   // cout <<"First test: " << a << endl;

   // b = a;
   // cout << "Second test (copy constructor): " << b << endl;

   // c.push_back(3);
   // c.push_back(4);
   // c.push_back(5);
   // c.push_back(6);
   // c.push_back(7);

   // a = c;

   // cout << "Third test (copy constructor with intlist): " << c << endl;

   /*Testing the accessors*/

   // cout << "Testing in function" << endl;
   // if(a.in(1)){
   //    cout << "Found" << endl;
   // }
   // else{
   //    cout << "Not found " << endl;
   // }

   // if(a.in(6)){
   //    cout << "Found" << endl;
   // }
   // else{
   //    cout << "Not found" << endl;
   // }

   // cout << endl;

   // cout << "Testing Operator | function" << endl;

   // b.push_back(3);
   // b.push_back(4);
   // b.push_back(5);
   // b.push_back(6);
   // b.push_back(7);

   // sum = a|b;

   // cout << sum << endl;
   
   // cout << endl;

   // cout << "Testing Operator & function" << endl;

   // sum = a&b;

   // cout << sum << endl;

   /*Testing mutators*/

   cout << a << endl;

   cout << "Testing add function" << endl;

   a.add(1);
   a.add(2);
   a.add(3);
   a.add(5);
   a.add(6);

   cout << a << endl;

   cout << "Testing push_front function" << endl;
   a.push_front(1);
   
   cout << a << endl;






   return 0;
}
