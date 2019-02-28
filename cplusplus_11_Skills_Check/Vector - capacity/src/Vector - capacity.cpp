//============================================================================
// Name        : Vector.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> v;

	cout << "vector::capacity" << endl;

	cout << "adding vectors using: for(i=0;i<5;++i) v.push_back(i+1);" << endl;

	for( int i=0 ; i < 5 ; ++i ) v.push_back(i+1);

	cout << "Number of elements in vector = " << v.size() << endl;
	cout << "Capacity of vector           = " << v.capacity() << endl << endl;

	return 0;
}
