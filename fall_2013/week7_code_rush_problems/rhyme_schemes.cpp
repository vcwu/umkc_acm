// ACM - G - Rhyme Schemes.cpp
// Calculates the number of different rhyme schemes in a poem with n lines
//Robert Holland - 10/11/13
//Unfortunately, what I had discussed in class does not work, because it treats schemes like aabb and bbaa as different, when they actually aren't.  After a while of trying to modify it I decided that it made more sense to start over, as things were getting messy.  I put together the recursive version, which worked well for the sample input, but couldn't handle 100.  I then modified the recursive version to save results to a table to reduce explosive recursion.  It solves 100 very fast, and only takes a few seconds to get 200 on my laptop.  I tried 300, but it just hung, which I think is because of overflow problems with the doubles, rather than a problem with the algorithm, as the answer for 200 was pretty close to the max value for a double anyway.
//Basically, the idea of the new algorithm is to consider the rhyme(s) that occur most often first, and force recursive calls to use a frequency for subsequent rhymes that is strictly less.  For example, we consider aaaaa, then aaaaN, then aaaNN, then aaNNN, then aabbN, then abcde, where a, b, c, d, and e are specific rhymes, and the N's are a non-terminal that represents the sub-problem where the frequency of any rhyme in the sub-problem is strictly less than the frequency of a/b/c/etc.  For each of these forms we also examine the number of ways that the terminals can be arranged.  This gives the number of rhyme schemes for a given number of lines of poetry, without counting certain configurations twice like the previous method did, because in this method, we are guaranteed that the sub-problem does not contain a copy of the part we removed from the original problem.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

/** Calculates the number of rhyme schemes given the number of line in a poem
	@param n The number of lines in the poem
	@param a The maximum number of lines in any one rhyming set (used for recursion, it should be the same as n normally)
	@param table A table is used to prevent explosive recursion from getting out of hand
			The table should be n by n, and contain either correct values or -1 at every position
	@return The number of possible rhyme schemes for the given poem size
*/
double rhyme( int n, int a, vector<vector<double>> &table );

/** Calculates the combination "n choose k" for the given parameters
	adapted from here: http://stackoverflow.com/a/9331125
	@param n The number of items to choose from
	@param k The number of items to choose
	@return The number of different ways to choose k of n items
*/
double combination( double n, double k );

int main()
{
	// open the input file
	ifstream fin("input.txt");
	// create a vector to store the list of poem sizes
	vector<int> the_List;

	// create a variable to store a poem size
	int n;
	// read the first poem size
	fin >> n;

	// store each value in the list
	while ( n != 0 )
	{
		the_List.push_back(n);
		fin >> n;
	}
	// n == 0 now

	// find the largest value in the list
	for ( vector<int>::iterator it = the_List.begin(); it != the_List.end(); ++it )
	{
		if ( *it > n )
		{
			n = *it;
		}
	}

	// create a 2d vector to use as the table
	vector<vector<double>> the_Table;
	// create a temporary vector to help build the table
	vector<double> temp;

	// fill the temp vector with -1 (impossible value, signals that the correct value has not been found yet)
	for ( int i = 0; i <= n; i++ )
	{
		temp.push_back(-1);
	}

	// fill the table using copies of the temp vector
	for ( int i = 0; i <= n; i++ )
	{
		the_Table.push_back(temp);
	}

	// create a string to store the result
	string result;
	// create a string stream so that the result can be converted to a string
	stringstream s;

	// loop for each value in the list
	for ( vector<int>::iterator it = the_List.begin(); it != the_List.end(); ++it )
	{
		// for some reason, setprecision(0) was truncating the result after 26 characters,
		// so I had to figure out a different way to get the result formatted correctly

		// store the calculated value in the string stream using fixed formatting
		s << fixed << rhyme( *it, *it, the_Table ) << endl;
		// read the line into the string
		getline(s, result);
		// output the desired information, including only the desired part of the string
		cout << *it << " " << result.substr(0, result.find(".")) << endl;
		
		// this doesn't work
		//cout << *it << " " << fixed << setprecision(0) << rhyme( *it, *it, the_Table ) << endl;
	}

	// allow the user to see the output
	system("pause");
	return 0;
}

// Calculates the number of rhyme schemes given the number of line in a poem
double rhyme( int n, int a, vector<vector<double>> &table )
{
	if ( table.at(n).at(a) != -1 )
	{
		// if we have already calculated the value, use that
		return table.at(n).at(a);
	}
	else if ( n == 0 )
	{
		// if there are no more lines to allocate, we have found a valid allocation
		table.at(n).at(a) = 1;
		return 1;
	}
	else if ( a == 0 )
	{
		// if the maximum size of allocation is 0, but there is still more to allocate, this allocation is invalid
		table.at(n).at(a) = 0;
		return 0;
	}
	else
	{
		// we will use a as the upper bound of allocation, but be can never allocate more than n either
		if ( n < a )
		{
			a = n;
		}

		// create a variable to store the number of allocations we have found
		double sum = 0;
		// create a variable to store the current number of combinations for the current allocation
		double choice;
		// create a variable to store the multiplicity of the current allocation value
		int j;

		// try allocating each amount allowed
		for ( int k = 1; k <= a; k++ )
		{
			// initialize the combinations and multiplicity
			choice = combination ( n, k );
			j = 1;

			// loop for each multiplicity of this allocation, making sure that we don't allocate more than we have
			for (; j*k < n; j++ )
			{
				// add the number of rhyme patterns that can be allocated using the remaining lines
				// such that all further rhymes are allocated less
				// which is ( (n, k)*(n-k, k)*...*(n-j*k, k)/(j!) )*rhyme( n-j*k, k-1, )
				sum += choice * rhyme( n-j*k, k-1, table ) / j;
				// increment choice to reflect the number of combinations at the next multiplicity
				choice = ( choice * combination( n-j*k, k ) )/j;
			}
			
			// if i evenly divides n, it is possible for all rhymes to have the same allocation
			if ( j*k == n )
			{
				// all the appropriate amount to the sum for when this occurs,
				// which is (n, k)*(n-k, k)*...*(n-j*k, k)*...*(k, k)/(j!)
				sum += choice / j;
			}
		}

		// save the calculated amount so that we don't have to re-calculate later
		table.at(n).at(a) = sum;
			
		// return the calculated amount
		return sum;
	}
}

// Calculates the combination "n choose k" for the given parameters
double combination( double n, double k )
{
	if ( k > n )
	{
		// we can't choose more than we have
		return 0;
	}
	else if ( k == 0 || k == n )
	{
		// choosing none or all can only happen one way
		return 1;
	}
	else
	{
		// (n, k) and (n, n-k) are the same, so calculate the one that is easier
		if ( k * 2 > n )
		{
			k = n-k;
		}

		// create a variable to store the result,
		// and initialize it with the largest value from the numerator,
		// divided by the smallest value in the denominator
		double result = n;
		// iterate through the values in the denominator
		for( double i = 2; i <= k; i++ )
		{
			// multiply by the next term smallest in the numerator
			result *= (n-i+1);
			// divide by the next largest term in the denominator,
			// this is safe because we have had at least i terms in the numerator,
			// so we know that one is a multiple of i
			result /= i;
		}
		// return the result that we have calculated
		return result;
	}
}
