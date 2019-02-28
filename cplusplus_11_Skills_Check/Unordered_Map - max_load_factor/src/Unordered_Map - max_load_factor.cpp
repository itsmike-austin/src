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

	cout << "max_load_factor of unordered_map (get version) = " << um.max_load_factor() << endl;

	cout << "um.max_load_factor(2);" << endl;

	um.max_load_factor(2);

	cout << "max_load_factor after set = " << um.max_load_factor() << endl;

	return 0;
}
