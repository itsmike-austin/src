//============================================================================
// Name        : Iterator.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iterator>
#include <algorithm>
#include <list>

using namespace std;

int main() {
	list<int> alst;

	cout << "Iterator - prev - next" << endl;

	cout << "for(i=0;i<10;++i)list.push_back(i*1);" << endl;

	for( int i=0 ; i < 10 ; ++i ) alst.push_back(i*1);

	cout << "last element of list using prev(list.begin()) is " << *prev(alst.begin()) << endl;

	cout << "List using next: ";
	for_each(alst.begin(),next(alst.begin(),4),[](int x) {cout << x << " ";});

	cout << endl;

	return 0;
}
