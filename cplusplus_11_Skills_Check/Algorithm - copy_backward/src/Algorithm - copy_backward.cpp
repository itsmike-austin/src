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
	vector<int> v1 = {1,2,3,4,5};
	vector<int> v2(5);

	cout << "Algorithm - copy_backward" << endl;

	cout << "Original v1: ";
	for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Original v2: ";
	for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "copy_backward(v1.begin(),v1.end(),v2.end());" << endl;

	copy_backward(v1.begin(),v1.end(),v2.end());

	cout << "Final v1: ";
	for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Final v2: ";
	for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
