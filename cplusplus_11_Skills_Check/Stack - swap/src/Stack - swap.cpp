//============================================================================
// Name        : Stack.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>

using namespace std;

int main() {
	stack<int> s1;
	stack<int> s2;

	cout << "Stack swap"
			<< endl
			<< "for(i=0;i<5;++i)s1.push(i+1);"
			<< endl
			<< "for(i=0;i<3;++i)s2.push(100+i);"
			<< endl;

	for( int i=0 ; i < 5 ; ++i ) s1.push(i+1);
	for( int i=0 ; i < 3 ; ++i ) s2.push(100+i);

	cout << "s1.swap(s2);" << endl;

	s1.swap(s2);

	cout << "Final s1 contents: ";
	while( !s1.empty() ) {
		cout << s1.top() << " ";
		s1.pop();
	}
	cout << endl;

	cout << "Final s2 contents: ";
	while( !s2.empty() ) {
		cout << s2.top() << " ";
		s2.pop();
	}
	cout << endl << endl;

	return 0;
}
