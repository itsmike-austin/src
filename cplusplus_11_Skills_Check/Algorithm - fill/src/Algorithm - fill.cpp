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
	vector<int> v(5);

	cout << "Algorithm - fill" << endl;

	cout << "fill(v.begin(),v.end(),1);" << endl;

	fill(v.begin(),v.end(),1);

	cout << "Final v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
