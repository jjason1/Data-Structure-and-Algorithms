#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;
bool checkSeat = false;

// Function should display menu options
void DisplayMenu()
{
	cout << "Menu options:" << endl;
	cout << "1. Display All Seats Status:" << endl;
	cout << "2. Total Number of Available Seats:" << endl;
	cout << "3. Display Available Seats: " << endl;
	cout << "4. Book Seat:" << endl;
	cout << "5. Cancel Seat:" << endl;
	cout << "6. Change Seat:" << endl;
	cout << "7. Quit:" << endl;
	cout << endl;
	cout << "Please select an option: " << endl;
}
// Function should show all seats and seat status where a 0 marks the seat status as available and an
// 1 marks the seat status as occupied.
void DisplayAllSeatsStatus(const vector<string> &seats, const vector<bool> &seatStatus)
{
	cout << "Seat	Status" << endl;
	for (unsigned int i = 0; i < seats.size(); ++i)
	{
		cout << seats[i] << "	" << seatStatus[i] << endl;
	}
}
// Function display which seats are currently available
void DisplayAvailableSeats(const vector<string> &seats, const vector<bool> &seatStatus)
{
	cout << "Available seats:" << endl;
	for (unsigned int i = 0; i < seats.size(); ++i)
	{
		if (!seatStatus[i])
		{
			cout << seats[i] << endl;
		}
	}
}
// Function should show the number of seats not currently booked
int TotalNumberOfAvailableSeats(const vector<bool> &seatStatus)
{
	int count = 0;
	for (unsigned i = 0; i < seatStatus.size(); ++i)
	{
		if (!seatStatus[i])
		{
			count++;
		}
	}
	return count;
}
// Function should take in a seat from user and mark that seat as unavailable
void BookSeat(const string &userInput, const vector<string> &seats, vector<bool> &seatStatus)
{
	checkSeat = false;
	for (unsigned int i = 0; i < seats.size(); ++i)
	{
		if (seats[i] == userInput)
		{
			if (seatStatus[i] == false)
			{
				checkSeat = true;
				seatStatus[i] = true;
				DisplayAllSeatsStatus(seats, seatStatus);
			}
			else
			{
				cout << "That seat is already taken." << endl;
			}
		}
	}
}

// Function should take in a seat from user and mark that seat as availab
void CancelSeat(const string &userInput, const vector<string> &seats, vector<bool> &seatStatus)
{
	for (unsigned int i = 0; i < seats.size(); ++i)
	{
		if (seats[i] == userInput)
		{
			seatStatus[i] = false;
			DisplayAllSeatsStatus(seats, seatStatus);
		}
	}
}
// Function should take in two seats from the user.  It should mark the first seat as available and
// the second seat as unavailable
void ChangeSeat(const string &input1, const string &input2, const vector<string> &seats, vector<bool> &seatStatus)
{
	for (unsigned int i = 0; i < seats.size(); ++i)
	{
		if (seats[i] == input1)
		{
			seatStatus[i] = false;
		}

		if (seats[i] == input2)
		{
			seatStatus[i] = true;
		}
	}
	DisplayAllSeatsStatus(seats, seatStatus);
}

int main()
{
	int selection;
	vector<string> seats{"1A", "1B", "1C", "1D", "1E",
						 "2A", "2B", "2C", "2D", "2E",
						 "3A", "3B", "3C", "3D", "3E",
						 "4A", "4B", "4C", "4D", "4E",
						 "5A", "5B", "5C", "5D", "5E"};
	vector<bool> seatStatus(25, false);

	DisplayMenu();
	cin >> selection;
	cout << endl;

	while (selection != 7)
	{
		if (selection == 1)
		{
			DisplayAllSeatsStatus(seats, seatStatus);
		}
		else if (selection == 2)
		{
			cout << "Number of available seats: " << TotalNumberOfAvailableSeats(seatStatus) << endl;
		}
		else if (selection == 3)
		{
			DisplayAvailableSeats(seats, seatStatus);
		}
		else if (selection == 4)
		{
			string userInput;
			while (!checkSeat)
			{
				cout << "Enter seat to book: " << endl;
				cin >> userInput;
				cout << endl;
				BookSeat(userInput, seats, seatStatus);
			}
			checkSeat = false;
		}
		else if (selection == 5)
		{
			string userInput;
			cout << "Enter seat to cancel: " << endl;
			cin >> userInput;
			cout << endl;
			CancelSeat(userInput, seats, seatStatus);
		}
		else if (selection == 6)
		{
			string input1, input2;
			cout << "Enter seat to cancel: " << endl;
			cin >> input1;
			cout << endl;
			cout << "Enter seat to book: " << endl;
			cin >> input2;
			cout << endl;
			ChangeSeat(input1, input2, seats, seatStatus);
		}

		cout << endl;
		DisplayMenu();
		cin >> selection;
		cout << endl;
	}

	return 0;
}