#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000; // clock per milliseconds

// Declaration of the function needed for this program, the definitions are below main
// Generates a random integer between the given range
int genRandInt(int, int);

// Fills three arrays with random integers
void fillArrays(int[], int[], int[]);

// Partitions an array using the midpoint as the pivot
int partition(int[], int, int);

// Finds the median among three integers
int findMedian(int, int, int);

// Partitions an array using the median of three as the pivot
int partitionThree(int[], int, int);

// Implements Quicksort using the midpoint as the pivot
void Quicksort_midpoint(int[], int, int);

// Implements Quicksort using the median of three as the pivot
void Quicksort_medianOfThree(int[], int, int);

// Implements Insertion Sort algorithm
void InsertionSort(int[], int);

// Swaps two elements in an array
void swap(int[], int, int);

int main()
{
    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];
    int i = 0;

    int numbersSize = 0;
    int numbers[NUMBERS_SIZE];
    int start = 0;
    int end = 0;
    int elapsed = 0;
    srand(time(0));
    fillArrays(arr1, arr2, arr3);
    numbersSize = NUMBERS_SIZE;
    for (i = 0; i < numbersSize; ++i)
    {
        numbers[i] = arr1[i];
    }

    start = clock();
    Quicksort_midpoint(numbers, 0, numbersSize - 1);
    end = clock();
    elapsed = end - start;
    cout << "Quicksort_midpoint elapsed time: " << elapsed / CLOCKS_PER_MS << " ms" << endl;
    for (i = 0; i < numbersSize; ++i)
    {
        numbers[i] = arr2[i];
    }

    start = clock();
    Quicksort_medianOfThree(numbers, 0, numbersSize - 1);
    end = clock();
    elapsed = end - start;
    cout << "Quicksort_medianOfThree elapsed time: " << elapsed / CLOCKS_PER_MS << " ms" << endl;
    for (i = 0; i < numbersSize; ++i)
    {
        numbers[i] = arr3[i];
    }

    start = clock();
    InsertionSort(numbers, numbersSize);
    end = clock();
    elapsed = end - start;
    cout << "InsertionSort elapsed time: " << elapsed / CLOCKS_PER_MS << " ms" << endl;
    return 0;
}

// The start of the definition for each function

int genRandInt(int low, int high)
{
    // Generates a random integer within the range [0, high - low]
    int randomRange = high - low;

    // Generates a random integer within the range [0, randomRange]
    int randomOffset = rand() % (randomRange + 1);

    // Returns the generated random integer within the desired range [low, high]
    return low + randomOffset;
}

// Fills three arrays with random integers
void fillArrays(int arr1[], int arr2[], int arr3[])
{
    // Iterates over the array elements
    for (int i = 0; i < NUMBERS_SIZE; ++i)
    {
        // Generates a random integer and assigns it to arr1[i]
        arr1[i] = genRandInt(0, NUMBERS_SIZE);

        // Assigns the value of arr1[i] to arr2[i]
        arr2[i] = arr1[i];

        // Assigns the value of arr1[i] to arr3[i]
        arr3[i] = arr1[i];
    }
}

int partition(int numbers[], int i, int k)
{
    int low = 0;         // Initialize low pointer
    int high = 0;        // Initialize high pointer
    int midpoint = 0;    // Initialize midpoint variable
    int pivot = 0;       // Initialize pivot variable
    bool finish = false; // Initialize finish flag

    midpoint = i + (k - i) / 2; // Calculate the midpoint index
    pivot = numbers[midpoint];  // Set the pivot value

    low = i;  // Set low pointer to the starting index
    high = k; // Set high pointer to the ending index

    while (!finish) // Start the partitioning process
    {
        while (numbers[low] < pivot) // Find the first element greater than or equal to pivot from the left side
        {
            ++low;
        }

        while (pivot < numbers[high]) // Find the first element smaller than or equal to pivot from the right side
        {
            --high;
        }

        if (low >= high) // If low pointer crosses or equals the high pointer, we have finished partitioning
        {
            finish = true; // Set the finish flag to exit the loop
        }
        else
        {
            swap(numbers, low, high); // Swap the elements at low and high pointers

            ++low;  // Move the low pointer one step to the right
            --high; // Move the high pointer one step to the left
        }
    }

    return high; // Return the index of the pivot element after partitioning
}

