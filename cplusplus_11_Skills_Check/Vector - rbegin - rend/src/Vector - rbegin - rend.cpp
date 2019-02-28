//============================================================================
// Name        : Vector.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

using namespace std;

int main() {
	cout << "vector::rbegin - rend" << endl;

	vector<int> v = {1,2,3,4,5};

	cout << "executing: for(it=v.rbegin();it!=v.rend();++it)cout << *it << endl;" << endl;

	cout << "Vector using rbegin-end: ";
	for( auto it=v.rbegin() ; it != v.rend() ; ++it ) cout << *it << " ";
	cout << endl << endl;

	return 0;
}
