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
	return (n > 3);
}

int main() {
	vector<int> v = {1,2,3,4,5};

	cout << "Algorithm - count_if" << endl;

	cout << "Original v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "count_if(v1.begin(),v1.end(),predicate); where predicate = n > 3" << endl;

	cout << "Number of elements greater than 3 are: " << count_if(v.begin(),v.end(),predicate) << endl;

	return 0;
}
