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
	unordered_map<char,int> um;

	cout << "Count of items in the unordered_map: " << um.size();

	cout << "Adding items using um.emplace('a',1)...('e',5)" << endl;

	um.emplace('a',1);
	um.emplace('b',2);
	um.emplace('c',3);
	um.emplace('d',4);
	um.emplace('e',5);

	cout << "Unordered map contains the following elements" << endl;

	for( auto it=um.begin() ; it != um.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl << endl;

	return 0;
}
