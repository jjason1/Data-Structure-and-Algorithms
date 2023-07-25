#include <string>
#include "Character.h"
using namespace std;

class Elf : public Character{
    private:
    string familyName;

    public:
    Elf(string, double, double, string);
    string getFamily() const;
    void attack(Character &);
};



