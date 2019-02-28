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

	cout << "Initial size of unordered map = " << um.size() << endl;

	cout << "um.clear();" << endl;

	um.clear();

	cout << "Size of unordered map after clear = " << um.size() << endl << endl;

	return 0;
}
