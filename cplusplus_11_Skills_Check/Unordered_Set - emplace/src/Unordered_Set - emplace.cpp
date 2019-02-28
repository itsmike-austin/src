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

	cout << "unordered_set - emplace" << endl;

	cout << "unordered_set size(): " << us.size() << endl;

	cout << "us.emplace(\"a\");" << endl
			<< "us.emplace(\"b\");" << endl
			<< "us.emplace(\"c\");" << endl;

	us.emplace("a");
	us.emplace("b");
	us.emplace("c");

	cout << "unordered_set size(): " << us.size() << endl;

	cout << "Final contents: ";
	for( const string& x : us ) {
		cout << x << " ";
	}
	cout << endl << endl;

	return 0;
}
