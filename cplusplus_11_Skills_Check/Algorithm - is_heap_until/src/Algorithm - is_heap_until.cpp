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
	vector<int> v = {4,3,5,1,2};

	cout << "Algorithm - is_heap_until" << endl;

	cout << "Original v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "result=is_heap_until(v.begin(),v.end());" << endl;

	auto result = is_heap_until(v.begin(),v.end());

	cout << *result << " is the first element which violates the max heap." << endl;

	v = {5,4,3,2,1};

	cout << "New v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	result = is_heap_until(v.begin(),v.end());

	cout << "Entire range is a valid heap = " << (result == end(v) ? "true" : "false") << endl;

	return 0;
}
