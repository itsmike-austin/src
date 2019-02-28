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

	cout << "Initial size of unordered_map = " << um.size() << endl;

	um = {
			{'a',1},
			{'b',2},
			{'c',3},
			{'d',4},
			{'e',5}
	};

	cout << "Final size after adding 5 to map = " << um.size() << endl;

	return 0;
}
