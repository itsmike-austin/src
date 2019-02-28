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
	vector<int> v = {3,5,2,1,4};
	bool result;

	cout << "Algorithm - is_heap" << endl;

	cout << "Original v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "bool result=is_heap(v.begin(),v.end());" << endl;

	result = is_heap(v.begin(),v.end());

	cout << "Given sequence is a max heap = " << (result == true ? "true" : "false") << endl;

	v = {5,4,3,2,1};

	cout << "New v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	result = is_heap(v.begin(),v.end());

	cout << "Given sequence is a max heap = " << (result == true ? "true" : "false") << endl;

	return 0;
}
