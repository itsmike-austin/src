//============================================================================
// Name        : Unordered_Set.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
	unordered_set<string> us = {"a","b","d","c"};

	string input;

	getline(cin,input);

	unordered_set<string>::const_iterator got = us.find(input);

	if ( got == us.end() ) {
		cout << input
				<< " was not found";
	}else{
		cout << *got
				<< " is in the unordered_set";
	}

	cout << endl << endl;

	return 0;
}
