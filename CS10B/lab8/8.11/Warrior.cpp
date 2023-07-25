
#include <iostream>

using namespace std;

#include "Character.h"
#include "Warrior.h"

Warrior::Warrior(string name, double health, double attackStrength, string allegiance)
    : Character(WARRIOR, name, health, attackStrength), allegiance(allegiance) {}

void Warrior::attack(Character& opponent)
{
    cout << "Warrior " << name << " ";
    double damage = attackStrength * (health / MAX_HEALTH);
    if (opponent.getType() == WARRIOR)
    {
        Warrior& opp = dynamic_cast<Warrior&>(opponent);
        if (opp.getAllegiance() == allegiance)
        {
            cout << "does not attack Warrior " << opp.getName() << "." << endl;
            cout << "They share an allegiance with " << allegiance << "." << endl;
            return;
        }
    }
    cout << "attacks " << opponent.getName() << " --- SLASH!!" << endl;
    cout << opponent.getName() << " takes " << damage << " damage." << endl;
    opponent.damage(damage);
}

string Warrior::getAllegiance() const
{
    return allegiance;
}