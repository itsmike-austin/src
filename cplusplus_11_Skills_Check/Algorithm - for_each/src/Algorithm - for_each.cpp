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

int print_even(int n)
{
	if ( n%2 == 0 ) cout << n << ' ';
	return 0;
}

int main() {
	vector<int> v = {1,2,3,4,5};

	cout << "Algorithm - for_each" << endl;

	cout << "Sequence: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "for_each(v.begin(),v.end(),print_even); where print_even = (n%2 == 0)" << endl;

	cout << "Vector contains the following even numbers: ";
	for_each(v.begin(),v.end(),print_even);
	cout << endl;

	return 0;
}
