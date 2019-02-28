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
	unordered_set<string> us1 = {"a","b","c","d","e"};
	unordered_set<string> us2 = {"r","s","t","u","v"};

	cout << "unordered_set - swap" << endl;

	cout << "Original set1: ";
	for( const string& x : us1 ) {
		cout << x << " ";
	}
	cout << endl;

	cout << "Original set2: ";
	for( const string& x : us2 ) {
		cout << x << " ";
	}
	cout << endl;

	cout << "us1.swap(us2);" << endl;
	us1.swap(us2);

	cout << "Final set1: ";
	for( const string&  x : us1 ) {
		cout << x << " ";
	}
	cout << endl;

	cout << "Final set2: ";
	for( const string& x : us2 ) {
		cout << x << " ";
	}
	cout << endl;

	return 0;
}
