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
	unordered_set<string> us; // = {"a","b","c","d","e"};

	cout << "unordered_set - max_bucket_count";

	cout << "us.size(): " << us.size() << endl;
	cout << "us.max_bucket_count(): " << us.max_bucket_count() << endl;

	return 0;
}
