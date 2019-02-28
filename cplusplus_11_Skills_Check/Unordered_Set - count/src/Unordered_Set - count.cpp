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
	unordered_set<string> us = {"a","b","c","d"};

	for(auto& x :{"a","b","x","z"} ) {
		if ( us.count(x) > 0 ) {
			cout << "set has: " << x << endl;
		}else{
			cout << "set does not have: " << x << endl;
		}
	}
	return 0;
}
