#ifndef ITEMTOPURCHASE_H
#define ITEMTOPURCHASE_H

#include <iostream>
#include <string>
using namespace std;

class ItemToPurchase {
    public:
    ItemToPurchase(); /*constructor*/
    ItemToPurchase(string, string, int, int); /*constructor*/

    void setName(string); /*mutators */
    void setPrice(int); /*mutators */
    void setQuantity(int); /*mutators */
    void setDescription(string); /*mutators */
    
    string name() const; /*accessors*/
    int price() const; /*accessors*/
    int quantity() const; /*accessors*/
    string description() const; /*accessors*/
    void printItemCost() const; /*accessors*/
    void printItemDescription() const; /*accessors*/

    private:
    string _name;
    int _price;
    int _quantity;
    string _description;
};

#endif