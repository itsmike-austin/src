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

bool predicate(int n)
{
	return (n%2 != 0);
}

int main() {
	vector<int> v1 = {1,2,3,4,5};
	vector<int> v2(3);

	cout << "Algorithm - copy_if" << endl;

	cout << "Original v1: ";
	for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Original v2: ";
	for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "copy_if(v1.begin(),v1.end(),v2.begin(),predicate); where predicate = n%2 != 0" << endl;

	copy_if(v1.begin(),v1.end(),v2.begin(),predicate);

	cout << "Odd numbers in vector: ";
	for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
