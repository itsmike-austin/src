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
	vector<int> v2 = {10,20,30,40,50};

	cout << "Algorithm - iter_swap" << endl;

	cout << "Original v1: ";
	for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Original v2: ";
	for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "iter_swap(v1.begin(),v2.begin());" << endl;
	cout << "iter_swap(v1.begin()+1,v2.begin()+2);" << endl;

	iter_swap(v1.begin(),v2.begin());
	iter_swap(v1.begin()+1,v2.begin()+2);

	cout << "Final v1: ";
	for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Final v2: ";
	for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
