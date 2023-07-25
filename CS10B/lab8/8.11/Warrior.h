#ifndef __WARRIOR_H__
#define __WARRIOR_H__

#include <string>
#include "Character.h"
using namespace std;

class Warrior : public Character {

    private:

    string allegiance;

    public:

    Warrior(string, double, double, string);
    void attack(Character &);
    string getAllegiance() const;
};

#endif
