#include <string>
#include "Character.h"
using namespace std;

class Wizard : public Character{
    private:
    int rank;

    public:
    Wizard(string, double, double, int);
    void attack(Character &);
    int getRank() const;
};