int findMedian(int a, int b, int c)
{
    if (a > b) // Check if a is greater than b
    {
        if (b > c) // Check if b is greater than c
        {
            return b; // b is the median, return b
        }
        else if (a > c) // Check if a is greater than c
        {
            return c; // c is the median, return c
        }
        else // a is less than or equal to c
        {
            return a; // a is the median, return a
        }
    }
    else // b is greater than or equal to a
    {
        if (a > c) // Check if a is greater than c
        {
            return a; // a is the median, return a
        }
        else if (b > c) // Check if b is greater than c
        {
            return c; // c is the median, return c
        }
        else // b is less than or equal to c
        {
            return b; // b is the median, return b
        }
    }
}

int partitionThree(int numbers[], int i, int k)
{
    int low = 0;         // Initialize low pointer
    int high = 0;        // Initialize high pointer
    int pivot = 0;       // Initialize pivot variable
    bool finish = false; // Initialize finish flag

    pivot = findMedian(numbers[i], numbers[(i + k) / 2], numbers[k]); // Calculate the pivot using the findMedian function

    low = i;  // Set low pointer to the starting index
    high = k; // Set high pointer to the ending index

    while (!finish) // Start the partitioning process
    {
        while (numbers[low] < pivot) // Find the first element greater than or equal to pivot from the left side
        {
            ++low;
        }

        while (pivot < numbers[high]) // Find the first element smaller than or equal to pivot from the right side
        {
            --high;
        }

        if (low >= high) // If low pointer crosses or equals the high pointer, we have finished partitioning
        {
            finish = true; // Set the finish flag to exit the loop
        }
        else
        {
            swap(numbers, low, high); // Swap the elements at low and high pointers

            ++low;  // Move the low pointer one step to the right
            --high; // Move the high pointer one step to the left
        }
    }

    return high; // Return the index of the pivot element after partitioning
}

void Quicksort_midpoint(int numbers[], int i, int k)
{
    int j = 0; // Initialize j variable to store the partition index

    if (i >= k) // Base case: If i is greater than or equal to k, the array is already sorted or empty
    {
        return; // Exit the function
    }

    j = partition(numbers, i, k); // Perform partitioning and get the partition index

    Quicksort_midpoint(numbers, i, j);     // Recursively sort the left subarray before the partition
    Quicksort_midpoint(numbers, j + 1, k); // Recursively sort the right subarray after the partition
}

void Quicksort_medianOfThree(int numbers[], int i, int k)
{
    int j = 0; // Initialize j variable to store the partition index

    if (i >= k) // Base case: If i is greater than or equal to k, the array is already sorted or empty
    {
        return; // Exit the function
    }

    j = partitionThree(numbers, i, k); // Perform partitioning using the partitionThree function

    Quicksort_medianOfThree(numbers, i, j);     // Recursively sort the left subarray before the partition
    Quicksort_medianOfThree(numbers, j + 1, k); // Recursively sort the right subarray after the partition
}

void InsertionSort(int numbers[], int numbersSize)
{
    for (int i = 1; i < numbersSize; ++i) // Iterate through the array starting from the second element
    {
        int index = numbers[i]; // Store the current element in a variable
        int j = i;              // Initialize j to the current index

        while ((j > 0) && (numbers[j - 1] > index)) // Compare the current element with the elements before it
        {
            numbers[j] = numbers[j - 1]; // Shift elements to the right
            --j;                         // Move j one step to the left
        }
        numbers[j] = index; // Place the current element in its correct position
    }
}

void swap(int numbers[], int low, int high)
{
    int currNum = 0; // Initialize a variable to store the current number

    currNum = numbers[low];       // Store the number at the low index
    numbers[low] = numbers[high]; // Replace the number at the low index with the number at the high index
    numbers[high] = currNum;      // Replace the number at the high index with the stored number
}
