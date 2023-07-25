#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

// Function to calculate letter grade from average exam score
char calcLetterGrade(double average)
{
    if (average >= 90.0)
    {
        return 'A';
    }
    else if (average >= 80.0)
    {
        return 'B';
    }
    else if (average >= 70.0)
    {
        return 'C';
    }
    else if (average >= 60.0)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}

int main()
{
    string fileName;
    cout << "Enter the name of the TSV file: ";
    cin >> fileName;

    ifstream inFS(fileName); // Opens the file and check if its open
    if (!inFS.is_open())
    {
        cout << "Could not open file " << fileName << endl;
        return 1;
    }

    ofstream outFS("report.txt"); // Creates a report.txt file and check if its open
    if (!outFS.is_open())
    {
        cout << "Could not create report.txt." << endl;
        return 1;
    }

    double midterm1total = 0.0;
    double midterm2total = 0.0;
    double finaltotal = 0.0;
    double average = 0.0;
    char letterGrade;

    int totalStudents = 0;
    int midterm1, midterm2, finalScore;

    string lastName, firstName;

    while (inFS >> lastName >> firstName >> midterm1 >> midterm2 >> finalScore)
    {

        if (inFS.fail())
        {
            break;
        }
        else
        {
            average = (midterm1 + midterm2 + finalScore) / 3.0; // Calculate the average score
            letterGrade = calcLetterGrade(average);             // Find the letter grade using the average score

            // Output the information onto the report.txt file
            outFS << lastName << "\t" << firstName << "\t" << midterm1 << "\t" << midterm2 << "\t" << finalScore << "\t" << letterGrade << endl;

            // Converts the int to doubles and increment student population by 1
            midterm1total += midterm1;
            midterm2total += midterm2;
            finaltotal += finalScore;
            totalStudents++;
        }
    }

    // Calculates the averages of midterms and finals by divding the midterm by the total students
    double midterm1Average = midterm1total / totalStudents;
    double midterm2Average = midterm2total / totalStudents;
    double finalAverage = finaltotal / totalStudents;

    // Outputting information onto the report.txt file
    outFS << endl;
    outFS << fixed << setprecision(2)
          << "Averages: midterm1 " << midterm1Average
          << ", midterm2 " << midterm2Average
          << ", final " << finalAverage << endl;

    inFS.close();
    outFS.close();

    return 0;
}