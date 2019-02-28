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

bool cmp_fcn(int a,int b)
{
	return (a > b);
}

int main()
{
	forward_list<int> fl = {1,4,2,5,3};

	cout << "fl.sort();" << endl;

	cout << "Original list: ";
	for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
	cout << endl;

	fl.sort();

	cout << "Final list: ";
	for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
	cout << endl << endl;

	cout << "fl.sort(cmp_fcn): sort with external compare function." << endl;

	fl.clear();
	fl = {1,4,2,5,3};

	cout << "Original list: ";
	for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
	cout << endl;

	fl.sort(cmp_fcn);

	cout << "Sorted list: ";
	for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
	cout << endl << endl;

	return 0;
}
