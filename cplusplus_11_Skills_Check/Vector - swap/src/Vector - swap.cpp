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
	vector<int> v2 = {1,2,3,4,5};

	cout << "vector::swap" << endl;

	cout << "Original v1 size: " << v1.size() << endl;

	cout << "Original v2: ";
	for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "v1.swap(v2);" << endl;

	v1.swap(v2);

	cout << "Final v1: ";
	for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Final v2.size(): " << v2.size() << endl << endl;

	return 0;
}
