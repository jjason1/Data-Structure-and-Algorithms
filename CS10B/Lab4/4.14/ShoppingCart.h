#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include "ItemToPurchase.h"
#include <vector>
#include <string>

using namespace std;

class ShoppingCart{
    public:
    ShoppingCart(); /*constructor*/
    ShoppingCart(string customerName, string date); /*constructor*/

    string customerName() const; /*accessors*/
    string date(); /*accessors*/
    int numItemsInCart() const; /*accessors*/
    int costOfCart() const; /*accessors*/
    void printTotal() const; /*accessors*/
    void printDescriptions() const; /*accessors*/

    void addItem(ItemToPurchase); /*mutators */
    void removeItem(string); /*mutators */
    void modifyItem(ItemToPurchase); /*mutators */

    private:
    string _customerName;
    string _currentDate;
    vector <ItemToPurchase> _cartItems;
};

#endif