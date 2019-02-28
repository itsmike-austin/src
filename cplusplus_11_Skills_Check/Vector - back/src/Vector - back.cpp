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
	auto il = {1,2,3,4,5};
	vector<int> v(il);

	cout << "vector::back" << endl;

	cout << "original list: ";
	for( auto it=il.begin() ; it != il.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "vector<int> v(il);" << endl;

	cout << "vector contents: ";
	for( unsigned i=0 ; i < v.size() ; ++i ) cout << v[i] << " ";
	cout << endl;

	cout << "Last element of contents via v.back(): " << v.back() << endl << endl;

	return 0;
}
