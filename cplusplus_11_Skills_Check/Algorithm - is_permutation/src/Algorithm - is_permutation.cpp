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
	vector<int> v1 = {1,2,3,4,5};
	vector<int> v2 = {5,4,3,2,1};
	bool result;

	cout << "Algorithm - is_permutation" << endl;

	cout << "Original v1: ";
	for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Original v2: ";
	for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "is_permutation(v1.begin(),v1.end(),v2.begin());" << endl;

	result = is_permutation(v1.begin(),v1.end(),v2.begin());

	cout << "v2 is permutation of v1 = " << (result == true ? "true" : "false") << endl;

	cout << "v2[0] = 10;" << endl;

	v2[0] = 10;

	result = is_permutation(v1.begin(),v1.end(),v2.begin());

	cout << "v2 is permutation of v1 = " << (result == true ? "true" : "false") << endl;

	cout << "Final v2: ";
	for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
