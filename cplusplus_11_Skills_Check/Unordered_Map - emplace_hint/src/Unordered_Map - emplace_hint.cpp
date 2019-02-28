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
			{'b',2},
			{'c',3},
			{'d',4},
	};

	cout << "Unordered_Map - emplace_hint" << endl;

	cout << "um.emplace_hint(um.end(),'e',5);" << endl;

	um.emplace_hint(um.end(),'e',5);
	um.emplace_hint(um.begin(),'a',1);

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
