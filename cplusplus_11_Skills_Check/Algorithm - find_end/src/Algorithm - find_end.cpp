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
	vector<int> v1 = {1,2,1,2,1,2};
	vector<int> v2 = {1,2};

	cout << "Algorithm - find_all" << endl;

	cout << "Original v1: ";
	for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Original v2: ";
	for(auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "result=find_end(v1.begin(),v1.end(),v2.begin(),v2.end());" << endl;

	auto result = find_end(v1.begin(),v1.end(),v2.begin(),v2.end());

	if ( result != v1.end() )
		cout << "Last sequence found at location: "
		     << distance(v1.begin(),result)
			 << endl;

	v2 = {1,3};
	cout << "Modified v2: ";
	for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	result = find_end(v1.begin(),v1.end(),v2.begin(),v2.end());

	if ( result == v1.end() ) cout << "Sequence not present in vector!" << endl;

	return 0;
}
