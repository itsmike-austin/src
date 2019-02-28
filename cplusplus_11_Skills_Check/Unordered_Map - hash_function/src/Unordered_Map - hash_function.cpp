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
	unordered_map<string,string> um;

	cout << "Unordered_Map::hash_function()" << endl;

	cout << "auto fun = um.hash_function();" << endl;

	auto fun = um.hash_function();

	cout << "Hash function for a = " << fun("a") << endl;
	cout << "Hash function for A = " << fun("A") << endl << endl;

	return 0;
}
