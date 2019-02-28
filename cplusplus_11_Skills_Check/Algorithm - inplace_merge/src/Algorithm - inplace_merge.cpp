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
	vector<int> v = {1,3,2,4,5};

	cout << "Algorithm - inplace_merge" << endl;

	cout << "Vector v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "inplace_merge(v.begin(),v.begin()+2,v.end());" << endl;

	inplace_merge(v.begin(),v.begin()+2,v.end());

	cout << "Final v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
