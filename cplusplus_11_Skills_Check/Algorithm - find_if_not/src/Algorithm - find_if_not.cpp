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

bool unary_pred(int n)
{
	return ((n%2) == 0);
}

int main() {
	vector<int> v = {2,4,61,8,10};

	cout << "Algorithm - find_if_not" << endl;

	cout << "Original v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "it=find_if_not(v.begin(),v.end(),unary_pred); where unary_pred=((n%2)==0)" << endl;

	auto it = find_if_not(v.begin(),v.end(),unary_pred);

	if ( it != end(v) ) cout << "First odd number is " << *it << endl;

	v = {2,4,6,8,10};

	cout << "New v: ";
	for( auto ax=v.begin() ; ax != v.end() ; ++ax ) cout << *ax << " ";
	cout << endl;

	cout << "it=find_if_not(v.begin(),v.end,unary_pred);" << endl;

	it = find_if_not(v.begin(),v.end(),unary_pred);

	if ( it == v.end() ) cout << "Only even elements in vector!" << endl;

	return 0;
}
