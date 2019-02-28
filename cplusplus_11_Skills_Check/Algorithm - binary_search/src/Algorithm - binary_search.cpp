//============================================================================
// Name        : Algorithm.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<int> v = {1,2,3,4,5};

	cout << "Algorithm - binary_search" << endl;

	cout << "Original vector: ";
	for( auto it = v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "binary_search(v.begin(),v.end(),3);" << endl;

	bool result = binary_search(v.begin(),v.end(),3);

	if ( result == true ) cout << "Element 3 exists in vector." << endl;

	cout << "v[2] = 10;" << endl;

	v[2] = 10;

	cout << "executing binary search." << endl;

	result = binary_search(v.begin(),v.end(),3);

	if ( result == false ) cout << "Element 3 does not exist." << endl;

	return 0;
}
