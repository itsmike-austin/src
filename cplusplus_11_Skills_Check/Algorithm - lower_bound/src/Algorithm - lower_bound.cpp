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
	vector<int> v = {1,2,5,13,14};

	cout << "Algorithm - lower_bound" << endl;

	cout << "Original v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "lower_bound(v.begin(),v.end(),2};" << endl;

	auto it = lower_bound(v.begin(),v.end(),2);

	cout << "First element greater than 2 is: " << *it << endl;

	cout << "lower_bound(v.begin(),v.end(),30);" << endl;

	it = lower_bound(v.begin(),v.end(),30);

	cout << "All elements are less than 30 is " << (it == end(v) ? "true" : "false") << endl;

	return 0;
}
