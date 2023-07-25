#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

bool rCopy(const string&, const string&);
bool rCopyHelper(ifstream& in, ofstream& out);


int main(int argc, char* argv[]) {
    string inFile, outFile;

    inFile = argv[1];
    outFile = argv[2];

    rCopy(inFile, outFile);

    return 0;
}

bool rCopy(const string& inFile, const string& outFile){

    bool copy = false; 

    ifstream inFS(inFile);
    if(!inFS.is_open()){
        cout << "Error opening " << inFile << endl;
        cout << "Copy not completed" << endl;
        return copy;
        exit(1);
    }

    ofstream outFS(outFile);
    if(!outFS.is_open()){
         cout << "Error opening " << outFile << endl;
        cout << "Copy not completed" << endl;
        return copy;
        exit(1);
    }

    copy = rCopyHelper(inFS, outFS);

    inFS.close();
    outFS.close();

    return copy;
}

bool rCopyHelper(ifstream &in, ofstream &out){
    char ch;

    if(in.get(ch)){
        if(!rCopyHelper(in, out)){
            return false;
        }

        out << ch;
        return true;
    }

    return true;
}
