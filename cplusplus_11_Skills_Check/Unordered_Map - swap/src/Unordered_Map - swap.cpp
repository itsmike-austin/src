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
	unordered_map<char,int> um1 = {
			{'a',1},
			{'b',2},
			{'c',3},
			{'d',4},
			{'e',5},
	};

	unordered_map<char,int> um2;

	cout << "Original um1: ";
	for( auto it=um1.begin() ; it != um1.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl;

	cout << "um1.swap(um2);" << endl;

	um1.swap(um2);

	cout << "Final um1: ";
	for( auto it=um1.begin() ; it != um1.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl;

	cout << "Final um2: ";
	for( auto it=um2.begin() ; it != um2.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl << endl;

	return 0;
}
