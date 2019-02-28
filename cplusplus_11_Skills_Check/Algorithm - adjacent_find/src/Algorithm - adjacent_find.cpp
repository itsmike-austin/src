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
	vector<int> v = {1,2,3,3,5};
	auto it = adjacent_find(v.begin(),v.end());

	if ( it != v.end() ) {
		cout << "First occurence of consecutive identical element = " << *it << endl;
	}

	cout << "executing v[3] = 4;" << endl;
	v[3] = 4;

	cout << "executing it=adjacent_find(v.begin(),v.end());" << endl;

	it = adjacent_find(v.begin(),v.end());

	if ( it == v.end() ) {
		cout << "There are no consecutive identical items." << endl;
	}

	cout << "Final vector: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl << endl;

	return 0;
}
