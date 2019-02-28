//============================================================================
// Name        : Algorithm.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iterator>
#include <list>

using namespace std;

int main() {
	list<int> alst;

	cout << "Iterator - distance" << endl;

	cout << "for(i=0;i<5;++i)list.push_back(i*1);" << endl;

	for( int i=0 ; i < 5 ; ++i ) alst.push_back(i*1);

	list<int>::iterator first = alst.begin();
	list<int>::iterator last  = alst.end();

	cout << "distance between list.begin() and list.end() using distance(l.begin(),l.end() is: " << distance(first,last) << endl;

	return 0;
}
