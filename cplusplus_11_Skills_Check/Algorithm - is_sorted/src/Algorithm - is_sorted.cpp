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
	bool result;

	cout << "Algorithm - is_sorted" << endl;

	cout << "Original v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "is_sorted(v.begin(),v.end());" << endl;

	result = is_sorted(v.begin(),v.end());

	cout << "Vector is sorted = " << (result == true ? "true" : "false") << endl;

	cout << "v[0] = 10;" << endl;

	v[0] = 10;

	result = is_sorted(v.begin(),v.end());

	cout << "Vector is sorted = " << (result == true ? "true" : "false") << endl;

	cout << "Final v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
