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
	vector<int> v = {1,2,3,4,5};
	int *p;

	cout << "vector::data" << endl;

	cout << "extracting using p = v.data();" << endl;

	p = v.data();

	cout << "output int* p" << endl;
	for( unsigned i=0 ; i < v.size() ; ++i ) cout << *p++ << " ";
	cout << endl << endl;

	return 0;
}
