// ACM - A - Quick Change.cpp : Defines the entry point for the console application.
// Calculates the number of each type of coin to give in change
//robert holland

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	// open the input file
	ifstream input("input.txt");

	// create variables to store the number of transactions and the change
	// to be given for the current transaction
	int transactions, changeRemaining;
	// read the number of transactions from the input file
	input >> transactions;

	// use const int to make changing the number of coins easier
	const int numCoinTypes = 4;
	// create an array storing the value of each coin
	const int coinTypes[numCoinTypes] = { 25, 10, 5, 1 };

	// process all transactions
	for ( int i = 0; i < transactions; i++ )
	{
		// read the change to be given in this transaction
		input >> changeRemaining;

		// create an array initialized to 0 to store the number of coins to give in change
		int amountOfCoins[numCoinTypes] = {};

		// loop for each type of coin
		for ( int j = 0; j < numCoinTypes; j++ )
		{
			// give one more of that coin until that coin would be too big
			while ( changeRemaining >= coinTypes[j] )
			{
				amountOfCoins[j]++;
				changeRemaining -= coinTypes[j];
			}
		}

		// print the results
		cout << i+1 << " " << amountOfCoins[0] << " QUARTER(S), " << amountOfCoins[1] << " DIME(S), " << amountOfCoins[2] << " NICKEL(S), " << amountOfCoins[3] << " PENNY(S)" << endl;
	}

	// allow the user to see the output
	system("pause");
	return 0;
}

