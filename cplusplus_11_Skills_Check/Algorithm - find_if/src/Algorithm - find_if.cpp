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

bool unary_pre(int n)
{
	return ((n%2) == 0);
}

int main() {
	vector<int> v = {10,2,3,4,5};

	cout << "Algorithm - find_if" << endl;

	cout << "Vector v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "find_if(v.begin(),v.end(),unary_pre); where unary_pre=((n%2)==0)" << endl;

	auto it = find_if(v.begin(),v.end(),unary_pre);

	if ( it != end(v) ) cout << "First even number is " << *it << endl;

	cout << "v = {1};" << endl;

	v = {1};

	cout << "find_if(v.begin(),v.end(),unary_pre);" << endl;
	it = find_if(v.begin(),v.end(),unary_pre);

	if ( it == end(v) ) cout << "Only odd elements present in this sequence." << endl;

	return 0;
}
