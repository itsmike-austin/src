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

	cout << "Unordered_Map - bucket_size" << endl;

	cout << "There are 5 elements in the map." << endl;

	for( unsigned int i=0 ; i < um.bucket_count() ; ++i ) {
		cout << "Bucket "
				<< i
				<< " contains "
				<< um.bucket_size(i)
				<< " elements."
				<< endl;
	}

	return 0;
}
