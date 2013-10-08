// ACM - Codeception.cpp : Defines the entry point for the console application.
// Prints its own source code with the given modifications
//Perceptive Software Code Dash 2013
//Problem 7 - The beginning of the end
//Robert Holland

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// this is the single instance of the target phrase in the code
const string target = "int x = 42";

// this string contains all the information that the program needs to print out its
// source code, including this string, without infinite recursion occurring
const string self = "// ACM - Codeception.cpp : Defines the entry point for the console application.NEW_LINE// Prints its own source code with the given modificationsNEW_LINENEW_LINE#include \"stdafx.h\"NEW_LINE#include <iostream>NEW_LINE#include <string>NEW_LINE#include <fstream>NEW_LINENEW_LINEusing namespace std;NEW_LINENEW_LINE// this is the single instance of the target phrase in the codeNEW_LINEconst string target = \"INSERT_TARGET\";NEW_LINENEW_LINE// this string contains all the information that the program needs to print out itsNEW_LINE// source code, including this string, without infinite recursion occurringNEW_LINEconst string self = \"INSERT_SELF\";NEW_LINENEW_LINE/** Transforms the string transform_This by replacing every instance of replace_This with with_ThisNEW_LINE	@param transform_This The string to be transformedNEW_LINE	@param replace_This The substring to be replacedNEW_LINE	@param with_This The substring to replace replace_This withNEW_LINE	@return The number of instances of replace_This replacedNEW_LINE*/NEW_LINEint sweep_Transform( string &transform_This, const string &replace_This, const string &with_This );NEW_LINENEW_LINEint main()NEW_LINE{NEW_LINE	// create a string containing \"NEW_\" followed by \"LINE\"NEW_LINE	string newLine =\"NEW_\";NEW_LINE	newLine += \"LINE\";NEW_LINE	// create a string containing \"INSERT_\" followed by \"TARGET\"NEW_LINE	string insertTarget = \"INSERT_\";NEW_LINE	insertTarget += \"TARGET\";NEW_LINE	// create a string containing \"INSERT_\" followed by \"SELF\"NEW_LINE	string insertSelf = \"INSERT_\";NEW_LINE	insertSelf += \"SELF\";NEW_LINENEW_LINE	// create a string to store the code to be printed outNEW_LINE	string full_Self = self;NEW_LINENEW_LINE	// replace all instances of the newLine string with the newLine characterNEW_LINE	sweep_Transform( full_Self, newLine, \"\\n\" );NEW_LINENEW_LINE	// inserts the target at the correct positionNEW_LINE	sweep_Transform( full_Self, insertTarget, target );NEW_LINENEW_LINE	// create a string to store the self string as it appears in the source fileNEW_LINE	string real_Self = self;NEW_LINE	// transform the escaped characters in the string back into the escaped formNEW_LINE	sweep_Transform( real_Self, \"\\\\\", \"\\\\\\\\\" );NEW_LINE	sweep_Transform( real_Self, \"\\\"\", \"\\\\\\\"\" );NEW_LINENEW_LINE	// inserts the encoded string in the correct positionNEW_LINE	sweep_Transform( full_Self, insertSelf, real_Self );NEW_LINENEW_LINE	// replace the target string and count how many times it appearedNEW_LINE	int target_counter = sweep_Transform( full_Self, target, \"int x = 666\" );NEW_LINENEW_LINE	// overwrite the source code with the modified source code!!NEW_LINE	ofstream output(\"ACM - Codeception.cpp\");NEW_LINENEW_LINE	// if target string appeared an incorrect number of timesNEW_LINE	if ( target_counter != 1 )NEW_LINE	{NEW_LINE		// print an error messageNEW_LINE		output << \"ERROR: requirements not met!\"<< endl;NEW_LINE	}NEW_LINE	else // if the target string appeared the correct number of timesNEW_LINE	{NEW_LINE		// print the source code (with the modification)NEW_LINE		output << full_Self;NEW_LINE	}NEW_LINENEW_LINE	return 0;NEW_LINE}NEW_LINENEW_LINE// Transforms the string transform_This by replacing every instance of replace_This with with_ThisNEW_LINEint sweep_Transform( string &transform_This, const string &replace_This, const string &with_This )NEW_LINE{NEW_LINE	// initialize the number of instances replaced to 0NEW_LINE	int count = 0;NEW_LINE	// loop for each instance of replace_This in transform_This, advance to the next instance starting after this one each time, and increment countNEW_LINE	for ( size_t found = transform_This.find( replace_This ); found != string::npos; found = transform_This.find( replace_This, found+with_This.length() ), count++ )NEW_LINE	{NEW_LINE		// replace replace_This with with_ThisNEW_LINE		transform_This.replace( found, replace_This.length(), with_This );NEW_LINE	}NEW_LINE	// return the number of instances replacedNEW_LINE	return count;NEW_LINE}";

/** Transforms the string transform_This by replacing every instance of replace_This with with_This
	@param transform_This The string to be transformed
	@param replace_This The substring to be replaced
	@param with_This The substring to replace replace_This with
	@return The number of instances of replace_This replaced
*/
int sweep_Transform( string &transform_This, const string &replace_This, const string &with_This );

int main()
{
	// create a string containing "NEW_" followed by "LINE"
	string newLine ="NEW_";
	newLine += "LINE";
	// create a string containing "INSERT_" followed by "TARGET"
	string insertTarget = "INSERT_";
	insertTarget += "TARGET";
	// create a string containing "INSERT_" followed by "SELF"
	string insertSelf = "INSERT_";
	insertSelf += "SELF";

	// create a string to store the code to be printed out
	string full_Self = self;

	// replace all instances of the newLine string with the newLine character
	sweep_Transform( full_Self, newLine, "\n" );

	// inserts the target at the correct position
	sweep_Transform( full_Self, insertTarget, target );

	// create a string to store the self string as it appears in the source file
	string real_Self = self;
	// transform the escaped characters in the string back into the escaped form
	sweep_Transform( real_Self, "\\", "\\\\" );
	sweep_Transform( real_Self, "\"", "\\\"" );

	// inserts the encoded string in the correct position
	sweep_Transform( full_Self, insertSelf, real_Self );

	// replace the target string and count how many times it appeared
	int target_counter = sweep_Transform( full_Self, target, "int x = 666" );

	// overwrite the source code with the modified source code!!
	ofstream output("ACM - Codeception.cpp");

	// if target string appeared an incorrect number of times
	if ( target_counter != 1 )
	{
		// print an error message
		output << "ERROR: requirements not met!"<< endl;
	}
	else // if the target string appeared the correct number of times
	{
		// print the source code (with the modification)
		output << full_Self;
	}

	return 0;
}

// Transforms the string transform_This by replacing every instance of replace_This with with_This
int sweep_Transform( string &transform_This, const string &replace_This, const string &with_This )
{
	// initialize the number of instances replaced to 0
	int count = 0;
	// loop for each instance of replace_This in transform_This, advance to the next instance starting after this one each time, and increment count
	for ( size_t found = transform_This.find( replace_This ); found != string::npos; found = transform_This.find( replace_This, found+with_This.length() ), count++ )
	{
		// replace replace_This with with_This
		transform_This.replace( found, replace_This.length(), with_This );
	}
	// return the number of instances replaced
	return count;
}