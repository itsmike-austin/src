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

bool is_odd(int n)
{
	return (n%2 != 0);
}

int main() {
	vector<int> v = {2,4,6,8,11};

	cout << "Algorithm - any_of" << endl;

	cout << "Original vector: ";
	for( auto it = v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "result = any_of(v.begin(),v.end(),is_odd);" << endl;

	bool result = any_of(v.begin(),v.end(),is_odd);

	if ( result == true  ) {
		cout << "Vector contains at least one odd number" << endl;
	}

	cout << "Changing the v[4] from 11 to 10" << endl;

	v[4] = 10;

	cout << "checking for odd numbers." << endl;

	result = any_of(v.begin(),v.end(),is_odd);

	if ( result == false ) {
		cout << "Vector contains all even numbers." << endl;
	}

	return 0;
}
