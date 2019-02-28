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
	vector<int> v = {1,3,3,3,3};

	cout << "Algorithm - count" << endl;

	cout << "Original v: ";
	for(auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "count(v.begin(),v.end(),3);" << endl;

	cout << "Number of 3s are: " << count(v.begin(),v.end(),3);

	return 0;
}
