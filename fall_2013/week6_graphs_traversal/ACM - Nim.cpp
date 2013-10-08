// ACM - Nim.cpp : Defines the entry point for the console application.
// Determines if a given configuration of the game of Nim is winnable
//Robert Holland

#include "stdafx.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

enum status { WINNABLE, UNWINNABLE };

int main()
{
	// allows reduction of the max pile size for testing purposes,
	// raising it will also require changing the way the key is composed and decomposed
	const int max_Pile_Size = 9;

	// stores a map for each possible game size (total number of stones in all piles)
	// the 0 position is used in the construction process but ignored later because it is irrelevant
	vector< map<int, status> >  vector_Map(37);

	// vectors of ints to store the sizes of individual piles (mainly for sorting purposes)
	vector<int> board_Pos(4), arrangement(4), sorted(4);

	// construct the vector_Map so that it contains every possible game
	// in this case, there are 9^4 minus duplicates
	// the map doesn't allow duplicates, so we won't have to deal with those later
	for ( int i = 0; i <= max_Pile_Size; i++ )
	{
		for ( int j = 0; j <= max_Pile_Size; j++ )
		{
			for ( int k = 0; k <= max_Pile_Size; k++ )
			{
				for ( int l = 0; l <= max_Pile_Size; l++ )
				{
					// store the pile sizes in a vector
					board_Pos[0] = i;
					board_Pos[1] = j;
					board_Pos[2] = k;
					board_Pos[3] = l;

					// sort the vector so that duplicates will match
					sort<vector<int>::iterator>( board_Pos.begin(), board_Pos.end() );

					// insert the game key with an initial value of UNWINNABLE into the correct map
					vector_Map[i+j+k+l][ board_Pos[0]*1000 + board_Pos[1]*100 + board_Pos[2]*10 + board_Pos[3] ] = UNWINNABLE;
				}
			}
		}
	}


	// loop through each map in the vector, and generate winning games from loosing games
	for ( int i = 1; i <= 36; i++ )
	{
		for ( map<int, status>::iterator it = vector_Map[i].begin(); it != vector_Map[i].end(); ++it )
		{
			if ( it->second == UNWINNABLE )
			{
				// decompose the key into a vector
				board_Pos[0] = it->first/1000;
				board_Pos[1] = (it->first/100)%10;
				board_Pos[2] = (it->first/10)%10;
				board_Pos[3] = it->first%10;

				// add 1, 2, or 3 stones to each pile
				for ( int pile = 0; pile < 4; pile++ )
				{
					// save the original layout in a new variable that we can modify
					arrangement = board_Pos;
					// increment the appropriate pile
					arrangement[pile]++;
					while ( arrangement[pile] <= max_Pile_Size && arrangement[pile] - board_Pos[pile] <= 3 )
					{
						// save the modified layout in a new variable that we can sort
						sorted = arrangement;
						// sort that layout
						sort<vector<int>::iterator>( sorted.begin(), sorted.end() );

						// change the status for the sorted layout to WINNABLE
						vector_Map[ sorted[0]+sorted[1]+sorted[2]+sorted[3] ][ sorted[0]*1000 + sorted[1]*100 + sorted[2]*10 + sorted[3] ] = WINNABLE;

						// add another stone to the current pile (up to 3 extras)
						arrangement[pile]++;
					}
				}
			}
		}
	}

	// We now have a vector of maps containing the status of every possible game (within the size limitations)
	// Checking if a game can be won is as simple as checking the value for the game's key


	// create input and output streams
	ifstream input("input.txt");
	ofstream output("output.txt");

	// read in the number of games we are testing
	int number_Of_Games;
	input >> number_Of_Games;

	// for each game
	for ( int i = 0; i < number_Of_Games; i++ )
	{
		// read the pile sizes into a vector
		for ( int j = 0; j < 4; j++ )
		{
			input >> board_Pos[j];
		}

		// sort the vector of pile sizes so that it will match the keys in the map
		sort<vector<int>::iterator>( board_Pos.begin(), board_Pos.end() );

		// test the key's status
		if ( WINNABLE == vector_Map[ board_Pos[0]+board_Pos[1]+board_Pos[2]+board_Pos[3] ][ board_Pos[0]*1000 + board_Pos[1]*100 + board_Pos[2]*10 + board_Pos[3] ] )
		{
			// output the results to the output file and the screen
			output << "1" << endl;
			cout << board_Pos[0] << " " << board_Pos[1] << " " << board_Pos[2] << " " << board_Pos[3] << " is winnable." << endl;
		}
		else
		{
			// output the results to the output file and the screen
			output << "0" << endl;
			cout << board_Pos[0] << " " << board_Pos[1] << " " << board_Pos[2] << " " << board_Pos[3] << " is unwinnable." << endl;
		}

	}

	// allow the user to see the output
	system("pause");
	return 0;
}