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
	unordered_set<string> us = {"a","b","c","d","e"};

	cout << "unordered_set - clear" << endl;

	cout << "Original size: " << us.size() << endl;

	cout << "Original contents: ";
	for( const string& x : us ) {
		cout << x << " ";
	}
	cout << endl;

	cout << "us.clear();" << endl;
	us.clear();

	cout << "us.size(): " << us.size() << endl << endl;

	return 0;
}
