//============================================================================
// Name        : ForwardList.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <forward_list>

using namespace std;

int main()
{
	forward_list<int> fl = {1,2,3,4,5};

	cout << "fl.reverse()" << endl;
	cout << "Original list: ";
	for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
	cout << endl;

	fl.reverse();

	cout << "Final list: ";
	for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
