#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

void readData(const string &, vector<double> &, vector<double> &);
double interpolation(double, const vector<double> &, const vector<double> &);
bool isOrdered(const vector<double> &);
void reorder(vector<double> &, vector<double> &);

int main(int argc, char *argv[]) {
    double angle;
    string fileName;
    vector<double> flightAngle;
    vector<double> lift;

    if(argc != 2){
      cout << "Usage: progname inputFile" << endl;
      return 1;
   }
    fileName = argv[1];
    readData(fileName, flightAngle, lift);
    
    
    reorder(flightAngle, lift);


    bool check = true;
    string input;

    while(check){
        cout << "Enter the angle: ";
        cin >> angle;

        cout << interpolation(angle, flightAngle, lift);
        cout << endl << "Would you like to enter another angle? ";
        cin >> input;
        if(input == "No" || input == "no"){
            check = false;
        }
    }

    return 0;
}

void readData(const string &fileName, vector<double> &flightAngle, vector<double> &lift){
    ifstream inFS;
    inFS.open(fileName);

    if (!inFS.is_open()) {
      cout << "Error opening " << fileName << endl;
      exit(1);
    }   
    
    double input;

    while(inFS >> input){
        flightAngle.push_back(input);

        inFS >> input;

        lift.push_back(input);
    }
}

double interpolation(double angle, const vector<double> &flightAngle, const vector<double> &lift){
    
    double coefficient;
    double fa, a, c, fc;

    for(unsigned int i = 0; i < flightAngle.size(); ++i){

        if(flightAngle[i] == angle){
            coefficient = lift[i];
            break;
        }
        else if(angle < flightAngle[i]){
            c = flightAngle[i];
            fc = lift[i];
            a = flightAngle[i-1];
            fa = lift[i-1];
            coefficient = fa + ((angle - a) / (c - a)) * (fc - fa);
            break;
        }
    }

    return coefficient;
}

bool isOrdered(const vector<double> &flightAngle){

    for(unsigned int i = 1; i < flightAngle.size(); ++i){
        if(flightAngle[i] < flightAngle[i-1]){
            return false;
            break;
        }
    }
    return true;
}

void reorder(vector<double> &flightAngle, vector<double> &lift){
    double temp1, temp2;

    while(!isOrdered(flightAngle)){
        for (unsigned int i = 0; i < flightAngle.size()-1; ++i) {
            if(flightAngle[i] > flightAngle[i+1])
            {   
                temp1 = flightAngle[i];
                flightAngle[i] = flightAngle[i+1];
                flightAngle[i+1] = temp1;

                temp2 = lift[i];
                lift[i] = lift[i + 1]; 
                lift[i+1] = temp2;
            }
        }
    }
}