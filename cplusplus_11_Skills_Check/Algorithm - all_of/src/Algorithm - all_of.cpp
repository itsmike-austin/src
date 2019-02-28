//============================================================================
// Name        : Algorithm.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>

using namespace std;

bool is_even(int n)
{
	return ( n % 2 == 0 );
}

int main() {
	vector<int> v = {2,4,6,8,10};
	bool result;

	cout << "algorithm - all_of" << endl;

	cout << "Original vector: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "executing result=all_of(v.begin(),v.end(),is_even -- a function);" << endl;

	result = all_of(v.begin(),v.end(),is_even);

	if ( result == true ) {
		cout << "Vector contains all even numbers." << endl;
	}

	cout << "setting v[0] = 1; and re-checking for even numbers." << endl;

	v[0] = 1;

	result = all_of(v.begin(),v.end(),is_even);

	if ( result == false ) {
		cout << "Vector doesn't contain all even numbers." << endl;
	}

	cout << "Final vector: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
