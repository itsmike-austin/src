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

	cout << "unordered_set - bucket_count" << endl;

	unsigned n = us.bucket_count();

	cout << "Original content: ";
	for( auto it=us.begin() ; it != us.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "us.bucket_count(): " << us.bucket_count() << endl;

	for( unsigned i=0 ; i < n ; ++i ) {
		cout << "bucket #: " << i << " contains: ";
		for( auto it=us.begin(i) ; it != us.end(i) ; ++it ) cout << *it << " ";
		cout << endl;
	}
	cout << endl;

	return 0;
}
