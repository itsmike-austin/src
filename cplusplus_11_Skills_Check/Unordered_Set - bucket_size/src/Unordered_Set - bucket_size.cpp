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

	cout << "unordered_set - bucket_size(n)" << endl;

	cout << "Contents: " << endl;
	for( auto it=us.begin() ; it != us.end() ; ++it ) cout << *it << " ";
	cout <<  endl;

	cout << "us.bucket_count(): " << us.bucket_count() << endl;

	for( unsigned i=0 ; i < us.bucket_count() ; ++i )
		cout << "bucket # " << i << " has " << us.bucket_size(i) << " elements." << endl;

	cout << endl;

	return 0;
}
