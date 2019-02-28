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

	cout << "unordered_set - bucket(x)" << endl;

	for( const string& x : us ) {
		cout << x << " is in bucket # " << us.bucket(x) << endl;
	}
	return 0;
}
