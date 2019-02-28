//============================================================================
// Name        : Unordered_Set.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
	unordered_set<string> first = {"howdy ma","howdy pa","howdy yall"};
	unordered_set<string> second;

	cout << "unordered_set<string> first contents: ";
	for( unordered_set<string>::iterator it = first.begin() ; it != first.end() ; ++it ) {
		cout << *it << " ";
	}
	cout << endl;

	cout << "unordered_set<string> second contents: ";
	for( unordered_set<string>::iterator it = second.begin() ; it != second.end() ; ++it ) {
		cout << *it << " ";
	}
	cout << endl << endl;

	cout << "first "  << (first.empty() ? "is empty" : "is not empty") << endl;
	cout << "second " << (second.empty() ? "is empty" : "is not empty") << endl;

	return 0;
}
