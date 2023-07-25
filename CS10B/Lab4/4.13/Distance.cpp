#include <iostream>
#include <string>
#include <math.h>
#include "Distance.h"
using namespace std;

Distance::Distance(){
    _feet = 0;
    _inches = 0;
}

Distance::Distance(double in){

    _feet = 0;
    _inches = in;

    init();
}

Distance::Distance(unsigned ft, double in){

    _feet = ft;
    _inches = in;
    
    init();
}

unsigned Distance::getFeet() const {
    return _feet;
}

double Distance::getInches() const{
    return _inches;
}

double Distance::distanceInInches() const{

    double inches, sum;

    inches = _feet * 12.0;

    sum = _inches + inches; 

    return sum;
}

double Distance::distanceInFeet() const{

    double feet, sum;

    feet = _inches / 12.0;

    sum = _feet + feet;

    return sum;
}

double Distance::distanceInMeters() const{

    return distanceInInches() * 0.0254;
}

Distance Distance::operator+(const Distance &rhs) const{
    // Distance sum;

    // sum._feet = this->_feet + rhs._feet;
    // sum._inches = this->_inches + rhs._inches;

    // return sum;

    Distance sum = distanceInInches() + rhs.distanceInInches();

    return sum;
}

Distance Distance::operator-(const Distance &rhs) const{
    // Distance sum;

    // sum._feet = this->_feet - rhs._feet;
    // sum._inches = this->_inches - rhs._inches;

    // return sum;

    Distance sum = distanceInInches() - rhs.distanceInInches();
    
    return sum;
}

ostream & operator<<(ostream &out, const Distance &rhs){
    return out << rhs.getFeet() << "' " << rhs.getInches() << '"';

}

void Distance::init(){

   if(_inches < 0){
        _inches = -1 * _inches;
    }

    while(_inches >=12){
        _inches -= 12;
        _feet +=1;
    }
}
