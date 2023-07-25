#include <iostream>
#include "Character.h"
#include "Wizard.h"
using namespace std;

Wizard::Wizard(string name, double health, double attackStrength, int rank) : 
Character(WIZARD, name, health, attackStrength), rank(rank){}

int Wizard::getRank() const{
    return rank;
}

void Wizard::attack(Character &opponent){

    cout << "Wizard " << name << " attacks " << opponent.getName() << " --- POOF!!" << endl;
    double damage = attackStrength;

    if(opponent.getType() == WIZARD){
        Wizard &opp = dynamic_cast<Wizard&>(opponent);
        damage = attackStrength * (static_cast<double>(rank) / static_cast<double>(opp.getRank()));
    }

    cout << opponent.getName() << " takes " << damage << " damage." << endl;
    opponent.damage(damage);

}