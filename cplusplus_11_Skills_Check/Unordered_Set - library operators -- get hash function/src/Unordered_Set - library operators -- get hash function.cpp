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
	unordered_set<string>
	a = {"goole","yahoo","verizon"},
	b = {"goole","verizon","yahoo"},
	c = {"verizon","goole","yahoo","oracle"};

	cout << "unordered_set - operators" << endl;

	cout << "set a: ";
	for( auto it=a.begin() ; it != a.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "set b: ";
	for( auto it=b.begin() ; it != b.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "set c: ";
	for( auto it=c.begin() ; it != c.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "a == b: ";
	cout << (a == b ? "a equals b" : "a not equal to b") << endl;
	cout << "b != c: ";
	cout << (b != c ? "b and c are not equal" : "b equals c") << endl;

	return 0;
}
