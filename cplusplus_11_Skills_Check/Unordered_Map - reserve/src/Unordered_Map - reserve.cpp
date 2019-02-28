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

	cout << "um.reserve(5);" << endl;

	um.reserve(5);

	cout << "Bucket count after reserve = " << um.bucket_count() << endl;

	return 0;
}
