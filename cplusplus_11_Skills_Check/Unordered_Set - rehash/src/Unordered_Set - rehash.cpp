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

	cout << "unordered_set - rehash: set the number of buckets in a container" << endl;

	cout << "us.rehash(12);" << endl;

	us.rehash(12);

	us.insert("android");
	us.insert("java");
	us.insert("html");
	us.insert("css");
	us.insert("javascript");

	cout << "current bucket_count: " << us.bucket_count() << endl;

	return 0;
}
