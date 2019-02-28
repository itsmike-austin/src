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
	int val = 5;
	vector<int> v = {1,2,3,4,5};

	cout << "Algorithm - find" << endl;

	cout << "Original v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "find(v.begin(),v.end(),val); where val = 5" << endl;

	auto result = find(v.begin(),v.end(),val);

	if ( result != end(v) ) cout << "Vector contains element " << val << endl;

	cout << "val = 15;" << endl;

	val = 15;

	result = find(v.begin(),v.end(),val);

	if ( result == end(v) ) cout << "Vector does not contain element " << val << endl;

	return 0;
}
