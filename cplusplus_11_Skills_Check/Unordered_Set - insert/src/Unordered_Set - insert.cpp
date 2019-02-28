//============================================================================
// Name        : Unordered_Set.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <array>
#include <unordered_set>

using namespace std;

int main() {
	unordered_set<string> us = {"a","b","c","d"};
	array<string,2> larr = {"y","z"};
	string lString = "aString";

	cout << "Unordered_Set - insert" << endl;
	cout << "us.size(): " << us.size() << endl;
	cout << "Original content: ";
	for( const string& x : us ) {
		cout << x << " ";
	}
	cout << endl;

	cout << "us.insert(array of 2)" << endl;
	us.insert(larr.begin(),larr.end());
	cout << "us.size(): " << us.size() << endl;
	cout << "us.insert(lString);" << endl;
	us.insert(lString);
	cout << "us.size(): " << us.size() << endl;
	cout << "us.insert({\"howdy\",\"ma\"});" << endl;
	us.insert({"howdy","ma"});

	cout << "Final contents: ";
	for( const string& x : us ) {
		cout << x << " ";
	}
	cout << endl << endl;

	return 0;
}
