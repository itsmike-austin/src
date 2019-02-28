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

bool is_even(int n)
{
	return ( (n%2) == 0 );
}

int main() {
	vector<int> v = {1,2,3,4,5};
	bool result;

	cout << "Algorithm - is_partitioned" << endl;

	cout << "Original v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "result=is_partitioned(v.begin(),v.end(),is_even); where is_even = ((n%2)==0)" << endl;

	result = is_partitioned(v.begin(),v.end(),is_even);

	cout << "Vector is partitioned = " << (result == true ? "true" : "false") << endl;

	cout << "partition(v.begin(),v.end(),is_even);" << endl;

	partition(v.begin(),v.end(),is_even);

	result = is_partitioned(v.begin(),v.end(),is_even);

	cout << "Vector is partitioned = " << (result == true ? "true" : "false") << endl;

	cout << "Final v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
