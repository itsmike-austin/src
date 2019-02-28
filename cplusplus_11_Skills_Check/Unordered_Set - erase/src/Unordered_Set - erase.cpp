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
	unordered_set<string> us = {"howdy","ma","and","pa"};

	cout << "unordered_set - erase" << endl;

	cout << "Original set: ";
	for( const string& x : us ) {
		cout << x << " ";
	}
	cout << endl;

	cout << "us.erase(\"howdy\");" << endl;
	us.erase("howdy");

	cout << "Modified set: ";
	for( const string& x : us ) {
		cout << x << " ";
	}
	cout << endl;

	cout << "us.erase(\"and\");" << endl;
	us.erase("and");
	cout << "Final set: ";
	for( const string& x : us ) {
		cout << x << " ";
	}
	cout << endl;

	return 0;
}
