#include "ShoppingCart.h"
#include <vector>
#include <string>

using namespace std;

ShoppingCart::ShoppingCart(){
    _customerName = "none";
    _currentDate = "January 1, 2016";
}
ShoppingCart::ShoppingCart(string customerName, string date){
    _customerName = customerName;
    _currentDate = date;
}

string ShoppingCart::customerName() const{
    return _customerName;
}

string ShoppingCart::date(){
    return _currentDate;
}

void ShoppingCart::addItem(ItemToPurchase item){

    _cartItems.push_back(item);
}

void ShoppingCart::removeItem(string itemName){

    bool check = true;

    for(unsigned int i = 0; i < _cartItems.size(); ++i){
        if(_cartItems[i].name() == itemName ){
            _cartItems.erase(_cartItems.begin() + i);
            check = false;
        }
    }

    if(check){
        cout << "Item not found in cart. Nothing removed." << endl;
    }
}

void ShoppingCart::modifyItem(ItemToPurchase item){

    bool check = true;
    
    for(unsigned int i = 0; i < _cartItems.size(); ++i){

        if(_cartItems[i].name() == item.name()){
            if(item.description() != "none"){
                _cartItems[i].setDescription(item.description());
               
            }
            if(item.price() != 0){
                _cartItems[i].setPrice(item.price());
             
            }
            if(item.quantity() != 0){
                _cartItems[i].setQuantity(item.quantity());
            }

            check = false;
        }  
    }

    if(check){
        cout << "Item not found in cart. Nothing modified." << endl;
    }
}

int ShoppingCart::numItemsInCart() const{

    int sum = 0; 

    for(unsigned int i = 0; i < _cartItems.size(); ++i){
        sum = sum + _cartItems[i].quantity();
    }

    return sum;
}

int ShoppingCart::costOfCart() const{

    int sum = 0;

    for(unsigned int i = 0; i < _cartItems.size(); ++i){
        sum = sum + (_cartItems[i].price() * _cartItems[i].quantity());
    }

    return sum;
}

void ShoppingCart::printTotal() const{

    int sum = 0;

    for(unsigned int i = 0; i < _cartItems.size(); ++i){
        sum = sum + _cartItems[i].quantity();
    }
    cout << _customerName << "'s Shopping Cart - " << _currentDate << endl;
    cout << "Number of Items: " << sum << endl;

    cout << endl;

    if(_cartItems.size() == 0){
        cout << "SHOPPING CART IS EMPTY" << endl;

        cout << endl;

        cout << "Total: $" << 0 << endl;
    }
    else{
       for(unsigned int i  = 0; i < _cartItems.size(); ++i){
        _cartItems[i].printItemCost();
        } 
    
    cout << endl;
    cout << "Total: $" << costOfCart() << endl;

    }

}

void ShoppingCart::printDescriptions() const{

    cout << _customerName << "'s Shopping Cart - " << _currentDate << endl;

    cout << endl;

    cout << "Item Descriptions" << endl;
    for(unsigned int i = 0; i < _cartItems.size(); ++i){
        _cartItems[i].printItemDescription();
    }
}