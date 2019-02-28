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

	cout << "Unordered_Map - find." << endl;

	cout << "auto it = um.find('d');" << endl;

	auto it = um.find('d');

	cout << "Iterator points to "
			<< it->first
			<< " = "
			<< it->second
			<< endl << endl;

	return 0;
}
