// ACM - B - Candy Sharing Game.cpp : Defines the entry point for the console application.
// Simulates a candy sharing game.

//robert holland

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	// create a stream to read the input file
	ifstream input("input.txt");

	// store the number of students in the first game
	int numStudents;
	input >> numStudents;

	// loop until the EOF marker is reached
	while ( numStudents != 0 )
	{
		// create two arrays, one to store the number of candies each student has...
		int *classRoom = new int[numStudents];
		// and the other to store how many they will have after this round is over
		int *temp = new int[numStudents];
		// create a variable to track if the game should continue
		// (not all students have the same amount of candy yet)
		bool continueStatus = true;
		// create a variable to track how much candy the first student has
		int first;
		// create a variable to track how many rounds the game has lasted
		int rounds = 0;

		// read the initial data on how much candy each student has
		for ( int i = 0; i < numStudents; i++ )
		{
			input >> classRoom[i];
		}

		// loop until each student has the same amount of candy
		while ( continueStatus == true )
		{
			// they might have the same amount after this round
			continueStatus = false;

			// re-arrange the candy as per the instructions
			for ( int i = 0; i < numStudents; i++ )
			{
				// This moves each student to the left, but it shouldn't affect the results
				// The new total for student i+1 is the amount they had before, minus the amount they gave
				// away, plus the amount they gain from the person to their left.
				temp[i] = classRoom[(i+1)%numStudents] - classRoom[(i+1)%numStudents]/2 + classRoom[i]/2;
				// Give each student with an odd number of pieces an extra piece
				if ( temp[i]%2 != 0 )
				{
					temp[i]++;
				}
			}

			// save the number of pieces the first student has
			first = temp[0];

			// clean-up before next round
			for ( int i = 0; i < numStudents; i++ )
			{
				// transfer the data back to the classRoom array to prepare for the next round
				classRoom[i] = temp[i];
				// if we find someone that doesn't have the same number of pieces as the first
				// student, then we have to do at least one more round
				if ( classRoom[i] != first )
				{
					continueStatus = true;
				}
			}

			// increment rounds because we just completed one
			rounds++;

		}

		// output the number of rounds and amount of candy the first student has
		// which is of course the amount that all have
		cout << rounds << " " << first << endl;

		// free dynamically allocated memory
		delete[] classRoom;
		delete[] temp;

		// get the number of students for the next game
		input >> numStudents;
	}

	// allow the user to see the output
	system("pause");
	return 0;
}

