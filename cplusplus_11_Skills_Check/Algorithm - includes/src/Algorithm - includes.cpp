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
	vector<int> v2 = {3,4,5};
	bool result;

	cout << "Algorithm - includes" << endl;

	cout << "Vector v1: ";
	for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Vector v2: ";
	for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "includes(v1.begin(),v1.end(),v2.begin(),v2.end());" << endl;

	result = includes(v1.begin(),v1.end(),v2.begin(),v2.end());

	cout << "Vector v2 is a subset of v1 = " << (result == true ? "true" : "false") << endl;

	cout << "v2 = {10};" << endl;

	v2 = {10};

	result = includes(v1.begin(),v1.end(),v2.begin(),v2.end());

	cout << "Vector v2 is a subset of v1 = " << (result == true ? "true" : "false") << endl;

	return 0;
}
