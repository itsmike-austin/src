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

	cout << "Unordered_Map bucket_count -- 5 items in map." << endl;

	unordered_map<char,int> um = {
			{'a',1},
			{'b',2},
			{'c',3},
			{'d',4},
			{'e',5},
	};


	cout << "Number of buckets = " << um.bucket_count() << endl;

	return 0;
}
