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

	cout << "vector::begin - end" << endl;

	cout << "using begin and end to get list: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl << endl;

	cout << "vector::cbegin- cend" << endl;

	cout << "using constant begin and end to get list: ";
	for( auto it=v.cbegin() ; it != v.cend() ; ++it ) cout << *it << " ";
	cout << endl << endl;

	return 0;
}
