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
#include <string>

using namespace std;

int main() {
	vector<string> v1 = {"One","Two","Three"};
	vector<string> v2 = {"One","Two","Three"};

	cout << "v1: ";
	for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "v2: ";
	for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "lexicographical_compare(v1.begin(),v1.end(),v2.begin(),v2.end());" << endl;

	bool result = lexicographical_compare(v1.begin(),v1.end(),v2.begin(),v2.end());

	cout << "v1 is " << (result == true ? "less than" : "greater than") << " v2." << endl;

	cout << "v1[0] = \"two\";" << endl;

	v1[0] = "two";

	result = lexicographical_compare(v1.begin(),v1.end(),v2.begin(),v2.end());

	cout << "v1 is " << (result == false ? "less than" : "more than") << " v2." << endl;

	return 0;
}
