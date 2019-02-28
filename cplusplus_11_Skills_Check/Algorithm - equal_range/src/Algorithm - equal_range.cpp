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
	vector<int> v = {1,2,2,2,2};
	int cnt = 0;

	cout << "Algorithm - equal_range" << endl;

	cout << "Original v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "range=equal_range(v.begin(),v.end(),2);" << endl;
	cout << "for(it=range.first;it=range.second;++it) ++cnt;" << endl;

	auto range = equal_range(v.begin(),v.end(),2);

	for( auto it=range.first ; it != range.second ; ++it ) ++cnt;

	cout << "Element 2 occurs " << cnt << " times." << endl;

	return 0;
}
