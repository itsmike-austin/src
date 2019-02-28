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
	vector<int> v1;
	vector<int> v2;
	unsigned size;

	cout << "vector::reserve" << endl;

	cout << "calculating capacity using v1.capacty(): " << v1.capacity() << endl;

	size = v1.capacity();

	for( int i=0 ; i < 25 ; ++i ) {
		v1.push_back(i);
		if ( size != v1.capacity() ) {
			size = v1.capacity();
			cout << "Expanding vector v1 to hold " << size << " elements" << endl;
		}
	}

	cout << endl << endl;

	for( int i=0 ; i < 25 ; ++i ) {
		v2.push_back(i);
		if ( size != v2.capacity() ) {
			size = v2.capacity();
			cout << "Expanding vector v2 to hold " << size << " elements" << endl;
		}
	}

	return 0;
}
