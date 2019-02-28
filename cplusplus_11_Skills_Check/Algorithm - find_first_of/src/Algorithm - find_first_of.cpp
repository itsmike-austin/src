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
	vector<int> v1 = {5,2,6,1,3,4,7};
	vector<int> v2 = {10,1};

	cout << "Algorithm - find_first_of" << endl;

	cout << "Original v1: ";
	for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Original v2: ";
	for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "result=find_first_of(v1.begin(),v1.end(),v2.begin(),v2.end());" << endl;

	auto result = find_first_of(v1.begin(),v1.end(),v2.begin(),v2.end());

	if ( result != v1.end() ) cout << "Found first match at location "
			                       << distance(v1.begin(),result)
								   << endl;

	cout << "v2 = {11,13};" << endl;

	v2 = {11,13};

	cout << "find_end(v1.begin(),v1.end(),v2,begin(),v2.end());" << endl;

	result = find_end(v1.begin(),v1.end(),v2.begin(),v2.end());

	if ( result == v1.end() ) cout << "Sequence not found!" << endl;

	return 0;
}
