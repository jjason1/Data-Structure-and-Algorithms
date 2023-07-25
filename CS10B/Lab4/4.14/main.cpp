#include <iostream>
#include <vector>
#include <string>
#include "ShoppingCart.h"

using namespace std;
char PrintMenu();


int main() {

   string name, date;
   ShoppingCart cart;
   
   cout << "Enter customer's name: ";
   getline(cin, name);
   cout << endl;

   cout << "Enter today's date: ";
   getline(cin, date);
   cout << endl;
   cout << endl;

   cart = ShoppingCart(name, date);

   cout << "Customer name: " << cart.customerName() << endl;
   cout << "Today's date: " << cart.date() << endl;

   string itemName, itemDescription;
   int price, quantity;
   ItemToPurchase item;

   char input = PrintMenu();

   while(input != 'q'){

      if(input == 'a'){
         cout << endl << "ADD ITEM TO CART" << endl;

         cout << "Enter the item name: " << endl;
         cin.ignore();
         getline(cin, itemName);

         cout << "Enter the item description: " << endl;
         getline(cin, itemDescription);
   
         cout << "Enter the item price: " << endl;
         cin >> price;
         
         cout << "Enter the item quantity: " << endl;
         cin >> quantity;
         
         item = ItemToPurchase(itemName, itemDescription, price, quantity);
         
         cart.addItem(item);
   
      }
      else if(input == 'd'){
         cout << endl << "REMOVE ITEM FROM CART" << endl;
         cin.ignore();
         cout << "Enter name of item to remove: " << endl;
         getline(cin, itemName);
         cart.removeItem(itemName);
      }
      else if(input == 'c'){
         ItemToPurchase newItem;
         string newName;
         int newQuantity;

         cout << endl << "CHANGE ITEM QUANTITY" << endl;
         cin.ignore();
         cout << "Enter the item name: " << endl;
         getline(cin, newName);
         cout << "Enter the new quantity: " << endl;
         cin >> newQuantity;

         newItem.setName(newName);
         newItem.setQuantity(newQuantity);

         cart.modifyItem(newItem);

      }
      else if(input == 'i'){
         cout << endl;
         cout << "OUTPUT ITEMS' DESCRIPTIONS" << endl;
         cart.printDescriptions();

      }
      else if (input == 'o')
      {
         cout << endl;
         cout << "OUTPUT SHOPPING CART" << endl;
         cart.printTotal();
      }
      else if(input == 'q'){
         break;
      }   

      input = PrintMenu();
   }
  
   return 0;
}

char PrintMenu(){

   char input;
   bool check = true;

   cout << endl;
   cout << "MENU" << endl;
   cout << "a - Add item to cart" << endl;
   cout << "d - Remove item from cart" << endl;
   cout << "c - Change item quantity" << endl;
   cout << "i - Output items' descriptions" << endl;
   cout << "o - Output shopping cart" << endl;
   cout << "q - Quit" << endl;
   cout << endl;

   while(check)
   {
      cout << "Choose an option: ";
      cin >> input;
      cout << endl;

      if(input == 'a' || input == 'd' || input == 'c' || input == 'i' || input == 'o' || input == 'q'){
         check = false;
      }
   }

   return input;

}
