//============================================================================
// Name        : Unordered_Map.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
	unordered_map<char,int> um = {
			{'a',1},
			{'b',2},
			{'c',3},
			{'d',4},
			{'e',5},
	};

	cout << "Unordered_Ma[ - equal_range" << endl;

	cout << "um.equal_range('b'); where map = {a..e,1..5}" << endl;

	auto ret = um.equal_range('b');

	cout << "Lower bound is "
			<< ret.first->first
			<< " = "
			<< ret.first->second << endl;

	cout << "Upper bound is "
			<< ret.second->first
			<< " = "
			<< ret.second->second
			<< endl << endl;
	return 0;
}
