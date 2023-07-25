#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
   unsigned int i;
   string inputFile;
   string outputFile;
   
   if(argc != 3){
      cout << "Usage: progname inputFile outputFile" << endl;
      return 1;
   }
   // Assign to inputFile value of 2nd command line argument
   inputFile = argv[1];
   // Assign to outputFile value of 3rd command line argument
   outputFile = argv[2];
   
   // Create input stream and open input csv file.
   ifstream inFS;
   inFS.open(inputFile);
   
   // Verify file opened correctly.
   // Output error message and return 1 if file stream did not open correctly.
   if (!inFS.is_open()) {
      cout << "Error opening: " << inputFile << endl;
      return 1;
   }
   
   // Read in integers from input file to vector.
   vector<int> inputVector;
   int input;
   while(inFS >> input){
      inputVector.push_back(input);
      inFS.ignore();
   }
   
   // Close input stream.
   inFS.close();
   
   // Get integer average of all values read in.
   int average = 0;
   int sum = 0;

   for(i = 0; i < inputVector.size(); ++i){
      sum += inputVector[i];
   }
   average = sum / inputVector.size();

   // Convert each value within vector to be the difference between the original value and the average.
   for(i = 0; i < inputVector.size(); ++i){
      inputVector[i] = inputVector[i] - average;
   }
   
   // Create output stream and open/create output csv file.
   ofstream outFS;
   outFS.open(outputFile);

   // Verify file opened or was created correctly.
   // Output error message and return 1 if file stream did not open correctly.
   if(!outFS.is_open()){
      cout << "Error opening: " << outputFile << endl;
      return 1;
   }
   
   // Write converted values into ouptut csv file, each integer separated by a comma.
   for(i = 0; i < inputVector.size() -1; ++i){
      outFS << inputVector[i] << ",";
   }
   
   outFS << inputVector.back();
   
   // Close output stream.
   outFS.close();
   
   return 0;
}