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
	stack<int> s;

	cout << "Initial size of stack = "
			<< s.size()
			<< endl
			<< "for(i=0;i<5;++i)s.push(i+1);"
			<< endl;

	for( int i=0 ; i < 5 ; ++i ) s.push(i+1);

	cout << "Stack size after push operation = " << s.size() << endl << endl;

	return 0;
}
