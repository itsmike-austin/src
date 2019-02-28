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
	unordered_set<string> us;

	cout << "unordered_set - reserve : set the bucket_count n or more elements, the most appropriate" << endl;

	cout << "us.reserve(5);" << endl;

	us.reserve(5);

	us.insert("android");
	us.insert("java");
	us.insert("html");
	us.insert("css");
	us.insert("wordpress");

	cout << "us.bucket_count: " << us.bucket_count() << endl;

	cout << "us contains: ";
	for( auto it=us.begin() ; it != us.end() ; ++it ) cout << *it << " ";
	cout << endl << endl;

	return 0;
}
