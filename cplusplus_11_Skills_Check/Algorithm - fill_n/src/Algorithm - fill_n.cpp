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
	vector<int> v(5,1);

	cout << "Original v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "fill_n(v.begin()+2,3,4);" << endl;

	fill_n(v.begin()+2,3,4);

	cout << "Final v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
