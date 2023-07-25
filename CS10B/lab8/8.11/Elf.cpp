#include <iostream>
#include "Elf.h"
#include "Character.h"
using namespace std;


Elf::Elf(string name, double health, double attackStrength, string familyName):
Character(ELF, name, health, attackStrength), familyName(familyName){}

string Elf::getFamily() const{
    return familyName;
}

void Elf::attack(Character& opponent)
{
    cout << "Elf " << name << " ";
    double damage = attackStrength * (health / MAX_HEALTH);
    if (opponent.getType() == ELF)
    {
        Elf& opp = dynamic_cast<Elf&>(opponent);
        if (opp.getFamily() == familyName)
        {
            cout << "does not attack Elf " << opp.getName() << "." << endl;
            cout << "They are both members of the " << familyName << " family." << endl;
            return;
        }
    }
    cout << "shoots an arrow at " << opponent.getName() << " --- TWANG!!" << endl;
    cout << opponent.getName() << " takes " << damage << " damage." << endl;
    opponent.damage(damage);
}

