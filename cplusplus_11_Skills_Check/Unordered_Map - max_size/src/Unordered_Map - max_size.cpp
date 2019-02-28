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

	cout << "max_size of unordered_map = " << um.max_size() << endl;

	return 0;
}
