//include any standard libraries needed
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

const int ARR_CAP = 100;

//  - Passes in an array along with the size of the array.
//  - Returns the mean of all values stored in the array.
double mean(const double array[], int arraySize){
	double sum, mean;

	for(int i = 0; i < arraySize; ++i){
		sum += array[i];
	}

	mean = sum/arraySize;

	return mean;
}

//  - Passes in an array, the size of the array by reference, and the index of a value to be removed from the array.
//  - Removes the value at this index by shifting all of the values after this value up, keeping the same relative order of all values not removed.
//  - Reduces arraySize by 1.
void remove(double array[], int &arraySize, int index){
    for(int i = index; i < (arraySize-1); ++i){
        array[i] = array[i+1];
    }

    arraySize--;
}


// - Passes in an array and the size of the array.
// - Outputs each value in the array separated by a comma and space, with no comma, space or newline at the end.
void display(const double array[], int arraySize){
    for(int i = 0; i < arraySize-1; ++i){
        cout << array[i] << ", ";
    }
    cout << array[arraySize - 1];
}

int main(int argc, char *argv[]) {
   
   // verify file name provided on command line
   string fileName;
   ifstream inFS;

   fileName = argv[1];

   // open file and verify it opened
   inFS.open(argv[1]);

   	if(!inFS.is_open()) {
    	cout << "Error opening " << fileName << endl;
    	exit(1);
	} 

   // Declare an array of doubles of size ARR_CAP.
   	double array[ARR_CAP];
   
   // Fill the array with up to ARR_CAP doubles from the file entered at the command line.
   int i = 0;
   int count = 0;
   double num;
   while(inFS >> num){
    array[i] = num; 
    i++;
    count++;
   }   
   
   // Call the mean function passing it this array and output the 
   // value returned.

    cout << "Mean: " << mean(array, count) << endl;

    
   // Ask the user for the index (0 to size - 1) of the value they want to remove.
   int indexToRemove;
   cout << "Enter index of value to be removed (0 to " << count -1 << "): ";
   cin >> indexToRemove;

	
   // Call the display function to output the array.
   cout << "Before removing value: ";
   display(array, count);
   cout << endl;
   
   // Call the remove function to remove the value at the index
   // provided by the user.

   remove(array, count, indexToRemove);
  
    
   // Call the display function again to output the array
   // with the value removed.
   cout << "After removing value: ";
   display(array, count);
   cout << endl;

   
   // Call the mean function again to get the new mean
    cout << endl << "Mean: " << mean(array, count) << endl;
   
	return 0;
}