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
	vector<int> v1 = {1,2,3};
	vector<int> v2 = {1,2,4,4,5};

	cout << "Algorithm - equal" << endl;

	cout << "Original v1: ";
	for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Original v2: ";
	for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "equal(v1.begin(),v1.end(),v2.begin());" << endl;

	bool result = equal(v1.begin(),v1.end(),v2.begin());

	if ( result == false ) cout << "Vector range is not equal." << endl;

	cout << "v2[2] = 3;" << endl;

	v2[2] = 3;

	result = equal(v1.begin(),v1.end(),v2.begin());

	if ( result == true ) cout << "Vector range is equal" << endl;

	return 0;
}
