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
	vector<int> v = {1,2,3,5,4};

	cout << "Algorithm - is_sorted_until" << endl;

	cout << "Original v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "is_sorted_until(v.begin(),v.end());" << endl;

	auto it = is_sorted_until(v.begin(),v.end());

	cout << "First unsorted element = " << *it << endl;

	cout << "v[3] = 4;" << endl;

	v[3] = 4;

	it = is_sorted_until(v.begin(),v.end());

	cout << "Entire vector is sorted = " << (it == end(v) ? "true" : "false") << endl;

	cout << "Final v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
