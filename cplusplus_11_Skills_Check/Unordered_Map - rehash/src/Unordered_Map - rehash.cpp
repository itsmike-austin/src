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

	unordered_map<char,int> mymap;

	cout << "Initial bucket count: " << mymap.bucket_count() << endl;

	cout << "mymap.rehash(20);" << endl;

	mymap.rehash(20);

	cout << "Current bucket_count: " << mymap.bucket_count() << endl;

	return 0;
}
